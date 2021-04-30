module PVCAM

include("libpvcam/PL.jl")

using .PL
export PL

export camera_name, open_camera, setup_cont, start_cont, stop_cont, latest_frame, polled_cont! 
import Base.showerror
#FIXME: global struct
const CAMERA_NUMBER = 0 # default to first camera available
const CAMERA_NAME = Ref{String}()
const CAMERA_HANDLE = Ref{Int16}(-1)
const FRAME_OFFSET = Ref{Int64}(0)
const FULL_FRAME = [PL.rgn_type(0,1199,1,0,1199,1)]
const EXPOSURE_MODE = Ref{Int16}(PL.TIMED_MODE)
const CIRC_BUFFER = Ref{Vector{UInt16}}()
const CB_START = Ref{Ptr{UInt16}}(0)

struct PVCAMError <: Exception
code::Int16
end

function Base.showerror(io::IO, error::PVCAMError)
    message = Vector{UInt8}(undef, PL.ERROR_MSG_LEN)
    PL.error_message(error.code, message)
    message[end] = 0
    print(io, unsafe_string(pointer(message)))
end

check_error() = throw(PVCAMError(PL.error_code()))

function __init__()
    PL.pvcam_init() || check_error()
    CAMERA_NAME[] = camera_name(CAMERA_NUMBER)
    CAMERA_HANDLE[] = open_camera(CAMERA_NAME[])
    atexit(PL.pvcam_uninit)
end

function camera_name(cam_num::Integer)
    name = Vector{UInt8}(undef, PL.CAM_NAME_LEN)
    PL.cam_get_name(cam_num, name) || check_error()
    name[end] = 0
    return unsafe_string(pointer(name))
end

function open_camera(camera_name::String)
    camera_handle = Ref{Int16}()
    open_mode = Int16(PL.OPEN_EXCLUSIVE)
    PL.cam_open(camera_name, camera_handle, open_mode) || check_error()
    return camera_handle[]
end

function setup_cont(camera_handle = CAMERA_HANDLE[], region_array = FULL_FRAME, exp_mode = EXPOSURE_MODE[], exposure_time = 40, muxed = 1)::Int64
    muxed > 1 && (PL.set_param(camera_handle, PL.PARAM_LAST_MUXED_SIGNAL, Ref(muxed)) || check_error())
    PL.set_param(camera_handle, PL.PARAM_CLEAR_MODE, Ref(Int32(PL.CLEAR_NEVER))) || check_error()
    #PL.set_param(camera_handle, PL.PARAM_EXPOSE_OUT_MODE, Ref(Int32(PL.EXPOSE_OUT_ALL_ROWS))) || check_error()
    exp_bytes = Ref{UInt32}()
    num_regions = length(region_array)
    PL.exp_setup_cont(camera_handle, num_regions, region_array, exp_mode, exposure_time, exp_bytes, PL.CIRC_OVERWRITE) || check_error()
    return exp_bytes[]
end


function start_cont(camera_handle, circ_buffer_size = length(CIRC_BUFFER[]) * sizeof(UInt16))
    PL.exp_start_cont(camera_handle, CIRC_BUFFER[], circ_buffer_size) || check_error()
    return @async println("Continuous acquisition started...")
end

function get_latest_frame_ptr(camera_h)
    frame_address = Ref{Ptr{UInt16}}(0)
    PL.exp_get_latest_frame(camera_h, frame_address) || check_error()
    return frame_address[]
end

function stop_cont(camera_h = CAMERA_HANDLE[])
    PL.exp_stop_cont(camera_h, PL.CCS_CLEAR) || check_error()
    return @async println("Stopped continuous acquisition.")
end

function latest_frame(camera_h = CAMERA_HANDLE[], start_ptr = CB_START[])
    current_ptr = get_latest_frame_ptr(camera_h)
    start_idx = (current_ptr - start_ptr) ÷ sizeof(UInt16) + 1
    stop_idx = start_idx + FRAME_OFFSET[]
    return CIRC_BUFFER[][start_idx:stop_idx] #FIXME: find zero-copy solution
end

function polled_cont!(; camera_handle = CAMERA_HANDLE[], regions = FULL_FRAME, exposure_mode = EXPOSURE_MODE[], exposure_time = 40, muxed = 1)
    exposure_bytes = setup_cont(camera_handle, regions, exposure_mode, exposure_time, UInt8(muxed))
    nframes = 20
    CIRC_BUFFER[] = Vector{UInt16}(undef, (nframes * exposure_bytes) ÷ sizeof(UInt16))
    FRAME_OFFSET[] = exposure_bytes ÷ sizeof(UInt16) - 1
    CB_START[] = pointer(CIRC_BUFFER[])
    start_cont(camera_handle)
    return
end

function initialize_cont()
    polled_cont!()
    sleep(0.5) # arbitrary length pause: we need to pause while we wait for acquisition to get rolling
    retry(latest_frame, delays = fill(0.5, 10))() 
end

end # module
