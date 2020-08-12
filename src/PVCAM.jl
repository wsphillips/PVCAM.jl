module PVCAM

include("libpvcam/PL.jl")

using .PL
export PL

export camera_name, open_camera, setup_cont, start_cont, stop_cont, latest_frame, polled_cont! 

const CAMERA_NUMBER = 0
const BUFFER_MODE = Int16(PL.CIRC_OVERWRITE)
const CAMERA_NAME = Ref{String}()
const CAMERA_HANDLE = Ref{Int16}(-1)
const FRAME_OFFSET = Ref{Int64}(0)
ROIS = [PL.rgn_type(0,1199,1,0,1199,1)]
const EXPOSURE_MODE = Ref{Int16}(PL.TIMED_MODE)

atexit() do
    PL.pvcam_uninit()
end

function __init__()
    Bool(PL.pvcam_init()) || @error "Failed to initialized PVCAM"
    CAMERA_NAME[] = camera_name(CAMERA_NUMBER)
    CAMERA_HANDLE[] = open_camera(CAMERA_NAME[])
end

function camera_name(cam_num::Integer)

    name = Vector{UInt8}(undef, PL.CAM_NAME_LEN)

    Bool(PL.cam_get_name(cam_num, name)) || @warn "Unable to retrieve camera name"

    name[end] = 0
    return unsafe_string(pointer(name))
end

function open_camera(camera_name::String)

    camera_handle = Ref{Int16}()
    open_mode = Int16(PL.OPEN_EXCLUSIVE)

    Bool(PL.cam_open(camera_name, camera_handle, open_mode)) || @warn "Unable to open camera"

    return camera_handle[]
end

function setup_cont(camera_handle = CAMERA_HANDLE[], region_array = ROIS, exp_mode = EXPOSURE_MODE[], exposure_time = 40)
    exp_bytes = Ref{UInt32}()
    num_regions = UInt16(length(region_array))
    Bool(PL.exp_setup_cont(camera_handle, num_regions, region_array, exp_mode, UInt32(exposure_time),
                                    exp_bytes, BUFFER_MODE)) || @warn "Unable to setup continuous acquisition"

    return Int(exp_bytes[])
end

function start_cont(camera_handle, circ_buffer_mem, circ_buffer_size = UInt32(length(circ_buffer_mem) * sizeof(UInt16)))

    Bool(PL.exp_start_cont(camera_handle, circ_buffer_mem, UInt32(circ_buffer_size))) || @warn "Unable to start continuous acquisition."

    return println("Continuous acquisition started...")
end

function get_latest_frame_ptr(camera_h)
    frame_address = Ref{Ptr{UInt16}}()
    Bool(PL.exp_get_latest_frame(camera_h, frame_address)) || @warn "Unable to poll for latest frame."
    return frame_address[]
end

function stop_cont(camera_h = CAMERA_HANDLE[])
    cam_state = Int16(PL.CCS_CLEAR)
    if Bool(PL.exp_stop_cont(camera_h, cam_state)) 
        println("Stopped continuous acquisition.")
    else
        @warn "Unable to stop continuous acquisition"
    end
end

function latest_frame(buffer, camera_h = CAMERA_HANDLE[])
    current_ptr = get_latest_frame_ptr(camera_h)
    start_ptr = pointer(buffer)
    start_idx = Int((current_ptr - start_ptr) / sizeof(UInt16)) + 1
    stop_idx = start_idx + FRAME_OFFSET[]
    return start_idx:stop_idx
end

function polled_cont!(; camera_handle = CAMERA_HANDLE[], regions = ROIS, exposure_mode = EXPOSURE_MODE[], exposure_time = 40)
    
    exposure_bytes = setup_cont(camera_handle, regions, exposure_mode, exposure_time)
    circ_buffer_frames = 20
    circ_buffer = Vector{UInt16}(undef, Int((circ_buffer_frames * exposure_bytes) / sizeof(UInt16)))
    FRAME_OFFSET[] = Int(exposure_bytes / sizeof(UInt16)) - 1
    start_cont(camera_handle, circ_buffer)
    return circ_buffer
end

end # module
