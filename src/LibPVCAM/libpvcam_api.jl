
function pl_pvcam_get_ver(pvcam_version::Ref{UInt16})
    ccall((:pl_pvcam_get_ver, :libpvcam), UInt16, (Ref{UInt16},), pvcam_version)
end

function pl_pvcam_init()
    ccall((:pl_pvcam_init, :libpvcam), UInt16, ())
end

function pl_pvcam_uninit()
    ccall((:pl_pvcam_uninit, :libpvcam), UInt16, ())
end

function pl_cam_check(hcam::Int16)
    ccall((:pl_cam_check, :libpvcam), UInt16, (Int16,), hcam)
end

function pl_cam_close(hcam::Int16)
    ccall((:pl_cam_close, :libpvcam), UInt16, (Int16,), hcam)
end

function pl_cam_get_name(cam_num::Int16, camera_name)
    ccall((:pl_cam_get_name, :libpvcam), UInt16, (Int16, Cstring), cam_num, camera_name)
end

function pl_cam_get_total(totl_cams::Ref{Int16})
    ccall((:pl_cam_get_total, :libpvcam), UInt16, (Ref{Int16},), totl_cams)
end

function pl_cam_open(camera_name, hcam::Ref{Int16}, o_mode::Int16)
    ccall((:pl_cam_open, :libpvcam), UInt16, (Cstring, Ref{Int16}, Int16), camera_name, hcam, o_mode)
end

function pl_cam_register_callback(hcam::Int16, callback_event::Cint, callback::Ref{Cvoid})
    ccall((:pl_cam_register_callback, :libpvcam), UInt16, (Int16, Cint, Ref{Cvoid}), hcam, callback_event, callback)
end

function pl_cam_register_callback_ex(hcam::Int16, callback_event::Cint, callback::Ref{Cvoid}, context::Ref{Cvoid})
    ccall((:pl_cam_register_callback_ex, :libpvcam), UInt16, (Int16, Cint, Ref{Cvoid}, Ref{Cvoid}), hcam, callback_event, callback, context)
end

function pl_cam_register_callback_ex2(hcam::Int16, callback_event::Cint, callback::Ref{Cvoid})
    ccall((:pl_cam_register_callback_ex2, :libpvcam), UInt16, (Int16, Cint, Ref{Cvoid}), hcam, callback_event, callback)
end

function pl_cam_register_callback_ex3(hcam::Int16, callback_event::Cint, callback::Ref{Cvoid}, context::Ref{Cvoid})
    ccall((:pl_cam_register_callback_ex3, :libpvcam), UInt16, (Int16, Cint, Ref{Cvoid}, Ref{Cvoid}), hcam, callback_event, callback, context)
end

function pl_cam_deregister_callback(hcam::Int16, callback_event::Cint)
    ccall((:pl_cam_deregister_callback, :libpvcam), UInt16, (Int16, Cint), hcam, callback_event)
end

function pl_error_code()
    ccall((:pl_error_code, :libpvcam), Int16, ())
end

function pl_error_message(err_code::Int16, msg)
    ccall((:pl_error_message, :libpvcam), UInt16, (Int16, Cstring), err_code, msg)
end

function pl_get_param(hcam::Int16, param_id::UInt32, param_attribute::Int16, param_value::Ref{Cvoid})
    ccall((:pl_get_param, :libpvcam), UInt16, (Int16, UInt32, Int16, Ref{Cvoid}), hcam, param_id, param_attribute, param_value)
end

function pl_set_param(hcam::Int16, param_id::UInt32, param_value::Ref{Cvoid})
    ccall((:pl_set_param, :libpvcam), UInt16, (Int16, UInt32, Ref{Cvoid}), hcam, param_id, param_value)
end

function pl_get_enum_param(hcam::Int16, param_id::UInt32, index::UInt32, value::Ref{Cint}, desc, length::UInt32)
    ccall((:pl_get_enum_param, :libpvcam), UInt16, (Int16, UInt32, UInt32, Ref{Cint}, Cstring, UInt32), hcam, param_id, index, value, desc, length)
end

function pl_enum_str_length(hcam::Int16, param_id::UInt32, index::UInt32, length::Ref{UInt32})
    ccall((:pl_enum_str_length, :libpvcam), UInt16, (Int16, UInt32, UInt32, Ref{UInt32}), hcam, param_id, index, length)
end

function pl_pp_reset(hcam::Int16)
    ccall((:pl_pp_reset, :libpvcam), UInt16, (Int16,), hcam)
end

function pl_create_smart_stream_struct(array::Ref{Ptr{smart_stream_type}}, entries::UInt16)
    ccall((:pl_create_smart_stream_struct, :libpvcam), UInt16, (Ref{Ptr{smart_stream_type}}, UInt16), array, entries)
end

function pl_release_smart_stream_struct(array::Ref{Ptr{smart_stream_type}})
    ccall((:pl_release_smart_stream_struct, :libpvcam), UInt16, (Ref{Ptr{smart_stream_type}},), array)
end

function pl_create_frame_info_struct(new_frame::Ref{Ptr{FRAME_INFO}})
    ccall((:pl_create_frame_info_struct, :libpvcam), UInt16, (Ref{Ptr{FRAME_INFO}},), new_frame)
end

function pl_release_frame_info_struct(frame_to_delete::Ref{FRAME_INFO})
    ccall((:pl_release_frame_info_struct, :libpvcam), UInt16, (Ref{FRAME_INFO},), frame_to_delete)
end

function pl_exp_setup_seq(hcam::Int16, exp_total::UInt16, rgn_total::UInt16, rgn_array::Ref{rgn_type}, exp_mode::Int16, exposure_time::UInt32, exp_bytes::Ref{UInt32})
    ccall((:pl_exp_setup_seq, :libpvcam), UInt16, (Int16, UInt16, UInt16, Ref{rgn_type}, Int16, UInt32, Ref{UInt32}), hcam, exp_total, rgn_total, rgn_array, exp_mode, exposure_time, exp_bytes)
end

function pl_exp_start_seq(hcam::Int16, pixel_stream::Ref{Cvoid})
    ccall((:pl_exp_start_seq, :libpvcam), UInt16, (Int16, Ref{Cvoid}), hcam, pixel_stream)
end

function pl_exp_setup_cont(hcam::Int16, rgn_total::UInt16, rgn_array::Ref{rgn_type}, exp_mode::Int16, exposure_time::UInt32, exp_bytes::Ref{UInt32}, buffer_mode::Int16)
    ccall((:pl_exp_setup_cont, :libpvcam), UInt16, (Int16, UInt16, Ref{rgn_type}, Int16, UInt32, Ref{UInt32}, Int16), hcam, rgn_total, rgn_array, exp_mode, exposure_time, exp_bytes, buffer_mode)
end

function pl_exp_start_cont(hcam::Int16, pixel_stream::Ref{Cvoid}, size::UInt32)
    ccall((:pl_exp_start_cont, :libpvcam), UInt16, (Int16, Ref{Cvoid}, UInt32), hcam, pixel_stream, size)
end

function pl_exp_check_status(hcam::Int16, status::Ref{Int16}, bytes_arrived::Ref{UInt32})
    ccall((:pl_exp_check_status, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{UInt32}), hcam, status, bytes_arrived)
end

function pl_exp_check_cont_status(hcam::Int16, status::Ref{Int16}, bytes_arrived::Ref{UInt32}, buffer_cnt::Ref{UInt32})
    ccall((:pl_exp_check_cont_status, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{UInt32}, Ref{UInt32}), hcam, status, bytes_arrived, buffer_cnt)
end

function pl_exp_check_cont_status_ex(hcam::Int16, status::Ref{Int16}, byte_cnt::Ref{UInt32}, buffer_cnt::Ref{UInt32}, frame_info::Ref{FRAME_INFO})
    ccall((:pl_exp_check_cont_status_ex, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{UInt32}, Ref{UInt32}, Ref{FRAME_INFO}), hcam, status, byte_cnt, buffer_cnt, frame_info)
end

function pl_exp_get_latest_frame(hcam::Int16, frame::Ref{Ptr{Cvoid}})
    ccall((:pl_exp_get_latest_frame, :libpvcam), UInt16, (Int16, Ref{Ptr{Cvoid}}), hcam, frame)
end

function pl_exp_get_latest_frame_ex(hcam::Int16, frame::Ref{Ptr{Cvoid}}, frame_info::Ref{FRAME_INFO})
    ccall((:pl_exp_get_latest_frame_ex, :libpvcam), UInt16, (Int16, Ref{Ptr{Cvoid}}, Ref{FRAME_INFO}), hcam, frame, frame_info)
end

function pl_exp_get_oldest_frame(hcam::Int16, frame::Ref{Ptr{Cvoid}})
    ccall((:pl_exp_get_oldest_frame, :libpvcam), UInt16, (Int16, Ref{Ptr{Cvoid}}), hcam, frame)
end

function pl_exp_get_oldest_frame_ex(hcam::Int16, frame::Ref{Ptr{Cvoid}}, frame_info::Ref{FRAME_INFO})
    ccall((:pl_exp_get_oldest_frame_ex, :libpvcam), UInt16, (Int16, Ref{Ptr{Cvoid}}, Ref{FRAME_INFO}), hcam, frame, frame_info)
end

function pl_exp_unlock_oldest_frame(hcam::Int16)
    ccall((:pl_exp_unlock_oldest_frame, :libpvcam), UInt16, (Int16,), hcam)
end

function pl_exp_stop_cont(hcam::Int16, cam_state::Int16)
    ccall((:pl_exp_stop_cont, :libpvcam), UInt16, (Int16, Int16), hcam, cam_state)
end

function pl_exp_abort(hcam::Int16, cam_state::Int16)
    ccall((:pl_exp_abort, :libpvcam), UInt16, (Int16, Int16), hcam, cam_state)
end

function pl_exp_finish_seq(hcam::Int16, pixel_stream::Ref{Cvoid}, hbuf::Int16)
    ccall((:pl_exp_finish_seq, :libpvcam), UInt16, (Int16, Ref{Cvoid}, Int16), hcam, pixel_stream, hbuf)
end

function pl_io_script_control(hcam::Int16, addr::UInt16, state::Cdouble, location::UInt32)
    ccall((:pl_io_script_control, :libpvcam), UInt16, (Int16, UInt16, Cdouble, UInt32), hcam, addr, state, location)
end

function pl_io_clear_script_control(hcam::Int16)
    ccall((:pl_io_clear_script_control, :libpvcam), UInt16, (Int16,), hcam)
end

function pl_exp_init_seq()
    ccall((:pl_exp_init_seq, :libpvcam), UInt16, ())
end

function pl_exp_uninit_seq()
    ccall((:pl_exp_uninit_seq, :libpvcam), UInt16, ())
end

function pl_dd_get_info(hcam::Int16, bytes::Int16, text)
    ccall((:pl_dd_get_info, :libpvcam), UInt16, (Int16, Int16, Cstring), hcam, bytes, text)
end

function pl_dd_get_info_length(hcam::Int16, bytes::Ref{Int16})
    ccall((:pl_dd_get_info_length, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, bytes)
end

function pl_dd_get_ver(hcam::Int16, dd_version::Ref{UInt16})
    ccall((:pl_dd_get_ver, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, dd_version)
end

function pl_dd_get_retries(hcam::Int16, max_retries::Ref{UInt16})
    ccall((:pl_dd_get_retries, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, max_retries)
end

function pl_dd_set_retries(hcam::Int16, max_retries::UInt16)
    ccall((:pl_dd_set_retries, :libpvcam), UInt16, (Int16, UInt16), hcam, max_retries)
end

function pl_dd_get_timeout(hcam::Int16, m_sec::Ref{UInt16})
    ccall((:pl_dd_get_timeout, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, m_sec)
end

function pl_dd_set_timeout(hcam::Int16, m_sec::UInt16)
    ccall((:pl_dd_set_timeout, :libpvcam), UInt16, (Int16, UInt16), hcam, m_sec)
end

function pl_ccd_get_adc_offset(hcam::Int16, offset::Ref{Int16})
    ccall((:pl_ccd_get_adc_offset, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, offset)
end

function pl_ccd_set_adc_offset(hcam::Int16, offset::Int16)
    ccall((:pl_ccd_set_adc_offset, :libpvcam), UInt16, (Int16, Int16), hcam, offset)
end

function pl_ccd_get_chip_name(hcam::Int16, chip_name)
    ccall((:pl_ccd_get_chip_name, :libpvcam), UInt16, (Int16, Cstring), hcam, chip_name)
end

function pl_ccd_get_clear_cycles(hcam::Int16, clear_cycles::Ref{UInt16})
    ccall((:pl_ccd_get_clear_cycles, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, clear_cycles)
end

function pl_ccd_set_clear_cycles(hcam::Int16, clr_cycles::UInt16)
    ccall((:pl_ccd_set_clear_cycles, :libpvcam), UInt16, (Int16, UInt16), hcam, clr_cycles)
end

function pl_ccd_get_clear_mode(hcam::Int16, clear_mode::Ref{Int16})
    ccall((:pl_ccd_get_clear_mode, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, clear_mode)
end

function pl_ccd_set_clear_mode(hcam::Int16, ccd_clear::Int16)
    ccall((:pl_ccd_set_clear_mode, :libpvcam), UInt16, (Int16, Int16), hcam, ccd_clear)
end

function pl_ccd_get_color_mode(hcam::Int16, color_mode::Ref{UInt16})
    ccall((:pl_ccd_get_color_mode, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, color_mode)
end

function pl_ccd_get_cooling_mode(hcam::Int16, cooling::Ref{Int16})
    ccall((:pl_ccd_get_cooling_mode, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, cooling)
end

function pl_ccd_get_frame_capable(hcam::Int16, frame_capable::Ref{UInt16})
    ccall((:pl_ccd_get_frame_capable, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, frame_capable)
end

function pl_ccd_get_fwell_capacity(hcam::Int16, fwell_capacity::Ref{UInt32})
    ccall((:pl_ccd_get_fwell_capacity, :libpvcam), UInt16, (Int16, Ref{UInt32}), hcam, fwell_capacity)
end

function pl_ccd_get_mpp_capable(hcam::Int16, mpp_capable::Ref{Int16})
    ccall((:pl_ccd_get_mpp_capable, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, mpp_capable)
end

function pl_ccd_get_preamp_dly(hcam::Int16, preamp_dly::Ref{UInt16})
    ccall((:pl_ccd_get_preamp_dly, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, preamp_dly)
end

function pl_ccd_get_preamp_off_control(hcam::Int16, preamp_off_control::Ref{UInt32})
    ccall((:pl_ccd_get_preamp_off_control, :libpvcam), UInt16, (Int16, Ref{UInt32}), hcam, preamp_off_control)
end

function pl_ccd_set_preamp_off_control(hcam::Int16, preamp_off_control::UInt32)
    ccall((:pl_ccd_set_preamp_off_control, :libpvcam), UInt16, (Int16, UInt32), hcam, preamp_off_control)
end

function pl_ccd_get_preflash(hcam::Int16, pre_flash::Ref{UInt16})
    ccall((:pl_ccd_get_preflash, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, pre_flash)
end

function pl_ccd_get_pmode(hcam::Int16, pmode::Ref{Int16})
    ccall((:pl_ccd_get_pmode, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, pmode)
end

function pl_ccd_set_pmode(hcam::Int16, pmode::Int16)
    ccall((:pl_ccd_set_pmode, :libpvcam), UInt16, (Int16, Int16), hcam, pmode)
end

function pl_ccd_get_premask(hcam::Int16, pre_mask::Ref{UInt16})
    ccall((:pl_ccd_get_premask, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, pre_mask)
end

function pl_ccd_get_prescan(hcam::Int16, prescan::Ref{UInt16})
    ccall((:pl_ccd_get_prescan, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, prescan)
end

function pl_ccd_get_postmask(hcam::Int16, post_mask::Ref{UInt16})
    ccall((:pl_ccd_get_postmask, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, post_mask)
end

function pl_ccd_get_postscan(hcam::Int16, postscan::Ref{UInt16})
    ccall((:pl_ccd_get_postscan, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, postscan)
end

function pl_ccd_get_par_size(hcam::Int16, par_size::Ref{UInt16})
    ccall((:pl_ccd_get_par_size, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, par_size)
end

function pl_ccd_get_ser_size(hcam::Int16, ser_size::Ref{UInt16})
    ccall((:pl_ccd_get_ser_size, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, ser_size)
end

function pl_ccd_get_serial_num(hcam::Int16, serial_num::Ref{UInt16})
    ccall((:pl_ccd_get_serial_num, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, serial_num)
end

function pl_ccs_get_status(hcam::Int16, ccs_status::Ref{Int16})
    ccall((:pl_ccs_get_status, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, ccs_status)
end

function pl_ccd_get_summing_well(hcam::Int16, s_well_exists::Ref{UInt16})
    ccall((:pl_ccd_get_summing_well, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, s_well_exists)
end

function pl_ccd_get_tmp(hcam::Int16, cur_tmp::Ref{Int16})
    ccall((:pl_ccd_get_tmp, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, cur_tmp)
end

function pl_ccd_get_tmp_range(hcam::Int16, tmp_hi_val::Ref{Int16}, tmp_lo_val::Ref{Int16})
    ccall((:pl_ccd_get_tmp_range, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{Int16}), hcam, tmp_hi_val, tmp_lo_val)
end

function pl_ccd_get_tmp_setpoint(hcam::Int16, tmp_setpoint::Ref{Int16})
    ccall((:pl_ccd_get_tmp_setpoint, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, tmp_setpoint)
end

function pl_ccd_set_tmp_setpoint(hcam::Int16, tmp_setpoint::Int16)
    ccall((:pl_ccd_set_tmp_setpoint, :libpvcam), UInt16, (Int16, Int16), hcam, tmp_setpoint)
end

function pl_ccd_set_readout_port(arg1::Int16, arg2::Int16)
    ccall((:pl_ccd_set_readout_port, :libpvcam), UInt16, (Int16, Int16), arg1, arg2)
end

function pl_ccd_get_pix_par_dist(hcam::Int16, pix_par_dist::Ref{UInt16})
    ccall((:pl_ccd_get_pix_par_dist, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, pix_par_dist)
end

function pl_ccd_get_pix_par_size(hcam::Int16, pix_par_size::Ref{UInt16})
    ccall((:pl_ccd_get_pix_par_size, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, pix_par_size)
end

function pl_ccd_get_pix_ser_dist(hcam::Int16, pix_ser_dist::Ref{UInt16})
    ccall((:pl_ccd_get_pix_ser_dist, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, pix_ser_dist)
end

function pl_ccd_get_pix_ser_size(hcam::Int16, pix_ser_size::Ref{UInt16})
    ccall((:pl_ccd_get_pix_ser_size, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, pix_ser_size)
end

function pl_spdtab_get_bits(hcam::Int16, spdtab_bits::Ref{Int16})
    ccall((:pl_spdtab_get_bits, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, spdtab_bits)
end

function pl_spdtab_get_gain(hcam::Int16, spdtab_gain::Ref{Int16})
    ccall((:pl_spdtab_get_gain, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, spdtab_gain)
end

function pl_spdtab_set_gain(hcam::Int16, spdtab_gain::Int16)
    ccall((:pl_spdtab_set_gain, :libpvcam), UInt16, (Int16, Int16), hcam, spdtab_gain)
end

function pl_spdtab_get_max_gain(hcam::Int16, spdtab_max_gain::Ref{Int16})
    ccall((:pl_spdtab_get_max_gain, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, spdtab_max_gain)
end

function pl_spdtab_get_num(hcam::Int16, spdtab_num::Ref{Int16})
    ccall((:pl_spdtab_get_num, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, spdtab_num)
end

function pl_spdtab_set_num(hcam::Int16, spdtab_num::Int16)
    ccall((:pl_spdtab_set_num, :libpvcam), UInt16, (Int16, Int16), hcam, spdtab_num)
end

function pl_spdtab_get_entries(hcam::Int16, spdtab_entries::Ref{Int16})
    ccall((:pl_spdtab_get_entries, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, spdtab_entries)
end

function pl_spdtab_get_port(hcam::Int16, spdtab_port::Ref{Int16})
    ccall((:pl_spdtab_get_port, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, spdtab_port)
end

function pl_spdtab_get_port_total(hcam::Int16, total_ports::Ref{Int16})
    ccall((:pl_spdtab_get_port_total, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, total_ports)
end

function pl_spdtab_get_time(hcam::Int16, spdtab_time::Ref{UInt16})
    ccall((:pl_spdtab_get_time, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, spdtab_time)
end

function pl_shtr_get_close_dly(hcam::Int16, shtr_close_dly::Ref{UInt16})
    ccall((:pl_shtr_get_close_dly, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, shtr_close_dly)
end

function pl_shtr_set_close_dly(hcam::Int16, shtr_close_dly::UInt16)
    ccall((:pl_shtr_set_close_dly, :libpvcam), UInt16, (Int16, UInt16), hcam, shtr_close_dly)
end

function pl_shtr_get_open_dly(hcam::Int16, shtr_open_dly::Ref{UInt16})
    ccall((:pl_shtr_get_open_dly, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, shtr_open_dly)
end

function pl_shtr_set_open_dly(hcam::Int16, shtr_open_dly::UInt16)
    ccall((:pl_shtr_set_open_dly, :libpvcam), UInt16, (Int16, UInt16), hcam, shtr_open_dly)
end

function pl_shtr_get_open_mode(hcam::Int16, shtr_open_mode::Ref{Int16})
    ccall((:pl_shtr_get_open_mode, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, shtr_open_mode)
end

function pl_shtr_set_open_mode(hcam::Int16, shtr_open_mode::Int16)
    ccall((:pl_shtr_set_open_mode, :libpvcam), UInt16, (Int16, Int16), hcam, shtr_open_mode)
end

function pl_shtr_get_status(hcam::Int16, shtr_status::Ref{Int16})
    ccall((:pl_shtr_get_status, :libpvcam), UInt16, (Int16, Ref{Int16}), hcam, shtr_status)
end

function pl_exp_get_time_seq(hcam::Int16, exp_time::Ref{UInt16})
    ccall((:pl_exp_get_time_seq, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, exp_time)
end

function pl_exp_set_time_seq(hcam::Int16, exp_time::UInt16)
    ccall((:pl_exp_set_time_seq, :libpvcam), UInt16, (Int16, UInt16), hcam, exp_time)
end

function pl_exp_check_progress(hcam::Int16, status::Ref{Int16}, bytes_arrived::Ref{UInt32})
    ccall((:pl_exp_check_progress, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{UInt32}), hcam, status, bytes_arrived)
end

function pl_exp_set_cont_mode(hcam::Int16, mode::Int16)
    ccall((:pl_exp_set_cont_mode, :libpvcam), UInt16, (Int16, Int16), hcam, mode)
end

function pl_subsys_do_diag(hcam::Int16, subsys_id::UInt8, err_code::Ref{UInt16})
    ccall((:pl_subsys_do_diag, :libpvcam), UInt16, (Int16, UInt8, Ref{UInt16}), hcam, subsys_id, err_code)
end

function pl_subsys_get_id(hcam::Int16, subsys_id::UInt8, part_num::Ref{UInt16}, revision::Ref{UInt8})
    ccall((:pl_subsys_get_id, :libpvcam), UInt16, (Int16, UInt8, Ref{UInt16}, Ref{UInt8}), hcam, subsys_id, part_num, revision)
end

function pl_subsys_get_name(hcam::Int16, subsys_id::UInt8, subsys_name)
    ccall((:pl_subsys_get_name, :libpvcam), UInt16, (Int16, UInt8, Cstring), hcam, subsys_id, subsys_name)
end

function pl_exp_get_driver_buffer(hcam::Int16, pixel_stream::Ref{Ptr{Cvoid}}, byte_cnt::Ref{UInt32})
    ccall((:pl_exp_get_driver_buffer, :libpvcam), UInt16, (Int16, Ref{Ptr{Cvoid}}, Ref{UInt32}), hcam, pixel_stream, byte_cnt)
end

function pl_buf_init()
    ccall((:pl_buf_init, :libpvcam), UInt16, ())
end

function pl_buf_uninit()
    ccall((:pl_buf_uninit, :libpvcam), UInt16, ())
end

function pl_buf_alloc(hbuf::Ref{Int16}, exp_total::Int16, bit_depth::Int16, rgn_total::Int16, rgn_array::Ref{rgn_type})
    ccall((:pl_buf_alloc, :libpvcam), UInt16, (Ref{Int16}, Int16, Int16, Int16, Ref{rgn_type}), hbuf, exp_total, bit_depth, rgn_total, rgn_array)
end

function pl_buf_get_exp_date(hbuf::Int16, exp_num::Int16, year::Ref{Int16}, month::Ref{UInt8}, day::Ref{UInt8}, hour::Ref{UInt8}, min::Ref{UInt8}, sec::Ref{UInt8}, msec::Ref{UInt16})
    ccall((:pl_buf_get_exp_date, :libpvcam), UInt16, (Int16, Int16, Ref{Int16}, Ref{UInt8}, Ref{UInt8}, Ref{UInt8}, Ref{UInt8}, Ref{UInt8}, Ref{UInt16}), hbuf, exp_num, year, month, day, hour, min, sec, msec)
end

function pl_buf_set_exp_date(hbuf::Int16, exp_num::Int16, year::Int16, month::UInt8, day::UInt8, hour::UInt8, min::UInt8, sec::UInt8, msec::UInt16)
    ccall((:pl_buf_set_exp_date, :libpvcam), UInt16, (Int16, Int16, Int16, UInt8, UInt8, UInt8, UInt8, UInt8, UInt16), hbuf, exp_num, year, month, day, hour, min, sec, msec)
end

function pl_buf_get_exp_time(hbuf::Int16, exp_num::Int16, exp_msec::Ref{UInt32})
    ccall((:pl_buf_get_exp_time, :libpvcam), UInt16, (Int16, Int16, Ref{UInt32}), hbuf, exp_num, exp_msec)
end

function pl_buf_get_exp_total(hbuf::Int16, total_exps::Ref{Int16})
    ccall((:pl_buf_get_exp_total, :libpvcam), UInt16, (Int16, Ref{Int16}), hbuf, total_exps)
end

function pl_buf_get_img_bin(himg::Int16, ibin::Ref{Int16}, jbin::Ref{Int16})
    ccall((:pl_buf_get_img_bin, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{Int16}), himg, ibin, jbin)
end

function pl_buf_get_img_handle(hbuf::Int16, exp_num::Int16, img_num::Int16, himg::Ref{Int16})
    ccall((:pl_buf_get_img_handle, :libpvcam), UInt16, (Int16, Int16, Int16, Ref{Int16}), hbuf, exp_num, img_num, himg)
end

function pl_buf_get_img_ofs(himg::Int16, s_ofs::Ref{Int16}, p_ofs::Ref{Int16})
    ccall((:pl_buf_get_img_ofs, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{Int16}), himg, s_ofs, p_ofs)
end

function pl_buf_get_img_ptr(himg::Int16, img_addr::Ref{Ptr{Cvoid}})
    ccall((:pl_buf_get_img_ptr, :libpvcam), UInt16, (Int16, Ref{Ptr{Cvoid}}), himg, img_addr)
end

function pl_buf_get_img_size(himg::Int16, x_size::Ref{Int16}, y_size::Ref{Int16})
    ccall((:pl_buf_get_img_size, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{Int16}), himg, x_size, y_size)
end

function pl_buf_get_img_total(hbuf::Int16, totl_imgs::Ref{Int16})
    ccall((:pl_buf_get_img_total, :libpvcam), UInt16, (Int16, Ref{Int16}), hbuf, totl_imgs)
end

function pl_buf_get_size(hbuf::Int16, buf_size::Ref{Cint})
    ccall((:pl_buf_get_size, :libpvcam), UInt16, (Int16, Ref{Cint}), hbuf, buf_size)
end

function pl_buf_free(hbuf::Int16)
    ccall((:pl_buf_free, :libpvcam), UInt16, (Int16,), hbuf)
end

function pl_buf_get_bits(hbuf::Int16, bit_depth::Ref{Int16})
    ccall((:pl_buf_get_bits, :libpvcam), UInt16, (Int16, Ref{Int16}), hbuf, bit_depth)
end

function pl_exp_unravel(hcam::Int16, exposure::UInt16, pixel_stream::Ref{Cvoid}, rgn_total::UInt16, rgn_array::Ref{rgn_type}, array_list::Ref{Ptr{UInt16}})
    ccall((:pl_exp_unravel, :libpvcam), UInt16, (Int16, UInt16, Ref{Cvoid}, UInt16, Ref{rgn_type}, Ref{Ptr{UInt16}}), hcam, exposure, pixel_stream, rgn_total, rgn_array, array_list)
end

function pl_exp_wait_start_xfer(hcam::Int16, tlimit::UInt32)
    ccall((:pl_exp_wait_start_xfer, :libpvcam), UInt16, (Int16, UInt32), hcam, tlimit)
end

function pl_exp_wait_end_xfer(hcam::Int16, tlimit::UInt32)
    ccall((:pl_exp_wait_end_xfer, :libpvcam), UInt16, (Int16, UInt32), hcam, tlimit)
end

function pv_cam_get_ccs_mem(hcam::Int16, size::Ref{UInt16})
    ccall((:pv_cam_get_ccs_mem, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, size)
end

function pv_cam_send_debug(hcam::Int16, debug_str, reply_len::UInt16, reply_str)
    ccall((:pv_cam_send_debug, :libpvcam), UInt16, (Int16, Cstring, UInt16, Cstring), hcam, debug_str, reply_len, reply_str)
end

function pv_cam_write_read(hcam::Int16, c_class::UInt8, write_bytes::UInt16, write_array::Ref{UInt8}, read_array::Ref{UInt8})
    ccall((:pv_cam_write_read, :libpvcam), UInt16, (Int16, UInt8, UInt16, Ref{UInt8}, Ref{UInt8}), hcam, c_class, write_bytes, write_array, read_array)
end

function pv_dd_active(hcam::Int16, pixel_stream::Ref{Cvoid})
    ccall((:pv_dd_active, :libpvcam), UInt16, (Int16, Ref{Cvoid}), hcam, pixel_stream)
end

function pv_exp_get_bytes(hcam::Int16, exp_bytes::Ref{UInt32})
    ccall((:pv_exp_get_bytes, :libpvcam), UInt16, (Int16, Ref{UInt32}), hcam, exp_bytes)
end

function pv_exp_get_script(hcam::Int16, script_valid::Ref{UInt16})
    ccall((:pv_exp_get_script, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, script_valid)
end

function pv_exp_get_status(hcam::Int16, status::Ref{Int16}, byte_cnt::Ref{UInt32}, frame_cnt::Ref{UInt32})
    ccall((:pv_exp_get_status, :libpvcam), UInt16, (Int16, Ref{Int16}, Ref{UInt32}, Ref{UInt32}), hcam, status, byte_cnt, frame_cnt)
end

function pv_exp_set_bytes(hcam::Int16, frame_count::UInt32, seq_bytes::UInt32, pixel_stream::Ref{Cvoid})
    ccall((:pv_exp_set_bytes, :libpvcam), UInt16, (Int16, UInt32, UInt32, Ref{Cvoid}), hcam, frame_count, seq_bytes, pixel_stream)
end

function pv_exp_set_script(hcam::Int16, script_valid::UInt16)
    ccall((:pv_exp_set_script, :libpvcam), UInt16, (Int16, UInt16), hcam, script_valid)
end

function pv_set_error_code(omode::Int16, err_code::Int16)
    ccall((:pv_set_error_code, :libpvcam), UInt16, (Int16, Int16), omode, err_code)
end

function pv_cam_do_reads(hcam::Int16)
    ccall((:pv_cam_do_reads, :libpvcam), UInt16, (Int16,), hcam)
end

function pv_free(block::Ref{Cvoid}, heap::Int16)
    ccall((:pv_free, :libpvcam), UInt16, (Ref{Cvoid}, Int16), block, heap)
end

function pv_malloc(size::UInt32, heap::Int16)
    ccall((:pv_malloc, :libpvcam), Ptr{Cvoid}, (UInt32, Int16), size, heap)
end

function pv_realloc(block::Ref{Cvoid}, size::UInt32, heap::Int16)
    ccall((:pv_realloc, :libpvcam), Ptr{Cvoid}, (Ref{Cvoid}, UInt32, Int16), block, size, heap)
end

function pv_script_set_hook(pfn::Ref{pm_script_hook})
    ccall((:pv_script_set_hook, :libpvcam), UInt16, (Ref{pm_script_hook},), pfn)
end

function pv_ccd_get_accum_capable(hcam::Int16, accum_capable::Ref{UInt16})
    ccall((:pv_ccd_get_accum_capable, :libpvcam), UInt16, (Int16, Ref{UInt16}), hcam, accum_capable)
end

function pv_exp_get_frames(hcam::Int16, exp_frames::Ref{UInt32})
    ccall((:pv_exp_get_frames, :libpvcam), UInt16, (Int16, Ref{UInt32}), hcam, exp_frames)
end

function pv_exp_set_frames(hcam::Int16, exp_frames::UInt32)
    ccall((:pv_exp_set_frames, :libpvcam), UInt16, (Int16, UInt32), hcam, exp_frames)
end

function pv_exp_set_no_readout_timeout(hcam::Int16)
    ccall((:pv_exp_set_no_readout_timeout, :libpvcam), UInt16, (Int16,), hcam)
end

function pv_exp_reset_no_readout_timeout(hcam::Int16)
    ccall((:pv_exp_reset_no_readout_timeout, :libpvcam), UInt16, (Int16,), hcam)
end

function pm_cam_write_read(hcam::Int16, c_class::UInt8, write_bytes::UInt16, write_array::Ref{UInt8}, read_array::Ref{UInt8})
    ccall((:pm_cam_write_read, :libpvcam), UInt16, (Int16, UInt8, UInt16, Ref{UInt8}, Ref{UInt8}), hcam, c_class, write_bytes, write_array, read_array)
end

function pl_ddi_get_ver(ddi_version::Ref{UInt16})
    ccall((:pl_ddi_get_ver, :libpvcam), UInt16, (Ref{UInt16},), ddi_version)
end

function pl_cam_get_diags(hcam::Int16)
    ccall((:pl_cam_get_diags, :libpvcam), UInt16, (Int16,), hcam)
end

function pl_md_frame_decode(pDstFrame::Ref{md_frame}, pSrcBuf::Ref{Cvoid}, srcBufSize::UInt32)
    ccall((:pl_md_frame_decode, :libpvcam), UInt16, (Ref{md_frame}, Ref{Cvoid}, UInt32), pDstFrame, pSrcBuf, srcBufSize)
end

function pl_md_frame_recompose(pDstBuf::Ref{Cvoid}, offX::UInt16, offY::UInt16, dstWidth::UInt16, dstHeight::UInt16, pSrcFrame::Ref{md_frame})
    ccall((:pl_md_frame_recompose, :libpvcam), UInt16, (Ref{Cvoid}, UInt16, UInt16, UInt16, UInt16, Ref{md_frame}), pDstBuf, offX, offY, dstWidth, dstHeight, pSrcFrame)
end

function pl_md_create_frame_struct_cont(pFrame::Ref{Ptr{md_frame}}, roiCount::UInt16)
    ccall((:pl_md_create_frame_struct_cont, :libpvcam), UInt16, (Ref{Ptr{md_frame}}, UInt16), pFrame, roiCount)
end

function pl_md_create_frame_struct(pFrame::Ref{Ptr{md_frame}}, pSrcBuf::Ref{Cvoid}, srcBufSize::UInt32)
    ccall((:pl_md_create_frame_struct, :libpvcam), UInt16, (Ref{Ptr{md_frame}}, Ref{Cvoid}, UInt32), pFrame, pSrcBuf, srcBufSize)
end

function pl_md_release_frame_struct(pFrame::Ref{md_frame})
    ccall((:pl_md_release_frame_struct, :libpvcam), UInt16, (Ref{md_frame},), pFrame)
end

function pl_md_read_extended(pOutput::Ref{md_ext_item_collection}, pExtMdPtr::Ref{Cvoid}, extMdSize::UInt32)
    ccall((:pl_md_read_extended, :libpvcam), UInt16, (Ref{md_ext_item_collection}, Ref{Cvoid}, UInt32), pOutput, pExtMdPtr, extMdSize)
end
