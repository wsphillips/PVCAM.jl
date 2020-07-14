
#const PV_PTR_DECL = (*)
#const FALSE = PV_FAIL
#const TRUE = PV_OK
const rs_bool = UInt16
const int8 = UInt8
const uns8 = Cuchar
const int16 = Int16
const uns16 = UInt16
const int32 = Cint
const uns32 = UInt32
const flt32 = Cfloat
const flt64 = Cdouble
const ulong64 = Culonglong
const long64 = Clonglong

const void_ptr = Ptr{Cvoid}
const void_ptr_ptr = Ptr{Ptr{Cvoid}}
const rs_bool_ptr = Ptr{rs_bool}
const char_ptr = Cstring
const int8_ptr = Ptr{int8}
const uns8_ptr = Ptr{uns8}
const int16_ptr = Ptr{int16}
const uns16_ptr = Ptr{uns16}
const int32_ptr = Ptr{int32}
const uns32_ptr = Ptr{uns32}
const flt32_ptr = Ptr{flt32}
const flt64_ptr = Ptr{flt64}
const ulong64_ptr = Ptr{ulong64}
const long64_ptr = Ptr{long64}
const rs_bool_const_ptr = Ptr{rs_bool}
const char_const_ptr = Cstring
const int8_const_ptr = Ptr{int8}
const uns8_const_ptr = Ptr{uns8}
const int16_const_ptr = Ptr{int16}
const uns16_const_ptr = Ptr{uns16}
const int32_const_ptr = Ptr{int32}
const uns32_const_ptr = Ptr{uns32}
const flt32_const_ptr = Ptr{flt32}
const flt64_const_ptr = Ptr{flt64}
const ulong64_const_ptr = Ptr{ulong64}
const long64_const_ptr = Ptr{long64}

const PVCAM_LIB_VERSION_MAJOR = 2
const MAX_CAM = 16
const CAM_NAME_LEN = 32
const PARAM_NAME_LEN = 32
const ERROR_MSG_LEN = 255
const CCD_NAME_LEN = 17
const MAX_ALPHA_SER_NUM_LEN = 32
const MAX_PP_NAME_LEN = 32
const MAX_SYSTEM_NAME_LEN = 32
const MAX_VENDOR_NAME_LEN = 32
const MAX_PRODUCT_NAME_LEN = 32
const MAX_CAM_PART_NUM_LEN = 32
const MAX_GAIN_NAME_LEN = 32
const MAX_CAM_SYSTEMS_INFO_LEN = 1024
const PP_MAX_PARAMETERS_PER_FEATURE = 10
const PL_MD_FRAME_SIGNATURE = 5328208
const PL_MD_EXT_TAGS_MAX_SUPPORTED = 255

# MS16_BYTE ( two_byte_value ) ( ( uns8 ) ( ( ( uns16 ) ( two_byte_value ) >> 8 ) & 0xFF ) )
# LS16_BYTE ( two_byte_value ) ( ( uns8 ) ( ( ( uns16 ) ( two_byte_value ) >> 0 ) & 0xFF ) )
# MS32_BYTE ( four_byte_value ) ( ( uns8 ) ( ( ( uns32 ) ( four_byte_value ) >> 24 ) & 0xFF ) )
# MH32_BYTE ( four_byte_value ) ( ( uns8 ) ( ( ( uns32 ) ( four_byte_value ) >> 16 ) & 0xFF ) )
# ML32_BYTE ( four_byte_value ) ( ( uns8 ) ( ( ( uns32 ) ( four_byte_value ) >> 8 ) & 0xFF ) )
# LS32_BYTE ( four_byte_value ) ( ( uns8 ) ( ( ( uns32 ) ( four_byte_value ) >> 0 ) & 0xFF ) )
# VAL_UNS16 ( ms_byte , ls_byte ) ( ( ( uns16 ) ( ( uns8 ) ( ms_byte ) ) << 8 ) | ( ( uns16 ) ( ( uns8 ) ( ls_byte ) ) << 0 ) )
# VAL_UNS32 ( ms_byte , mh_byte , ml_byte , ls_byte ) ( ( ( uns32 ) ( ( uns8 ) ( ms_byte ) ) << 24 ) | ( ( uns32 ) ( ( uns8 ) ( mh_byte ) ) << 16 ) | ( ( uns32 ) ( ( uns8 ) ( ml_byte ) ) << 8 ) | ( ( uns32 ) ( ( uns8 ) ( ls_byte ) ) << 0 ) )
# VAL_INT64 ( b0 , b1 , b2 , b3 , b4 , b5 , b6 , b7 ) ( ( ( long64 ) ( ( uns8 ) ( b0 ) ) << 56 ) | ( ( long64 ) ( ( uns8 ) ( b1 ) ) << 48 ) | ( ( long64 ) ( ( uns8 ) ( b2 ) ) << 40 ) | ( ( long64 ) ( ( uns8 ) ( b3 ) ) << 32 ) | ( ( long64 ) ( ( uns8 ) ( b4 ) ) << 24 ) | ( ( long64 ) ( ( uns8 ) ( b5 ) ) << 16 ) | ( ( long64 ) ( ( uns8 ) ( b6 ) ) << 8 ) | ( ( long64 ) ( ( uns8 ) ( b7 ) ) << 0 ) )

const TYPE_INT16 = 1
const TYPE_INT32 = 2
const TYPE_FLT64 = 4
const TYPE_UNS8 = 5
const TYPE_UNS16 = 6
const TYPE_UNS32 = 7
const TYPE_UNS64 = 8
const TYPE_ENUM = 9
const TYPE_BOOLEAN = 11
const TYPE_INT8 = 12
const TYPE_CHAR_PTR = 13
const TYPE_VOID_PTR = 14
const TYPE_VOID_PTR_PTR = 15
const TYPE_INT64 = 16
const TYPE_SMART_STREAM_TYPE = 17
const TYPE_SMART_STREAM_TYPE_PTR = 18
const TYPE_FLT32 = 19
const CLASS0 = 0
const CLASS2 = 2
const CLASS3 = 3

# PARAM_DD_INFO_LENGTH ( ( CLASS0 << 16 ) + ( TYPE_INT16 << 24 ) + 1 )
# PARAM_DD_VERSION ( ( CLASS0 << 16 ) + ( TYPE_UNS16 << 24 ) + 2 )
# PARAM_DD_RETRIES ( ( CLASS0 << 16 ) + ( TYPE_UNS16 << 24 ) + 3 )
# PARAM_DD_TIMEOUT ( ( CLASS0 << 16 ) + ( TYPE_UNS16 << 24 ) + 4 )
# PARAM_DD_INFO ( ( CLASS0 << 16 ) + ( TYPE_CHAR_PTR << 24 ) + 5 )
# PARAM_CAM_INTERFACE_TYPE ( ( CLASS0 << 16 ) + ( TYPE_ENUM << 24 ) + 10 )
# PARAM_CAM_INTERFACE_MODE ( ( CLASS0 << 16 ) + ( TYPE_ENUM << 24 ) + 11 )
# PARAM_ADC_OFFSET ( ( CLASS2 << 16 ) + ( TYPE_INT16 << 24 ) + 195 )
# PARAM_CHIP_NAME ( ( CLASS2 << 16 ) + ( TYPE_CHAR_PTR << 24 ) + 129 )
# PARAM_SYSTEM_NAME ( ( CLASS2 << 16 ) + ( TYPE_CHAR_PTR << 24 ) + 130 )
# PARAM_VENDOR_NAME ( ( CLASS2 << 16 ) + ( TYPE_CHAR_PTR << 24 ) + 131 )
# PARAM_PRODUCT_NAME ( ( CLASS2 << 16 ) + ( TYPE_CHAR_PTR << 24 ) + 132 )
# PARAM_CAMERA_PART_NUMBER ( ( CLASS2 << 16 ) + ( TYPE_CHAR_PTR << 24 ) + 133 )
# PARAM_COOLING_MODE ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 214 )
# PARAM_PREAMP_DELAY ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 502 )
# PARAM_COLOR_MODE ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 504 )
# PARAM_MPP_CAPABLE ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 224 )
# PARAM_PREAMP_OFF_CONTROL ( ( CLASS2 << 16 ) + ( TYPE_UNS32 << 24 ) + 507 )
# PARAM_PREMASK ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 53 )
# PARAM_PRESCAN ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 55 )
# PARAM_POSTMASK ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 54 )
# PARAM_POSTSCAN ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 56 )
# PARAM_PIX_PAR_DIST ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 500 )
# PARAM_PIX_PAR_SIZE ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 63 )
# PARAM_PIX_SER_DIST ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 501 )
# PARAM_PIX_SER_SIZE ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 62 )
# PARAM_SUMMING_WELL ( ( CLASS2 << 16 ) + ( TYPE_BOOLEAN << 24 ) + 505 )
# PARAM_FWELL_CAPACITY ( ( CLASS2 << 16 ) + ( TYPE_UNS32 << 24 ) + 506 )
# PARAM_PAR_SIZE ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 57 )
# PARAM_SER_SIZE ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 58 )
# PARAM_ACCUM_CAPABLE ( ( CLASS2 << 16 ) + ( TYPE_BOOLEAN << 24 ) + 538 )
# PARAM_FLASH_DWNLD_CAPABLE ( ( CLASS2 << 16 ) + ( TYPE_BOOLEAN << 24 ) + 539 )
# PARAM_READOUT_TIME ( ( CLASS2 << 16 ) + ( TYPE_FLT64 << 24 ) + 179 )
# PARAM_CLEARING_TIME ( ( CLASS2 << 16 ) + ( TYPE_INT64 << 24 ) + 180 )
# PARAM_POST_TRIGGER_DELAY ( ( CLASS2 << 16 ) + ( TYPE_INT64 << 24 ) + 181 )
# PARAM_PRE_TRIGGER_DELAY ( ( CLASS2 << 16 ) + ( TYPE_INT64 << 24 ) + 182 )
# PARAM_CLEAR_CYCLES ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 97 )
# PARAM_CLEAR_MODE ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 523 )
# PARAM_FRAME_CAPABLE ( ( CLASS2 << 16 ) + ( TYPE_BOOLEAN << 24 ) + 509 )
# PARAM_PMODE ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 524 )
# PARAM_TEMP ( ( CLASS2 << 16 ) + ( TYPE_INT16 << 24 ) + 525 )
# PARAM_TEMP_SETPOINT ( ( CLASS2 << 16 ) + ( TYPE_INT16 << 24 ) + 526 )
# PARAM_CAM_FW_VERSION ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 532 )
# PARAM_HEAD_SER_NUM_ALPHA ( ( CLASS2 << 16 ) + ( TYPE_CHAR_PTR << 24 ) + 533 )
# PARAM_PCI_FW_VERSION ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 534 )
# PARAM_FAN_SPEED_SETPOINT ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 710 )
# PARAM_CAM_SYSTEMS_INFO ( ( CLASS2 << 16 ) + ( TYPE_CHAR_PTR << 24 ) + 536 )
# PARAM_EXPOSURE_MODE ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 535 )
# PARAM_EXPOSE_OUT_MODE ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 560 )
# PARAM_BIT_DEPTH ( ( CLASS2 << 16 ) + ( TYPE_INT16 << 24 ) + 511 )
# PARAM_IMAGE_FORMAT ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 248 )
# PARAM_IMAGE_COMPRESSION ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 249 )
# PARAM_SCAN_MODE ( ( CLASS3 << 16 ) + ( TYPE_ENUM << 24 ) + 250 )
# PARAM_SCAN_DIRECTION ( ( CLASS3 << 16 ) + ( TYPE_ENUM << 24 ) + 251 )
# PARAM_SCAN_DIRECTION_RESET ( ( CLASS3 << 16 ) + ( TYPE_BOOLEAN << 24 ) + 252 )
# PARAM_SCAN_LINE_DELAY ( ( CLASS3 << 16 ) + ( TYPE_UNS16 << 24 ) + 253 )
# PARAM_SCAN_LINE_TIME ( ( CLASS3 << 16 ) + ( TYPE_INT64 << 24 ) + 254 )
# PARAM_SCAN_WIDTH ( ( CLASS3 << 16 ) + ( TYPE_UNS16 << 24 ) + 255 )
# PARAM_GAIN_INDEX ( ( CLASS2 << 16 ) + ( TYPE_INT16 << 24 ) + 512 )
# PARAM_SPDTAB_INDEX ( ( CLASS2 << 16 ) + ( TYPE_INT16 << 24 ) + 513 )
# PARAM_GAIN_NAME ( ( CLASS2 << 16 ) + ( TYPE_CHAR_PTR << 24 ) + 514 )
# PARAM_READOUT_PORT ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 247 )
# PARAM_PIX_TIME ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 516 )
# PARAM_SHTR_CLOSE_DELAY ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 519 )
# PARAM_SHTR_OPEN_DELAY ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 520 )
# PARAM_SHTR_OPEN_MODE ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 521 )
# PARAM_SHTR_STATUS ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 522 )
# PARAM_IO_ADDR ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 527 )
# PARAM_IO_TYPE ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 528 )
# PARAM_IO_DIRECTION ( ( CLASS2 << 16 ) + ( TYPE_ENUM << 24 ) + 529 )
# PARAM_IO_STATE ( ( CLASS2 << 16 ) + ( TYPE_FLT64 << 24 ) + 530 )
# PARAM_IO_BITDEPTH ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 531 )
# PARAM_GAIN_MULT_FACTOR ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 537 )
# PARAM_GAIN_MULT_ENABLE ( ( CLASS2 << 16 ) + ( TYPE_BOOLEAN << 24 ) + 541 )
# PARAM_PP_FEAT_NAME ( ( CLASS2 << 16 ) + ( TYPE_CHAR_PTR << 24 ) + 542 )
# PARAM_PP_INDEX ( ( CLASS2 << 16 ) + ( TYPE_INT16 << 24 ) + 543 )
# PARAM_ACTUAL_GAIN ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 544 )
# PARAM_PP_PARAM_INDEX ( ( CLASS2 << 16 ) + ( TYPE_INT16 << 24 ) + 545 )
# PARAM_PP_PARAM_NAME ( ( CLASS2 << 16 ) + ( TYPE_CHAR_PTR << 24 ) + 546 )
# PARAM_PP_PARAM ( ( CLASS2 << 16 ) + ( TYPE_UNS32 << 24 ) + 547 )
# PARAM_READ_NOISE ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 548 )
# PARAM_PP_FEAT_ID ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 549 )
# PARAM_PP_PARAM_ID ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 550 )
# PARAM_SMART_STREAM_MODE_ENABLED ( ( CLASS2 << 16 ) + ( TYPE_BOOLEAN << 24 ) + 700 )
# PARAM_SMART_STREAM_MODE ( ( CLASS2 << 16 ) + ( TYPE_UNS16 << 24 ) + 701 )
# PARAM_SMART_STREAM_EXP_PARAMS ( ( CLASS2 << 16 ) + ( TYPE_VOID_PTR << 24 ) + 702 )
# PARAM_SMART_STREAM_DLY_PARAMS ( ( CLASS2 << 16 ) + ( TYPE_VOID_PTR << 24 ) + 703 )
# PARAM_EXP_TIME ( ( CLASS3 << 16 ) + ( TYPE_UNS16 << 24 ) + 1 )
# PARAM_EXP_RES ( ( CLASS3 << 16 ) + ( TYPE_ENUM << 24 ) + 2 )
# PARAM_EXP_RES_INDEX ( ( CLASS3 << 16 ) + ( TYPE_UNS16 << 24 ) + 4 )
# PARAM_EXPOSURE_TIME ( ( CLASS3 << 16 ) + ( TYPE_UNS64 << 24 ) + 8 )
# PARAM_BOF_EOF_ENABLE ( ( CLASS3 << 16 ) + ( TYPE_ENUM << 24 ) + 5 )
# PARAM_BOF_EOF_COUNT ( ( CLASS3 << 16 ) + ( TYPE_UNS32 << 24 ) + 6 )
# PARAM_BOF_EOF_CLR ( ( CLASS3 << 16 ) + ( TYPE_BOOLEAN << 24 ) + 7 )
# PARAM_CIRC_BUFFER ( ( CLASS3 << 16 ) + ( TYPE_BOOLEAN << 24 ) + 299 )
# PARAM_FRAME_BUFFER_SIZE ( ( CLASS3 << 16 ) + ( TYPE_UNS64 << 24 ) + 300 )
# PARAM_BINNING_SER ( ( CLASS3 << 16 ) + ( TYPE_ENUM << 24 ) + 165 )
# PARAM_BINNING_PAR ( ( CLASS3 << 16 ) + ( TYPE_ENUM << 24 ) + 166 )
# PARAM_METADATA_ENABLED ( ( CLASS3 << 16 ) + ( TYPE_BOOLEAN << 24 ) + 168 )
# PARAM_ROI_COUNT ( ( CLASS3 << 16 ) + ( TYPE_UNS16 << 24 ) + 169 )
# PARAM_CENTROIDS_ENABLED ( ( CLASS3 << 16 ) + ( TYPE_BOOLEAN << 24 ) + 170 )
# PARAM_CENTROIDS_RADIUS ( ( CLASS3 << 16 ) + ( TYPE_UNS16 << 24 ) + 171 )
# PARAM_CENTROIDS_COUNT ( ( CLASS3 << 16 ) + ( TYPE_UNS16 << 24 ) + 172 )
# PARAM_CENTROIDS_MODE ( ( CLASS3 << 16 ) + ( TYPE_ENUM << 24 ) + 173 )
# PARAM_CENTROIDS_BG_COUNT ( ( CLASS3 << 16 ) + ( TYPE_ENUM << 24 ) + 174 )
# PARAM_CENTROIDS_THRESHOLD ( ( CLASS3 << 16 ) + ( TYPE_UNS32 << 24 ) + 175 )
# PARAM_TRIGTAB_SIGNAL ( ( CLASS3 << 16 ) + ( TYPE_ENUM << 24 ) + 180 )
# PARAM_LAST_MUXED_SIGNAL ( ( CLASS3 << 16 ) + ( TYPE_UNS8 << 24 ) + 181 )
# PARAM_FRAME_DELIVERY_MODE ( ( CLASS3 << 16 ) + ( TYPE_ENUM << 24 ) + 400 )

#const PVCAM_FRAME_INFO_GUID = _TAG_PVCAM_FRAME_INFO_GUID
#const FRAME_INFO = _TAG_FRAME_INFO
#

# temporary placeholder for script hook type (looks like a callback function
# pointer)
pm_script_hook = Ptr{Cvoid}

struct PVCAM_FRAME_INFO_GUID
    f1::UInt32
    f2::UInt16
    f3::UInt16
    f4::NTuple{8, UInt8}
end

struct FRAME_INFO
    FrameInfoGUID::PVCAM_FRAME_INFO_GUID
    hCam::Int16
    FrameNr::Int32
    TimeStampe::long64
    ReadouTime::Int32
    TimeStampBOF::long64
end

@cenum PL_OPEN_MODES::UInt32 begin
    OPEN_EXCLUSIVE = 0
end

@cenum PL_COOL_MODES::UInt32 begin
    NORMAL_COOL = 0
    CRYO_COOL = 1
    NO_COOL = 2
end

@cenum PL_MPP_MODES::UInt32 begin
    MPP_UNKNOWN = 0
    MPP_ALWAYS_OFF = 1
    MPP_ALWAYS_ON = 2
    MPP_SELECTABLE = 3
end

@cenum PL_SHTR_MODES::UInt32 begin
    SHTR_FAULT = 0
    SHTR_OPENING = 1
    SHTR_OPEN = 2
    SHTR_CLOSING = 3
    SHTR_CLOSED = 4
    SHTR_UNKNOWN = 5
end

@cenum PL_PMODES::UInt32 begin
    PMODE_NORMAL = 0
    PMODE_FT = 1
    PMODE_MPP = 2
    PMODE_FT_MPP = 3
    PMODE_ALT_NORMAL = 4
    PMODE_ALT_FT = 5
    PMODE_ALT_MPP = 6
    PMODE_ALT_FT_MPP = 7
end

@cenum PL_COLOR_MODES::UInt32 begin
    COLOR_NONE = 0
    COLOR_RESERVED = 1
    COLOR_RGGB = 2
    COLOR_GRBG = 3
    COLOR_GBRG = 4
    COLOR_BGGR = 5
end

@cenum PL_IMAGE_FORMATS::UInt32 begin
    PL_IMAGE_FORMAT_MONO16 = 0
    PL_IMAGE_FORMAT_BAYER16 = 1
    PL_IMAGE_FORMAT_MONO8 = 2
    PL_IMAGE_FORMAT_BAYER8 = 3
    PL_IMAGE_FORMAT_MONO24 = 4
    PL_IMAGE_FORMAT_BAYER24 = 5
    PL_IMAGE_FORMAT_RGB24 = 6
    PL_IMAGE_FORMAT_RGB48 = 7
    PL_IMAGE_FORMAT_RGB72 = 8
end

@cenum PL_IMAGE_COMPRESSIONS::UInt32 begin
    PL_IMAGE_COMPRESSION_NONE = 0
    PL_IMAGE_COMPRESSION_RESERVED8 = 8
    PL_IMAGE_COMPRESSION_BITPACK9 = 9
    PL_IMAGE_COMPRESSION_BITPACK10 = 10
    PL_IMAGE_COMPRESSION_BITPACK11 = 11
    PL_IMAGE_COMPRESSION_BITPACK12 = 12
    PL_IMAGE_COMPRESSION_BITPACK13 = 13
    PL_IMAGE_COMPRESSION_BITPACK14 = 14
    PL_IMAGE_COMPRESSION_BITPACK15 = 15
    PL_IMAGE_COMPRESSION_RESERVED16 = 16
    PL_IMAGE_COMPRESSION_BITPACK17 = 17
    PL_IMAGE_COMPRESSION_BITPACK18 = 18
    PL_IMAGE_COMPRESSION_RESERVED24 = 24
    PL_IMAGE_COMPRESSION_RESERVED32 = 32
end

@cenum PL_PARAM_ATTRIBUTES::UInt32 begin
    ATTR_CURRENT = 0
    ATTR_COUNT = 1
    ATTR_TYPE = 2
    ATTR_MIN = 3
    ATTR_MAX = 4
    ATTR_DEFAULT = 5
    ATTR_INCREMENT = 6
    ATTR_ACCESS = 7
    ATTR_AVAIL = 8
end

@cenum PL_PARAM_ACCESS::UInt32 begin
    ACC_READ_ONLY = 1
    ACC_READ_WRITE = 2
    ACC_EXIST_CHECK_ONLY = 3
    ACC_WRITE_ONLY = 4
end

@cenum PL_IO_TYPE::UInt32 begin
    IO_TYPE_TTL = 0
    IO_TYPE_DAC = 1
end

@cenum PL_IO_DIRECTION::UInt32 begin
    IO_DIR_INPUT = 0
    IO_DIR_OUTPUT = 1
    IO_DIR_INPUT_OUTPUT = 2
end

@cenum PL_READOUT_PORTS::UInt32 begin
    READOUT_PORT_0 = 0
    READOUT_PORT_1 = 1
end

@cenum PL_CLEAR_MODES::UInt32 begin
    CLEAR_NEVER = 0
    CLEAR_PRE_EXPOSURE = 1
    CLEAR_PRE_SEQUENCE = 2
    CLEAR_POST_SEQUENCE = 3
    CLEAR_PRE_POST_SEQUENCE = 4
    CLEAR_PRE_EXPOSURE_POST_SEQ = 5
    MAX_CLEAR_MODE = 6
end

@cenum PL_SHTR_OPEN_MODES::UInt32 begin
    OPEN_NEVER = 0
    OPEN_PRE_EXPOSURE = 1
    OPEN_PRE_SEQUENCE = 2
    OPEN_PRE_TRIGGER = 3
    OPEN_NO_CHANGE = 4
end

@cenum PL_EXPOSURE_MODES::UInt32 begin
    TIMED_MODE = 0
    STROBED_MODE = 1
    BULB_MODE = 2
    TRIGGER_FIRST_MODE = 3
    FLASH_MODE = 4
    VARIABLE_TIMED_MODE = 5
    INT_STROBE_MODE = 6
    MAX_EXPOSE_MODE = 7
    EXT_TRIG_INTERNAL = 1792
    EXT_TRIG_TRIG_FIRST = 2048
    EXT_TRIG_EDGE_RISING = 2304
end

@cenum PL_EXPOSE_OUT_MODES::UInt32 begin
    EXPOSE_OUT_FIRST_ROW = 0
    EXPOSE_OUT_ALL_ROWS = 1
    EXPOSE_OUT_ANY_ROW = 2
    EXPOSE_OUT_ROLLING_SHUTTER = 3
    MAX_EXPOSE_OUT_MODE = 4
end

@cenum PL_FAN_SPEEDS::UInt32 begin
    FAN_SPEED_HIGH = 0
    FAN_SPEED_MEDIUM = 1
    FAN_SPEED_LOW = 2
    FAN_SPEED_OFF = 3
end

@cenum PL_TRIGTAB_SIGNALS::UInt32 begin
    PL_TRIGTAB_SIGNAL_EXPOSE_OUT = 0
end

@cenum PL_FRAME_DELIVERY_MODES::UInt32 begin
    PL_FRAME_DELIVERY_MODE_MAX_FPS = 0
    PL_FRAME_DELIVERY_MODE_CONSTANT_INTERVALS = 1
end

@cenum PL_CAM_INTERFACE_TYPES::UInt32 begin
    PL_CAM_IFC_TYPE_UNKNOWN = 0
    PL_CAM_IFC_TYPE_1394 = 256
    PL_CAM_IFC_TYPE_1394_A = 257
    PL_CAM_IFC_TYPE_1394_B = 258
    PL_CAM_IFC_TYPE_USB = 512
    PL_CAM_IFC_TYPE_USB_1_1 = 513
    PL_CAM_IFC_TYPE_USB_2_0 = 514
    PL_CAM_IFC_TYPE_USB_3_0 = 515
    PL_CAM_IFC_TYPE_USB_3_1 = 516
    PL_CAM_IFC_TYPE_PCI = 1024
    PL_CAM_IFC_TYPE_PCI_LVDS = 1025
    PL_CAM_IFC_TYPE_PCIE = 2048
    PL_CAM_IFC_TYPE_PCIE_LVDS = 2049
    PL_CAM_IFC_TYPE_PCIE_X1 = 2050
    PL_CAM_IFC_TYPE_PCIE_X4 = 2051
    PL_CAM_IFC_TYPE_VIRTUAL = 4096
    PL_CAM_IFC_TYPE_ETHERNET = 8192
end

@cenum PL_CAM_INTERFACE_MODES::UInt32 begin
    PL_CAM_IFC_MODE_UNSUPPORTED = 0
    PL_CAM_IFC_MODE_CONTROL_ONLY = 1
    PL_CAM_IFC_MODE_IMAGING = 2
end

@cenum PL_CENTROIDS_MODES::UInt32 begin
    PL_CENTROIDS_MODE_LOCATE = 0
    PL_CENTROIDS_MODE_TRACK = 1
    PL_CENTROIDS_MODE_BLOB = 2
end

@cenum PL_SCAN_MODES::UInt32 begin
    PL_SCAN_MODE_AUTO = 0
    PL_SCAN_MODE_PROGRAMMABLE_LINE_DELAY = 1
    PL_SCAN_MODE_PROGRAMMABLE_SCAN_WIDTH = 2
end

@cenum PL_SCAN_DIRECTIONS::UInt32 begin
    PL_SCAN_DIRECTION_DOWN = 0
    PL_SCAN_DIRECTION_UP = 1
    PL_SCAN_DIRECTION_DOWN_UP = 2
end

@cenum PP_FEATURE_IDS::UInt32 begin
    PP_FEATURE_RING_FUNCTION = 0
    PP_FEATURE_BIAS = 1
    PP_FEATURE_BERT = 2
    PP_FEATURE_QUANT_VIEW = 3
    PP_FEATURE_BLACK_LOCK = 4
    PP_FEATURE_TOP_LOCK = 5
    PP_FEATURE_VARI_BIT = 6
    PP_FEATURE_RESERVED = 7
    PP_FEATURE_DESPECKLE_BRIGHT_HIGH = 8
    PP_FEATURE_DESPECKLE_DARK_LOW = 9
    PP_FEATURE_DEFECTIVE_PIXEL_CORRECTION = 10
    PP_FEATURE_DYNAMIC_DARK_FRAME_CORRECTION = 11
    PP_FEATURE_HIGH_DYNAMIC_RANGE = 12
    PP_FEATURE_DESPECKLE_BRIGHT_LOW = 13
    PP_FEATURE_DENOISING = 14
    PP_FEATURE_DESPECKLE_DARK_HIGH = 15
    PP_FEATURE_ENHANCED_DYNAMIC_RANGE = 16
    PP_FEATURE_MAX = 17
end

@cenum PP_PARAMETER_IDS::UInt32 begin
    PP_PARAMETER_RF_FUNCTION = 0
    PP_FEATURE_BIAS_ENABLED = 10
    PP_FEATURE_BIAS_LEVEL = 11
    PP_FEATURE_BERT_ENABLED = 20
    PP_FEATURE_BERT_THRESHOLD = 21
    PP_FEATURE_QUANT_VIEW_ENABLED = 30
    PP_FEATURE_QUANT_VIEW_E = 31
    PP_FEATURE_BLACK_LOCK_ENABLED = 40
    PP_FEATURE_BLACK_LOCK_BLACK_CLIP = 41
    PP_FEATURE_TOP_LOCK_ENABLED = 50
    PP_FEATURE_TOP_LOCK_WHITE_CLIP = 51
    PP_FEATURE_VARI_BIT_ENABLED = 60
    PP_FEATURE_VARI_BIT_BIT_DEPTH = 61
    PP_FEATURE_DESPECKLE_BRIGHT_HIGH_ENABLED = 80
    PP_FEATURE_DESPECKLE_BRIGHT_HIGH_THRESHOLD = 81
    PP_FEATURE_DESPECKLE_BRIGHT_HIGH_MIN_ADU_AFFECTED = 82
    PP_FEATURE_DESPECKLE_DARK_LOW_ENABLED = 90
    PP_FEATURE_DESPECKLE_DARK_LOW_THRESHOLD = 91
    PP_FEATURE_DESPECKLE_DARK_LOW_MAX_ADU_AFFECTED = 92
    PP_FEATURE_DEFECTIVE_PIXEL_CORRECTION_ENABLED = 100
    PP_FEATURE_DYNAMIC_DARK_FRAME_CORRECTION_ENABLED = 110
    PP_FEATURE_HIGH_DYNAMIC_RANGE_ENABLED = 120
    PP_FEATURE_DESPECKLE_BRIGHT_LOW_ENABLED = 130
    PP_FEATURE_DESPECKLE_BRIGHT_LOW_THRESHOLD = 131
    PP_FEATURE_DESPECKLE_BRIGHT_LOW_MAX_ADU_AFFECTED = 132
    PP_FEATURE_DENOISING_ENABLED = 140
    PP_FEATURE_DENOISING_NO_OF_ITERATIONS = 141
    PP_FEATURE_DENOISING_GAIN = 142
    PP_FEATURE_DENOISING_OFFSET = 143
    PP_FEATURE_DENOISING_LAMBDA = 144
    PP_FEATURE_DESPECKLE_DARK_HIGH_ENABLED = 150
    PP_FEATURE_DESPECKLE_DARK_HIGH_THRESHOLD = 151
    PP_FEATURE_DESPECKLE_DARK_HIGH_MIN_ADU_AFFECTED = 152
    PP_FEATURE_ENHANCED_DYNAMIC_RANGE_ENABLED = 160
    PP_PARAMETER_ID_MAX = 161
end


struct smart_stream_type
    entries::uns16
    params::Ptr{uns32}
end

@cenum PL_SMT_MODES::UInt32 begin
    SMTMODE_ARBITRARY_ALL = 0
    SMTMODE_MAX = 1
end

@cenum PL_IMAGE_STATUSES::UInt32 begin
    READOUT_NOT_ACTIVE = 0
    EXPOSURE_IN_PROGRESS = 1
    READOUT_IN_PROGRESS = 2
    READOUT_COMPLETE = 3
    FRAME_AVAILABLE = 3
    READOUT_FAILED = 4
    ACQUISITION_IN_PROGRESS = 5
    MAX_CAMERA_STATUS = 6
end

@cenum PL_CCS_ABORT_MODES::UInt32 begin
    CCS_NO_CHANGE = 0
    CCS_HALT = 1
    CCS_HALT_CLOSE_SHTR = 2
    CCS_CLEAR = 3
    CCS_CLEAR_CLOSE_SHTR = 4
    CCS_OPEN_SHTR = 5
    CCS_CLEAR_OPEN_SHTR = 6
end

@cenum PL_IRQ_MODES::UInt32 begin
    NO_FRAME_IRQS = 0
    BEGIN_FRAME_IRQS = 1
    END_FRAME_IRQS = 2
    BEGIN_END_FRAME_IRQS = 3
end

@cenum PL_CIRC_MODES::UInt32 begin
    CIRC_NONE = 0
    CIRC_OVERWRITE = 1
    CIRC_NO_OVERWRITE = 2
end

@cenum PL_EXP_RES_MODES::UInt32 begin
    EXP_RES_ONE_MILLISEC = 0
    EXP_RES_ONE_MICROSEC = 1
    EXP_RES_ONE_SEC = 2
end

@cenum PL_SRC_MODES::UInt32 begin
    SCR_PRE_OPEN_SHTR = 0
    SCR_POST_OPEN_SHTR = 1
    SCR_PRE_FLASH = 2
    SCR_POST_FLASH = 3
    SCR_PRE_INTEGRATE = 4
    SCR_POST_INTEGRATE = 5
    SCR_PRE_READOUT = 6
    SCR_POST_READOUT = 7
    SCR_PRE_CLOSE_SHTR = 8
    SCR_POST_CLOSE_SHTR = 9
end

@cenum PL_CALLBACK_EVENT::UInt32 begin
    PL_CALLBACK_BOF = 0
    PL_CALLBACK_EOF = 1
    PL_CALLBACK_CHECK_CAMS = 2
    PL_CALLBACK_CAM_REMOVED = 3
    PL_CALLBACK_CAM_RESUMED = 4
    PL_CALLBACK_MAX = 5
end


struct rgn_type
    s1::uns16
    s2::uns16
    sbin::uns16
    p1::uns16
    p2::uns16
    pbin::uns16
end

struct io_struct
    io_port::uns16
    io_type::uns32
    state::flt64
    next::Ptr{io_struct}
end

const io_entry = io_struct

struct io_list
    pre_open::io_entry
    post_open::io_entry
    pre_flash::io_entry
    post_flash::io_entry
    pre_integrate::io_entry
    post_integrate::io_entry
    pre_readout::io_entry
    post_readout::io_entry
    pre_close::io_entry
    post_close::io_entry
end

struct active_camera_type
    shutter_close_delay::uns16
    shutter_open_delay::uns16
    rows::uns16
    cols::uns16
    prescan::uns16
    postscan::uns16
    premask::uns16
    postmask::uns16
    preflash::uns16
    clear_count::uns16
    preamp_delay::uns16
    mpp_selectable::rs_bool
    frame_selectable::rs_bool
    do_clear::int16
    open_shutter::int16
    mpp_mode::rs_bool
    frame_transfer::rs_bool
    alt_mode::rs_bool
    exp_res::uns32
    io_hdr::Ptr{io_list}
end

@cenum PL_MD_FRAME_FLAGS::UInt32 begin
    PL_MD_FRAME_FLAG_ROI_TS_SUPPORTED = 1
    PL_MD_FRAME_FLAG_UNUSED_2 = 2
    PL_MD_FRAME_FLAG_UNUSED_3 = 4
    PL_MD_FRAME_FLAG_UNUSED_4 = 16
    PL_MD_FRAME_FLAG_UNUSED_5 = 32
    PL_MD_FRAME_FLAG_UNUSED_6 = 64
    PL_MD_FRAME_FLAG_UNUSED_7 = 128
end

@cenum PL_MD_ROI_FLAGS::UInt32 begin
    PL_MD_ROI_FLAG_INVALID = 1
    PL_MD_ROI_FLAG_HEADER_ONLY = 2
    PL_MD_ROI_FLAG_UNUSED_3 = 4
    PL_MD_ROI_FLAG_UNUSED_4 = 16
    PL_MD_ROI_FLAG_UNUSED_5 = 32
    PL_MD_ROI_FLAG_UNUSED_6 = 64
    PL_MD_ROI_FLAG_UNUSED_7 = 128
end


struct md_frame_header
    signature::uns32
    version::uns8
    frameNr::uns32
    roiCount::uns16
    timestampBOF::uns32
    timestampEOF::uns32
    timestampResNs::uns32
    exposureTime::uns32
    exposureTimeResNs::uns32
    roiTimestampResNs::uns32
    bitDepth::uns8
    colorMask::uns8
    flags::uns8
    extendedMdSize::uns16
    imageFormat::uns8
    imageCompression::uns8
    _reserved::NTuple{6, uns8}
end

struct md_frame_roi_header
    roiNr::uns16
    timestampBOR::uns32
    timestampEOR::uns32
    roi::rgn_type
    flags::uns8
    extendedMdSize::uns16
    roiDataSize::uns32
    _reserved::NTuple{3, uns8}
end

@cenum PL_MD_EXT_TAGS::UInt32 begin
    PL_MD_EXT_TAG_PARTICLE_ID = 0
    PL_MD_EXT_TAG_PARTICLE_M0 = 1
    PL_MD_EXT_TAG_PARTICLE_M2 = 2
    PL_MD_EXT_TAG_MAX = 3
end


struct md_ext_item_info
    tag::PL_MD_EXT_TAGS
    type::uns16
    size::uns16
    name::Cstring
end

struct md_ext_item
    tagInfo::Ptr{md_ext_item_info}
    value::Ptr{Cvoid}
end

struct md_ext_item_collection
    list::NTuple{255, md_ext_item}
    map::NTuple{255, Ptr{md_ext_item}}
    count::uns16
end

struct md_frame_roi
    header::Ptr{md_frame_roi_header}
    data::Ptr{Cvoid}
    dataSize::uns32
    extMdData::Ptr{Cvoid}
    extMdDataSize::uns16
end

struct md_frame
    header::Ptr{md_frame_header}
    extMdData::Ptr{Cvoid}
    extMdDataSize::uns16
    impliedRoi::rgn_type
    roiArray::Ptr{md_frame_roi}
    roiCapacity::uns16
    roiCount::uns16
end

const PPVCAM_FRAME_INFO_GUID = Ptr{PVCAM_FRAME_INFO_GUID}
const PFRAME_INFO = Ptr{FRAME_INFO}
const smart_stream_type_ptr = Ptr{smart_stream_type}
const rgn_ptr = Ptr{rgn_type}
const rgn_const_ptr = Ptr{rgn_type}
const io_entry_ptr = Ptr{io_entry}
const io_list_ptr = Ptr{io_list}
const io_list_ptr_ptr = Ptr{Ptr{io_list}}
const active_camera_ptr = Ptr{active_camera_type}

# Skipping Typedef: CXType_FunctionProto pm_script_hook

const PL_CALLBACK_SIG_LEGACY = Ptr{Cvoid}
const PL_CALLBACK_SIG_EX = Ptr{Cvoid}
const PL_CALLBACK_SIG_EX2 = Ptr{Cvoid}
const PL_CALLBACK_SIG_EX3 = Ptr{Cvoid}
