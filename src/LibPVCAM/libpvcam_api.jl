
function pl_pvcam_get_ver(pvcam_version::Ref{uns16})
    ccall((:pl_pvcam_get_ver, :libpvcam), UInt16, (Ref{uns16},), pvcam_version)
end

function pl_pvcam_init()
    ccall((:pl_pvcam_init, :libpvcam), UInt16, ())
end

function pl_pvcam_uninit()
    ccall((:pl_pvcam_uninit, :libpvcam), UInt16, ())
end

function pl_cam_check(hcam::int16)
    ccall((:pl_cam_check, :libpvcam), UInt16, (int16,), hcam)
end

function pl_cam_close(hcam::int16)
    ccall((:pl_cam_close, :libpvcam), UInt16, (int16,), hcam)
end

function pl_cam_get_name(cam_num::int16, camera_name)
    ccall((:pl_cam_get_name, :libpvcam), UInt16, (int16, Cstring), cam_num, camera_name)
end

function pl_cam_get_total(totl_cams::Ref{int16})
    ccall((:pl_cam_get_total, :libpvcam), UInt16, (Ref{int16},), totl_cams)
end

function pl_cam_open(camera_name, hcam::Ref{int16}, o_mode::int16)
    ccall((:pl_cam_open, :libpvcam), UInt16, (Cstring, Ref{int16}, int16), camera_name, hcam, o_mode)
end

function pl_cam_register_callback(hcam::int16, callback_event::int32, callback::Ref{Cvoid})
    ccall((:pl_cam_register_callback, :libpvcam), UInt16, (int16, int32, Ref{Cvoid}), hcam, callback_event, callback)
end

function pl_cam_register_callback_ex(hcam::int16, callback_event::int32, callback::Ref{Cvoid}, context::Ref{Cvoid})
    ccall((:pl_cam_register_callback_ex, :libpvcam), UInt16, (int16, int32, Ref{Cvoid}, Ref{Cvoid}), hcam, callback_event, callback, context)
end

function pl_cam_register_callback_ex2(hcam::int16, callback_event::int32, callback::Ref{Cvoid})
    ccall((:pl_cam_register_callback_ex2, :libpvcam), UInt16, (int16, int32, Ref{Cvoid}), hcam, callback_event, callback)
end

function pl_cam_register_callback_ex3(hcam::int16, callback_event::int32, callback::Ref{Cvoid}, context::Ref{Cvoid})
    ccall((:pl_cam_register_callback_ex3, :libpvcam), UInt16, (int16, int32, Ref{Cvoid}, Ref{Cvoid}), hcam, callback_event, callback, context)
end

function pl_cam_deregister_callback(hcam::int16, callback_event::int32)
    ccall((:pl_cam_deregister_callback, :libpvcam), UInt16, (int16, int32), hcam, callback_event)
end

function pl_error_code()
    ccall((:pl_error_code, :libpvcam), int16, ())
end

function pl_error_message(err_code::int16, msg)
    ccall((:pl_error_message, :libpvcam), UInt16, (int16, Cstring), err_code, msg)
end

function pl_get_param(hcam::int16, param_id::uns32, param_attribute::int16, param_value::Ref{Cvoid})
    ccall((:pl_get_param, :libpvcam), UInt16, (int16, uns32, int16, Ref{Cvoid}), hcam, param_id, param_attribute, param_value)
end

function pl_set_param(hcam::int16, param_id::uns32, param_value::Ref{Cvoid})
    ccall((:pl_set_param, :libpvcam), UInt16, (int16, uns32, Ref{Cvoid}), hcam, param_id, param_value)
end

function pl_get_enum_param(hcam::int16, param_id::uns32, index::uns32, value::Ref{int32}, desc, length::uns32)
    ccall((:pl_get_enum_param, :libpvcam), UInt16, (int16, uns32, uns32, Ref{int32}, Cstring, uns32), hcam, param_id, index, value, desc, length)
end

function pl_enum_str_length(hcam::int16, param_id::uns32, index::uns32, length::Ref{uns32})
    ccall((:pl_enum_str_length, :libpvcam), UInt16, (int16, uns32, uns32, Ref{uns32}), hcam, param_id, index, length)
end

function pl_pp_reset(hcam::int16)
    ccall((:pl_pp_reset, :libpvcam), UInt16, (int16,), hcam)
end

function pl_create_smart_stream_struct(array::Ref{Ptr{smart_stream_type}}, entries::uns16)
    ccall((:pl_create_smart_stream_struct, :libpvcam), UInt16, (Ref{Ptr{smart_stream_type}}, uns16), array, entries)
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

function pl_exp_setup_seq(hcam::int16, exp_total::uns16, rgn_total::uns16, rgn_array::Ref{rgn_type}, exp_mode::int16, exposure_time::uns32, exp_bytes::Ref{uns32})
    ccall((:pl_exp_setup_seq, :libpvcam), UInt16, (int16, uns16, uns16, Ref{rgn_type}, int16, uns32, Ref{uns32}), hcam, exp_total, rgn_total, rgn_array, exp_mode, exposure_time, exp_bytes)
end

function pl_exp_start_seq(hcam::int16, pixel_stream::Ref{Cvoid})
    ccall((:pl_exp_start_seq, :libpvcam), UInt16, (int16, Ref{Cvoid}), hcam, pixel_stream)
end

function pl_exp_setup_cont(hcam::int16, rgn_total::uns16, rgn_array::Ref{rgn_type}, exp_mode::int16, exposure_time::uns32, exp_bytes::Ref{uns32}, buffer_mode::int16)
    ccall((:pl_exp_setup_cont, :libpvcam), UInt16, (int16, uns16, Ref{rgn_type}, int16, uns32, Ref{uns32}, int16), hcam, rgn_total, rgn_array, exp_mode, exposure_time, exp_bytes, buffer_mode)
end

function pl_exp_start_cont(hcam::int16, pixel_stream::Ref{Cvoid}, size::uns32)
    ccall((:pl_exp_start_cont, :libpvcam), UInt16, (int16, Ref{Cvoid}, uns32), hcam, pixel_stream, size)
end

function pl_exp_check_status(hcam::int16, status::Ref{int16}, bytes_arrived::Ref{uns32})
    ccall((:pl_exp_check_status, :libpvcam), UInt16, (int16, Ref{int16}, Ref{uns32}), hcam, status, bytes_arrived)
end

function pl_exp_check_cont_status(hcam::int16, status::Ref{int16}, bytes_arrived::Ref{uns32}, buffer_cnt::Ref{uns32})
    ccall((:pl_exp_check_cont_status, :libpvcam), UInt16, (int16, Ref{int16}, Ref{uns32}, Ref{uns32}), hcam, status, bytes_arrived, buffer_cnt)
end

function pl_exp_check_cont_status_ex(hcam::int16, status::Ref{int16}, byte_cnt::Ref{uns32}, buffer_cnt::Ref{uns32}, frame_info::Ref{FRAME_INFO})
    ccall((:pl_exp_check_cont_status_ex, :libpvcam), UInt16, (int16, Ref{int16}, Ref{uns32}, Ref{uns32}, Ref{FRAME_INFO}), hcam, status, byte_cnt, buffer_cnt, frame_info)
end

function pl_exp_get_latest_frame(hcam::int16, frame::Ref{Ptr{Cvoid}})
    ccall((:pl_exp_get_latest_frame, :libpvcam), UInt16, (int16, Ref{Ptr{Cvoid}}), hcam, frame)
end

function pl_exp_get_latest_frame_ex(hcam::int16, frame::Ref{Ptr{Cvoid}}, frame_info::Ref{FRAME_INFO})
    ccall((:pl_exp_get_latest_frame_ex, :libpvcam), UInt16, (int16, Ref{Ptr{Cvoid}}, Ref{FRAME_INFO}), hcam, frame, frame_info)
end

function pl_exp_get_oldest_frame(hcam::int16, frame::Ref{Ptr{Cvoid}})
    ccall((:pl_exp_get_oldest_frame, :libpvcam), UInt16, (int16, Ref{Ptr{Cvoid}}), hcam, frame)
end

function pl_exp_get_oldest_frame_ex(hcam::int16, frame::Ref{Ptr{Cvoid}}, frame_info::Ref{FRAME_INFO})
    ccall((:pl_exp_get_oldest_frame_ex, :libpvcam), UInt16, (int16, Ref{Ptr{Cvoid}}, Ref{FRAME_INFO}), hcam, frame, frame_info)
end

function pl_exp_unlock_oldest_frame(hcam::int16)
    ccall((:pl_exp_unlock_oldest_frame, :libpvcam), UInt16, (int16,), hcam)
end

function pl_exp_stop_cont(hcam::int16, cam_state::int16)
    ccall((:pl_exp_stop_cont, :libpvcam), UInt16, (int16, int16), hcam, cam_state)
end

function pl_exp_abort(hcam::int16, cam_state::int16)
    ccall((:pl_exp_abort, :libpvcam), UInt16, (int16, int16), hcam, cam_state)
end

function pl_exp_finish_seq(hcam::int16, pixel_stream::Ref{Cvoid}, hbuf::int16)
    ccall((:pl_exp_finish_seq, :libpvcam), UInt16, (int16, Ref{Cvoid}, int16), hcam, pixel_stream, hbuf)
end

function pl_io_script_control(hcam::int16, addr::uns16, state::flt64, location::uns32)
    ccall((:pl_io_script_control, :libpvcam), UInt16, (int16, uns16, flt64, uns32), hcam, addr, state, location)
end

function pl_io_clear_script_control(hcam::int16)
    ccall((:pl_io_clear_script_control, :libpvcam), UInt16, (int16,), hcam)
end

function pl_exp_init_seq()
    ccall((:pl_exp_init_seq, :libpvcam), UInt16, ())
end

function pl_exp_uninit_seq()
    ccall((:pl_exp_uninit_seq, :libpvcam), UInt16, ())
end

function pl_dd_get_info(hcam::int16, bytes::int16, text)
    ccall((:pl_dd_get_info, :libpvcam), UInt16, (int16, int16, Cstring), hcam, bytes, text)
end

function pl_dd_get_info_length(hcam::int16, bytes::Ref{int16})
    ccall((:pl_dd_get_info_length, :libpvcam), UInt16, (int16, Ref{int16}), hcam, bytes)
end

function pl_dd_get_ver(hcam::int16, dd_version::Ref{uns16})
    ccall((:pl_dd_get_ver, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, dd_version)
end

function pl_dd_get_retries(hcam::int16, max_retries::Ref{uns16})
    ccall((:pl_dd_get_retries, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, max_retries)
end

function pl_dd_set_retries(hcam::int16, max_retries::uns16)
    ccall((:pl_dd_set_retries, :libpvcam), UInt16, (int16, uns16), hcam, max_retries)
end

function pl_dd_get_timeout(hcam::int16, m_sec::Ref{uns16})
    ccall((:pl_dd_get_timeout, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, m_sec)
end

function pl_dd_set_timeout(hcam::int16, m_sec::uns16)
    ccall((:pl_dd_set_timeout, :libpvcam), UInt16, (int16, uns16), hcam, m_sec)
end

function pl_ccd_get_adc_offset(hcam::int16, offset::Ref{int16})
    ccall((:pl_ccd_get_adc_offset, :libpvcam), UInt16, (int16, Ref{int16}), hcam, offset)
end

function pl_ccd_set_adc_offset(hcam::int16, offset::int16)
    ccall((:pl_ccd_set_adc_offset, :libpvcam), UInt16, (int16, int16), hcam, offset)
end

function pl_ccd_get_chip_name(hcam::int16, chip_name)
    ccall((:pl_ccd_get_chip_name, :libpvcam), UInt16, (int16, Cstring), hcam, chip_name)
end

function pl_ccd_get_clear_cycles(hcam::int16, clear_cycles::Ref{uns16})
    ccall((:pl_ccd_get_clear_cycles, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, clear_cycles)
end

function pl_ccd_set_clear_cycles(hcam::int16, clr_cycles::uns16)
    ccall((:pl_ccd_set_clear_cycles, :libpvcam), UInt16, (int16, uns16), hcam, clr_cycles)
end

function pl_ccd_get_clear_mode(hcam::int16, clear_mode::Ref{int16})
    ccall((:pl_ccd_get_clear_mode, :libpvcam), UInt16, (int16, Ref{int16}), hcam, clear_mode)
end

function pl_ccd_set_clear_mode(hcam::int16, ccd_clear::int16)
    ccall((:pl_ccd_set_clear_mode, :libpvcam), UInt16, (int16, int16), hcam, ccd_clear)
end

function pl_ccd_get_color_mode(hcam::int16, color_mode::Ref{uns16})
    ccall((:pl_ccd_get_color_mode, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, color_mode)
end

function pl_ccd_get_cooling_mode(hcam::int16, cooling::Ref{int16})
    ccall((:pl_ccd_get_cooling_mode, :libpvcam), UInt16, (int16, Ref{int16}), hcam, cooling)
end

function pl_ccd_get_frame_capable(hcam::int16, frame_capable::Ref{UInt16})
    ccall((:pl_ccd_get_frame_capable, :libpvcam), UInt16, (int16, Ref{UInt16}), hcam, frame_capable)
end

function pl_ccd_get_fwell_capacity(hcam::int16, fwell_capacity::Ref{uns32})
    ccall((:pl_ccd_get_fwell_capacity, :libpvcam), UInt16, (int16, Ref{uns32}), hcam, fwell_capacity)
end

function pl_ccd_get_mpp_capable(hcam::int16, mpp_capable::Ref{int16})
    ccall((:pl_ccd_get_mpp_capable, :libpvcam), UInt16, (int16, Ref{int16}), hcam, mpp_capable)
end

function pl_ccd_get_preamp_dly(hcam::int16, preamp_dly::Ref{uns16})
    ccall((:pl_ccd_get_preamp_dly, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, preamp_dly)
end

function pl_ccd_get_preamp_off_control(hcam::int16, preamp_off_control::Ref{uns32})
    ccall((:pl_ccd_get_preamp_off_control, :libpvcam), UInt16, (int16, Ref{uns32}), hcam, preamp_off_control)
end

function pl_ccd_set_preamp_off_control(hcam::int16, preamp_off_control::uns32)
    ccall((:pl_ccd_set_preamp_off_control, :libpvcam), UInt16, (int16, uns32), hcam, preamp_off_control)
end

function pl_ccd_get_preflash(hcam::int16, pre_flash::Ref{uns16})
    ccall((:pl_ccd_get_preflash, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, pre_flash)
end

function pl_ccd_get_pmode(hcam::int16, pmode::Ref{int16})
    ccall((:pl_ccd_get_pmode, :libpvcam), UInt16, (int16, Ref{int16}), hcam, pmode)
end

function pl_ccd_set_pmode(hcam::int16, pmode::int16)
    ccall((:pl_ccd_set_pmode, :libpvcam), UInt16, (int16, int16), hcam, pmode)
end

function pl_ccd_get_premask(hcam::int16, pre_mask::Ref{uns16})
    ccall((:pl_ccd_get_premask, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, pre_mask)
end

function pl_ccd_get_prescan(hcam::int16, prescan::Ref{uns16})
    ccall((:pl_ccd_get_prescan, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, prescan)
end

function pl_ccd_get_postmask(hcam::int16, post_mask::Ref{uns16})
    ccall((:pl_ccd_get_postmask, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, post_mask)
end

function pl_ccd_get_postscan(hcam::int16, postscan::Ref{uns16})
    ccall((:pl_ccd_get_postscan, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, postscan)
end

function pl_ccd_get_par_size(hcam::int16, par_size::Ref{uns16})
    ccall((:pl_ccd_get_par_size, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, par_size)
end

function pl_ccd_get_ser_size(hcam::int16, ser_size::Ref{uns16})
    ccall((:pl_ccd_get_ser_size, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, ser_size)
end

function pl_ccd_get_serial_num(hcam::int16, serial_num::Ref{uns16})
    ccall((:pl_ccd_get_serial_num, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, serial_num)
end

function pl_ccs_get_status(hcam::int16, ccs_status::Ref{int16})
    ccall((:pl_ccs_get_status, :libpvcam), UInt16, (int16, Ref{int16}), hcam, ccs_status)
end

function pl_ccd_get_summing_well(hcam::int16, s_well_exists::Ref{UInt16})
    ccall((:pl_ccd_get_summing_well, :libpvcam), UInt16, (int16, Ref{UInt16}), hcam, s_well_exists)
end

function pl_ccd_get_tmp(hcam::int16, cur_tmp::Ref{int16})
    ccall((:pl_ccd_get_tmp, :libpvcam), UInt16, (int16, Ref{int16}), hcam, cur_tmp)
end

function pl_ccd_get_tmp_range(hcam::int16, tmp_hi_val::Ref{int16}, tmp_lo_val::Ref{int16})
    ccall((:pl_ccd_get_tmp_range, :libpvcam), UInt16, (int16, Ref{int16}, Ref{int16}), hcam, tmp_hi_val, tmp_lo_val)
end

function pl_ccd_get_tmp_setpoint(hcam::int16, tmp_setpoint::Ref{int16})
    ccall((:pl_ccd_get_tmp_setpoint, :libpvcam), UInt16, (int16, Ref{int16}), hcam, tmp_setpoint)
end

function pl_ccd_set_tmp_setpoint(hcam::int16, tmp_setpoint::int16)
    ccall((:pl_ccd_set_tmp_setpoint, :libpvcam), UInt16, (int16, int16), hcam, tmp_setpoint)
end

function pl_ccd_set_readout_port(arg1::int16, arg2::int16)
    ccall((:pl_ccd_set_readout_port, :libpvcam), UInt16, (int16, int16), arg1, arg2)
end

function pl_ccd_get_pix_par_dist(hcam::int16, pix_par_dist::Ref{uns16})
    ccall((:pl_ccd_get_pix_par_dist, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, pix_par_dist)
end

function pl_ccd_get_pix_par_size(hcam::int16, pix_par_size::Ref{uns16})
    ccall((:pl_ccd_get_pix_par_size, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, pix_par_size)
end

function pl_ccd_get_pix_ser_dist(hcam::int16, pix_ser_dist::Ref{uns16})
    ccall((:pl_ccd_get_pix_ser_dist, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, pix_ser_dist)
end

function pl_ccd_get_pix_ser_size(hcam::int16, pix_ser_size::Ref{uns16})
    ccall((:pl_ccd_get_pix_ser_size, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, pix_ser_size)
end

function pl_spdtab_get_bits(hcam::int16, spdtab_bits::Ref{int16})
    ccall((:pl_spdtab_get_bits, :libpvcam), UInt16, (int16, Ref{int16}), hcam, spdtab_bits)
end

function pl_spdtab_get_gain(hcam::int16, spdtab_gain::Ref{int16})
    ccall((:pl_spdtab_get_gain, :libpvcam), UInt16, (int16, Ref{int16}), hcam, spdtab_gain)
end

function pl_spdtab_set_gain(hcam::int16, spdtab_gain::int16)
    ccall((:pl_spdtab_set_gain, :libpvcam), UInt16, (int16, int16), hcam, spdtab_gain)
end

function pl_spdtab_get_max_gain(hcam::int16, spdtab_max_gain::Ref{int16})
    ccall((:pl_spdtab_get_max_gain, :libpvcam), UInt16, (int16, Ref{int16}), hcam, spdtab_max_gain)
end

function pl_spdtab_get_num(hcam::int16, spdtab_num::Ref{int16})
    ccall((:pl_spdtab_get_num, :libpvcam), UInt16, (int16, Ref{int16}), hcam, spdtab_num)
end

function pl_spdtab_set_num(hcam::int16, spdtab_num::int16)
    ccall((:pl_spdtab_set_num, :libpvcam), UInt16, (int16, int16), hcam, spdtab_num)
end

function pl_spdtab_get_entries(hcam::int16, spdtab_entries::Ref{int16})
    ccall((:pl_spdtab_get_entries, :libpvcam), UInt16, (int16, Ref{int16}), hcam, spdtab_entries)
end

function pl_spdtab_get_port(hcam::int16, spdtab_port::Ref{int16})
    ccall((:pl_spdtab_get_port, :libpvcam), UInt16, (int16, Ref{int16}), hcam, spdtab_port)
end

function pl_spdtab_get_port_total(hcam::int16, total_ports::Ref{int16})
    ccall((:pl_spdtab_get_port_total, :libpvcam), UInt16, (int16, Ref{int16}), hcam, total_ports)
end

function pl_spdtab_get_time(hcam::int16, spdtab_time::Ref{uns16})
    ccall((:pl_spdtab_get_time, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, spdtab_time)
end

function pl_shtr_get_close_dly(hcam::int16, shtr_close_dly::Ref{uns16})
    ccall((:pl_shtr_get_close_dly, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, shtr_close_dly)
end

function pl_shtr_set_close_dly(hcam::int16, shtr_close_dly::uns16)
    ccall((:pl_shtr_set_close_dly, :libpvcam), UInt16, (int16, uns16), hcam, shtr_close_dly)
end

function pl_shtr_get_open_dly(hcam::int16, shtr_open_dly::Ref{uns16})
    ccall((:pl_shtr_get_open_dly, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, shtr_open_dly)
end

function pl_shtr_set_open_dly(hcam::int16, shtr_open_dly::uns16)
    ccall((:pl_shtr_set_open_dly, :libpvcam), UInt16, (int16, uns16), hcam, shtr_open_dly)
end

function pl_shtr_get_open_mode(hcam::int16, shtr_open_mode::Ref{int16})
    ccall((:pl_shtr_get_open_mode, :libpvcam), UInt16, (int16, Ref{int16}), hcam, shtr_open_mode)
end

function pl_shtr_set_open_mode(hcam::int16, shtr_open_mode::int16)
    ccall((:pl_shtr_set_open_mode, :libpvcam), UInt16, (int16, int16), hcam, shtr_open_mode)
end

function pl_shtr_get_status(hcam::int16, shtr_status::Ref{int16})
    ccall((:pl_shtr_get_status, :libpvcam), UInt16, (int16, Ref{int16}), hcam, shtr_status)
end

function pl_exp_get_time_seq(hcam::int16, exp_time::Ref{uns16})
    ccall((:pl_exp_get_time_seq, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, exp_time)
end

function pl_exp_set_time_seq(hcam::int16, exp_time::uns16)
    ccall((:pl_exp_set_time_seq, :libpvcam), UInt16, (int16, uns16), hcam, exp_time)
end

function pl_exp_check_progress(hcam::int16, status::Ref{int16}, bytes_arrived::Ref{uns32})
    ccall((:pl_exp_check_progress, :libpvcam), UInt16, (int16, Ref{int16}, Ref{uns32}), hcam, status, bytes_arrived)
end

function pl_exp_set_cont_mode(hcam::int16, mode::int16)
    ccall((:pl_exp_set_cont_mode, :libpvcam), UInt16, (int16, int16), hcam, mode)
end

function pl_subsys_do_diag(hcam::int16, subsys_id::uns8, err_code::Ref{uns16})
    ccall((:pl_subsys_do_diag, :libpvcam), UInt16, (int16, uns8, Ref{uns16}), hcam, subsys_id, err_code)
end

function pl_subsys_get_id(hcam::int16, subsys_id::uns8, part_num::Ref{uns16}, revision::Ref{uns8})
    ccall((:pl_subsys_get_id, :libpvcam), UInt16, (int16, uns8, Ref{uns16}, Ref{uns8}), hcam, subsys_id, part_num, revision)
end

function pl_subsys_get_name(hcam::int16, subsys_id::uns8, subsys_name)
    ccall((:pl_subsys_get_name, :libpvcam), UInt16, (int16, uns8, Cstring), hcam, subsys_id, subsys_name)
end

function pl_exp_get_driver_buffer(hcam::int16, pixel_stream::Ref{Ptr{Cvoid}}, byte_cnt::Ref{uns32})
    ccall((:pl_exp_get_driver_buffer, :libpvcam), UInt16, (int16, Ref{Ptr{Cvoid}}, Ref{uns32}), hcam, pixel_stream, byte_cnt)
end

function pl_buf_init()
    ccall((:pl_buf_init, :libpvcam), UInt16, ())
end

function pl_buf_uninit()
    ccall((:pl_buf_uninit, :libpvcam), UInt16, ())
end

function pl_buf_alloc(hbuf::Ref{int16}, exp_total::int16, bit_depth::int16, rgn_total::int16, rgn_array::Ref{rgn_type})
    ccall((:pl_buf_alloc, :libpvcam), UInt16, (Ref{int16}, int16, int16, int16, Ref{rgn_type}), hbuf, exp_total, bit_depth, rgn_total, rgn_array)
end

function pl_buf_get_exp_date(hbuf::int16, exp_num::int16, year::Ref{int16}, month::Ref{uns8}, day::Ref{uns8}, hour::Ref{uns8}, min::Ref{uns8}, sec::Ref{uns8}, msec::Ref{uns16})
    ccall((:pl_buf_get_exp_date, :libpvcam), UInt16, (int16, int16, Ref{int16}, Ref{uns8}, Ref{uns8}, Ref{uns8}, Ref{uns8}, Ref{uns8}, Ref{uns16}), hbuf, exp_num, year, month, day, hour, min, sec, msec)
end

function pl_buf_set_exp_date(hbuf::int16, exp_num::int16, year::int16, month::uns8, day::uns8, hour::uns8, min::uns8, sec::uns8, msec::uns16)
    ccall((:pl_buf_set_exp_date, :libpvcam), UInt16, (int16, int16, int16, uns8, uns8, uns8, uns8, uns8, uns16), hbuf, exp_num, year, month, day, hour, min, sec, msec)
end

function pl_buf_get_exp_time(hbuf::int16, exp_num::int16, exp_msec::Ref{uns32})
    ccall((:pl_buf_get_exp_time, :libpvcam), UInt16, (int16, int16, Ref{uns32}), hbuf, exp_num, exp_msec)
end

function pl_buf_get_exp_total(hbuf::int16, total_exps::Ref{int16})
    ccall((:pl_buf_get_exp_total, :libpvcam), UInt16, (int16, Ref{int16}), hbuf, total_exps)
end

function pl_buf_get_img_bin(himg::int16, ibin::Ref{int16}, jbin::Ref{int16})
    ccall((:pl_buf_get_img_bin, :libpvcam), UInt16, (int16, Ref{int16}, Ref{int16}), himg, ibin, jbin)
end

function pl_buf_get_img_handle(hbuf::int16, exp_num::int16, img_num::int16, himg::Ref{int16})
    ccall((:pl_buf_get_img_handle, :libpvcam), UInt16, (int16, int16, int16, Ref{int16}), hbuf, exp_num, img_num, himg)
end

function pl_buf_get_img_ofs(himg::int16, s_ofs::Ref{int16}, p_ofs::Ref{int16})
    ccall((:pl_buf_get_img_ofs, :libpvcam), UInt16, (int16, Ref{int16}, Ref{int16}), himg, s_ofs, p_ofs)
end

function pl_buf_get_img_ptr(himg::int16, img_addr::Ref{Ptr{Cvoid}})
    ccall((:pl_buf_get_img_ptr, :libpvcam), UInt16, (int16, Ref{Ptr{Cvoid}}), himg, img_addr)
end

function pl_buf_get_img_size(himg::int16, x_size::Ref{int16}, y_size::Ref{int16})
    ccall((:pl_buf_get_img_size, :libpvcam), UInt16, (int16, Ref{int16}, Ref{int16}), himg, x_size, y_size)
end

function pl_buf_get_img_total(hbuf::int16, totl_imgs::Ref{int16})
    ccall((:pl_buf_get_img_total, :libpvcam), UInt16, (int16, Ref{int16}), hbuf, totl_imgs)
end

function pl_buf_get_size(hbuf::int16, buf_size::Ref{int32})
    ccall((:pl_buf_get_size, :libpvcam), UInt16, (int16, Ref{int32}), hbuf, buf_size)
end

function pl_buf_free(hbuf::int16)
    ccall((:pl_buf_free, :libpvcam), UInt16, (int16,), hbuf)
end

function pl_buf_get_bits(hbuf::int16, bit_depth::Ref{int16})
    ccall((:pl_buf_get_bits, :libpvcam), UInt16, (int16, Ref{int16}), hbuf, bit_depth)
end

function pl_exp_unravel(hcam::int16, exposure::uns16, pixel_stream::Ref{Cvoid}, rgn_total::uns16, rgn_array::Ref{rgn_type}, array_list::Ref{Ptr{uns16}})
    ccall((:pl_exp_unravel, :libpvcam), UInt16, (int16, uns16, Ref{Cvoid}, uns16, Ref{rgn_type}, Ref{Ptr{uns16}}), hcam, exposure, pixel_stream, rgn_total, rgn_array, array_list)
end

function pl_exp_wait_start_xfer(hcam::int16, tlimit::uns32)
    ccall((:pl_exp_wait_start_xfer, :libpvcam), UInt16, (int16, uns32), hcam, tlimit)
end

function pl_exp_wait_end_xfer(hcam::int16, tlimit::uns32)
    ccall((:pl_exp_wait_end_xfer, :libpvcam), UInt16, (int16, uns32), hcam, tlimit)
end

function pv_cam_get_ccs_mem(hcam::int16, size::Ref{uns16})
    ccall((:pv_cam_get_ccs_mem, :libpvcam), UInt16, (int16, Ref{uns16}), hcam, size)
end

function pv_cam_send_debug(hcam::int16, debug_str, reply_len::uns16, reply_str)
    ccall((:pv_cam_send_debug, :libpvcam), UInt16, (int16, Cstring, uns16, Cstring), hcam, debug_str, reply_len, reply_str)
end

function pv_cam_write_read(hcam::int16, c_class::uns8, write_bytes::uns16, write_array::Ref{uns8}, read_array::Ref{uns8})
    ccall((:pv_cam_write_read, :libpvcam), UInt16, (int16, uns8, uns16, Ref{uns8}, Ref{uns8}), hcam, c_class, write_bytes, write_array, read_array)
end

function pv_dd_active(hcam::int16, pixel_stream::Ref{Cvoid})
    ccall((:pv_dd_active, :libpvcam), UInt16, (int16, Ref{Cvoid}), hcam, pixel_stream)
end

function pv_exp_get_bytes(hcam::int16, exp_bytes::Ref{uns32})
    ccall((:pv_exp_get_bytes, :libpvcam), UInt16, (int16, Ref{uns32}), hcam, exp_bytes)
end

function pv_exp_get_script(hcam::int16, script_valid::Ref{UInt16})
    ccall((:pv_exp_get_script, :libpvcam), UInt16, (int16, Ref{UInt16}), hcam, script_valid)
end

function pv_exp_get_status(hcam::int16, status::Ref{int16}, byte_cnt::Ref{uns32}, frame_cnt::Ref{uns32})
    ccall((:pv_exp_get_status, :libpvcam), UInt16, (int16, Ref{int16}, Ref{uns32}, Ref{uns32}), hcam, status, byte_cnt, frame_cnt)
end

function pv_exp_set_bytes(hcam::int16, frame_count::uns32, seq_bytes::uns32, pixel_stream::Ref{Cvoid})
    ccall((:pv_exp_set_bytes, :libpvcam), UInt16, (int16, uns32, uns32, Ref{Cvoid}), hcam, frame_count, seq_bytes, pixel_stream)
end

function pv_exp_set_script(hcam::int16, script_valid::UInt16)
    ccall((:pv_exp_set_script, :libpvcam), UInt16, (int16, UInt16), hcam, script_valid)
end

function pv_set_error_code(omode::int16, err_code::int16)
    ccall((:pv_set_error_code, :libpvcam), UInt16, (int16, int16), omode, err_code)
end

function pv_cam_do_reads(hcam::int16)
    ccall((:pv_cam_do_reads, :libpvcam), UInt16, (int16,), hcam)
end

function pv_free(block::Ref{Cvoid}, heap::int16)
    ccall((:pv_free, :libpvcam), UInt16, (Ref{Cvoid}, int16), block, heap)
end

function pv_malloc(size::uns32, heap::int16)
    ccall((:pv_malloc, :libpvcam), Ptr{Cvoid}, (uns32, int16), size, heap)
end

function pv_realloc(block::Ref{Cvoid}, size::uns32, heap::int16)
    ccall((:pv_realloc, :libpvcam), Ptr{Cvoid}, (Ref{Cvoid}, uns32, int16), block, size, heap)
end

function pv_script_set_hook(pfn::Ref{pm_script_hook})
    ccall((:pv_script_set_hook, :libpvcam), UInt16, (Ref{pm_script_hook},), pfn)
end

function pv_ccd_get_accum_capable(hcam::int16, accum_capable::Ref{UInt16})
    ccall((:pv_ccd_get_accum_capable, :libpvcam), UInt16, (int16, Ref{UInt16}), hcam, accum_capable)
end

function pv_exp_get_frames(hcam::int16, exp_frames::Ref{uns32})
    ccall((:pv_exp_get_frames, :libpvcam), UInt16, (int16, Ref{uns32}), hcam, exp_frames)
end

function pv_exp_set_frames(hcam::int16, exp_frames::uns32)
    ccall((:pv_exp_set_frames, :libpvcam), UInt16, (int16, uns32), hcam, exp_frames)
end

function pv_exp_set_no_readout_timeout(hcam::int16)
    ccall((:pv_exp_set_no_readout_timeout, :libpvcam), UInt16, (int16,), hcam)
end

function pv_exp_reset_no_readout_timeout(hcam::int16)
    ccall((:pv_exp_reset_no_readout_timeout, :libpvcam), UInt16, (int16,), hcam)
end

function pm_cam_write_read(hcam::int16, c_class::uns8, write_bytes::uns16, write_array::Ref{uns8}, read_array::Ref{uns8})
    ccall((:pm_cam_write_read, :libpvcam), UInt16, (int16, uns8, uns16, Ref{uns8}, Ref{uns8}), hcam, c_class, write_bytes, write_array, read_array)
end

function pl_ddi_get_ver(ddi_version::Ref{uns16})
    ccall((:pl_ddi_get_ver, :libpvcam), UInt16, (Ref{uns16},), ddi_version)
end

function pl_cam_get_diags(hcam::int16)
    ccall((:pl_cam_get_diags, :libpvcam), UInt16, (int16,), hcam)
end

function pl_md_frame_decode(pDstFrame::Ref{md_frame}, pSrcBuf::Ref{Cvoid}, srcBufSize::uns32)
    ccall((:pl_md_frame_decode, :libpvcam), UInt16, (Ref{md_frame}, Ref{Cvoid}, uns32), pDstFrame, pSrcBuf, srcBufSize)
end

function pl_md_frame_recompose(pDstBuf::Ref{Cvoid}, offX::uns16, offY::uns16, dstWidth::uns16, dstHeight::uns16, pSrcFrame::Ref{md_frame})
    ccall((:pl_md_frame_recompose, :libpvcam), UInt16, (Ref{Cvoid}, uns16, uns16, uns16, uns16, Ref{md_frame}), pDstBuf, offX, offY, dstWidth, dstHeight, pSrcFrame)
end

function pl_md_create_frame_struct_cont(pFrame::Ref{Ptr{md_frame}}, roiCount::uns16)
    ccall((:pl_md_create_frame_struct_cont, :libpvcam), UInt16, (Ref{Ptr{md_frame}}, uns16), pFrame, roiCount)
end

function pl_md_create_frame_struct(pFrame::Ref{Ptr{md_frame}}, pSrcBuf::Ref{Cvoid}, srcBufSize::uns32)
    ccall((:pl_md_create_frame_struct, :libpvcam), UInt16, (Ref{Ptr{md_frame}}, Ref{Cvoid}, uns32), pFrame, pSrcBuf, srcBufSize)
end

function pl_md_release_frame_struct(pFrame::Ref{md_frame})
    ccall((:pl_md_release_frame_struct, :libpvcam), UInt16, (Ref{md_frame},), pFrame)
end

function pl_md_read_extended(pOutput::Ref{md_ext_item_collection}, pExtMdPtr::Ref{Cvoid}, extMdSize::uns32)
    ccall((:pl_md_read_extended, :libpvcam), UInt16, (Ref{md_ext_item_collection}, Ref{Cvoid}, uns32), pOutput, pExtMdPtr, extMdSize)
end
