
function pvcam_get_ver(pvcam_version::Ref{UInt16})::Bool
    ccall((:pl_pvcam_get_ver, :libpvcam), UInt16, (Ref{UInt16},), pvcam_version)
end

function pvcam_init()::Bool
    ccall((:pl_pvcam_init, :libpvcam), UInt16, ())
end

function pvcam_uninit()::Bool
    ccall((:pl_pvcam_uninit, :libpvcam), UInt16, ())
end

function cam_check(hcam::Integer)::Bool
    ccall((:pl_cam_check, :libpvcam), UInt16, (Int16,), hcam)
end

function cam_close(hcam::Integer)::Bool
    ccall((:pl_cam_close, :libpvcam), UInt16, (Int16,), hcam)
end

function cam_get_name(cam_num::Integer, camera_name::Vector{UInt8})::Bool
    ccall((:pl_cam_get_name, :libpvcam), UInt16, (Int16, Ref{UInt8}), cam_num, camera_name)
end

function cam_get_total(totl_cams::Ref{Int16})::Bool
    ccall((:pl_cam_get_total, :libpvcam), UInt16, (Ref{Int16},), totl_cams)
end

function cam_open(camera_name, hcam::Ref{Int16}, o_mode::Integer)::Bool
    ccall((:pl_cam_open, :libpvcam), UInt16, (Cstring, Ref{Int16}, Int16), camera_name, hcam, o_mode)
end

function cam_register_callback(hcam::Integer, callback_event::Integer, callback::Ref{Cvoid})::Bool
    ccall((:pl_cam_register_callback, :libpvcam), UInt16, (Int16, Cint, Ref{Cvoid}), hcam, callback_event, callback)
end

function cam_register_callback_ex(hcam::Integer, callback_event::Integer, callback::Ref{Cvoid}, context::Ref{Cvoid})::Bool
    ccall((:pl_cam_register_callback_ex, :libpvcam), UInt16, (Int16, Cint, Ref{Cvoid}, Ref{Cvoid}), hcam, callback_event, callback, context)
end

function cam_register_callback_ex2(hcam::Integer, callback_event::Integer, callback::Ref{Cvoid})::Bool
    ccall((:pl_cam_register_callback_ex2, :libpvcam), UInt16, (Int16, Cint, Ref{Cvoid}), hcam, callback_event, callback)
end

function cam_register_callback_ex3(hcam::Integer, callback_event::Integer, callback::Ref{Cvoid}, context::Ref{Cvoid})::Bool
    ccall((:pl_cam_register_callback_ex3, :libpvcam), UInt16, (Int16, Cint, Ref{Cvoid}, Ref{Cvoid}), hcam, callback_event, callback, context)
end

function cam_deregister_callback(hcam::Integer, callback_event::Integer)::Bool
    ccall((:pl_cam_deregister_callback, :libpvcam), UInt16, (Int16, Cint), hcam, callback_event)
end

function error_code()
    ccall((:pl_error_code, :libpvcam), Int16, ())
end

function error_message(err_code::Integer, msg)::Bool
    ccall((:pl_error_message, :libpvcam), UInt16, (Int16, Ref{UInt8}), err_code, msg)
end

function get_param(hcam::Integer, param_id::Integer, param_attribute::Integer, param_value::Ref{Cvoid})::Bool
    ccall((:pl_get_param, :libpvcam), UInt16, (Int16, UInt32, Int16, Ref{Cvoid}), hcam, param_id, param_attribute, param_value)
end

function set_param(hcam::Integer, param_id::Integer, param_value::Ref{Cvoid})::Bool
    ccall((:pl_set_param, :libpvcam), UInt16, (Int16, UInt32, Ref{Cvoid}), hcam, param_id, param_value)
end

function get_enum_param(hcam::Integer, param_id::Integer, index::Integer, value::Ref{Cint}, desc, length::Integer)::Bool
    ccall((:pl_get_enum_param, :libpvcam), UInt16, (Int16, UInt32, UInt32, Ref{Cint}, Cstring, UInt32), hcam, param_id, index, value, desc, length)
end

function enum_str_length(hcam::Integer, param_id::Integer, index::Integer, length::Ref{UInt32})::Bool
    ccall((:pl_enum_str_length, :libpvcam), UInt16, (Int16, UInt32, UInt32, Ref{UInt32}), hcam, param_id, index, length)
end

function pp_reset(hcam::Integer)::Bool
    ccall((:pl_pp_reset, :libpvcam), UInt16, (Int16,), hcam)
end

function create_smart_stream_struct(array::Ref{Ptr{smart_stream_type}}, entries::Integer)::Bool
    ccall((:pl_create_smart_stream_struct, :libpvcam), UInt16, (Ref{Ptr{smart_stream_type}}, UInt16), array, entries)
end

function release_smart_stream_struct(array::Ref{Ptr{smart_stream_type}})::Bool
    ccall((:pl_release_smart_stream_struct, :libpvcam), UInt16, (Ref{Ptr{smart_stream_type}},), array)
end

function create_frame_info_struct(new_frame::Ref{Ptr{FRAME_INFO}})::Bool
    ccall((:pl_create_frame_info_struct, :libpvcam), UInt16, (Ref{Ptr{FRAME_INFO}},), new_frame)
end

function release_frame_info_struct(frame_to_delete::Ref{FRAME_INFO})::Bool
    ccall((:pl_release_frame_info_struct, :libpvcam), UInt16, (Ref{FRAME_INFO},), frame_to_delete)
end

function exp_setup_seq(hcam::Integer, exp_total::Integer, rgn_total::Integer, rgn_array::Ref{rgn_type}, exp_mode::Integer, exposure_time::Integer, exp_bytes::Ref{UInt32})::Bool
    ccall((:pl_exp_setup_seq, :libpvcam), UInt16, (Int16, UInt16, UInt16, Ref{rgn_type}, Int16, UInt32, Ref{UInt32}), hcam, exp_total, rgn_total, rgn_array, exp_mode, exposure_time, exp_bytes)
end

function exp_start_seq(hcam::Integer, pixel_stream::Vector{UInt16})::Bool
    ccall((:pl_exp_start_seq, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, pixel_stream)
end

function exp_setup_cont(hcam::Integer, rgn_total::Integer, rgn_array::Vector{rgn_type}, exp_mode::Integer, exposure_time::Integer, exp_bytes::Ref{UInt32}, buffer_mode::PL_CIRC_MODES)::Bool
    ccall((:pl_exp_setup_cont, :libpvcam), UInt16, (Int16, UInt16, Ref{rgn_type}, Int16, UInt32, Ref{UInt32}, Int16), hcam, rgn_total, rgn_array, exp_mode, exposure_time, exp_bytes, buffer_mode)
end

function exp_start_cont(hcam::Integer, pixel_stream::Vector{UInt16}, size::Integer)::Bool
    ccall((:pl_exp_start_cont, :libpvcam), UInt16, (Int16, Ref{UInt16}, UInt32), hcam, pixel_stream, size)
end

function exp_check_status(hcam::Integer, status::Ref{Int16}, bytes_arrived::Ref{UInt32})::Bool
    ccall((:pl_exp_check_status, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{UInt32}), hcam, status, bytes_arrived)
end

function exp_check_cont_status(hcam::Integer, status::Ref{Int16}, bytes_arrived::Ref{UInt32}, buffer_cnt::Ref{UInt32})::Bool
    ccall((:pl_exp_check_cont_status, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{UInt32}, Ref{UInt32}), hcam, status, bytes_arrived, buffer_cnt)
end

function exp_check_cont_status_ex(hcam::Integer, status::Ref{Int16}, byte_cnt::Ref{UInt32}, buffer_cnt::Ref{UInt32}, frame_info::Ref{FRAME_INFO})::Bool
    ccall((:pl_exp_check_cont_status_ex, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{UInt32}, Ref{UInt32}, Ref{FRAME_INFO}), hcam, status, byte_cnt, buffer_cnt, frame_info)
end

function exp_get_latest_frame(hcam::Integer, frame::Ref{Ptr{UInt16}})::Bool
    ccall((:pl_exp_get_latest_frame, :libpvcam), UInt16, (Int16, Ref{Ptr{UInt16}}), hcam, frame)
end

function exp_get_latest_frame_ex(hcam::Integer, frame::Ref{Ptr{UInt16}}, frame_info::Ref{FRAME_INFO})::Bool
    ccall((:pl_exp_get_latest_frame_ex, :libpvcam), UInt16, (Int16, Ref{Ptr{UInt16}}, Ref{FRAME_INFO}), hcam, frame, frame_info)
end

function exp_get_oldest_frame(hcam::Integer, frame::Ref{Ptr{Cvoid}})::Bool
    ccall((:pl_exp_get_oldest_frame, :libpvcam), UInt16, (Int16, Ref{Ptr{Cvoid}}), hcam, frame)
end

function exp_get_oldest_frame_ex(hcam::Integer, frame::Ref{Ptr{Cvoid}}, frame_info::Ref{FRAME_INFO})::Bool
    ccall((:pl_exp_get_oldest_frame_ex, :libpvcam), UInt16, (Int16, Ref{Ptr{Cvoid}}, Ref{FRAME_INFO}), hcam, frame, frame_info)
end

function exp_unlock_oldest_frame(hcam::Integer)::Bool
    ccall((:pl_exp_unlock_oldest_frame, :libpvcam), UInt16, (Int16,), hcam)
end

function exp_stop_cont(hcam::Integer, cam_state::PL_CCS_ABORT_MODES)::Bool
    ccall((:pl_exp_stop_cont, :libpvcam), UInt16, (Int16, Int16), hcam, cam_state)
end

function exp_abort(hcam::Integer, cam_state::Integer)::Bool
    ccall((:pl_exp_abort, :libpvcam), UInt16, (Int16, Int16), hcam, cam_state)
end

function exp_finish_seq(hcam::Integer, pixel_stream::Ref{Cvoid}, hbuf::Integer)::Bool
    ccall((:pl_exp_finish_seq, :libpvcam), UInt16, (Int16, Ref{Cvoid}, Int16), hcam, pixel_stream, hbuf)
end

function io_script_control(hcam::Integer, addr::Integer, state::Cdouble, location::Integer)::Bool
    ccall((:pl_io_script_control, :libpvcam), UInt16, (Int16, UInt16, Cdouble, UInt32), hcam, addr, state, location)
end

function io_clear_script_control(hcam::Integer)::Bool
    ccall((:pl_io_clear_script_control, :libpvcam), UInt16, (Int16,), hcam)
end

function md_frame_decode(pDstFrame::Ref{md_frame}, pSrcBuf::Ref{Cvoid}, srcBufSize::Integer)::Bool
    ccall((:pl_md_frame_decode, :libpvcam), UInt16, (Ref{md_frame}, Ref{Cvoid}, UInt32), pDstFrame, pSrcBuf, srcBufSize)
end

function md_frame_recompose(pDstBuf::Ref{Cvoid}, offX::Integer, offY::Integer, dstWidth::Integer, dstHeight::Integer, pSrcFrame::Ref{md_frame})::Bool
    ccall((:pl_md_frame_recompose, :libpvcam), UInt16, (Ref{Cvoid}, UInt16, UInt16, UInt16, UInt16, Ref{md_frame}), pDstBuf, offX, offY, dstWidth, dstHeight, pSrcFrame)
end

function md_create_frame_struct_cont(pFrame::Ref{Ptr{md_frame}}, roiCount::Integer)::Bool
    ccall((:pl_md_create_frame_struct_cont, :libpvcam), UInt16, (Ref{Ptr{md_frame}}, UInt16), pFrame, roiCount)
end

function md_create_frame_struct(pFrame::Ref{Ptr{md_frame}}, pSrcBuf::Ref{Cvoid}, srcBufSize::Integer)::Bool
    ccall((:pl_md_create_frame_struct, :libpvcam), UInt16, (Ref{Ptr{md_frame}}, Ref{Cvoid}, UInt32), pFrame, pSrcBuf, srcBufSize)
end

function md_release_frame_struct(pFrame::Ref{md_frame})::Bool
    ccall((:pl_md_release_frame_struct, :libpvcam), UInt16, (Ref{md_frame},), pFrame)
end

function md_read_extended(pOutput::Ref{md_ext_item_collection}, pExtMdPtr::Ref{Cvoid}, extMdSize::Integer)::Bool
    ccall((:pl_md_read_extended, :libpvcam), UInt16, (Ref{md_ext_item_collection}, Ref{Cvoid}, UInt32), pOutput, pExtMdPtr, extMdSize)
end
