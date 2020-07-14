/******************************************************************************/
/* Copyright (C) Roper Scientific, Inc. All rights reserved.                  */
/******************************************************************************/
#include "master.h"
#ifndef _PVCAM_H
#define _PVCAM_H

/******************************************************************************/
/* Constants                                                                  */
/******************************************************************************/

/**
@brief Major version of PVCAM library.

The major version can be checked by application while loading the PVCAM library
at runtime. If major versions don't match it means public API has changed and
application should refuse to use such library or should support various versions
of PVCAM API.

@note Keep in mind that PVCAM *package* version (e.g. "3.7.3.3" that can be read
via #pl_pvcam_get_ver API function) has no relation to PVCAM *library* version
(e.g. "8.0.1234" on Windows that has no API function to access).
*/
#if defined(_WIN32)
    #define PVCAM_LIB_VERSION_MAJOR 8
#elif defined(__linux__)
    #define PVCAM_LIB_VERSION_MAJOR 2
#endif

/** Maximum number of cameras on this system. */
#define MAX_CAM                16

/******************************************************************************/
/* Name/ID sizes                                                              */
/******************************************************************************/

/** Maximum length of a camera name including space for null terminator. */
/** @see #pl_cam_get_name for details. */
#define CAM_NAME_LEN                32
/** @deprecated Use #MAX_PP_NAME_LEN instead. */
#define PARAM_NAME_LEN              32
/** Maximum length of an error message including space for null terminator. */
/** @see #pl_error_message for details. */
#define ERROR_MSG_LEN               255
/** Maximum length of a sensor chip name including space for null terminator. */
/** @see #PARAM_CHIP_NAME for details. */
#define CCD_NAME_LEN                17
/** Maximum length of a camera serial number string including space for null
    terminator. */
/** @see #PARAM_HEAD_SER_NUM_ALPHA for details. */
#define MAX_ALPHA_SER_NUM_LEN       32
/** Maximum length of a post-processing parameter/feature name including space
    for null terminator. */
/** @see #PARAM_PP_FEAT_NAME and #PARAM_PP_PARAM_NAME for details. */
#define MAX_PP_NAME_LEN             32
/** Maximum length of a system name including space for null terminator. */
/** @see #PARAM_SYSTEM_NAME for details. */
#define MAX_SYSTEM_NAME_LEN         32
/** Maximum length of a vendor name. including space for null terminator */
/** @see #PARAM_VENDOR_NAME for details. */
#define MAX_VENDOR_NAME_LEN         32
/** Maximum length of a product name including space for null terminator. */
/** @see #PARAM_PRODUCT_NAME for details. */
#define MAX_PRODUCT_NAME_LEN        32
/** Maximum length of a camera part number including space for null terminator. */
/** @see #PARAM_CAMERA_PART_NUMBER for details. */
#define MAX_CAM_PART_NUM_LEN        32
/** Maximum length of a gain name including space for null terminator. */
/** @see #PARAM_GAIN_NAME for details. */
#define MAX_GAIN_NAME_LEN           32
/** Maximum length of a gain name including space for null terminator. */
/** @see #PARAM_CAM_SYSTEMS_INFO for details. */
#define MAX_CAM_SYSTEMS_INFO_LEN    1024

/******************************************************************************/
/* Data types                                                                 */
/******************************************************************************/

/**
GUID for #FRAME_INFO structure.
*/
typedef struct _TAG_PVCAM_FRAME_INFO_GUID
{
    uns32 f1;
    uns16 f2;
    uns16 f3;
    uns8  f4[8];
}
PVCAM_FRAME_INFO_GUID;

/**
Structure used to uniquely identify frames in the camera.
*/
typedef struct _TAG_FRAME_INFO
{
    PVCAM_FRAME_INFO_GUID FrameInfoGUID;
    int16 hCam;
    int32 FrameNr;
    long64 TimeStamp;
    int32 ReadoutTime;
    long64 TimeStampBOF;
}
FRAME_INFO;

/**
The modes under which the camera can be open.
Used with the function #pl_cam_open.
Treated as @c #int16 type.
*/
typedef enum PL_OPEN_MODES
{
    OPEN_EXCLUSIVE
}
PL_OPEN_MODES;

/**
Used with the #PARAM_COOLING_MODE parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_COOL_MODES
{
    /**
    This is a thermo-electrically (TE)-cooled camera with air or liquid assisted
    cooling.
    */
    NORMAL_COOL,
    /**
    The camera is cryogenically cooled. A camera cooled via Liquid Nitrogen (LN)
    in an attached Dewar is an example of a cryo-cooled camera.
    */
    CRYO_COOL,
    /**
    The camera has no cooling. It is used for board-level cameras only where
    OEM customers are supposed to add their own cooling hardware.
    */
    NO_COOL
}
PL_COOL_MODES;

/**
Used with the #PARAM_MPP_CAPABLE parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_MPP_MODES
{
    MPP_UNKNOWN,
    MPP_ALWAYS_OFF,
    MPP_ALWAYS_ON,
    MPP_SELECTABLE
}
PL_MPP_MODES;

/**
Used with the #PARAM_SHTR_STATUS parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_SHTR_MODES
{
    SHTR_FAULT,
    SHTR_OPENING,
    SHTR_OPEN,
    SHTR_CLOSING,
    SHTR_CLOSED,
    SHTR_UNKNOWN
}
PL_SHTR_MODES;

/**
Used with the #PARAM_PMODE parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_PMODES
{
    PMODE_NORMAL,
    PMODE_FT,
    PMODE_MPP,
    PMODE_FT_MPP,
    PMODE_ALT_NORMAL,
    PMODE_ALT_FT,
    PMODE_ALT_MPP,
    PMODE_ALT_FT_MPP
}
PL_PMODES;

/**
Used with the #PARAM_COLOR_MODE parameter ID.
Treated as @c #int32 type (but should not exceed a value of 255 due to
#md_frame_header.colorMask)
*/
typedef enum PL_COLOR_MODES
{
    COLOR_NONE     = 0, /**< Monochrome camera, no color mask. */
    COLOR_RESERVED = 1, /**< Reserved, do not use. */
    COLOR_RGGB     = 2, /**< Color camera with RGGB color mask. */
    COLOR_GRBG,         /**< Color camera with GRBG color mask. */
    COLOR_GBRG,         /**< Color camera with GBRG color mask. */
    COLOR_BGGR          /**< Color camera with BGGR color mask. */
}
PL_COLOR_MODES;

/**
Image format specifies the buffer format in which the pixels are
transferred. The format should be used together with #PARAM_BIT_DEPTH
because it specifies only the format of the pixel container, not the
actual bit depth of the pixel it contains.
Used with the #PARAM_IMAGE_FORMAT parameter ID.
Treated as @c #int32 type (but should not exceed a value of 255 due to
#md_frame_header.imageFormat field).
*/
typedef enum PL_IMAGE_FORMATS
{
    PL_IMAGE_FORMAT_MONO16 = 0, /**< 16bit mono, 2 bytes per pixel. */
    PL_IMAGE_FORMAT_BAYER16,    /**< 16bit bayer masked image, 2 bytes per pixel. See also #PL_COLOR_MODES. */
    PL_IMAGE_FORMAT_MONO8,      /**< 8bit mono, 1 byte per pixel. */
    PL_IMAGE_FORMAT_BAYER8,     /**< 8bit bayer masked image, 1 byte per pixel. See also #PL_COLOR_MODES. */
    PL_IMAGE_FORMAT_MONO24,     /**< 24 bit mono, 3 bytes per pixel. */
    PL_IMAGE_FORMAT_BAYER24,    /**< 24 bit bayer masked image, 3 bytes per pixel. See also #PL_COLOR_MODES. */
    PL_IMAGE_FORMAT_RGB24,      /**< 8 bit RGB, 1 byte per sample, 3 bytes per pixel. */
    PL_IMAGE_FORMAT_RGB48,      /**< 16 bit RGB, 2 bytes per sample, 6 bytes per pixel. */
    PL_IMAGE_FORMAT_RGB72,      /**< 24 bit RGB, 3 bytes per sample, 9 bytes per pixel. */
}
PL_IMAGE_FORMATS;

/**
Image compression used to reduce the size of the pixel data. Once the
image is decompressed the pixels can be accessed according to #PL_IMAGE_FORMATS type.
Used with the #PARAM_IMAGE_COMPRESSION parameter ID.
Treated as @c #int32 type (but should not exceed a value of 255 due to
#md_frame_header.imageCompression field).
*/
typedef enum PL_IMAGE_COMPRESSIONS
{
    PL_IMAGE_COMPRESSION_NONE = 0,     /**< No compression, the pixels can be accessed according to #PL_IMAGE_FORMATS */
    /* Bit-packing compression modes */
    PL_IMAGE_COMPRESSION_RESERVED8 = 8,
    PL_IMAGE_COMPRESSION_BITPACK9,        /**<  9-bit packing in 16bit format */
    PL_IMAGE_COMPRESSION_BITPACK10,       /**< 10-bit packing in 16bit format */
    PL_IMAGE_COMPRESSION_BITPACK11,       /**< 11-bit packing in 16bit format */
    PL_IMAGE_COMPRESSION_BITPACK12,       /**< 12-bit packing in 16bit format */
    PL_IMAGE_COMPRESSION_BITPACK13,       /**< 13-bit packing in 16bit format */
    PL_IMAGE_COMPRESSION_BITPACK14,       /**< 14-bit packing in 16bit format */
    PL_IMAGE_COMPRESSION_BITPACK15,       /**< 15-bit packing in 16bit format */
    PL_IMAGE_COMPRESSION_RESERVED16 = 16,
    PL_IMAGE_COMPRESSION_BITPACK17,       /**< 17-bit packing in 24bit format */
    PL_IMAGE_COMPRESSION_BITPACK18,       /**< 18-bit packing in 24bit format */
    PL_IMAGE_COMPRESSION_RESERVED24 = 24,
    PL_IMAGE_COMPRESSION_RESERVED32 = 32,
    /* Other compression modes below */
}
PL_IMAGE_COMPRESSIONS;

/**
Used with the function #pl_get_param.
Treated as @c #int16 type.
*/
typedef enum PL_PARAM_ATTRIBUTES
{
    /**
    Current value.
    For the enumerated type the value returned here is the value
    assigned to current enum item not the item index.
    The data type for this attribute is defined by #ATTR_TYPE.
    */
    ATTR_CURRENT,
    /**
    Number of possible values for enumerated and array data types.
    If the data type returned by #ATTR_TYPE is #TYPE_CHAR_PTR (and not an
    enumerated type), then the #ATTR_COUNT is the number of characters in the
    string including a space for NULL terminator. If 0 or 1 is returned,
    #ATTR_COUNT is a scalar (single element) of the following data types:
    #TYPE_INT8, #TYPE_UNS8, #TYPE_INT16, #TYPE_UNS16, #TYPE_INT32, #TYPE_UNS32,
    #TYPE_INT64, #TYPE_UNS64, #TYPE_FLT64 and #TYPE_BOOLEAN.
    The data type for this attribute is #TYPE_UNS32.
    */
    ATTR_COUNT,
    /**
    Data type of parameter.
    Data types used by #pl_get_param with attribute type (#ATTR_TYPE) are:

    |            Value           |       Type         |
    |----------------------------|--------------------|
    | TYPE_BOOLEAN               | rs_bool            |
    | TYPE_INT8                  | int8               |
    | TYPE_UNS8                  | uns8               |
    | TYPE_INT16                 | int16              |
    | TYPE_UNS16                 | uns16              |
    | TYPE_INT32                 | int32              |
    | TYPE_UNS32                 | uns32              |
    | TYPE_INT64                 | long64             |
    | TYPE_UNS64                 | ulong64            |
    | TYPE_FLT32                 | flt32              |
    | TYPE_FLT64                 | flt64              |
    | TYPE_ENUM                  | int32              |
    | TYPE_CHAR_PTR              | char*              |
    | TYPE_VOID_PTR              | void*              |
    | TYPE_VOID_PTR_PTR          | void**             |
    | TYPE_SMART_STREAM_TYPE     | smart_stream_type  |
    | TYPE_SMART_STREAM_TYPE_PTR | smart_stream_type* |

    The data type for this attribute is #TYPE_UNS16.
    */
    ATTR_TYPE,
    /**
    Minimum value. The value is only valid for the following data types:
    #TYPE_INT8, #TYPE_UNS8, #TYPE_INT16, #TYPE_UNS16, #TYPE_INT32, #TYPE_UNS32,
    #TYPE_INT64, #TYPE_UNS64, #TYPE_FLT64 and #TYPE_BOOLEAN.
    The data type for this attribute is defined by #ATTR_TYPE.
    */
    ATTR_MIN,
    /**
    Maximum value. The value is only valid for the following data types:
    #TYPE_INT8, #TYPE_UNS8, #TYPE_INT16, #TYPE_UNS16, #TYPE_INT32, #TYPE_UNS32,
    #TYPE_INT64, #TYPE_UNS64, #TYPE_FLT64 and #TYPE_BOOLEAN.
    The data type for this attribute is defined by #ATTR_TYPE.
    */
    ATTR_MAX,
    /**
    Default value. This value should be equal to the current value set
    in camera after power cycle. For the enumerated type the value
    returned here is the value assigned to current enum item not the item index.
    The data type for this attribute is defined by #ATTR_TYPE.
    */
    ATTR_DEFAULT,
    /**
    Step size for values (zero if non-linear or has no increment).
    The value is only valid for the following data types:
    #TYPE_INT8, #TYPE_UNS8, #TYPE_INT16, #TYPE_UNS16, #TYPE_INT32, #TYPE_UNS32,
    #TYPE_INT64, #TYPE_UNS64 and #TYPE_FLT64. The value for this attribute
    is never negative. If the value is not zero valid values can be easily
    calculated. First valid value is the value reported for attribute #ATTR_MIN,
    second value is minimum value plus increment (#ATTR_INCREMENT),
    and so on up to the maximum value (#ATTR_MAX).
    The data type for this attribute is defined by #ATTR_TYPE.
    */
    ATTR_INCREMENT,
    /**
    Reports if the parameter with ID param_id can be written to and/or read or
    (if it cannot be written to and/or read) tells whether a feature exists.
    If the param_id can be either written to or read the next step
    is to determine its data type.
    The access types are enumerated:
    #ACC_EXIST_CHECK_ONLY #ACC_READ_ONLY
    #ACC_WRITE_ONLY #ACC_READ_WRITE
    The data type for this attribute is #TYPE_UNS16.
    */
    ATTR_ACCESS,
    /**
    Feature available with attached hardware and software.
    The data type for this attribute is #TYPE_BOOLEAN.
    */
    ATTR_AVAIL
}
PL_PARAM_ATTRIBUTES;

/**
Used with the function #pl_get_param and #ATTR_ACCESS.
Treated as @c #uns16 type.
*/
typedef enum PL_PARAM_ACCESS
{
    ACC_READ_ONLY = 1,
    ACC_READ_WRITE,
    ACC_EXIST_CHECK_ONLY,
    ACC_WRITE_ONLY
}
PL_PARAM_ACCESS;

/**
Used with the #PARAM_IO_TYPE parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_IO_TYPE
{
    IO_TYPE_TTL, /**< The bit pattern written to this address.*/
    IO_TYPE_DAC /**< The value of the desired analog output written to the DAC at this address.*/
}
PL_IO_TYPE;

/**
Used with the #PARAM_IO_DIRECTION parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_IO_DIRECTION
{
    IO_DIR_INPUT,
    IO_DIR_OUTPUT,
    IO_DIR_INPUT_OUTPUT
}
PL_IO_DIRECTION;

/**
Used with the #PARAM_READOUT_PORT parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_READOUT_PORTS
{
    READOUT_PORT_0 = 0,
    READOUT_PORT_1
}
PL_READOUT_PORTS;

/**
Used with the #PARAM_CLEAR_MODE parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_CLEAR_MODES
{
    /**
    Don't ever clear the sensor. Useful for performing a readout after an
    exposure has been aborted.
    */
    CLEAR_NEVER,
    /**
    Before each exposure, clears the sensor the number of times specified by the
    @c clear_cycles variable. This mode can be used in a sequence. It is most
    useful when there is a considerable amount of time between exposures.
    */
    CLEAR_PRE_EXPOSURE,
    /**
    Before each sequence, clears the sensor the number of times specified by the
    @c clear_cycles variable. If no sequence is set up, this mode behaves as if
    the sequence has one exposure. The result is the same as using
    #CLEAR_PRE_EXPOSURE.
    */
    CLEAR_PRE_SEQUENCE,
    /**
    Clears continuously after the sequence ends. The camera continues clearing
    until a new exposure is set up or started, the abort command is sent, the
    speed entry number is changed, or the camera is reset.
    */
    CLEAR_POST_SEQUENCE,
    /**
    Clears @c clear_cycles times before each sequence and clears continuously
    after the sequence ends. The camera continues clearing until a new exposure
    is set up or started, the abort command is sent, the speed entry number is
    changed, or the camera is reset.
    */
    CLEAR_PRE_POST_SEQUENCE,
    /**
    Clears @c clear_cycles times before each exposure and clears continuously
    after the sequence ends. The camera continues clearing until a new exposure
    is set up or started, the abort command is sent, the speed entry number is
    changed, or the camera is reset.
    */
    CLEAR_PRE_EXPOSURE_POST_SEQ,

    /* Should be the last and never used value. */
    MAX_CLEAR_MODE
}
PL_CLEAR_MODES;

/**
Used with the #PARAM_SHTR_OPEN_MODE parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_SHTR_OPEN_MODES
{
    /**
    The shutter closes before the exposure and stays closed during the exposure.
    */
    OPEN_NEVER,
    /**
    Opens each exposure. Normal mode.
    */
    OPEN_PRE_EXPOSURE,
    /**
    Opens the shutter at the start of each sequence. Useful for frame transfer
    and external strobe devices.
    */
    OPEN_PRE_SEQUENCE,
    /**
    If using a triggered mode, this function causes the shutter to open before
    the external trigger is armed. If using a non-triggered mode, this function
    operates identical to #OPEN_PRE_EXPOSURE.
    */
    OPEN_PRE_TRIGGER,
    /**
    Sends no signals to open or close the shutter. Useful for frame transfer
    when you want to open the shutter and leave it open (see #pl_exp_abort).
    */
    OPEN_NO_CHANGE
}
PL_SHTR_OPEN_MODES;

/**
Used with the #PARAM_EXPOSURE_MODE parameter ID.
Treated as @c #int32 type.

Used with the functions #pl_exp_setup_cont and #pl_exp_setup_seq.
Treated as @c #int16 type.
*/
typedef enum PL_EXPOSURE_MODES
{
    /* Classic EXPOSURE modes, the MAX */
    TIMED_MODE,
    STROBED_MODE,
    BULB_MODE,
    TRIGGER_FIRST_MODE,
    FLASH_MODE, /**< @deprecated Not supported by any modern camera. */
    VARIABLE_TIMED_MODE,
    INT_STROBE_MODE, /**< @deprecated Not supported by any modern camera. */
    MAX_EXPOSE_MODE = 7,

    /*
    Extended EXPOSURE modes used with #PARAM_EXPOSURE_MODE when
    camera dynamically reports it's capabilities.
    The "7" in each of these calculations comes from previous
    definition of #MAX_EXPOSE_MODE when this file was defined.
    */
    EXT_TRIG_INTERNAL = (7 + 0) << 8,
    EXT_TRIG_TRIG_FIRST = (7 + 1) << 8,
    EXT_TRIG_EDGE_RISING  = (7 + 2) << 8
}
PL_EXPOSURE_MODES;

/**
Used with the #PARAM_EXPOSE_OUT_MODE parameter ID.
Build the values for the expose out modes that are "ORed" with the trigger
modes when setting up the script.
Treated as @c #int32 type.
*/
typedef enum PL_EXPOSE_OUT_MODES
{
    /**
    Expose out high when first row is exposed (from first row begin to first row end)
    */
    EXPOSE_OUT_FIRST_ROW = 0,
    /**
    Expose out high when all rows are exposed at once (from last row begin to first row end).
    The duration of the signal equals to exposure value entered which means the actual exposure
    time is longer - use this mode with triggered light source only.
    */
    EXPOSE_OUT_ALL_ROWS,
    /**
    Expose out high when any row is exposed (from first row begin to last row end)
    */
    EXPOSE_OUT_ANY_ROW,
    /**
    Like FIRST_ROW but the expose out signal is high when all rows are being exposed at once.
    If the exposure time entered is shorter than readout time the expose out signal will
    not become high at all.
    */
    EXPOSE_OUT_ROLLING_SHUTTER,

    /* Should be the last and never used value. */
    MAX_EXPOSE_OUT_MODE
}
PL_EXPOSE_OUT_MODES;

/**
Used with the #PARAM_FAN_SPEED_SETPOINT parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_FAN_SPEEDS
{
    FAN_SPEED_HIGH, /**< The full fan speed set in factory, the default value. */
    FAN_SPEED_MEDIUM, /**< Medium fan speed. */
    FAN_SPEED_LOW, /**< Low fan speed. */
    FAN_SPEED_OFF /**< Fan is turned off. */
}
PL_FAN_SPEEDS;

/**
Used with the #PARAM_TRIGTAB_SIGNAL parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_TRIGTAB_SIGNALS
{
    PL_TRIGTAB_SIGNAL_EXPOSE_OUT
}
PL_TRIGTAB_SIGNALS;

/**
Used with the #PARAM_FRAME_DELIVERY_MODE parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_FRAME_DELIVERY_MODES
{
    PL_FRAME_DELIVERY_MODE_MAX_FPS = 0,
    PL_FRAME_DELIVERY_MODE_CONSTANT_INTERVALS
}
PL_FRAME_DELIVERY_MODES;

/**
Used with the #PARAM_CAM_INTERFACE_TYPE parameter ID.

32-bit enum where:
- Upper 24 bits are interface classes, flags, 1bit = one class, 24 possible classes.
- Lower 8 bits are interface revisions, there are 254 possible revisions for each interface class.

Usage:
@code{.cpp}
 if (attrCurrent & PL_CAM_IFC_TYPE_USB)
    // The camera is running on USB, any USB
 if (attrCurrent & PL_CAM_IFC_TYPE_USB && type >= PL_CAM_IFC_TYPE_USB_3_0)
    // The camera is running on USB, the camera is running on at least USB 3.0
 if (attrCurrent == PL_CAM_IFC_TYPE_USB_3_1)
    // The camera is running exactly on USB 3.1
@endcode
*/
typedef enum PL_CAM_INTERFACE_TYPES
{
    PL_CAM_IFC_TYPE_UNKNOWN     = 0,        /**< Unrecognized type. */

    PL_CAM_IFC_TYPE_1394        = 0x100,    /**< A generic 1394 in case we cannot identify the sub type. */
    PL_CAM_IFC_TYPE_1394_A,                 /**< FireWire 400. */
    PL_CAM_IFC_TYPE_1394_B,                 /**< FireWire 800. */

    PL_CAM_IFC_TYPE_USB         = 0x200,    /**< A generic USB in case we cannot identify the sub type. */
    PL_CAM_IFC_TYPE_USB_1_1,                /**< FullSpeed (12 Mbit/s). */
    PL_CAM_IFC_TYPE_USB_2_0,                /**< HighSpeed (480 Mbit/s). */
    PL_CAM_IFC_TYPE_USB_3_0,                /**< SuperSpeed (5 Gbit/s). */
    PL_CAM_IFC_TYPE_USB_3_1,                /**< SuperSpeed+ (10 Gbit/s). */

    PL_CAM_IFC_TYPE_PCI         = 0x400,    /**< A generic PCI interface. */
    PL_CAM_IFC_TYPE_PCI_LVDS,               /**< LVDS PCI interface. */

    PL_CAM_IFC_TYPE_PCIE        = 0x800,    /**< A generic PCIe interface. */
    PL_CAM_IFC_TYPE_PCIE_LVDS,              /**< LVDS PCIe interface. */
    PL_CAM_IFC_TYPE_PCIE_X1,                /**< Single channel PCIe interface. */
    PL_CAM_IFC_TYPE_PCIE_X4,                /**< 4 channel PCIe interface. */

    PL_CAM_IFC_TYPE_VIRTUAL     = 0x1000,   /**< Base for all Virtual camera interfaces. */

    PL_CAM_IFC_TYPE_ETHERNET    = 0x2000    /**< Base for all Ethernet based cameras. */
}
PL_CAM_INTERFACE_TYPES;

/**
Used with the #PARAM_CAM_INTERFACE_MODE parameter ID.
*/
typedef enum PL_CAM_INTERFACE_MODES
{
    PL_CAM_IFC_MODE_UNSUPPORTED = 0, /**< Interface is not supported. */
    PL_CAM_IFC_MODE_CONTROL_ONLY,    /**< Control commands only. */
    PL_CAM_IFC_MODE_IMAGING          /**< Full imaging. */
}
PL_CAM_INTERFACE_MODES;

/**
Used with the #PARAM_CENTROIDS_MODE parameter ID.
*/
typedef enum PL_CENTROIDS_MODES
{
    PL_CENTROIDS_MODE_LOCATE = 0, /**< Locate mode (PrimeLocate) */
    PL_CENTROIDS_MODE_TRACK,      /**< Particle Tracking mode */
    PL_CENTROIDS_MODE_BLOB        /**< Blob Detection mode */
}
PL_CENTROIDS_MODES;


/**
Used with the #PARAM_SCAN_MODE parameter ID.
*/
typedef enum PL_SCAN_MODES
{
    /** Normal camera imaging and the default mode of operation, the FPGA
    reads each row in succession without inserting additional delays between rows */
    PL_SCAN_MODE_AUTO = 0,
    /** This mode allows the user to configure the #PARAM_SCAN_LINE_DELAY.
    The #PARAM_SCAN_WIDTH will become read-only and its value will be
    auto-calculated and reported by the camera */
    PL_SCAN_MODE_PROGRAMMABLE_LINE_DELAY,
    /** This mode allows the user to configure the #PARAM_SCAN_WIDTH.
    The #PARAM_SCAN_LINE_DELAY will become read-only and its value will be
    auto-calculated and reported by the camera */
    PL_SCAN_MODE_PROGRAMMABLE_SCAN_WIDTH
}
PL_SCAN_MODES;


/**
Used with the #PARAM_SCAN_DIRECTION parameter ID.
*/
typedef enum PL_SCAN_DIRECTIONS
{
    /**< Default mode. The camera starts reading from top to bottom */
    PL_SCAN_DIRECTION_DOWN = 0,
    /**< Camera starts reading from bottom to up */
    PL_SCAN_DIRECTION_UP,
    /**< Camera initially starts reading from top to bottom,
        and switches automatically to read out from bottom to top.
        The direction alternates between frames down-up-down-up and so on.
    */
    PL_SCAN_DIRECTION_DOWN_UP           
}
PL_SCAN_DIRECTIONS;

/**
Used with the #PARAM_PP_FEAT_ID parameter ID.
Treated as @c #uns16 type.
*/
typedef enum PP_FEATURE_IDS
{
    PP_FEATURE_RING_FUNCTION,
    PP_FEATURE_BIAS,
    PP_FEATURE_BERT,
    PP_FEATURE_QUANT_VIEW,
    PP_FEATURE_BLACK_LOCK,
    PP_FEATURE_TOP_LOCK,
    PP_FEATURE_VARI_BIT,
    PP_FEATURE_RESERVED,            /**< Should not be used at any time moving forward. */
    PP_FEATURE_DESPECKLE_BRIGHT_HIGH,
    PP_FEATURE_DESPECKLE_DARK_LOW,
    PP_FEATURE_DEFECTIVE_PIXEL_CORRECTION,
    PP_FEATURE_DYNAMIC_DARK_FRAME_CORRECTION,
    PP_FEATURE_HIGH_DYNAMIC_RANGE,
    PP_FEATURE_DESPECKLE_BRIGHT_LOW,
    PP_FEATURE_DENOISING,
    PP_FEATURE_DESPECKLE_DARK_HIGH,
    PP_FEATURE_ENHANCED_DYNAMIC_RANGE,
    PP_FEATURE_MAX
}
PP_FEATURE_IDS;

/**
Used with the #PARAM_PP_PARAM_ID parameter ID.
*/
#define PP_MAX_PARAMETERS_PER_FEATURE   10

/**
Used with the #PARAM_PP_PARAM_ID parameter ID.
Treated as @c #uns16 type.
*/
typedef enum PP_PARAMETER_IDS
{
    PP_PARAMETER_RF_FUNCTION                            = (PP_FEATURE_RING_FUNCTION * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_BIAS_ENABLED                             = (PP_FEATURE_BIAS * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_BIAS_LEVEL,
    PP_FEATURE_BERT_ENABLED                             = (PP_FEATURE_BERT * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_BERT_THRESHOLD,
    PP_FEATURE_QUANT_VIEW_ENABLED                       = (PP_FEATURE_QUANT_VIEW * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_QUANT_VIEW_E,
    PP_FEATURE_BLACK_LOCK_ENABLED                       = (PP_FEATURE_BLACK_LOCK * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_BLACK_LOCK_BLACK_CLIP,
    PP_FEATURE_TOP_LOCK_ENABLED                         = (PP_FEATURE_TOP_LOCK * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_TOP_LOCK_WHITE_CLIP,
    PP_FEATURE_VARI_BIT_ENABLED                         = (PP_FEATURE_VARI_BIT * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_VARI_BIT_BIT_DEPTH,
    PP_FEATURE_DESPECKLE_BRIGHT_HIGH_ENABLED            = (PP_FEATURE_DESPECKLE_BRIGHT_HIGH * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_DESPECKLE_BRIGHT_HIGH_THRESHOLD,
    PP_FEATURE_DESPECKLE_BRIGHT_HIGH_MIN_ADU_AFFECTED,
    PP_FEATURE_DESPECKLE_DARK_LOW_ENABLED               = (PP_FEATURE_DESPECKLE_DARK_LOW * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_DESPECKLE_DARK_LOW_THRESHOLD,
    PP_FEATURE_DESPECKLE_DARK_LOW_MAX_ADU_AFFECTED,
    PP_FEATURE_DEFECTIVE_PIXEL_CORRECTION_ENABLED       = (PP_FEATURE_DEFECTIVE_PIXEL_CORRECTION * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_DYNAMIC_DARK_FRAME_CORRECTION_ENABLED    = (PP_FEATURE_DYNAMIC_DARK_FRAME_CORRECTION * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_HIGH_DYNAMIC_RANGE_ENABLED               = (PP_FEATURE_HIGH_DYNAMIC_RANGE * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_DESPECKLE_BRIGHT_LOW_ENABLED             = (PP_FEATURE_DESPECKLE_BRIGHT_LOW * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_DESPECKLE_BRIGHT_LOW_THRESHOLD,
    PP_FEATURE_DESPECKLE_BRIGHT_LOW_MAX_ADU_AFFECTED,
    PP_FEATURE_DENOISING_ENABLED                        = (PP_FEATURE_DENOISING * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_DENOISING_NO_OF_ITERATIONS,
    PP_FEATURE_DENOISING_GAIN,
    PP_FEATURE_DENOISING_OFFSET,
    PP_FEATURE_DENOISING_LAMBDA,
    PP_FEATURE_DESPECKLE_DARK_HIGH_ENABLED              = (PP_FEATURE_DESPECKLE_DARK_HIGH * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_FEATURE_DESPECKLE_DARK_HIGH_THRESHOLD,
    PP_FEATURE_DESPECKLE_DARK_HIGH_MIN_ADU_AFFECTED,
    PP_FEATURE_ENHANCED_DYNAMIC_RANGE_ENABLED           = (PP_FEATURE_ENHANCED_DYNAMIC_RANGE * PP_MAX_PARAMETERS_PER_FEATURE),
    PP_PARAMETER_ID_MAX
}
PP_PARAMETER_IDS;

/**
Used with the #PARAM_SMART_STREAM_EXP_PARAMS and #PARAM_SMART_STREAM_DLY_PARAMS
parameter IDs and #pl_create_smart_stream_struct and
#pl_release_smart_stream_struct functions.
*/
typedef struct smart_stream_type
{
    uns16   entries;    /**< The number of entries in the array. */
    uns32*  params;     /**< The actual S.M.A.R.T. stream parameters. */
}
smart_stream_type;

/**
Used with the #PARAM_SMART_STREAM_MODE parameter ID.
Treated as @c #uns16 type.
*/
typedef enum PL_SMT_MODES
{
    SMTMODE_ARBITRARY_ALL = 0,
    SMTMODE_MAX
}
PL_SMT_MODES;

/**
Used with the functions #pl_exp_check_status, and #pl_exp_check_cont_status and
#pl_exp_check_cont_status_ex.
Treated as @c #int16 type.
*/
typedef enum PL_IMAGE_STATUSES
{
    /** The system is @b idle, no data is expected. If any arrives, it will be discarded. */
    READOUT_NOT_ACTIVE,
    /**
    The data collection routines are @b active. They are waiting for data to arrive,
    but none has arrived yet.
    */
    EXPOSURE_IN_PROGRESS,
    /** The data collection routines are @b active. The data has started to arrive. */
    READOUT_IN_PROGRESS,
    /** Means frame available for a circular buffer acquisition. */
    READOUT_COMPLETE,
    /** New camera status indicating at least one frame is available. */
    FRAME_AVAILABLE = READOUT_COMPLETE,
    /** Something went wrong. The function returns a #PV_FAIL and #pl_error_code is set. */
    READOUT_FAILED,

    ACQUISITION_IN_PROGRESS, /**< @deprecated Not used by PVCAM. */

    /* Should be the last and never used value. */
    MAX_CAMERA_STATUS
}
PL_IMAGE_STATUSES;

/**
Used with the function #pl_exp_abort.
Treated as @c #int16 type.
*/
typedef enum PL_CCS_ABORT_MODES
{
    CCS_NO_CHANGE = 0,      /**< Do not alter the current state of the CCS.*/
    CCS_HALT,               /**< Halt all CCS activity, and put the CCS into the idle state.*/
    CCS_HALT_CLOSE_SHTR,    /**< Close the shutter, then halt all CCS activity, and put the CCS into the idle state.*/
    CCS_CLEAR,              /**< Put the CCS into the continuous clearing state.*/
    CCS_CLEAR_CLOSE_SHTR,   /**< Close the shutter, then put the CCS into the continuous clearing state.*/
    CCS_OPEN_SHTR,          /**< Open the shutter, then halt all CCS activity, and put the CCS into the idle state.*/
    CCS_CLEAR_OPEN_SHTR     /**< Open the shutter, then put the CCS into the continuous clearing state.*/
}
PL_CCS_ABORT_MODES;

/**
Used with the #PARAM_BOF_EOF_ENABLE parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_IRQ_MODES
{
    NO_FRAME_IRQS = 0,
    BEGIN_FRAME_IRQS,
    END_FRAME_IRQS,
    BEGIN_END_FRAME_IRQS
}
PL_IRQ_MODES;

/**
Used with the function #pl_exp_setup_cont.
Treated as @c #int16 type.
*/
typedef enum PL_CIRC_MODES
{
    CIRC_NONE = 0,
    CIRC_OVERWRITE,
    CIRC_NO_OVERWRITE
}
PL_CIRC_MODES;

/**
Used with the #PARAM_EXP_RES parameter ID.
Treated as @c #int32 type.
*/
typedef enum PL_EXP_RES_MODES
{
    EXP_RES_ONE_MILLISEC = 0,
    EXP_RES_ONE_MICROSEC,
    EXP_RES_ONE_SEC
}
PL_EXP_RES_MODES;

/**
Used with the function #pl_io_script_control.
Treated as @c #uns32 type.
*/
typedef enum PL_SRC_MODES
{
    SCR_PRE_OPEN_SHTR = 0,
    SCR_POST_OPEN_SHTR,
    SCR_PRE_FLASH,
    SCR_POST_FLASH,
    SCR_PRE_INTEGRATE,
    SCR_POST_INTEGRATE,
    SCR_PRE_READOUT,
    SCR_POST_READOUT,
    SCR_PRE_CLOSE_SHTR,
    SCR_POST_CLOSE_SHTR
}
PL_SRC_MODES;

/**
Used with the functions pl_cam_register_callback* and #pl_cam_deregister_callback.
Used directly as an enum type without casting to any integral type.
*/
typedef enum PL_CALLBACK_EVENT
{
    PL_CALLBACK_BOF = 0,
    PL_CALLBACK_EOF,
    PL_CALLBACK_CHECK_CAMS,
    PL_CALLBACK_CAM_REMOVED,
    PL_CALLBACK_CAM_RESUMED,
    PL_CALLBACK_MAX
}
PL_CALLBACK_EVENT;

typedef struct rgn_type
{
    uns16 s1;   /**< First pixel in the serial register. */
    uns16 s2;   /**< Last pixel in the serial register. */
    uns16 sbin; /**< Serial binning for this region. */
    uns16 p1;   /**< First row in the parallel register. */
    uns16 p2;   /**< Last row in the parallel register. */
    uns16 pbin; /**< Parallel binning for this region. */
}
rgn_type;

typedef struct io_struct
{
    uns16 io_port;          /**< I/O port address. */
    uns32 io_type;          /**< I/O port type (TTL, DAC, etc.) */
    flt64 state;            /**< Desired output state for the port. */
    struct io_struct* next; /**< Linked list pointer.*/
}
io_entry;

typedef struct io_list
{
    io_entry pre_open;
    io_entry post_open;
    io_entry pre_flash;
    io_entry post_flash;
    io_entry pre_integrate;
    io_entry post_integrate;
    io_entry pre_readout;
    io_entry post_readout;
    io_entry pre_close;
    io_entry post_close;
}
io_list;

typedef struct active_camera_type
{
    uns16       shutter_close_delay; /**< Number of milliseconds for the shutter to close. */
    uns16       shutter_open_delay;  /**< Number of milliseconds for the shutter to open. */
    uns16       rows;                /**< Parallel size of the sensor active area. */
    uns16       cols;                /**< Serial size of the sensor active area. */
    uns16       prescan;             /**< Serial pixels before the active area. */
    uns16       postscan;            /**< Serial pixels after the active area. */
    uns16       premask;             /**< Parallel rows before the active area. */
    uns16       postmask;            /**< Parallel rows after the active area. */
    uns16       preflash;            /**< Number of milliseconds to flash the diode ring. */
    uns16       clear_count;         /**< Number of times to clear the sensor before exposure. */
    uns16       preamp_delay;        /**< Number of milliseconds for the preamp to settle. */
    rs_bool     mpp_selectable;      /**< Indicates MPP mode can be selected. */
    rs_bool     frame_selectable;    /**< Indicates frame transfer can be selected. */
    int16       do_clear;            /**< Clear: Never, Each Exposure, Each Sequence. */
    int16       open_shutter;        /**< Open: Never, Each Exposure, Each Sequence. */
    rs_bool     mpp_mode;            /**< Enable or disable MPP mode. */
    rs_bool     frame_transfer;      /**< Enable or disable frame transfer operation. */
    rs_bool     alt_mode;            /**< Enable or disable Alternate Parallel mode. */
    uns32       exp_res;             /**< Exposure resolution. */
    io_list*    io_hdr;              /**< Pointer to list of I/O script control commands. */
}
active_camera_type;

/******************************************************************************/
/* Start of Frame Metadata Types                                              */
/******************************************************************************/

/******************************************************************************/
/* Data headers and camera shared types                                       */

/**
Used in #md_frame_header structure.
Treated as @c #uns8 type.
*/
typedef enum PL_MD_FRAME_FLAGS
{
    /** Check this bit before using the timestampBOR and timestampEOR. */
    PL_MD_FRAME_FLAG_ROI_TS_SUPPORTED = 0x01,
    PL_MD_FRAME_FLAG_UNUSED_2         = 0x02,
    PL_MD_FRAME_FLAG_UNUSED_3         = 0x04,
    PL_MD_FRAME_FLAG_UNUSED_4         = 0x10,
    PL_MD_FRAME_FLAG_UNUSED_5         = 0x20,
    PL_MD_FRAME_FLAG_UNUSED_6         = 0x40,
    PL_MD_FRAME_FLAG_UNUSED_7         = 0x80
}
PL_MD_FRAME_FLAGS;

/**
Used in #md_frame_roi_header structure.
Treated as @c #uns8 type.
*/
typedef enum PL_MD_ROI_FLAGS
{
    /**
    This flag is used by #pl_md_frame_decode to discard invalid ROIs.
    An ROI with this flag will not be included in the #md_frame ROI array.
    */
    PL_MD_ROI_FLAG_INVALID      = 0x01,
    /**
    This flag is used to report an ROI that contains no pixel data. Such
    ROI is used to only mark a location within the frame.
    */
    PL_MD_ROI_FLAG_HEADER_ONLY  = 0x02,
    PL_MD_ROI_FLAG_UNUSED_3     = 0x04,
    PL_MD_ROI_FLAG_UNUSED_4     = 0x10,
    PL_MD_ROI_FLAG_UNUSED_5     = 0x20,
    PL_MD_ROI_FLAG_UNUSED_6     = 0x40,
    PL_MD_ROI_FLAG_UNUSED_7     = 0x80
}
PL_MD_ROI_FLAGS;

/**
The signature is located in the first 4 bytes of the frame header. The signature
is checked before any metadata-related operations are executed on the buffer.
*/
#define PL_MD_FRAME_SIGNATURE 5328208

/*
The structures are shared beween platforms, thus we must ensure that no
compiler will apply different struct alignment.
*/
#pragma pack(push)
#pragma pack(1)

/**
This is a frame header that is located before each frame. The size of this
structure must remain constant. The structure is generated by the camera
and should be 16-byte aligned.
*/
typedef struct md_frame_header
{                                 /* TOTAL: 48 bytes */
    uns32       signature;        /**< 4B - Equal to #PL_MD_FRAME_SIGNATURE. */
    uns8        version;          /**< 1B - Must be 1 in the first release. */

    uns32       frameNr;          /**< 4B - 1-based, reset with each acquisition. */
    uns16       roiCount;         /**< 2B - Number of ROIs in the frame, at least 1. */

    /** The final timestamp = timestampBOF * timestampResNs (in nano-seconds). */
    uns32       timestampBOF;     /**< 4B - Depends on resolution. */
    uns32       timestampEOF;     /**< 4B - Depends on resolution. */
    uns32       timestampResNs;   /**< 4B - 1=1ns, 1000=1us, 5000000=5ms, ... */

    /** The final exposure time = exposureTime * exposureTimeResNs (nano-seconds). */
    uns32       exposureTime;     /**< 4B - Depends on resolution. */
    uns32       exposureTimeResNs;/**< 4B - 1=1ns, 1000=1us, 5000000=5ms, ... */

    /** ROI timestamp resolution is stored here, no need to transfer with each ROI. */
    uns32       roiTimestampResNs;/**< 4B - ROI timestamps resolution. */

    uns8        bitDepth;         /**< 1B - Must be 10, 13, 14, 16, etc. */
    uns8        colorMask;        /**< 1B - Corresponds to #PL_COLOR_MODES. */
    uns8        flags;            /**< 1B - Frame flags, see #PL_MD_FRAME_FLAGS. */
    uns16       extendedMdSize;   /**< 2B - Must be 0 or actual ext md data size. */

    /** Version 2 header additions */
    uns8        imageFormat;      /**< 1B - Image data format, see #PL_IMAGE_FORMATS */
    uns8        imageCompression; /**< 1B - Image pixel data compression, see #PL_IMAGE_COMPRESSIONS */

    uns8        _reserved[6];
}
md_frame_header;

/**
This is a ROI header that is located before every ROI data. The size of this
structure must remain constant. The structure is genereated by the camera
and should be 16-byte aligned.
*/
typedef struct md_frame_roi_header
{                              /* TOTAL: 32 bytes */
    uns16    roiNr;            /**< 2B - 1-based, reset with each frame. */

    /** The final timestamp = timestampBOR * roiTimestampResNs. */
    uns32    timestampBOR;     /**< 4B - Depends on md_frame_header.roiTimestampResNs. */
    uns32    timestampEOR;     /**< 4B - Depends on md_frame_header.roiTimestampResNs. */

    rgn_type roi;              /**< 12B - ROI coordinates and binning. */

    uns8     flags;            /**< 1B - ROI flags, see #PL_MD_ROI_FLAGS. */
    uns16    extendedMdSize;   /**< 2B - Must be 0 or actual ext md data size in bytes. */

    /** Version 2 header additions */
    uns32    roiDataSize;      /**< 4B - ROI image data size in bytes. */

    uns8    _reserved[3];
}
md_frame_roi_header;

#pragma pack(pop)

/******************************************************************************/
/* Extended metadata related structures                                       */

/**
Maximum number of extended metadata tags supported.
*/
#define PL_MD_EXT_TAGS_MAX_SUPPORTED 255

/**
Available extended metadata tags.
Currently there are no extended metadata available.
Used in #md_ext_item_info structure.
Used directly as an enum type without casting to any integral type.
*/
typedef enum PL_MD_EXT_TAGS
{
    PL_MD_EXT_TAG_PARTICLE_ID = 0,
    PL_MD_EXT_TAG_PARTICLE_M0,
    PL_MD_EXT_TAG_PARTICLE_M2,
    PL_MD_EXT_TAG_MAX
}
PL_MD_EXT_TAGS;

/**
This structure describes the extended metadata TAG. This information is
retrieved from an internal table. User need this to correctly read and
display the extended metadata value.
*/
typedef struct md_ext_item_info
{
    PL_MD_EXT_TAGS tag;
    uns16          type;
    uns16          size;
    const char*    name;
}
md_ext_item_info;

/**
An extended metadata item together with its value. The user will retrieve a
collection of these items.
*/
typedef struct md_ext_item
{
    const md_ext_item_info* tagInfo;
    void*                   value;
}
md_ext_item;

/**
A collection of decoded extended metadata.
*/
typedef struct md_ext_item_collection
{
    md_ext_item     list[PL_MD_EXT_TAGS_MAX_SUPPORTED];
    md_ext_item*    map[PL_MD_EXT_TAGS_MAX_SUPPORTED];
    uns16           count;
}
md_ext_item_collection;

/**
This is a helper structure that is used to decode the md_frame_roi_header. Since
the header cannot contain any pointers PVCAM will calculate all information
using offsets from frame & ROI headers.

The structure must be created using the #pl_md_create_frame_struct function.
Please note the structure keeps only pointers to data residing in the image
buffer. Once the buffer is deleted the contents of the structure become invalid.
*/
typedef struct md_frame_roi
{
    md_frame_roi_header*    header;         /**< Points directly to the header within the buffer. */
    void*                   data;           /**< Points to the ROI image data. */
    uns32                   dataSize;       /**< Size of the ROI image data in bytes. */
    void*                   extMdData;      /**< Points directly to ext/ MD data within the buffer. */
    uns16                   extMdDataSize;  /**< Size of the ext. MD buffer. */
}
md_frame_roi;

/**
This is a helper structure that is used to decode the md_frame_header. Since
the header cannot contain any pointers we need to calculate all information
using only offsets.

Please note the structure keeps only pointers to data residing in the image
buffer. Once the buffer is deleted the contents of the structure become invalid.
*/
typedef struct md_frame
{
    md_frame_header*     header;       /**< Points directly to the header withing the buffer. */
    void*                extMdData;    /**< Points directly to ext/ MD data within the buffer. */
    uns16                extMdDataSize;/**< Size of the ext. MD buffer in bytes. */
    rgn_type             impliedRoi;   /**< Implied ROI calculated during decoding. */

    md_frame_roi*        roiArray;     /**< An array of ROI descriptors. */
    uns16                roiCapacity;  /**< Number of ROIs the structure can hold. */
    uns16                roiCount;     /**< Number of ROIs found during decoding. */
}
md_frame;

/******************************************************************************/
/*End of Frame Metadata Types                                                 */
/******************************************************************************/

/******************************************************************************/
/**
@addtogroup grp_pm_deprecated_typedefs
@{
*/

typedef PVCAM_FRAME_INFO_GUID*  PPVCAM_FRAME_INFO_GUID;
typedef FRAME_INFO*             PFRAME_INFO;
typedef smart_stream_type*      smart_stream_type_ptr;
typedef rgn_type*               rgn_ptr;
typedef const rgn_type*         rgn_const_ptr;
typedef io_entry*               io_entry_ptr;
typedef io_list*                io_list_ptr;
typedef io_list**               io_list_ptr_ptr;
typedef active_camera_type*     active_camera_ptr;

/** @} */ /* grp_pm_deprecated_typedefs */

/******************************************************************************/
/**
@defgroup grp_single_byte_macros Single-byte macros

These will pull out a single uns8 from either a two-uns8 integer quantity,
or a four-uns8 integer quantity and vice versa.

They ARE NOT machine specific.

The software using them is responsible for handling the interface requirements
of the NGC camera, which expects the high uns8 first, then the lower bytes
in order. There are several macros.

@{
*/

/** Extracts the most significant byte from a two-uns8 integer input. */
#define MS16_BYTE(two_byte_value)((uns8)(((uns16)(two_byte_value) >> 8) & 0xFF))
/** Extracts the least significant byte from a two-uns8 integer input. */
#define LS16_BYTE(two_byte_value)((uns8)(((uns16)(two_byte_value) >> 0) & 0xFF))

/** Extracts the most significant byte from a four-uns8 integer input. */
#define MS32_BYTE(four_byte_value)((uns8)(((uns32)(four_byte_value) >> 24) & 0xFF))
/** Extracts the middle-high significant byte from a four-uns8 integer input. */
#define MH32_BYTE(four_byte_value)((uns8)(((uns32)(four_byte_value) >> 16) & 0xFF))
/** Extracts the middle-low significant byte from a four-uns8 integer input. */
#define ML32_BYTE(four_byte_value)((uns8)(((uns32)(four_byte_value) >>  8) & 0xFF))
/** Extracts the least significant byte from a four-uns8 integer input. */
#define LS32_BYTE(four_byte_value)((uns8)(((uns32)(four_byte_value) >>  0) & 0xFF))

/** Produces a two-uns8 integer value from high & low uns8 input. */
#define VAL_UNS16(ms_byte,ls_byte)(\
    ((uns16)((uns8)(ms_byte)) << 8) |\
    ((uns16)((uns8)(ls_byte)) << 0))

/** Produces a four-uns8 integer value from 4 input bytes. */
#define VAL_UNS32(ms_byte,mh_byte,ml_byte,ls_byte)(\
    ((uns32)((uns8)(ms_byte)) << 24) |\
    ((uns32)((uns8)(mh_byte)) << 16) |\
    ((uns32)((uns8)(ml_byte)) <<  8) |\
    ((uns32)((uns8)(ls_byte)) <<  0))

/** Produces a 64-bit integer value from 8 input bytes. */
#define VAL_INT64(b0,b1,b2,b3,b4,b5,b6,b7)(\
    ((long64)((uns8)(b0)) << 56) |\
    ((long64)((uns8)(b1)) << 48) |\
    ((long64)((uns8)(b2)) << 40) |\
    ((long64)((uns8)(b3)) << 32) |\
    ((long64)((uns8)(b4)) << 24) |\
    ((long64)((uns8)(b5)) << 16) |\
    ((long64)((uns8)(b6)) <<  8) |\
    ((long64)((uns8)(b7)) <<  0))

/** @} */ /* grp_single_byte_macros */

/******************************************************************************/
/* Content which is needed to communicate with the PVCAM DLLs */

typedef int16 pm_script_hook(int16 hcam,
                             uns16 exp_total,
                             uns16 rgn_total,
                             const rgn_type* rgn_array,
                             int16 mode,
                             uns32 exposure_time,
                             uns32* pixels,
                             active_camera_type* active_camera);

/**
Data type used by #pl_get_param with #ATTR_TYPE.
@{
*/
#define TYPE_INT16                  1
#define TYPE_INT32                  2
#define TYPE_FLT64                  4
#define TYPE_UNS8                   5
#define TYPE_UNS16                  6
#define TYPE_UNS32                  7
#define TYPE_UNS64                  8
#define TYPE_ENUM                   9
#define TYPE_BOOLEAN               11
#define TYPE_INT8                  12
#define TYPE_CHAR_PTR              13
#define TYPE_VOID_PTR              14
#define TYPE_VOID_PTR_PTR          15
#define TYPE_INT64                 16
#define TYPE_SMART_STREAM_TYPE     17
#define TYPE_SMART_STREAM_TYPE_PTR 18
#define TYPE_FLT32                 19
/** @} */

/*
Defines for classes.
*/
#define CLASS0      0          /* Camera Communications */
#define CLASS2      2          /* Configuration/Setup */
#define CLASS3      3          /* Data Acuisition */

/******************************************************************************/
/* Start of parameter ID definitions.                                         */
/* Format: TTCCxxxx, where TT = Data type, CC = Class, xxxx = ID number       */
/* Please note that some data types encoded in the parameter IDs do not       */
/* correspond to the actual parameter data type. Please always check the      */
/* ATTR_TYPE before using the parameter.                                      */
/******************************************************************************/

/**
@defgroup grp_pm_parameters PVCAM parameters
*/

/**
@addtogroup grp_pm_parameters
@{
*/

/* CAMERA COMMUNICATION PARAMETERS */

/**
@brief Returns the length of an information message for each device driver.

Some devices have no message. In other words, they return a value of 0 for bytes.

Datatype: @c #int16

@note The availability is camera dependent.
*/
#define PARAM_DD_INFO_LENGTH        ((CLASS0<<16) + (TYPE_INT16<<24) + 1)
/**
@brief Returns a version number for the device driver used to access the camera.

The version is a formatted hexadecimal number, of the style:

|  High byte    |      Low      |      byte       |
|:-------------:|--------------:|:----------------|
|               | High nibble   |   Low nibble    |
| Major version | Minor version | Trivial version |

For example, the number 0xB1C0 indicates major release 177, minor release 12,
and trivial change 0. A major release is defined as anything that alters the
user interface, calling sequence, or parameter interpretation of any device
driver interface function (anything that would alter the driver's API). A new
major release often requires the calling software to change, but wherever
possible, major releases are backward compatible with earlier releases. A minor
release should be completely transparent to higher level software, but may
include internal enhancements. A trivial change is reserved for use by the
software staff to keep track of extremely minor variations. The last digit may
also be used to flag versions of the driver constructed for unique customers or
situations. Minor and trivial releases should require no change in the calling
software.

Open the camera before calling this parameter. Note that different cameras on
the same system may use different drivers. Thus, each camera can have its own
driver, and its own driver version.

Datatype: @c #uns16
*/
#define PARAM_DD_VERSION            ((CLASS0<<16) + (TYPE_UNS16<<24) + 2)
/**
@brief Reads/sets the maximum number of command retransmission attempts that are
    allowed.

When a command or status transmission is garbled, the system signals for a
re-transmission. After a certain number of failed transmissions (an initial
attempt + max_retries), the system abandons the attempt and concludes that the
communication link has failed. The camera will not close, but the command or
status read returns with an error. The maximum number of retries is initially
set by the device driver, and is matched to the communication link, hardware
platform, and operating system. It may also be reset by the user.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_DD_RETRIES            ((CLASS0<<16) + (TYPE_UNS16<<24) + 3)
/**
@brief Reads/sets the maximum time the driver waits for acknowledgment.

I.e., the slowest allowable response speed from the camera. This is a crucial
factor used in the device driver for communication control. If the driver sends
a command to the camera and does not receive acknowledgment within the timeout
period, the driver times out and returns an error. Unless reset by the user,
this timeout is a default setting that is contained in the device driver and is
matched to the communication link, hardware platform, and operating system.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_DD_TIMEOUT            ((CLASS0<<16) + (TYPE_UNS16<<24) + 4)
/**
@brief Returns an information message for each device.

Some devices have no message. The user is responsible for allocating enough
memory to hold the message string. Required number of bytes can be obtained via
parameter #PARAM_DD_INFO_LENGTH.

Datatype: @c char*

@note The availability is camera dependent.
*/
#define PARAM_DD_INFO               ((CLASS0<<16) + (TYPE_CHAR_PTR<<24) + 5)

/**
@brief Returns a list of camera communication interfaces.

For example it can be USB 3.0, PCIe, etc. Use the #ATTR_CURRENT to retrieve the
currently selected interface. Use the #pl_get_enum_param function to retrieve
all camera supported interfaces.

Datatype: @c enum (@c #int32)

@see #PL_CAM_INTERFACE_TYPES
@note The availability is camera dependent.
*/
#define PARAM_CAM_INTERFACE_TYPE    ((CLASS0<<16) + (TYPE_ENUM<<24) + 10)
/**
@brief Returns a list of camera communication interface modes.

For example returns whether the interface is fully capable of imaging or if it
has limitations. Use the #ATTR_CURRENT to retrieve the mode of the currently
selected interface. Use the #pl_get_enum_param function to retrieve the list of
modes for all camera supported interfaces.

The number of items reported by this parameter corresponds to the number of
items reported by the #PARAM_CAM_INTERFACE_TYPE, using the #pl_get_enum_param
call one can build a table of camera interfaces and their modes, simply iterate
through both parameters and build the table, for example:

| Enum index | Type id | Type string | Mode id | Mode string |
|:----------:|:-------:|:-----------:|:-------:|:-----------:|
|      0     |    514  |  "USB 2.0"  |    1    |  "Control"  |
|      1     |    515  |  "USB 3.0"  |    2    |  "Imaging"  |
|      2     |   2051  |  "PCIe x4"  |    2    |  "Imaging"  |

Datatype: @c enum (@c #int32)

@see #PL_CAM_INTERFACE_MODES
@note The availability is camera dependent.
*/
#define PARAM_CAM_INTERFACE_MODE    ((CLASS0<<16) + (TYPE_ENUM<<24) + 11)

/* CONFIGURATION AND SETUP PARAMETERS */

/**
@brief Bias offset voltage.

The units do not correspond to the output pixel values in any simple fashion
(the conversion rate should be linear, but may differ from system to system) but
a lower offset voltage will yield a lower value for all output pixels. Pixels
brought below zero by this method will be clipped at zero. Pixels raised above
saturation will be clipped at saturation. Before you can change the offset
level, you must read the current offset level. The default offset level will
also vary from system to system and may change with each speed and gain setting.

Datatype: @c #int16

@warning THIS VALUE IS SET AT THE FACTORY AND SHOULD NOT BE CHANGED!
If you would like to change this value, please contact customer service before
doing so.

@note The availability is camera dependent.
*/
#define PARAM_ADC_OFFSET            ((CLASS2<<16) + (TYPE_INT16<<24)     + 195)
/**
@brief The name of the sensor.

The name is a null-terminated text string. The user must pass in a character
array that is at least #CCD_NAME_LEN elements long.

Datatype: @c char*
*/
#define PARAM_CHIP_NAME             ((CLASS2<<16) + (TYPE_CHAR_PTR<<24)  + 129)
/**
@brief The name of the system.

The name is a null-terminated text string. The user must pass in a character
array that is at least #MAX_SYSTEM_NAME_LEN elements long. It is meant to
replace the purpose of #PARAM_CHIP_NAME behavior on some cameras which were
reporting their friendly product name with this parameter, and in turn help
future cameras go back to reporting the name of the sensor with
#PARAM_CHIP_NAME.

Datatype: @c char*

@note The availability is camera dependent.
*/
#define PARAM_SYSTEM_NAME           ((CLASS2<<16) + (TYPE_CHAR_PTR<<24)  + 130)
/**
@brief The name of the vendor.

The name is a null-terminated text string. The user must pass in a character
array that is at least #MAX_VENDOR_NAME_LEN elements long. This is meant to
differentiate between "QImaging" and "Photometrics" products moving forward.

Datatype: @c char*

@note The availability is camera dependent.
*/
#define PARAM_VENDOR_NAME           ((CLASS2<<16) + (TYPE_CHAR_PTR<<24)  + 131)
/**
@brief The name of the product.

The name is a null-terminated text string. The user must pass in a character
array that is at least #MAX_PRODUCT_NAME_LEN elements long. This is meant to
report camera name like "Prime 95B" or "Retiga R6". OEMs should also consider
using this for branding their cameras.

Datatype: @c char*

@note The availability is camera dependent.
*/
#define PARAM_PRODUCT_NAME          ((CLASS2<<16) + (TYPE_CHAR_PTR<<24)  + 132)
/**
@brief The part number of the camera.

The part number is a null-terminated text string. The user must pass in a
character array that is at least #MAX_CAM_PART_NUM_LEN elements long.

Datatype: @c char*

@note The availability is camera dependent.
*/
#define PARAM_CAMERA_PART_NUMBER    ((CLASS2<<16) + (TYPE_CHAR_PTR<<24)  + 133)

/**
@brief This is the type of cooling used by the current camera.

See #PL_COOL_MODES enum for all possible values.

Datatype: @c enum (@c #int32)
*/
#define PARAM_COOLING_MODE          ((CLASS2<<16) + (TYPE_ENUM<<24)      + 214)
/**
@brief The number of milliseconds required for the sensor output preamp to
stabilize, after it is turned on.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_PREAMP_DELAY          ((CLASS2<<16) + (TYPE_UNS16<<24)     + 502)
/**
@brief The color mode of the sensor.

This enum parameter provides a list of all possible color masks defined in
#PL_COLOR_MODES type. The real mask applied on sensor is reported as current
value (#ATTR_CURRENT). Take into account that for mono cameras is this parameter
usually not available (for #ATTR_AVAIL it returns @c FALSE) instead of reporting
#COLOR_NONE value.

Datatype: @c enum (@c #int32)

@note The availability is camera dependent.
*/
#define PARAM_COLOR_MODE            ((CLASS2<<16) + (TYPE_ENUM<<24)      + 504)
/**
@brief Indicates whether this sensor runs in MPP mode.

See #PL_MPP_MODES enum for all possible values.

Datatype: @c enum (@c #int32)

@note The availability is camera dependent.
*/
#define PARAM_MPP_CAPABLE           ((CLASS2<<16) + (TYPE_ENUM<<24)      + 224)
/**
@brief The exposure time limit in milliseconds above which the preamp is turned
off during exposure.

Datatype: @c #uns32

@note The availability is camera dependent.
*/
#define PARAM_PREAMP_OFF_CONTROL    ((CLASS2<<16) + (TYPE_UNS32<<24)     + 507)

/* Sensor dimensions and physical characteristics */

/**
@brief The number of masked lines at the near end of the parallel register.

It is next to the serial register. 0 means no mask (no normal mask). If the
premask is equal to par_size, this probably indicates a frame transfer device
with an ordinary mask. Accordingly, the sensor should probably be run in frame
transfer mode.

Datatype: @c #uns16
*/
#define PARAM_PREMASK               ((CLASS2<<16) + (TYPE_UNS16<<24)     +  53)
/**
@brief The number of pixels discarded from the serial register before the first
real data pixel.

Datatype: @c #uns16
*/
#define PARAM_PRESCAN               ((CLASS2<<16) + (TYPE_UNS16<<24)     +  55)
/**
@brief The number of masked lines at the far end of the parallel register.

It's away from the serial register. This is the number of additional parallel
shifts that need to be done after readout to clear the parallel register.

Datatype: @c #uns16
*/
#define PARAM_POSTMASK              ((CLASS2<<16) + (TYPE_UNS16<<24)     +  54)
/**
@brief The number of pixels to discard from the serial register after the last
real data pixel.

These must be read or discarded to clear the serial register.

Datatype: @c #uns16
*/
#define PARAM_POSTSCAN              ((CLASS2<<16) + (TYPE_UNS16<<24)     +  56)
/**
@brief This is the center-to-center distance between pixels in the parallel
direction.

It is measured in nanometers. This is identical to #PARAM_PIX_PAR_SIZE if there
are no interpixel dead areas.

Datatype: @c #uns16
*/
#define PARAM_PIX_PAR_DIST          ((CLASS2<<16) + (TYPE_UNS16<<24)     + 500)
/**
@brief This is the size of the active area of a pixel, in the parallel direction.

It is measured in nanometers.

Datatype: @c #uns16
*/
#define PARAM_PIX_PAR_SIZE          ((CLASS2<<16) + (TYPE_UNS16<<24)     +  63)
/**
@brief This is the center-to-center distance between pixels in the serial
direction.

It is measured in nanometers. This is identical to #PARAM_PIX_SER_SIZE, if there
are no dead areas.

Datatype: @c #uns16
*/
#define PARAM_PIX_SER_DIST          ((CLASS2<<16) + (TYPE_UNS16<<24)     + 501)
/**
@brief This is the size of the active area of a pixel in the serial direction.

It is measured in nanometers.

Datatype: @c #uns16
*/
#define PARAM_PIX_SER_SIZE          ((CLASS2<<16) + (TYPE_UNS16<<24)     +  62)
/**
@brief Checks to see if the summing well exists.

When a @c TRUE is returned for #ATTR_AVAIL, the summing well exists.

Datatype: @c #rs_bool

@note The availability is camera dependent.
*/
#define PARAM_SUMMING_WELL          ((CLASS2<<16) + (TYPE_BOOLEAN<<24)   + 505)
/**
@brief Gets the full-well capacity of this sensor, measured in electrons.

Datatype: @c #uns32

@note The availability is camera dependent.
*/
#define PARAM_FWELL_CAPACITY        ((CLASS2<<16) + (TYPE_UNS32<<24)     + 506)
/**
@brief The parallel size of the sensor chip, in active rows.

The full size of the parallel register is actually (par_size + premask + postmask).

Datatype: @c #uns16
*/
#define PARAM_PAR_SIZE              ((CLASS2<<16) + (TYPE_UNS16<<24)     +  57)
/**
@brief The serial size of the sensor chip, in active columns.

Datatype: @c #uns16
*/
#define PARAM_SER_SIZE              ((CLASS2<<16) + (TYPE_UNS16<<24)     +  58)
/**
@brief Returns @c TRUE for #ATTR_AVAIL if the camera has accumulation capability.

Accumulation functionality is provided with the Class 93 FF plug-in.

Datatype: @c #rs_bool

@note The availability is camera dependent.
*/
#define PARAM_ACCUM_CAPABLE         ((CLASS2<<16) + (TYPE_BOOLEAN<<24)   + 538)
/**
@brief Reports if the camera supports downloading things out of the camera.

This parameter is for Photometrics internal use only. It is largely unused
because we simply do it on all cameras now, thus it can become deprecated in
future.

Datatype: @c #rs_bool

@note The availability is camera dependent.
*/
#define PARAM_FLASH_DWNLD_CAPABLE   ((CLASS2<<16) + (TYPE_BOOLEAN<<24)   + 539)

/* General parameters */

/**
@brief Time it will take to read out the image from the sensor with the current
camera settings, in microseconds.

Settings have to be applied with #pl_exp_setup_seq or #pl_exp_setup_cont before
the camera will calculate the readout time for the new settings.

Datatype: @c #uns32

@note The availability is camera dependent.
*/
#define PARAM_READOUT_TIME          ((CLASS2<<16) + (TYPE_FLT64<<24)     + 179)
/**
@brief This parameter reports the time needed to clear the sensor.

The time is reported in nano seconds. This delay is incurred once prior to the
acquisition when pre-sequence clearing mode is chosen by the application. The
delay is incurred prior to every frame when the imaging application chooses
pre-exposure clearing mode.

The value is valid only after #pl_exp_setup_seq or #pl_exp_setup_cont call.

Datatype: @c #long64

@note The availability is camera dependent.
*/
#define PARAM_CLEARING_TIME         ((CLASS2<<16) + (TYPE_INT64<<24)     + 180)
/**
@brief Post trigger delay, in nano-seconds.

In addition to the #PARAM_CLEARING_TIME, there might be a delay between an
internal or external trigger and the transition event (low to high) for the
expose out signal. This happens, for example, in global all rows expose out mode
in which case the value is equal to readout time.

The value is valid only after #pl_exp_setup_seq or #pl_exp_setup_cont call.

Datatype: @c #long64

@note The availability is camera dependent.
*/
#define PARAM_POST_TRIGGER_DELAY    ((CLASS2<<16) + (TYPE_INT64<<24)     + 181)
/**
@brief Pre trigger delay, in nano-seconds.

For pre-exposure clearing mode and the first frame in pre-sequence clearing mode
the frame cycle time is the sum of #PARAM_EXPOSURE_TIME, #PARAM_PRE_TRIGGER_DELAY,
#PARAM_POST_TRIGGER_DELAY and #PARAM_CLEARING_TIME.

For second and subsequent frames in pre-sequence clearing mode (most typical
scenario) the frame cycle time is the sum of #PARAM_EXPOSURE_TIME,
#PARAM_PRE_TRIGGER_DELAY and #PARAM_POST_TRIGGER_DELAY.

Frame cycle time is defined as the interval between start of exposure for one
frame and the start of exposure for the next frame when the camera is in
internal triggered (timed) mode and setup for continuous (circular buffer)
acquisition.

The value is valid only after #pl_exp_setup_seq or #pl_exp_setup_cont call.

Datatype: @c #long64

@note The availability is camera dependent.
*/
#define PARAM_PRE_TRIGGER_DELAY     ((CLASS2<<16) + (TYPE_INT64<<24)     + 182)

/* CAMERA PARAMETERS */

/**
@brief Number of clear cycles.

This is the number of times the sensor must be cleared to completely remove
charge from the parallel register. The value is ignored in case the clearing
mode is set to #CLEAR_NEVER via #PARAM_CLEAR_MODE parameter.

Datatype: @c #uns16
*/
#define PARAM_CLEAR_CYCLES          ((CLASS2<<16) + (TYPE_UNS16<<24)     +  97)
/**
@brief Defines when clearing takes place.

All posible clearing modes are defined in #PL_CLEAR_MODES enum. But keep in
mind that some cameras might not support all modes. Use #pl_get_enum_param
function to enumerate all supported modes.

Datatype: @c enum (@c #int32)

@see @ref Clear_modes, @ref SCMOSClearControl
@note The availability is camera dependent.
*/
#define PARAM_CLEAR_MODE            ((CLASS2<<16) + (TYPE_ENUM<<24)      + 523)
/**
@brief Reports frame transfer capability.

Returns @c TRUE for #ATTR_AVAIL if this camera can run in frame transfer mode
(set through #PARAM_PMODE).

Datatype: @c #rs_bool

@note The availability is camera dependent.
*/
#define PARAM_FRAME_CAPABLE         ((CLASS2<<16) + (TYPE_BOOLEAN<<24)   + 509)
/**
@brief Parallel clocking method.

See #PL_PMODES enum for all possible values.
The @c "_FT" in mode name indicates frame transfer mode, @c "_FT_MPP" indicates
both frame transfer and MPP mode. @c "_ALT" indicates that custom parameters may
be loaded.

Datatype: @c enum (@c #int32)
*/
#define PARAM_PMODE                 ((CLASS2<<16) + (TYPE_ENUM <<24)     + 524)

/* Temperature parameters for the detector. */

/**
@brief Returns the current measured temperature of the sensor in hundredths of
degrees Celsius.

For example, a temperature of minus 35°C would be read as -3500.

Datatype: @c #int16

@note The availability is camera dependent.
*/
#define PARAM_TEMP                  ((CLASS2<<16) + (TYPE_INT16<<24)     + 525)
/**
@brief Sets the desired sensor temperature in hundredths of degrees Celsius.

E.g. -35°C is represented as -3500. The hardware attempts to heat or cool the
sensor to this temperature. The min/max allowable temperatures are given
#ATTR_MIN and #ATTR_MAX. Settings outside this range are ignored. Note that this
function only sets the desired temperature. Even if the desired temperature is
in a legal range, it still may be impossible to achieve. If the ambient
temperature is too high, it is difficult to get much cooling on an air-cooled
camera.

Datatype: @c #int16

@note The availability is camera dependent.
*/
#define PARAM_TEMP_SETPOINT         ((CLASS2<<16) + (TYPE_INT16<<24)     + 526)

/* Parameters used for firmware version retrieval. */

/**
@brief Returns the firmware version of the camera, as a hexadecimal number.

The form is @c MMmm, where @c MM is the major version and @c mm is the minor
version. For example, 0x0814 corresponds to version 8.20.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_CAM_FW_VERSION        ((CLASS2<<16) + (TYPE_UNS16<<24)     + 532)
/**
@brief Returns the alphanumeric serial number for the camera head.

The serial number for Photometrics-brand cameras has a maximum length of
#MAX_ALPHA_SER_NUM_LEN.

Datatype: @c char*

@note The availability is camera dependent.
*/
#define PARAM_HEAD_SER_NUM_ALPHA    ((CLASS2<<16) + (TYPE_CHAR_PTR<<24)  + 533)
/**
@brief Returns the version number of the PCI firmware.

This number is a single 16-bit unsigned value.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_PCI_FW_VERSION        ((CLASS2<<16) + (TYPE_UNS16<<24)     + 534)

/**
@brief Sets and gets the desired fan speed.

However, camera can automatically adjust the fan speed to higher level due to
sensor overheating or completely shut down power to the sensor board to protect
camera from damage. The default fan speed is supposed to be changed only
temporarily during experiments to reduce sound noise or vibrations.

Datatype: @c enum (@c #int32)

@warning Use this parameter with caution.
@note The availability is camera dependent.
*/
#define PARAM_FAN_SPEED_SETPOINT    ((CLASS2<<16) + (TYPE_ENUM<<24)      + 710)
/**
@brief Returns description of all camera nodes.

The text is a multi-line and null-terminated string. The user must pass in a
character array that is at least #MAX_CAM_SYSTEMS_INFO_LEN elements long or
dynamically allocated array to size returned for #ATTR_COUNT attribute.

The format is the same as can be seen in output of @c VersionInformation tool.

Datatype: @c char*

@warning Be very careful when you use this parameter. It is known to hang some
cameras when used together with other parameters e.g. while scanning camera
capabilities after open (Especially with Retiga R1/R3/R6 cameras). To work
around this limitation ensure there is no communication with camera one second
before and one second after this parameter is used!
@note The availability is camera dependent.
*/
#define PARAM_CAM_SYSTEMS_INFO      ((CLASS2<<16) + (TYPE_CHAR_PTR<<24)  + 536)

/**
@brief The exposure/triggering mode.

This parameter cannot be set but its value can be retrieved. The mode is set as
a value combined with expose-out mode via #pl_exp_setup_seq or
#pl_exp_setup_cont function.
See #PL_EXPOSURE_MODES enum for all possible values.

Datatype: @c enum (@c #int32)

@see @ref Exposure_modes, @ref sec_expModesExtended
*/
#define PARAM_EXPOSURE_MODE         ((CLASS2<<16) + (TYPE_ENUM<<24)      + 535)
/**
@brief The expose-out mode.

This parameter cannot be set but its value can be retrieved. The mode is set as
a value combined with extended exposure mode via #pl_exp_setup_seq or
#pl_exp_setup_cont function.
See #PL_EXPOSE_OUT_MODES enum for all possible values.

Datatype: @c enum (@c #int32)

@see @ref sec_exposeOutModes, @ref sec_expModesExtended
@note The availability is camera dependent.
*/
#define PARAM_EXPOSE_OUT_MODE       ((CLASS2<<16) + (TYPE_ENUM<<24)      + 560)

/* SPEED TABLE PARAMETERS */

/**
@brief Number of bits output by the currently selected speed choice.

Although this number might range between 6 and 16, the data will always be
returned in an unsigned 16-bit word. This value indicates the number of valid
bits within that word.

Datatype: @c #int16

@see @ref Port_and_speed_choices
*/
#define PARAM_BIT_DEPTH             ((CLASS2<<16) + (TYPE_INT16<<24)     + 511)
/**
@brief *Native* image format of the camera pixel stream.

This parameter is used to retrieve list of camera supported image formats. The
image format may depend on currently selected port and speed combination. It is
advised to check the image format before starting the acquisition. Some cameras
allow the native format to be selected. Use the #ATTR_ACCESS to check the write
permissions.

Datatype: @c enum (@c #int32)

@see #PL_IMAGE_FORMATS enum for all possible values.
*/
#define PARAM_IMAGE_FORMAT          ((CLASS2<<16) + (TYPE_ENUM<<24)      + 248)
/**
@brief *Native* image compression of the camera pixel stream.

This parameter is used to retrieve list of camera supported image compression modes.
The compression mode may depend on currently selected port and speed combination.
It is advised to check the compression mode before starting the acquisition. Some
cameras allow the native compression to be selected. Use the #ATTR_ACCESS to check
the write permissions.

Datatype: @c enum (@c #int32)

@see #PL_IMAGE_COMPRESSIONS enum for all possible values.
*/
#define PARAM_IMAGE_COMPRESSION     ((CLASS2<<16) + (TYPE_ENUM<<24)      + 249)
/**
@brief Scan mode of the camera.

This parameter is used to retrieve list of camera supported scan modes.

Datatype: @c enum (@c #int32)

@see #PL_SCAN_MODES enum for all possible values.
*/
#define PARAM_SCAN_MODE             ((CLASS3<<16) + (TYPE_ENUM<<24)      + 250)
/**
@brief Scan direction of the camera.

This parameter is used to retrieve list of camera supported scan directions.

Datatype: @c enum (@c #int32)

@see #PL_SCAN_DIRECTIONS enum for all possible values.
*/
#define PARAM_SCAN_DIRECTION                ((CLASS3<<16) + (TYPE_ENUM<<24)      + 251)
/**
@brief Scan direction reset state of the camera .

This parameter is used to retrieve scan direction reset state of camera.

Datatype: @c boolean (@c #rs_bool)
*/
#define PARAM_SCAN_DIRECTION_RESET          ((CLASS3<<16) + (TYPE_BOOLEAN<<24)      + 252)
/**
@brief Scan line delay value of the camera.

This parameter is used to retrieve scan line delay value of camera.

Datatype: @c uns16 (@c #uns16)
*/
#define PARAM_SCAN_LINE_DELAY               ((CLASS3<<16) + (TYPE_UNS16<<24)      + 253)
/**
@brief Scan line time of the camera.

This parameter is used to retrieve scan line time of camera.

Datatype: @c long64 (@c #long64)
*/
#define PARAM_SCAN_LINE_TIME                ((CLASS3<<16) + (TYPE_INT64<<24)      + 254)
/**
@brief Scan width in number of lines.

This parameter is used to retrieve scan width of camera.

Datatype: @c uns16 (@c #uns16)
*/
#define PARAM_SCAN_WIDTH                    ((CLASS3<<16) + (TYPE_UNS16<<24)      + 255)
/**
@brief Gain setting for the current speed choice.

The valid range for a gain setting is reported via #ATTR_MIN and #ATTR_MAX,
where the min. gain is usually 1 the max. gain may be as high as 16. Values
outside this range will be ignored. Note that gain setting may not be linear!
Values 1-16 may not correspond to 1x-16x, and there are holes between the
values. However, when the camera is initialized, and every time a new speed is
selected, the system will always reset to run at a gain of 1x.

Datatype: @c #int16

@see @ref Port_and_speed_choices
*/
#define PARAM_GAIN_INDEX            ((CLASS2<<16) + (TYPE_INT16<<24)     + 512)
/**
@brief Selects the sensor readout speed from a table of available choices.

Entries are 0-based and the range of possible values is 0 to @c max_entries,
where @c max_entries can be determined using #ATTR_MAX attribute. This setting
relates to other speed table values, including #PARAM_BIT_DEPTH,
#PARAM_PIX_TIME, #PARAM_READOUT_PORT, #PARAM_GAIN_INDEX and #PARAM_GAIN_NAME.
After setting #PARAM_SPDTAB_INDEX, the gain setting is always reset to a value
corresponding to 1x gain. To use a different gain setting, call #pl_set_param
with #PARAM_GAIN_INDEX after setting the speed table index.

Datatype: @c #int16

@see @ref Port_and_speed_choices
@note The availability is camera dependent.
*/
#define PARAM_SPDTAB_INDEX          ((CLASS2<<16) + (TYPE_INT16<<24)     + 513)
/**
@brief Name of the currently selected Gain (via #PARAM_GAIN_INDEX).

Use #ATTR_AVAIL to check for the availability. The gain name has a maximum
length of #MAX_GAIN_NAME_LEN and can be retrieved with the #ATTR_CURRENT
attribute.

Datatype: @c char*

@see @ref Port_and_speed_choices
@note The availability is camera dependent.
*/
#define PARAM_GAIN_NAME             ((CLASS2<<16) + (TYPE_CHAR_PTR<<24)  + 514)
/**
@brief Sensor readout port being used by the currently selected speed.

Different readout ports (used for alternate speeds) flip the image in serial,
parallel, or both.

Datatype: @c enum (@c #int32)

@see @ref Port_and_speed_choices
@note The availability is camera dependent.
*/
#define PARAM_READOUT_PORT          ((CLASS2<<16) + (TYPE_ENUM<<24)      + 247)
/**
@brief This is the actual speed for the currently selected speed choice.

It returns the time for each pixel, in nanoseconds. This readout time will
change as new speed choices are selected.

Datatype: @c #uns16

@see @ref Port_and_speed_choices
@note The availability is camera dependent.
*/
#define PARAM_PIX_TIME              ((CLASS2<<16) + (TYPE_UNS16<<24)     + 516)

/* SHUTTER PARAMETERS */

/**
@brief The shutter close delay.

This is the number of milliseconds required for the shutter to close. The
software default values compensate for the standard shutter that is shipped with
all cameras. You only need to set this value if you are using a shutter with
characteristics that differ from the standard shutter.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_SHTR_CLOSE_DELAY      ((CLASS2<<16) + (TYPE_UNS16<<24)     + 519)
/**
@brief The shutter open delay.

This is the number of milliseconds required for the shutter to open. The
software default values compensate for the standard shutter that is shipped with
all cameras. You only need to set this value if you are using a shutter with
characteristics that differ from the standard shutter.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_SHTR_OPEN_DELAY       ((CLASS2<<16) + (TYPE_UNS16<<24)     + 520)
/**
@brief The shutter opening condition.

See #PL_SHTR_OPEN_MODES enum for all possible values.

Datatype: @c enum (@c #int32)

@see @ref Exposure_loops
@note The availability is camera dependent.
*/
#define PARAM_SHTR_OPEN_MODE        ((CLASS2<<16) + (TYPE_ENUM <<24)     + 521)
/**
@brief The state of the camera shutter.

If the shutter is run too fast, it will overheat and trigger #SHTR_FAULT. The
shutter electronics will disconnect until the temperature returns to a suitable
range. Note that although the electronics have reset the voltages to open or
close the shutter, there is a lag time for the physical mechanism to respond.
See also #PARAM_SHTR_OPEN_DELAY and #PARAM_SHTR_CLOSE_DELAY.
See #PL_SHTR_MODES enum for all possible values.

Datatype: @c enum (@c #int32)

@note The availability is camera dependent.
*/
#define PARAM_SHTR_STATUS           ((CLASS2<<16) + (TYPE_ENUM <<24)     + 522)

/* I/O PARAMETERS */

/**
@brief Sets and gets the currently active I/O address.

The number of available I/O addresses can be obtained using the #ATTR_COUNT.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_IO_ADDR               ((CLASS2<<16) + (TYPE_UNS16<<24)     + 527)
/**
@brief Gets the type of I/O available at the current address.

See #PL_IO_TYPE enum for all possible values.

Datatype: @c enum (@c #int32)

@note The availability is camera dependent.
*/
#define PARAM_IO_TYPE               ((CLASS2<<16) + (TYPE_ENUM<<24)      + 528)
/**
@brief Gets the direction of the signal at the current address.

See #PL_IO_DIRECTION enum for all possible values.

Datatype: @c enum (@c #int32)

@note The availability is camera dependent.
*/
#define PARAM_IO_DIRECTION          ((CLASS2<<16) + (TYPE_ENUM<<24)      + 529)
/**
@brief Sets and gets the state of the currently active I/O signal.

The new (when setting) or return (when getting) value has different meanings,
depending on the I/O type:
- #IO_TYPE_TTL - A bit pattern, indicating the current state (0 or 1) of each of
  the control lines (bit 0 indicates line 0 state, etc.).
- #IO_TYPE_DAC - The value of the desired analog output (only applies to
  #pl_set_param).

The minimum and maximum range for the signal can be obtained using the #ATTR_MIN
and #ATTR_MAX attributes, respectively.

When outputting signals, the state is the desired output. For example, when
setting the output of a 12-bit DAC with a range of 0-5V to half-scale, the state
should be 2.5 (volts), not 1024 (bits).

Datatype: @c #flt64

@note The availability is camera dependent.
*/
#define PARAM_IO_STATE              ((CLASS2<<16) + (TYPE_FLT64<<24)     + 530)
/**
@brief Gets the bit depth for the signal at the current address.

The bit depth has different meanings, depending on the I/O Type:
- #IO_TYPE_TTL - The number of bits read or written at this address.
- #IO_TYPE_DAC - The number of bits written to the DAC.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_IO_BITDEPTH           ((CLASS2<<16) + (TYPE_UNS16<<24)     + 531)

/* GAIN MULTIPLIER PARAMETERS */

/**
@brief Gain multiplication factor for cameras with multiplication gain
functionality.

The valid range is reported via #ATTR_MIN and #ATTR_MAX.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_GAIN_MULT_FACTOR      ((CLASS2<<16) + (TYPE_UNS16<<24)     + 537)
/**
@brief Gain multiplier on/off indicator for cameras with the multiplication gain
functionality.

This parameter may be read-only, in which case the gain is always on.

Datatype: @c #rs_bool

@note The availability is camera dependent.
*/
#define PARAM_GAIN_MULT_ENABLE      ((CLASS2<<16) + (TYPE_BOOLEAN<<24)   + 541)

/* POST PROCESSING PARAMETERS */

/**
@brief This returns the name of the currently-selected post-processing feature.

The name is a null-terminated text string. User is responsible for buffer
allocation with at least #MAX_PP_NAME_LEN bytes.

Datatype: @c char*

@note The availability is camera dependent.
*/
#define PARAM_PP_FEAT_NAME          ((CLASS2<<16) + (TYPE_CHAR_PTR<<24) +  542)
/**
@brief This selects the current post-processing feature from a table of
available choices.

The entries are 0-based and the range of possible values is 0 to @c max_entries.
@c max_entries can be determined with the #ATTR_MAX attribute. This setting
relates to other post-processing table values, including #PARAM_PP_FEAT_NAME,
#PARAM_PP_FEAT_ID and #PARAM_PP_PARAM_INDEX.

Datatype: @c #int16

@note The availability is camera dependent.
*/
#define PARAM_PP_INDEX              ((CLASS2<<16) + (TYPE_INT16<<24)    +  543)
/**
@brief Gets the actual e/ADU for the current gain setting.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_ACTUAL_GAIN           ((CLASS2<<16) + (TYPE_UNS16<<24)     + 544)
/**
@brief This selects the current post-processing parameter from a table of
available choices.

The entries are 0-based and the range of possible values is 0 to @c max_entries.
@c max_entries can be determined with the #ATTR_MAX attribute. This setting
relates to other post-processing table values, including #PARAM_PP_PARAM_NAME,
#PARAM_PP_PARAM_ID and #PARAM_PP_PARAM.

Datatype: @c #int16

@note The availability is camera dependent.
*/
#define PARAM_PP_PARAM_INDEX        ((CLASS2<<16) + (TYPE_INT16<<24)    +  545)
/**
@brief Gets the name of the currently-selected post-processing parameter for the
currently-selected post-processing feature.

The name is a null-terminated text string. User is responsible for buffer
allocation with at least #MAX_PP_NAME_LEN bytes.

Datatype: @c char*

@note The availability is camera dependent.
*/
#define PARAM_PP_PARAM_NAME         ((CLASS2<<16) + (TYPE_CHAR_PTR<<24) +  546)
/**
@brief This gets or sets the post-processing parameter for the currently-selected
post-processing parameter in the index.

Datatype: @c #uns32

@note The availability is camera dependent.
*/
#define PARAM_PP_PARAM              ((CLASS2<<16) + (TYPE_UNS32<<24)    +  547)
/**
@brief Gets the read noise for the current speed.

Datatype: @c #uns16

@note The availability is camera dependent.
*/
#define PARAM_READ_NOISE            ((CLASS2<<16) + (TYPE_UNS16<<24)     + 548)
/**
@brief This returns the ID of the currently-selected post-processing feature.

This maps a specific post-processing module across cameras to help applications
filter for camera features they need to expose and those that they don't. It
helps to identify similarities between camera post-processing features.

Datatype: @c #uns32

@note The availability is camera dependent.
*/
#define PARAM_PP_FEAT_ID            ((CLASS2<<16) + (TYPE_UNS16<<24)    +  549)
/**
@brief This returns the ID of the currently-selected post-processing parameter.

This maps a specific post-processing parameter across cameras to help
applications filter for camera features they need to expose and those that they
don't. It helps to identify similarities between camera post-processing features.

Datatype: @c #uns32

@note The availability is camera dependent.
*/
#define PARAM_PP_PARAM_ID           ((CLASS2<<16) + (TYPE_UNS16<<24)    +  550)

/* S.M.A.R.T. STREAMING PARAMETERS */

/**
@brief This parameter allows the user to retrieve or set the state of the
S.M.A.R.T. streaming mode.

When a @c TRUE is returned by the camera, S.M.A.R.T. streaming is enabled.

Datatype: @c #rs_bool

@see @ref SMART_streaming
@note The availability is camera dependent.
*/
#define PARAM_SMART_STREAM_MODE_ENABLED     ((CLASS2<<16) + (TYPE_BOOLEAN<<24)  +  700)
/**
@brief This parameter allows the user to select between available S.M.A.R.T.
streaming modes.

See #PL_SMT_MODES enum for all possible values.
Currently the only available mode is #SMTMODE_ARBITRARY_ALL.

Datatype: @c #uns16

@see @ref SMART_streaming
@note The availability is camera dependent.
*/
#define PARAM_SMART_STREAM_MODE             ((CLASS2<<16) + (TYPE_UNS16<<24)    +  701)
/**
@brief This parameter allows to set or read the current exposure parameters for
S.M.A.R.T. streaming.

Datatype: @c #smart_stream_type*

@see @ref SMART_streaming
@note The availability is camera dependent.
*/
#define PARAM_SMART_STREAM_EXP_PARAMS       ((CLASS2<<16) + (TYPE_VOID_PTR<<24) +  702)
/**
@brief This parameter allows to set or read the current delays between exposures
in S.M.A.R.T. streaming.

Datatype: @c #smart_stream_type*

@see @ref SMART_streaming
@note The availability is camera dependent.
@note This parameter is currently not supported and #ATTR_AVAIL always returns
@c FALSE.
*/
#define PARAM_SMART_STREAM_DLY_PARAMS       ((CLASS2<<16) + (TYPE_VOID_PTR<<24) +  703)

/* ACQUISITION PARAMETERS */

/**
@brief Used to examine and change the exposure time in VTM only.

VTM is active if exposure mode is set to #VARIABLE_TIMED_MODE. This value is
limited to 16-bit. For higher exposure times separate single frame acquisitions,
or SMART streaming (if available), have to be used.

Datatype: @c #uns16
*/
#define PARAM_EXP_TIME              ((CLASS3<<16) + (TYPE_UNS16<<24)     +   1)
/**
@brief Gets the exposure resolution for the current resolution index.

This parameter does exactly the same as #PARAM_EXP_RES_INDEX but additionally
provides human-readable string for each exposure resolution.

For some older cameras this parameter might not be available (#ATTR_AVAIL
returns @c FALSE). In this case camera uses #EXP_RES_ONE_MILLISEC resolution.

Datatype: @c enum (@c #int32)
*/
#define PARAM_EXP_RES               ((CLASS3<<16) + (TYPE_ENUM<<24)      +   2)
/**
@brief Gets and sets the index into the exposure resolution table.

The table contains the resolutions supported by the camera. The value at this
index is an enumerated type, representing different resolutions. The number of
supported resolutions can be obtained by using the #ATTR_COUNT attribute.
See #PL_EXP_RES_MODES enum for all possible values.

Datatype: @c #uns16
*/
#define PARAM_EXP_RES_INDEX         ((CLASS3<<16) + (TYPE_UNS16<<24)     +   4)
/**
@brief Used to examine current exposure time and range of valid values.

The minimum and maximum value could be limited by camera HW. Use #ATTR_MIN and
#ATTR_MAX to retrieve it. This parameter is always available but for older
cameras not reporting their limits, the min. value is set to 0 and max. value
set to max. 32-bit value for backward compatibility. It means the range is not
known (it does not mean there are no limits). In such case e.g. camera manual
could specify some limits. Please note the reported value unit depends on
currently selected exposure resolution (#PARAM_EXP_RES).

Datatype: @c #ulong64
*/
#define PARAM_EXPOSURE_TIME         ((CLASS3<<16) + (TYPE_UNS64<<24)     +   8)

/* PARAMETERS FOR  BEGIN and END of FRAME Interrupts */

/**
@brief Enables and configures the BOF/EOF interrupts.

See #PL_IRQ_MODES enum for all possible values.

Datatype: @c enum (@c #int32)

@note The availability is camera dependent.
*/
#define PARAM_BOF_EOF_ENABLE        ((CLASS3<<16) + (TYPE_ENUM<<24)      +   5)
/**
@brief Returns the Begin-Of-Frame and/or End-Of-Frame count.

BOF/EOF counting is enabled and configured with #PARAM_BOF_EOF_ENABLE.

Datatype: @c #uns32

@note The availability is camera dependent.
*/
#define PARAM_BOF_EOF_COUNT         ((CLASS3<<16) + (TYPE_UNS32<<24)     +   6)
/**
@brief Clears the BOF/EOF count when a #pl_set_param is performed.

This is a write-only parameter.

Datatype: @c #rs_bool

@note The availability is camera dependent.
*/
#define PARAM_BOF_EOF_CLR           ((CLASS3<<16) + (TYPE_BOOLEAN<<24)   +   7)

/**
@brief Tests to see if the hardware/software can perform circular buffer.

When a @c TRUE is returned for #ATTR_AVAIL attribute, the circular buffer
function can be used.

Datatype: @c #rs_bool
*/
#define PARAM_CIRC_BUFFER           ((CLASS3<<16) + (TYPE_BOOLEAN<<24)   + 299)
/**
@brief Retrieves the min, max, current and recommended (default) buffer size in
bytes.

It applies for currently configured acquisition. This parameter becomes
available only after calling the #pl_exp_setup_seq or #pl_exp_setup_cont.
For sequence acquisition the attribute always report the full sequence size in
bytes. For circular buffer acquisition use the #ATTR_DEFAULT to retrieve the
recommended buffer size.

Datatype: @c #ulong64
*/
#define PARAM_FRAME_BUFFER_SIZE     ((CLASS3<<16) + (TYPE_UNS64<<24)     + 300)

/* Binning reported by camera */

/**
@brief Used to obtain serial part of serial x parallel binning factors
permutations.

It has to be always used in pair with #PARAM_BINNING_PAR parameter.

Datatype: @c enum (@c #int32)

@see @ref binning_factors_discovery
@note The availability is camera dependent.
*/
#define PARAM_BINNING_SER           ((CLASS3<<16) + (TYPE_ENUM<<24)      + 165)
/**
@brief Used to obtain parallel part of serial x parallel binning factors
permutations.

It has to be always used in pair with #PARAM_BINNING_SER parameter.

Datatype: @c enum (@c #int32)

@see @ref binning_factors_discovery
@note The availability is camera dependent.
*/
#define PARAM_BINNING_PAR           ((CLASS3<<16) + (TYPE_ENUM<<24)      + 166)

/* Parameters related to multiple ROIs and Centroids */

/**
@brief Parameter used to enable or disable the embedded frame metadata feature.

Once enabled the acquired frames will contain additional information describing
the frame.

Datatype: @c #rs_bool

@see @ref Embedded_frame_metadata
@note The availability is camera dependent.
*/
#define PARAM_METADATA_ENABLED      ((CLASS3<<16) + (TYPE_BOOLEAN<<24)   + 168)
/**
@brief The number of currently configured ROIs.

The #ATTR_CURRENT returns the currently configured number of ROIs set via
#pl_exp_setup_seq or #pl_exp_setup_cont functions. The #ATTR_MAX can be used to
retrieve the maximum number of ROIs the camera supports.

Datatype: @c #uns16
*/
#define PARAM_ROI_COUNT             ((CLASS3<<16) + (TYPE_UNS16  <<24)   + 169)
/**
@brief Parameter used to enable or disable the Centroids feature.

Datatype: @c #rs_bool

@see @ref Centroids
@note The availability is camera dependent.
*/
#define PARAM_CENTROIDS_ENABLED     ((CLASS3<<16) + (TYPE_BOOLEAN<<24)   + 170)
/**
@brief Deals with Centroid radius.

This read-write parameter is used to obtain the range of Centroids radii the
camera supports. Use the #ATTR_MIN and #ATTR_MAX to retrieve the range.

The radius defines the distance from the center pixel. For example if the camera
reports the radius range between 1 and 5 it means that the resulting ROIs can be
configured to following sizes: 1=3x3, 2=5x5, 3=7x7, 4=9x9, 5=11x11.

Use #pl_set_param to set the desired Centroids radius. Once set, make sure to
reconfigure the acquisition with #pl_exp_setup_seq or #pl_exp_setup_cont
functions.

Datatype: @c #uns16

@see @ref Centroids
@note The availability is camera dependent.
*/
#define PARAM_CENTROIDS_RADIUS      ((CLASS3<<16) + (TYPE_UNS16  <<24)   + 171)
/**
@brief Deals with number of Centroids.

This read-write parameter is used to obtain the supported number of Centroids
and set the desired number of Centroids to the camera.

Datatype: @c #uns16

@see @ref Centroids
@note The availability is camera dependent.
*/
#define PARAM_CENTROIDS_COUNT       ((CLASS3<<16) + (TYPE_UNS16  <<24)   + 172)
/**
@brief Deals with Centroid modes.

In case the camera supports centroids but reports this parameter as not
available, it uses #PL_CENTROIDS_MODE_LOCATE.
See #PL_CENTROIDS_MODES enum for all possible values.

Datatype: @c enum (@c #int32)

@see @ref Centroids
@note The availability is camera dependent.
*/
#define PARAM_CENTROIDS_MODE        ((CLASS3<<16) + (TYPE_ENUM   <<24)   + 173)
/**
@brief Supported Centroids background frame processing count.

This allows the camera to report supported selections for number of frames for
dynamic background removal. The processing is optimized only for selected set of
frames. Thus there is no related enumeration type with supported values for this
parameter.

Datatype: @c enum (@c #int32)

@see @ref Centroids
@note The availability is camera dependent.
*/
#define PARAM_CENTROIDS_BG_COUNT    ((CLASS3<<16) + (TYPE_ENUM   <<24)   + 174)
/**
@brief Used to configure threshold multiplier for particle detection.

It is a fixed-point real number in format Q8.4.
E.g. the value 1234 (0x4D2) means 77.2 (0x4D hex = 77 dec).

Datatype: @c #uns32

@see @ref Centroids
@note The availability is camera dependent.
*/
#define PARAM_CENTROIDS_THRESHOLD   ((CLASS3<<16) + (TYPE_UNS32  <<24)   + 175)

/* Parameters related to triggering table */

/**
@brief Used to select the output signal to be configured.

The configuration of number of active outputs is done via
#PARAM_LAST_MUXED_SIGNAL parameter.
See #PL_TRIGTAB_SIGNALS enum for all possible values.

Datatype: @c enum (@c #int32)

@see @ref TriggTable
@note The availability is camera dependent.
*/
#define PARAM_TRIGTAB_SIGNAL        ((CLASS3<<16) + (TYPE_ENUM<<24)      + 180)
/**
@brief Used to set the number of active output signals.

The chosen number of signals is then used by multiplexer for the signal
selected by #PARAM_TRIGTAB_SIGNAL parameter.

Datatype: @c #uns8

@see @ref TriggTable
@note The availability is camera dependent.
*/
#define PARAM_LAST_MUXED_SIGNAL     ((CLASS3<<16) + (TYPE_UNS8<<24)      + 181)
/**
@brief Deals with frame delivery modes.

This parameter allows to switch among various frame delivery modes.
If not available, camera runs in #PL_FRAME_DELIVERY_MODE_MAX_FPS mode.
See #PL_FRAME_DELIVERY_MODES enum for all possible values.

Datatype: @c enum (@c #int32)

@note The availability is camera dependent.
*/
#define PARAM_FRAME_DELIVERY_MODE   ((CLASS3<<16) + (TYPE_ENUM <<24)     + 400)

/** @} */ /* grp_pm_parameters */

/******************************************************************************/
/* End of parameter ID definitions.                                           */
/******************************************************************************/

/******************************************************************************/
/* Start of function prototypes.                                              */
/******************************************************************************/

#ifndef PV_EMBEDDED

/**
@defgroup grp_pm_deprecated_functions Deprecated PVCAM functions
@ingroup grp_pm_deprecated
These functions are included for compatibility reasons.
*/

/**
@defgroup grp_callbacks Callbacks

Use these callback function signatures with corresponding callback registering
functions to register for various camera notifications.

C++ code example:
(Proper error handling and other camera initialization omitted for clarity)
@code{.cpp}
void MyCamera::initialize()
{
    // Register for the End-Of-Frame notifications, passing 'this' as a context
    // in order to properly forward the notification to this class.
    pl_cam_register_callback_ex3(m_hCam, PL_CALLBACK_EOF, (void*)pvcamCallbackEofEx3, this);
}
void MyCamera::handleEofCallback(const FRAME_INFO* pFrameInfo)
{
    uns16* pFrameData = NULL;
    pl_exp_get_latest_frame(m_hCam, (void**)&pFrameData);
    // The displayFrame() should not do any lenghty processing, we need to
    // release the callback routine as quickly as possible.
    displayFrame(pFrameData, pFrameInfo);
}

// Using the PL_CALLBACK_SIG_EX3 function signature. This function is declared
// as static in the header file.
void PV_DECL MyCamera::pvcamCallbackEofEx3(const FRAME_INFO* pFrameInfo, void* pContext)
{
    MyCamera* pCamera = static_cast<MyCamera*>(pContext);
    pCamera->handleEofCallback(pFrameInfo);
}
@endcode

@{
*/

/**
A callback function signature for the #pl_cam_register_callback function.
*/
typedef void (PV_DECL *PL_CALLBACK_SIG_LEGACY)(void);

/**
A callback function signature for the #pl_cam_register_callback_ex function.

@param[in]  pContext    A pointer to the user defined context that was previously
                        passed into the #pl_cam_register_callback_ex function.
*/
typedef void (PV_DECL *PL_CALLBACK_SIG_EX)(void* pContext);

/**
A callback function signature for the #pl_cam_register_callback_ex2 function.

@param[in]  pFrameInfo  A pointer to a FRAME_INFO structure uniquely identifying
                        the incoming frame.
*/
typedef void (PV_DECL *PL_CALLBACK_SIG_EX2)(const FRAME_INFO* pFrameInfo);

/**
A callback function signature for the #pl_cam_register_callback_ex3 function.

@param[in]  pFrameInfo  A pointer to a FRAME_INFO structure uniquely identifying
                        the incoming frame.
@param[in]  pContext    A pointer to the user defined context that was previously
                        passed into the #pl_cam_register_callback_ex3 function.
*/
typedef void (PV_DECL *PL_CALLBACK_SIG_EX3)(const FRAME_INFO* pFrameInfo, void* pContext);

/** @} */ /* grp_callbacks */

#ifdef PV_C_PLUS_PLUS
extern "C"
{
#endif

/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*                 Camera Communications Function Prototypes                 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/

/**
@defgroup grp_pm_functions Public API functions
*/

/**
@addtogroup grp_pm_functions
@{
*/

/**
@brief Returns the PVCAM version number.
This function returns a version number for this edition of PVCAM.

The version is a highly formatted hexadecimal number, of the style:

|  High byte   |      Low      |      byte      |
|:------------:|--------------:|:---------------|
|              | High nibble   |   Low nibble   |
| Major version| Minor version | Trivial version|

For example, the number 0x11F1 indicates major release 17, minor release 15, and
trivial change 1. A major release is defined as anything that alters the interface,
calling sequence, parameter list, or interpretation of any function in the library.
This includes new functions and alterations to existing functions, but it does not
include alterations to the options libraries, which sit on top of PVCAM
(each option library includes its own, independent version number). A new major release
often requires a change in the PVCAM library, but wherever possible, major releases
are backward compatible with earlier releases. A minor release should be completely
transparent to higher-level software (PVCAM) but may include internal enhancements.
The trivial version is reserved for use by the software staff to keep track of extremely
minor variations. The last digit is used for build numbers, and should be ignored. Minor
and trivial releases should require no change in the calling software.

@param[out] pvcam_version   Version number of PVCAM installer.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see #PARAM_DD_VERSION
*/
rs_bool PV_DECL pl_pvcam_get_ver(uns16* pvcam_version);

/**
@brief Opens and initializes the library.

The PVCAM library requires significant system resources: memory, hardware access, etc.
#pl_pvcam_init prepares these resources for use, as well as allocating whatever static
memory the library needs. Until #pl_pvcam_init is called, every PVCAM function
(except for the error reporting functions) will fail and return an error message
that corresponds to <em>"library has not been initialized"</em>.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@note If this call fails, #pl_error_code contains the code that lists the reason for failure.

@see pl_pvcam_uninit, pl_cam_open, pl_error_code
*/
rs_bool PV_DECL pl_pvcam_init(void);

/**
@brief Closes the library, closes all devices, frees memory.

This function releases all system resources that #pl_pvcam_init acquired.
It also searches for all cameras that the user has opened. If it finds any,
it will close them before exiting.
It will also unlock and free memory, and clean up after itself as much as possible.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_pvcam_init, pl_cam_close, pl_error_code

@warning If the hardware is involved in acquiring data, the system may not be
able to disconnect immediately.
*/
rs_bool PV_DECL pl_pvcam_uninit(void);

/** @} */ /* grp_pm_functions */

/**
@addtogroup grp_pm_deprecated_functions
@{
*/
DEPRECATED rs_bool PV_DECL pl_cam_check(int16 hcam);
/** @} */ /* grp_pm_deprecated_functions */

/**
@addtogroup grp_pm_functions
@{
*/

/**
@brief Frees the current camera, prepares it for power-down.

This function has two effects. First, it removes the listed camera from
the reserved list, allowing other users to open and use the hardware.
Second, it performs all cleanup, close-down, and shutdown preparations needed
by the hardware. A camera can only be closed if it was previously opened.

@param[in]  hcam    Camera handle returned from #pl_cam_open.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_cam_open, pl_pvcam_init, pl_pvcam_uninit

@note #pl_pvcam_uninit automatically calls a #pl_cam_close on all cameras opened by
the current user.
*/
rs_bool PV_DECL pl_cam_close(int16 hcam);

/**
@brief Returns the name of a camera.

This function allows a user to learn the string identifier associated with every
camera on the current system. This is a companion to the #pl_cam_get_total function.
cam_num input can run from 0 to (@c totl_cams-1), inclusive. The user must pass in
a string that is at least #CAM_NAME_LEN characters long, #pl_cam_get_name then fills
that string with an appropriate null-terminated string. @c camera_name can be passed
directly into the #pl_cam_open function. It has no other use, aside from providing
a brief description of the camera.

@param[in]  cam_num     Camera number Range: 0 through (@c totl_cams-1).
@param[out] camera_name Text name assigned to a camera (with RSConfig).

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_cam_get_total, pl_cam_open, pl_cam_close

@note This call reports the names of all cameras on the system, even if all the cameras
are not available. If the hardware is turned off, or if another user has a camera open,
the camera name is reported, but is not available. #pl_cam_get_name returns a name,
and #pl_cam_open gives information on availability of that camera.
To build a complete list of every camera on the system, it is necessary to cycle through
all entries, as shown below:
@code{.cpp}
int total_cameras;
char name[CAM_NAME_LEN];
...
pl_cam_get_total(&total_cameras);
for (i = 0; i < total_cameras; i++) {
    pl_cam_get_name(i, name);
    printf("Camera %d is called '%s'\n", i, name);
}
@endcode
*/
rs_bool PV_DECL pl_cam_get_name(int16 cam_num, char* camera_name);

/**
@brief Returns the number of cameras attached to the system.

This function reports the number of cameras on the system.
All listed cameras may not all be available on multi-tasking systems, some cameras
may already be in use by other users. A companion function #pl_cam_get_name can
be used to get the string identifier associated with each camera.

@param[out] totl_cams   Total number of cameras in the system.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_cam_get_name, pl_cam_open, pl_cam_close

@note This function actually searches for all device drivers on the system, without
checking hardware. The list of cameras is obtained during #pl_pvcam_init. Thus, if a new camera
(new device driver) is added after the library was opened, the system won't know that the new
camera is there. The system also will not notice if a camera is removed. (Obviously, this is
only important on multi-tasking systems). A cycle of @c uninit / @c init regenerates the list of available
cameras, updating the system for any additions or deletions.
*/
rs_bool PV_DECL pl_cam_get_total(int16* totl_cams);

/**
@brief Reserves and initializes the camera hardware.

The string @a camera_name should be identical to one of the valid camera names returned by #pl_cam_get_name.
If the name is valid, #pl_cam_open completes a short set of checks and diagnostics as it attempts
to establish communication with the camera electronics unit. If successful, the camera is opened
and a valid camera handle is passed back in hcam. Otherwise, #pl_cam_open returns with a failure.
An explanation is shown in #pl_error_code.

The @a o_mode setting controls the mode under which the camera is opened.
Currently, the only possible choice is #OPEN_EXCLUSIVE. On multi-user systems, opening a camera
under the exclusive mode reserves it for the current user, locking out all other users on the
system. If #pl_cam_open is successful, the user has sole access to that camera until the camera
is closed or #pl_pvcam_uninit is called.

@param[in]  camera_name Text name assigned to a camera (with RSConfig).
@param[out] hcam        Camera handle returned from #pl_cam_open.
@param[in]  o_mode      Mode to open the camera in (must be #OPEN_EXCLUSIVE).

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_cam_get_name, pl_cam_get_total, pl_cam_close, pl_pvcam_init, pl_pvcam_uninit

@warning Despite the above paragraph, a successful #pl_cam_open does not mean that the camera
is in working order. It does mean that you can communicate with the device driver associated
with the camera. After a successful #pl_cam_open, call #pl_error_message, which reports any error
conditions.
*/
rs_bool PV_DECL pl_cam_open(char* camera_name, int16* hcam, int16 o_mode);

/** @} */ /* grp_pm_functions */

/**
@addtogroup grp_pm_deprecated_functions
@{
*/
DEPRECATED rs_bool PV_DECL pl_cam_register_callback(int16 hcam, int32 callback_event,
                                                    void* callback);
DEPRECATED rs_bool PV_DECL pl_cam_register_callback_ex(int16 hcam, int32 callback_event,
                                                       void* callback, void* context);
DEPRECATED rs_bool PV_DECL pl_cam_register_callback_ex2(int16 hcam, int32 callback_event,
                                                        void* callback);
/** @} */ /* grp_pm_deprecated_functions */

/**
@addtogroup grp_pm_functions
@{
*/

/**
@brief Installs a function that will be called when an event occurs in a camera providing
information about frame via #FRAME_INFO type and with user context information.

This function combines functionality provided by #pl_cam_register_callback_ex
and #pl_cam_register_callback_ex2.

Use this API call to install a function that will be called when the specified event
occurs providing additional frame information. Input parameter of the callback function
must be of #FRAME_INFO* type in order to receive information about the frame
(timestamp with precision of 0.1ms, frame counter number, ID (handle) of the camera that
produced the frame). Also pointer to a context that will be echoed back when the callback
is invoked can be passed to PVCAM in this function.

#### Example of Callback function:

@code{.cpp}
void EOFCallbackHandler(FRAME_INFO* pFrameInfo, void* pContext)
{
    const int32 frameNr = pFrameInfo->FrameNr;
    const long64 frameTime = pFrameInfo->TimeStamp;
    const int16 camID = pFrameInfo->hCam;
    // Display or process frame info etc.
    if (*(int16*)pContext == hCamera1)
        EOFCountCamera1++;
    else if (*(int16*)pContext == hCamera2)
        EOFCountCamera2++;
}
@endcode

@param[in]   hcam           Camera handle returned from #pl_cam_open.
@param[in]   callback_event Callback event to register for (see #PL_CALLBACK_EVENT).
@param[out]  callback       Callback function pointer.
@param[out]  context        Pointer to custom user context.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_cam_deregister_callback

@warning #pl_exp_finish_seq must be called if acquiring in sequential mode
(using #pl_exp_setup_seq and #pl_exp_start_seq) with callbacks notification after all frames are
read out and before new exposure is started by calling #pl_exp_start_seq.
Not all callbacks will be available for all camera systems/interfaces.

@note Only #PL_CALLBACK_BOF and #PL_CALLBACK_EOF are fully supported by all camera types.
Do not use other callback types in generic-purpose software.
*/
rs_bool PV_DECL pl_cam_register_callback_ex3(int16 hcam, int32 callback_event,
                                             void* callback, void* context);

/**
@brief Uninstalls a function for camera system event.

Use this API call to uninstall a function for the specified camera system event.

@param[in]  hcam            Camera handle returned from #pl_cam_open.
@param[in]  callback_event  Callback event to register for (see #PL_CALLBACK_EVENT).

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_cam_register_callback, pl_cam_register_callback_ex, pl_cam_register_callback_ex2,
pl_cam_register_callback_ex3.

@note Only #PL_CALLBACK_BOF and #PL_CALLBACK_EOF are fully supported by all camera types.
Do not use other callback types in generic-purpose software.
See callback descriptions section under #pl_cam_register_callback_ex3 for details.
*/
rs_bool PV_DECL pl_cam_deregister_callback(int16 hcam, int32 callback_event);

/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*                     Error Reporting Function Prototypes                   */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/

/**
@brief Returns the most recent error condition.

As every PVCAM function begins, it resets the error code to 0.
If an error occurs later in the function, the error code is set to a corresponding value.

@return The current error code. Note that a call to #pl_error_code does not
reset the error code.

@see pl_error_message

@note #pl_error_code works even before #pl_pvcam_init is called.
This allows a message to be returned if #pl_pvcam_init fails.

@warning The PVCAM library does not intercept signals. Errors that interrupt
the normal process (divide by zero, etc.) may cause the software to crash,
and #pl_error_code may or may not contain useful information.
*/
int16   PV_DECL pl_error_code(void);

/**
@brief Returns a string explaining input error code.

This function fills in the character string msg with a message that corresponds
to the value in @a err_code. The msg string is allocated by the user, and should be
at least #ERROR_MSG_LEN elements long.

@param[in]  err_code Unique ID of the error: returned from #pl_error_code.
@param[out] msg      Text description of err_code.

@return Returns #PV_OK if a message corresponding to the input code is found,
#PV_FAIL if the code does not have a corresponding message
(@a msg will be filled with the string <em>"Unknown error"</em>).
Even if a #PV_FAIL is returned, the value of #pl_error_code is not altered.

@see pl_error_code

@note #pl_error_message works even before #pl_pvcam_init is called.
This allows a message to be printed if #pl_pvcam_init fails.
All error messages are standalone sentence without ending period having error
code name appended in parenthesis.
*/
rs_bool PV_DECL pl_error_message(int16 err_code, char* msg);

/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*                   Configuration/Setup Function Prototypes                 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/

/**
@brief Returns the requested attribute for a PVCAM parameter.

This function returns the requested attribute for a PVCAM parameter.

@a param_id is an enumerated type that indicates the parameter in question.
@a param_value points to the value of the requested attribute for the parameter.
It is a @c void* because it can be different data types. The user is responsible for
passing in the correct data type (see attribute descriptions that follow).
@a param_attribute is used to retrieve characteristics of the parameter.
See #PL_PARAM_ATTRIBUTES for possible values for @a param_attribute.

Reading of values for attributes #ATTR_AVAIL, #ATTR_ACCESS and #ATTR_TYPE should
always succeed and return correct value. Values for other attributes can be read
only if #ATTR_ACCESS reports either #ACC_READ_ONLY or #ACC_READ_WRITE.

@param[in]  hcam            Camera handle returned from #pl_cam_open.
@param[in]  param_id        ID of the parameter to get or set (PARAM_...).
@param[in]  param_attribute Attribute of the parameter to get (ATTR_...).
@param[out] param_value     Value to get or set.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_set_param, pl_get_enum_param

@note The data type of @a param_value is documented in pvcam.h for each param_id.
*/
rs_bool PV_DECL pl_get_param(int16 hcam, uns32 param_id,
                             int16 param_attribute, void* param_value);

/**
@brief Sets the current value for a PVCAM parameter.

This function sets the current value for a PVCAM parameter.

@a param_id is an enumerated type that indicates the parameter in question.
@a param_value points to the new value of the parameter. For the enumerated type this
value is the value assigned to current enum item not the item index.

@param[in]  hcam        Camera handle returned from #pl_cam_open.
@param[in]  param_id    ID of the parameter to get or set (PARAM_...).
@param[in]  param_value Value to get or set.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_get_param, pl_get_enum_param

@note The data type of @a param_value is documented in pvcam.h for each @a param_id.
It can be retrieved using the #pl_get_param function, using the #ATTR_TYPE attribute.
The user should call the #pl_get_param function with the attribute #ATTR_ACCESS,
to verify that the parameter ID is writeable (settable), before calling the #pl_set_param
function.
*/
rs_bool PV_DECL pl_set_param(int16 hcam, uns32 param_id, void* param_value);

/**
@brief Returns the enumerated value of the parameter param_id at index.

This function will return the enumerated value of the parameter param_id at index.
It also returns a string associated with the enumerated type (desc).
@b length indicates the maximum length allowed for the returned description.

@param[in]  hcam        Camera handle returned from #pl_cam_open.
@param[in]  param_id    ID of the parameter to get or set (PARAM_...).
@param[in]  index       Index of enumeration Range: 0 through N-1 ... where N
                        is retrieved with get_param(...,#ATTR_COUNT,...).
@param[out] value       Numerical value of enumeration.
@param[out] desc        Text description of enumeration.
@param[in]  length      Length of text description of enumeration.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_get_param, pl_set_param, pl_enum_str_length

@note The user should call the #pl_get_param function with the attribute #ATTR_TYPE,
to verify that the parameter ID is an enumerated data type before calling the #pl_get_enum_param.
The user should also call the #pl_get_param function with the attribute #ATTR_COUNT to
determine how many valid enumerated values the parameter ID has.
Example: Suppose there is a parameter for camera readout speed. This parameter can be set to 1MHz,
5MHz or 10MHz with the appropriate values 1, 5 and 10. If the readout speed is currently set to 5MHz,
a call to #pl_get_param with #ATTR_CURRENT returns a value of 5.
A call to #pl_get_enum_param for the readout speed parameter at index 1 (the second item)
returns the enumerated type 5MHz with the value equal to 5 and the desc would contain "5MHz".
*/
rs_bool PV_DECL pl_get_enum_param(int16 hcam, uns32 param_id, uns32 index,
                                  int32* value, char* desc, uns32 length);

/**
@brief Returns the length of the descriptive string for the parameter @a param_id at index.

This function will return the length (length) of the descriptive string for the parameter
@a param_id at index. The length includes the terminating null ('\0') character.

@param[in]  hcam        Camera handle returned from #pl_cam_open.
@param[in]  param_id    ID of the parameter to get or set (PARAM_...).
@param[in]  index       Index of enumeration Range: 0 through N-1, where N
                        is retrieved with get_param(..., ATTR_COUNT, ...).
@param[out] length Length of text description of enumeration.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_get_enum_param

@note This function can be used to determine the amount of memory to allocate for
the descriptive string when calling the #pl_get_enum_param function. Using the example
in #pl_get_enum_param, the length returned would be 5 (4 printable characters plus 1 null character).
*/
rs_bool PV_DECL pl_enum_str_length(int16 hcam, uns32 param_id, uns32 index,
                                   uns32* length);

/**
@brief This function will reset all post-processing modules to their default values.

@param[in]  hcam    Camera handle returned from #pl_cam_open.

@warning Fails if post-processing modules are not available in current camera or
if @a hcam is not the handle of an open camera.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see PARAM_PP_FEAT_NAME, PARAM_PP_PARAM_INDEX, PARAM_PP_PARAM_NAME, PARAM_PP_PARAM,
PARAM_PP_FEAT_ID, PARAM_PP_PARAM_ID
*/
rs_bool PV_DECL pl_pp_reset(int16 hcam);

/**
@brief Creates and allocates variable of smart_stream_type type with the number of
entries passed in via the entries parameter and returns pointer to it.

This function will create a variable of smart_stream_type type and return a pointer
to access it. The entries parameter passed by the user determines how many entries
the structure will contain.

@param[out] array   Created struct to be returned.
@param[in]  entries Number of entries to be in smart stream struct.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_release_smart_stream_struct
*/
rs_bool PV_DECL pl_create_smart_stream_struct(smart_stream_type** array,
                                              uns16 entries);

/**
@brief Frees the space previously allocated by the #pl_create_smart_stream_struct function.

This function will deallocate a smart_stream_type variable created by
#pl_create_smart_stream_struct.

@param[in]  array   Struct to be released.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_create_smart_stream_struct
*/
rs_bool PV_DECL pl_release_smart_stream_struct(smart_stream_type** array);

/**
@brief Creates and allocates variable of #FRAME_INFO type and returns pointer to it.

This function will create a variable of #FRAME_INFO type and
return a pointer to access it. The GUID field of the #FRAME_INFO structure is assigned
by this function. Other fields are updated by PVCAM at the time of frame reception.

@param[out] new_frame   Frame info struct to be returned.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_release_frame_info_struct, pl_exp_get_latest_frame_ex, pl_exp_get_oldest_frame_ex,
pl_exp_check_cont_status_ex, pl_cam_register_callback_ex2, pl_cam_register_callback_ex3
*/
rs_bool PV_DECL pl_create_frame_info_struct(FRAME_INFO** new_frame);

/**
@brief Deletes variable of #FRAME_INFO type.

This function will deallocate #FRAME_INFO variable created by #pl_create_frame_info_struct.

@param[in]  frame_to_delete     Frame info struct to be released.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_create_frame_info_struct, pl_exp_get_latest_frame_ex, pl_exp_get_oldest_frame_ex,
pl_exp_check_cont_status_ex, pl_cam_register_callback_ex2, pl_cam_register_callback_ex3
*/
rs_bool PV_DECL pl_release_frame_info_struct(FRAME_INFO* frame_to_delete);

/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*                   Data Acquisition Function Prototypes                    */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/

/**
@brief Prepares the camera to perform a readout.

This function uses the array of regions, exposure mode, and exposure
time passed in and transmits them to the camera.
@a exp_total specifies the number of images to take.
The pointer @a rgn_array points to @a rgn_total region definitions, @a exp_mode specifies
the bitwise OR combination of exposure mode and expose out mode (see chapter Extended
Exposure Modes), @a exposure_time specifies the exposure time in the currently
selected exposure time resolution (see #PARAM_EXP_RES and #PARAM_EXP_RES_INDEX).
The pointer @a exp_bytes points to a variable that will be filled with number of bytes
in the pixel stream. The settings are then downloaded to the camera. If there is any
problem (overlapping regions or a frame-transfer setting for a camera that lacks that
capability), this function aborts and returns with a failure. #pl_error_code indicates
the definition problem. The @a exp_bytes pointer is filled with the number of bytes of
memory needed to buffer the full sequence. (It is the developer's responsibility to
allocate a memory buffer for the pixel stream.)
When this function returns, the camera is ready to begin the exposure. #pl_exp_start_seq
initiates exposure and readout.

@param[in]  hcam            Camera handle returned from #pl_cam_open.
@param[in]  exp_total       Total number of exposures to take.
@param[in]  rgn_total       Total number of regions defined for each image.
@param[in]  rgn_array       Array of regions (must be rgn_total in size).
                            See rgn_type for details.
@param[in]  exp_mode        Mode for capture (#TIMED_MODE, #STROBED_MODE, ...).
@param[in]  exposure_time   Time to expose in selected exposure resolution.
                            Default is milliseconds (see #PARAM_EXP_RES).
@param[out] exp_bytes       Value returned from PVCAM specifying the required
                            number of bytes to allocate for the capture.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_abort, pl_exp_check_status, pl_exp_start_seq, pl_exp_finish_seq

@note This function downloads new settings. After receiving the settings, the camera
merely waits in an idle state. The #pl_exp_abort command may be used to place the camera
into some other state, such as continuous clearing, but this will not alter or affect
the downloaded settings. Essentially, the camera is still holding the exposure sequence
and waiting to start, while it clears the sensor charge.
*/
rs_bool PV_DECL pl_exp_setup_seq(int16 hcam, uns16 exp_total, uns16 rgn_total,
                                 const rgn_type* rgn_array, int16 exp_mode,
                                 uns32 exposure_time, uns32* exp_bytes);

/**
@brief Begins exposing, returns immediately.

This is a companion function to #pl_exp_setup_seq. #pl_exp_setup_seq
must be called first to define the exposure and program this information into the camera.
After that, #pl_exp_start_seq may be called one or more times. Each time it is called,
it starts one sequence and returns immediately (a sequence may be one or more exposures).
Progress can be monitored through #pl_exp_check_status. The next sequence may be started
as soon as the readout has finished or an abort has been performed (#pl_exp_abort).

The @a hcam parameter defines which camera is used.
The user must allocate an appropriately sized memory buffer for data collection, pointed to
by @a pixel_stream. This buffer must be at least @c exp_bytes bytes, where @c exp_bytes
is the value returned from #pl_exp_setup_seq. In addition, this memory must be page-locked
or similarly protected on virtual memory systems - these requirements are system specific
and the responsibility of the application.

There is a special case for those users who want to use their own frame grabber
(with an appropriately equipped camera). If a null pointer is passed in for @a pixel_stream,
#pl_exp_start_seq will assume that the user is routing the data to a frame grabber or other
device under their control. Under these conditions, #pl_exp_start_seq initiates the exposure,
but does not attempt to collect incoming data.

@param[in]  hcam            Camera handle returned from #pl_cam_open.
@param[out] pixel_stream    Buffer to hold image(s).

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_check_status, pl_exp_setup_seq, pl_exp_finish_seq

@note Technically, this only changes the state of the CCS program.
Regardless of whether the CCS is idle or continuously clearing, this forces the CCS program
into the busy state. The camera settings are not altered by this command, but it does begin
executing. If the CCS is idle, there is no delay and the camera will begin running immediately.
If the CCS is continuously clearing, the system finishes the current parallel shift
(it finishes the current single parallel row) and then begins running. This produces a delay
of up to the parallel-shift time for this CCD (1-300 microseconds, depending on the CCD).
If the camera has been set up with one of the CLEAR_PRE_ clearing modes, it will also explicitly
clear the sensor as its first action.
*/
rs_bool PV_DECL pl_exp_start_seq(int16 hcam, void* pixel_stream);

/**
@brief Sets circular buffer mode.

This function sets the mode of operation for the circular buffer.
This function uses the array of regions, exposure mode, exposure time passed in,
and circular buffer mode and transmits them to the camera.
The pointer @a rgn_array points to @a rgn_total region definitions.
@a exp_mode specifies the bitwise OR combination of the exposure mode and expose out mode.
@a exposure_time specifies the exposure time in the currently selected exposure time resolution
(see #PARAM_EXP_RES and #PARAM_EXP_RES_INDEX). The pointer @a exp_bytes points to a variable that
will be filled with number of bytes in the pixel stream.
@a buffer_mode can be set to either #CIRC_OVERWRITE or #CIRC_NO_OVERWRITE. This function must be called
before calling #pl_exp_start_cont.

The settings are then downloaded to the camera. If there is any problem (overlapping regions
or a frame-transfer setting for a camera that lacks that capability), this function aborts and
returns with a failure. #pl_error_code indicates the definition problem.
The @a exp_bytes pointer is filled with the number of bytes of memory needed to buffer the full
sequence. (It is the developer's responsibility to allocate a memory buffer for the pixel stream.)
When this function returns, the camera is ready to begin the exposure. #pl_exp_start_cont initiates
exposure and readout.

@param[in]  hcam            Camera handle returned from #pl_cam_open.
@param[in]  rgn_total       Total number of regions defined for each image.
@param[in]  rgn_array       Array of regions (must be rgn_total in size).
                            See rgn_type for details.
@param[in]  exp_mode        Mode for capture (#TIMED_MODE, #STROBED_MODE, ...).
@param[in]  exposure_time   Time to expose in selected exposure resolution.
                            Default is milliseconds (see #PARAM_EXP_RES).
@param[out] exp_bytes       Value returned from PVCAM specifying the required
                            number of bytes to allocate for the capture.
@param[in]  buffer_mode     Circular buffer mode (#CIRC_OVERWRITE, #CIRC_NO_OVERWRITE).

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_start_cont, pl_exp_check_cont_status, pl_exp_get_oldest_frame, pl_exp_get_latest_frame,
pl_exp_unlock_oldest_frame, pl_exp_stop_cont

@note Use the parameter ID #PARAM_CIRC_BUFFER with #pl_get_param to see if the system can
perform circular buffer operations. The circular buffer is passed to #pl_exp_start_cont.
The buffer is allocated by your application.
*/
rs_bool PV_DECL pl_exp_setup_cont(int16 hcam, uns16 rgn_total,
                                  const rgn_type* rgn_array, int16 exp_mode,
                                  uns32 exposure_time, uns32* exp_bytes,
                                  int16 buffer_mode);

/**
@brief Begins continuous readout into circular buffer.

This function will initiate a continuous readout from the camera into a circular buffer.

@param[in]  hcam            Camera handle returned from #pl_cam_open.
@param[in]  pixel_stream    Buffer to hold image(s).
@param[in]  size            Size of continuous capture pixel_stream
                            (must be a multiple of @c byte_cnt).

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_setup_cont, pl_exp_check_cont_status, pl_exp_get_oldest_frame,
pl_exp_get_latest_frame, pl_exp_unlock_oldest_frame, pl_exp_stop_cont

@note If @a pixel_stream points to a buffer that is not an integer-multiple of the frame size
for the exposure, this function will return #PV_FAIL and set an appropriate error
code in #pl_error_code. For example, a buffer size of 1000 bytes with a frame size of 250 is OK,
but a buffer size of 900 bytes would cause a failure.
Use the parameter ID #PARAM_CIRC_BUFFER with #pl_get_param to check to see if the system can
perform circular buffer operations.
*/
rs_bool PV_DECL pl_exp_start_cont(int16 hcam, void* pixel_stream, uns32 size);

/**
@brief Begins continuous readout into circular buffer.

This is only useful when data collection has been set up and started, as with a call
to the Class 3 functions #pl_exp_setup_seq and #pl_exp_start_seq. In general,
Class 3 functions start an exposure then immediately return, allowing the progress to be monitored.
The status gives a quick evaluation of progress.
The variable status returns one of the values listed here: #PL_IMAGE_STATUSES.

More detailed information is returned in @a bytes_arrived. This reports on exactly
how many bytes of data have arrived so far.
This level of feedback is unimportant to many users.

@param[in]  hcam          Camera handle returned from #pl_cam_open.
@param[out] status        Status of the current capture (#EXPOSURE_IN_PROGRESS, ...).
@param[out] bytes_arrived Number of bytes that have arrived. For continuous
                          mode this is the number of bytes that have arrived
                          this time through the buffer.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_setup_seq, pl_exp_start_seq
*/
rs_bool PV_DECL pl_exp_check_status(int16 hcam, int16* status, uns32* bytes_arrived);

/**
@brief Checks the continuous readout status from the camera into a circular buffer.

This function will return the status of a continuous readout from the camera
into a circular buffer.
@a status is a pointer to one of the values listed here: #PL_IMAGE_STATUSES.

@param[in]   hcam           Camera handle returned from #pl_cam_open.
@param[out]  status         Status of the current capture (#EXPOSURE_IN_PROGRESS,...).
@param[out]  bytes_arrived  Number of bytes that have arrived. For continuous
                            mode this is the number of bytes that have arrived
                            this time through the buffer.
@param[out]  buffer_cnt     Number of times through the buffer (continuous mode).

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_setup_cont, pl_exp_start_cont, pl_exp_get_oldest frame, pl_exp_get_latest_frame,
pl_exp_unlock_oldest_frame, pl_exp_stop_cont

@note This function only returns meaningful results if a continuous readout from the camera
has been initiated by a call to #pl_exp_start_cont.
Use the parameter ID #PARAM_CIRC_BUFFER with #pl_get_param to check to see if the system can
perform circular buffer operations.
*/
rs_bool PV_DECL pl_exp_check_cont_status(int16 hcam, int16* status,
                                         uns32* bytes_arrived, uns32* buffer_cnt);

/**
@brief Checks the continuous readout status from the camera into a circular buffer.

This function will return the status of a continuous readout from the camera
into a circular buffer.
@a status is a pointer to one of the values listed here: #PL_IMAGE_STATUSES.

Values in the variable pointed to by frame_info will be updated with frame counters,
timestamps (with precision of 0.1ms) and readout time information assigned by device driver
at the moment of frame reception.

@param[in]  hcam        Camera handle returned from #pl_cam_open.
@param[out] status      Status of the current capture (#EXPOSURE_IN_PROGRESS,...).
@param[out] byte_cnt    Size of bufer to hold images (in bytes).
@param[out] buffer_cnt  Number of times through the buffer (continuous mode).
@param[out] frame_info  Frame info struct pointer.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_setup_cont, pl_exp_start_cont, pl_exp_get_oldest_frame, pl_exp_get_latest_frame,
pl_exp_unlock_oldest_frame, pl_exp_stop_cont, pl_create_frame_info_struct,
pl_exp_get_latest_frame_ex, pl_exp_get_oldest_frame_ex

@note This function only returns meaningful results if a continuous readout from the camera has
been initiated by a call to #pl_exp_start_cont. Use the parameter ID #PARAM_CIRC_BUFFER
with #pl_get_param to check to see if the system can perform circular buffer operations.
Variable pointed to by frame_info must be created with #pl_create_frame_info_struct.
*/
rs_bool PV_DECL pl_exp_check_cont_status_ex(int16 hcam, int16* status,
                                            uns32* byte_cnt, uns32* buffer_cnt,
                                            FRAME_INFO* frame_info);

/**
@brief This function returns a pointer to the most recently acquired frame in the circular buffer.

@param[in]  hcam    Camera handle returned from #pl_cam_open.
@param[out] frame   Pointer to the most recent frame.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_setup_cont, pl_exp_start_cont, pl_exp_check_cont_status, pl_exp_stop_cont

@note If the camera in use is not able to return the latest frame for the current operating mode,
this function will fail. For example, some cameras cannot return the latest frame in
#CIRC_NO_OVERWRITE mode. Use the parameter ID #PARAM_CIRC_BUFFER with #pl_get_param to check to
see if the system can perform circular buffer operations.
*/
rs_bool PV_DECL pl_exp_get_latest_frame(int16 hcam, void** frame);

/**
@brief returns pointer to most recent frame in circular buffer.

Additionally this function updates values of timestamps (with precision of 0.1ms),
frame counter numbers and readout time in variable of #FRAME_INFO type.

@param[in]  hcam        Camera handle returned from #pl_cam_open.
@param[out] frame       Pointer to the most recent frame.
@param[out] frame_info  Frame info struct pointer.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_setup_cont, pl_exp_start_cont, pl_exp_check_cont_status, pl_exp_stop_cont,
pl_exp_get_oldest_frame_ex, pl_exp_check_cont_status_ex, pl_cam_register_callback_ex2,
pl_create_frame_info_struct, pl_release_frame_info_struct

@note If the camera in use is not able to return the latest frame for the current operating mode,
this function will fail. For example, some cameras cannot return the latest frame
in #CIRC_NO_OVERWRITE mode. Use the parameter ID #PARAM_CIRC_BUFFER with #pl_get_param to check to see
if the system can perform circular buffer operations.
Variable pointed to by frame_info must be created with #pl_create_frame_info_struct.
*/
rs_bool PV_DECL pl_exp_get_latest_frame_ex(int16 hcam, void** frame,
                                           FRAME_INFO* frame_info);

/**
@brief This function locks the oldest unretrieved frame in the circular buffer,
and returns a pointer to that frame.

@param[in]  hcam  Camera handle returned from #pl_cam_open.
@param[out] frame Pointer to the oldest unretrieved frame.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_setup_cont, pl_exp_start_cont, pl_exp_check_cont_status,
pl_exp_unlock_oldest_frame, pl_exp_stop_cont, pl_exp_get_oldest_frame_ex

@note If the camera in use is not able to return the oldest frame for the current operating mode,
this function will fail. For example, some cameras cannot return the oldest frame
in #CIRC_OVERWRITE mode. Use the parameter ID #PARAM_CIRC_BUFFER with #pl_get_param to check
to see if the system can perform circular buffer operations.
*/
rs_bool PV_DECL pl_exp_get_oldest_frame(int16 hcam, void** frame);

/**
@brief This function locks the oldest unretrieved frame in the circular buffer,
and returns a pointer to that frame.

Additionally this function updates the values in the variable pointed to by @a frame_info
with the data collected at the time of frame reception by the device driver (e.g. frame counter value).
@param[in]  hcam        Camera handle returned from #pl_cam_open.
@param[out] frame       Pointer to the oldest unretrieved frame.
@param[out] frame_info  Frame info struct pointer.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_setup_cont, pl_exp_start_cont, pl_exp_check_cont_status,
pl_exp_unlock_oldest_frame, pl_exp_stop_cont, pl_exp_check_cont_status_ex,
pl_cam_register_callback_ex2, pl_create_frame_info_struct, pl_release_frame_info_struct

@note If the camera in use is not able to return the oldest frame for the current operating mode,
this function will fail. For example, some cameras cannot return the oldest frame in
#CIRC_OVERWRITE mode. Use the parameter ID #PARAM_CIRC_BUFFER with pl_get_param to check to see
if the system can perform circular buffer operations.
Variable pointed to by frame_info must be created with #pl_create_frame_info_struct.
*/
rs_bool PV_DECL pl_exp_get_oldest_frame_ex(int16 hcam, void** frame,
                                           FRAME_INFO* frame_info);

/**
@brief Makes oldest frame in circular buffer overwriteable.

This function unlocks the oldest frame in the circular buffer;
the frame should have been locked previously by a call to #pl_exp_get_oldest_frame.

@param[in]  hcam    Camera handle returned from #pl_cam_open.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_setup_cont, pl_exp_start_cont, pl_exp_check_cont_status, pl_exp_get_oldest_frame,
pl_exp_unlock_oldest_frame, pl_exp_stop_cont

@note Failure to call this function after using the frame will cause the continuous acquisition
progress to halt eventually, because the frame cannot be overwritten when it is locked.
Use the parameter ID #PARAM_CIRC_BUFFER with #pl_get_param to check to see if the system can perform
circular buffer operations.
*/
rs_bool PV_DECL pl_exp_unlock_oldest_frame(int16 hcam);

/**
@brief Stops continuous readout acquisition.

This function halts a continuous readout acquisition into a circular buffer.
@a cam_state defines the new state of the Camera Control Subsystem,
as described in the documentation for the #pl_exp_abort function.

@param[in]  hcam        Camera handle returned from #pl_cam_open.
@param[out] cam_state   State to set the camera in (#CCS_NO_CHANGE,...).

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_setup_cont, pl_exp_start_cont, pl_exp_check_cont_status, pl_exp_get_oldest_frame,
pl_exp_get_latest_frame, pl_exp_unlock_oldest_frame

@note Use the parameter ID #PARAM_CIRC_BUFFER with #pl_get_param to check to see if the system
can perform circular buffer operations.
*/
rs_bool PV_DECL pl_exp_stop_cont(int16 hcam, int16 cam_state);

/**
@brief Stops collecting data, cleans up device driver, halts camera.

#pl_exp_abort performs two functions: it stops the host device driver, and it may halt the camera
(@a hcam specifies which camera and which device driver are being used.) Halting the camera halts
@a readout, @c clearing, and all other camera activity. On the host side, data collection is controlled
by a device driver. If data collection is currently enabled (the image data @b active state), this
function stops collection, returns the low-level communication hardware and software to an image
data @b idle state, and disables collection. In the @b idle state, any data that arrives is ignored and
discarded. The @b idle state is the normal system default. On the camera side, the Camera Control
Subsystem (CCS) may be in the process of collecting data, or it may be in one of several idle states.
This function always stops the data collection software. In addition, it has the option of forcing
the CCS into a new state by setting the @a cam_state variable to one of the following constants,
which are camera dependent: #PL_CCS_ABORT_MODES.

@param[in]  hcam        Camera handle returned from #pl_cam_open.
@param[out] cam_state   State to set the camera in (#CCS_NO_CHANGE,...).

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@note This may also be called outside of an exposure. It can explicitly open the shutter,
close the shutter, or stop the CCS. In the @b idle state, the system takes the least possible
amount of action when image data arrives. On some systems, this involves placing the hardware
in reset state, so it is inactive. On SCSI systems, the driver does not initiate any data transfers,
although a buffer on the camera end may be filling up. If the CCS is halted and the shutter
is closed (#CCS_HALT_CLOSE_SHTR), the current image remains on the sensor (although dark charge
continues to accumulate). If @c clear_cycles is zero or the clear mode is #CLEAR_NEVER, the image
may be read off by performing a bias readout. In frame transfer mode, you may not want to close
the shutter when halting the CCS. Some frame transfer systems do not include a shutter, in which
case an attempt to open or close the shutter is ignored, but does not cause an error.
*/
rs_bool PV_DECL pl_exp_abort(int16 hcam, int16 cam_state);

/**
@brief Finishes and cleans up after #pl_exp_start_seq.

This cleans up after an exposure started through #pl_exp_start_seq has finished readout.
If the exposure has not finished readout, this function returns with an error.
Argument @a hbuf is not used at the moment.

@param[in]  hcam            Camera handle returned from #pl_cam_open.
@param[in]  pixel_stream    Buffer to hold image(s).
@param[in]  hbuf            Standard image buffer. Not used this time.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_exp_abort, pl_exp_check_status, pl_exp_setup_seq, pl_exp_start_seq

@note This function must also be called if acquiring in sequential mode
(using #pl_exp_setup_seq and #pl_exp_start_seq) with callbacks notification
after a frame is read out and before new exposure is started by calling #pl_exp_start_seq.
*/
rs_bool PV_DECL pl_exp_finish_seq(int16 hcam, void* pixel_stream, int16 hbuf);

/**
@brief Defines control of an I/O line from within a camera script.

This function allows the application program to define control of the available I/O lines
from within a script. This allows for more precise control of external devices. For example,
the application could request that a linear stage be indexed immediately after integration,
instead of waiting until after the data is read out, the shutter is closed, etc.

@a state has different meanings depending on the I/O type which are described here: #PL_IO_TYPE.
@a location can be set to the values described here: #PL_SRC_MODES.

@param[in]  hcam        Camera handle returned from #pl_cam_open.
@param[in]  addr        Specifies which I/O address to control.
@param[in]  state       Specifies the value to write to the register.
@param[in]  location    Specifies when to control the I/O (#SCR_PRE_FLASH,...).
                        Values are listed here: #PL_IO_TYPE.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_io_clear_script_control
*/
rs_bool PV_DECL pl_io_script_control(int16 hcam, uns16 addr, flt64 state,
                                     uns32 location);

/**
@brief Clears the current setup for control of the available I/O lines within a camera script.

This function allows the application program to clear the current setup for control
of the available I/O lines within the script. This allows the user to enter
a new setup for these lines.

@param[in]  hcam    Camera handle returned from #pl_cam_open.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.

@see pl_io_script_control
*/
rs_bool PV_DECL pl_io_clear_script_control(int16 hcam);

/** @} */ /* grp_pm_functions */

/*****************************************************************************/
/**
@addtogroup grp_pm_deprecated_functions
Most of the functions are obsolete and their corresponding PARAM_
parameters should be used with #pl_get_param, #pl_set_param,
#pl_get_enum_param and #pl_enum_str_length.
@{
*/

DEPRECATED rs_bool PV_DECL pl_exp_init_seq(void);
DEPRECATED rs_bool PV_DECL pl_exp_uninit_seq(void);
/** Use #PARAM_DD_INFO instead. */
DEPRECATED rs_bool PV_DECL pl_dd_get_info(int16 hcam, int16 bytes, char* text);
/** Use #PARAM_DD_INFO_LENGTH instead. */
DEPRECATED rs_bool PV_DECL pl_dd_get_info_length(int16 hcam, int16* bytes);
/** Use #PARAM_DD_VERSION instead. */
DEPRECATED rs_bool PV_DECL pl_dd_get_ver(int16 hcam, uns16* dd_version);
/** Use #PARAM_DD_RETRIES instead. */
DEPRECATED rs_bool PV_DECL pl_dd_get_retries(int16 hcam, uns16* max_retries);
/** Use #PARAM_DD_RETRIES instead. */
DEPRECATED rs_bool PV_DECL pl_dd_set_retries(int16 hcam, uns16 max_retries);
/** Use #PARAM_DD_TIMEOUT instead. */
DEPRECATED rs_bool PV_DECL pl_dd_get_timeout(int16 hcam, uns16* m_sec);
/** Use #PARAM_DD_TIMEOUT instead. */
DEPRECATED rs_bool PV_DECL pl_dd_set_timeout(int16 hcam, uns16 m_sec);
/** Use #PARAM_ADC_OFFSET instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_adc_offset(int16 hcam, int16* offset);
/** Use #PARAM_ADC_OFFSET instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_set_adc_offset(int16 hcam, int16 offset);
/** Use #PARAM_CHIP_NAME instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_chip_name(int16 hcam, char* chip_name);
/** Use #PARAM_CLEAR_CYCLES instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_clear_cycles(int16 hcam, uns16* clear_cycles);
/** Use #PARAM_CLEAR_CYCLES instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_set_clear_cycles(int16 hcam, uns16 clr_cycles);
/** Use #PARAM_CLEAR_MODE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_clear_mode(int16 hcam, int16* clear_mode);
/** Use #PARAM_CLEAR_MODE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_set_clear_mode(int16 hcam, int16 ccd_clear);
/** Use #PARAM_COLOR_MODE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_color_mode(int16 hcam, uns16* color_mode);
/** Use #PARAM_COOLING_MODE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_cooling_mode(int16 hcam, int16* cooling);
/** Use #PARAM_FRAME_CAPABLE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_frame_capable(int16 hcam, rs_bool* frame_capable);
/** Use #PARAM_FWELL_CAPACITY instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_fwell_capacity(int16 hcam, uns32* fwell_capacity);
/** Use #PARAM_MPP_CAPABLE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_mpp_capable(int16 hcam, int16* mpp_capable);
/** Use #PARAM_PREAMP_DELAY instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_preamp_dly(int16 hcam, uns16* preamp_dly);
/** Use #PARAM_PREAMP_OFF_CONTROL instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_preamp_off_control(int16 hcam,
                                                         uns32* preamp_off_control);
/** Use #PARAM_PREAMP_OFF_CONTROL instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_set_preamp_off_control(int16 hcam,
                                                         uns32 preamp_off_control);
/** Use deprecated PARAM_PREFLASH instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_preflash(int16 hcam, uns16* pre_flash);
/** Use #PARAM_PMODE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_pmode(int16 hcam, int16* pmode);
/** Use #PARAM_PMODE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_set_pmode(int16 hcam, int16 pmode);
/** Use #PARAM_PREMASK instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_premask(int16 hcam, uns16* pre_mask);
/** Use #PARAM_PRESCAN instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_prescan(int16 hcam, uns16* prescan);
/** Use #PARAM_POSTMASK instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_postmask(int16 hcam, uns16* post_mask);
/** Use #PARAM_POSTSCAN instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_postscan(int16 hcam, uns16* postscan);
/** Use #PARAM_PAR_SIZE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_par_size(int16 hcam, uns16* par_size);
/** Use #PARAM_SER_SIZE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_ser_size(int16 hcam, uns16* ser_size);
/** Use deprecated PARAM_SERIAL_NUM instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_serial_num(int16 hcam, uns16* serial_num);
/** Use deprecated PARAM_CCS_STATUS instead. */
DEPRECATED rs_bool PV_DECL pl_ccs_get_status(int16 hcam, int16* ccs_status);
/** Use #PARAM_SUMMING_WELL instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_summing_well(int16 hcam, rs_bool* s_well_exists);
/** Use #PARAM_TEMP instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_tmp(int16 hcam, int16* cur_tmp);
/** Use #PARAM_TEMP instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_tmp_range(int16 hcam, int16* tmp_hi_val,
                                                int16* tmp_lo_val);
/** Use #PARAM_TEMP_SETPOINT instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_tmp_setpoint(int16 hcam, int16* tmp_setpoint);
/** Use #PARAM_TEMP_SETPOINT instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_set_tmp_setpoint(int16 hcam, int16 tmp_setpoint);
DEPRECATED rs_bool PV_DECL pl_ccd_set_readout_port(int16 , int16 );
/** Use #PARAM_PIX_PAR_DIST instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_pix_par_dist(int16 hcam, uns16* pix_par_dist);
/** Use #PARAM_PIX_PAR_SIZE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_pix_par_size(int16 hcam, uns16* pix_par_size);
/** Use #PARAM_PIX_SER_DIST instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_pix_ser_dist(int16 hcam, uns16* pix_ser_dist);
/** Use #PARAM_PIX_SER_SIZE instead. */
DEPRECATED rs_bool PV_DECL pl_ccd_get_pix_ser_size(int16 hcam, uns16* pix_ser_size);
/** Use #PARAM_BIT_DEPTH instead. */
DEPRECATED rs_bool PV_DECL pl_spdtab_get_bits(int16 hcam, int16* spdtab_bits);
/** Use #PARAM_GAIN_INDEX instead. */
DEPRECATED rs_bool PV_DECL pl_spdtab_get_gain(int16 hcam, int16* spdtab_gain);
/** Use #PARAM_GAIN_INDEX instead. */
DEPRECATED rs_bool PV_DECL pl_spdtab_set_gain(int16 hcam, int16 spdtab_gain);
/** Use #PARAM_GAIN_INDEX instead. */
DEPRECATED rs_bool PV_DECL pl_spdtab_get_max_gain(int16 hcam, int16* spdtab_max_gain);
/** Use #PARAM_SPDTAB_INDEX instead. */
DEPRECATED rs_bool PV_DECL pl_spdtab_get_num(int16 hcam, int16* spdtab_num);
/** Use #PARAM_SPDTAB_INDEX instead. */
DEPRECATED rs_bool PV_DECL pl_spdtab_set_num(int16 hcam, int16 spdtab_num);
/** Use #PARAM_SPDTAB_INDEX instead. */
DEPRECATED rs_bool PV_DECL pl_spdtab_get_entries(int16 hcam, int16* spdtab_entries);
/** Use #PARAM_READOUT_PORT instead. */
DEPRECATED rs_bool PV_DECL pl_spdtab_get_port(int16 hcam, int16* spdtab_port);
/** Use #PARAM_READOUT_PORT instead. */
DEPRECATED rs_bool PV_DECL pl_spdtab_get_port_total(int16 hcam, int16* total_ports);
/** Use #PARAM_PIX_TIME instead. */
DEPRECATED rs_bool PV_DECL pl_spdtab_get_time(int16 hcam, uns16* spdtab_time);
/** Use #PARAM_SHTR_CLOSE_DELAY instead. */
DEPRECATED rs_bool PV_DECL pl_shtr_get_close_dly(int16 hcam, uns16* shtr_close_dly);
/** Use #PARAM_SHTR_CLOSE_DELAY instead. */
DEPRECATED rs_bool PV_DECL pl_shtr_set_close_dly(int16 hcam, uns16 shtr_close_dly);
/** Use #PARAM_SHTR_OPEN_DELAY instead. */
DEPRECATED rs_bool PV_DECL pl_shtr_get_open_dly(int16 hcam, uns16* shtr_open_dly);
/** Use #PARAM_SHTR_OPEN_DELAY instead. */
DEPRECATED rs_bool PV_DECL pl_shtr_set_open_dly(int16 hcam, uns16 shtr_open_dly);
/** Use #PARAM_SHTR_OPEN_MODE instead. */
DEPRECATED rs_bool PV_DECL pl_shtr_get_open_mode(int16 hcam, int16* shtr_open_mode);
/** Use #PARAM_SHTR_OPEN_MODE instead. */
DEPRECATED rs_bool PV_DECL pl_shtr_set_open_mode(int16 hcam, int16 shtr_open_mode);
/** Use #PARAM_SHTR_STATUS instead. */
DEPRECATED rs_bool PV_DECL pl_shtr_get_status(int16 hcam, int16* shtr_status);
/** Use #PARAM_EXP_TIME instead. */
DEPRECATED rs_bool PV_DECL pl_exp_get_time_seq(int16 hcam, uns16* exp_time);
/** Use #PARAM_EXP_TIME instead. */
DEPRECATED rs_bool PV_DECL pl_exp_set_time_seq(int16 hcam, uns16 exp_time);
/** Use #pl_exp_check_status or #pl_exp_check_cont_status instead. */
DEPRECATED rs_bool PV_DECL pl_exp_check_progress(int16 hcam, int16* status,
                                                 uns32* bytes_arrived);

/** Use #pl_exp_setup_cont instead. */
DEPRECATED rs_bool PV_DECL pl_exp_set_cont_mode(int16 hcam, int16 mode);
DEPRECATED rs_bool PV_DECL pl_subsys_do_diag(int16 hcam, uns8 subsys_id,
                                             uns16* err_code);
DEPRECATED rs_bool PV_DECL pl_subsys_get_id(int16 hcam, uns8 subsys_id,
                                            uns16* part_num, uns8* revision);
DEPRECATED rs_bool PV_DECL pl_subsys_get_name(int16 hcam, uns8 subsys_id,
                                              char* subsys_name);
DEPRECATED rs_bool PV_DECL pl_exp_get_driver_buffer(int16 hcam,
                                                    void** pixel_stream,
                                                    uns32* byte_cnt);
DEPRECATED rs_bool PV_DECL pl_buf_init(void);
DEPRECATED rs_bool PV_DECL pl_buf_uninit(void);
DEPRECATED rs_bool PV_DECL pl_buf_alloc(int16* hbuf, int16 exp_total,
                                        int16 bit_depth, int16 rgn_total,
                                        const rgn_type* rgn_array);
DEPRECATED rs_bool PV_DECL pl_buf_get_exp_date(int16 hbuf, int16 exp_num, int16* year,
                                               uns8* month, uns8* day, uns8* hour,
                                               uns8* min, uns8* sec, uns16* msec);
DEPRECATED rs_bool PV_DECL pl_buf_set_exp_date(int16 hbuf, int16 exp_num, int16 year,
                                               uns8 month, uns8 day, uns8 hour,
                                               uns8 min, uns8 sec, uns16 msec);
DEPRECATED rs_bool PV_DECL pl_buf_get_exp_time(int16 hbuf, int16 exp_num, uns32* exp_msec);
DEPRECATED rs_bool PV_DECL pl_buf_get_exp_total(int16 hbuf, int16* total_exps);
DEPRECATED rs_bool PV_DECL pl_buf_get_img_bin(int16 himg, int16* ibin, int16* jbin);
DEPRECATED rs_bool PV_DECL pl_buf_get_img_handle(int16 hbuf, int16 exp_num,
                                                 int16 img_num, int16* himg);
DEPRECATED rs_bool PV_DECL pl_buf_get_img_ofs(int16 himg, int16* s_ofs, int16* p_ofs);
DEPRECATED rs_bool PV_DECL pl_buf_get_img_ptr(int16 himg, void** img_addr);
DEPRECATED rs_bool PV_DECL pl_buf_get_img_size(int16 himg, int16* x_size, int16* y_size);
DEPRECATED rs_bool PV_DECL pl_buf_get_img_total(int16 hbuf, int16* totl_imgs);
DEPRECATED rs_bool PV_DECL pl_buf_get_size(int16 hbuf, int32* buf_size);
DEPRECATED rs_bool PV_DECL pl_buf_free(int16 hbuf);
DEPRECATED rs_bool PV_DECL pl_buf_get_bits(int16 hbuf, int16* bit_depth);
DEPRECATED rs_bool PV_DECL pl_exp_unravel(int16 hcam, uns16 exposure,
                                          void* pixel_stream, uns16 rgn_total,
                                          const rgn_type* rgn_array,
                                          uns16** array_list);
DEPRECATED rs_bool PV_DECL pl_exp_wait_start_xfer(int16 hcam, uns32 tlimit);
DEPRECATED rs_bool PV_DECL pl_exp_wait_end_xfer(int16 hcam, uns32 tlimit);

DEPRECATED rs_bool PV_DECL pv_cam_get_ccs_mem(int16 hcam, uns16* size);
DEPRECATED rs_bool PV_DECL pv_cam_send_debug(int16 hcam, char* debug_str,
                                             uns16 reply_len, char* reply_str);
DEPRECATED rs_bool PV_DECL pv_cam_write_read(int16 hcam, uns8 c_class, uns16 write_bytes,
                                             uns8* write_array, uns8* read_array);
DEPRECATED rs_bool PV_DECL pv_dd_active(int16 hcam, void* pixel_stream);
DEPRECATED rs_bool PV_DECL pv_exp_get_bytes(int16 hcam, uns32* exp_bytes);
DEPRECATED rs_bool PV_DECL pv_exp_get_script(int16 hcam, rs_bool* script_valid);
DEPRECATED rs_bool PV_DECL pv_exp_get_status(int16 hcam, int16* status,
                                             uns32* byte_cnt, uns32* frame_cnt);
DEPRECATED rs_bool PV_DECL pv_exp_set_bytes(int16 hcam, uns32 frame_count,
                                            uns32 seq_bytes, void* pixel_stream);
DEPRECATED rs_bool PV_DECL pv_exp_set_script(int16 hcam, rs_bool script_valid);
DEPRECATED rs_bool PV_DECL pv_set_error_code(int16 omode,int16 err_code);
DEPRECATED rs_bool PV_DECL pv_cam_do_reads(int16 hcam);
DEPRECATED rs_bool PV_DECL pv_free(void* block, int16 heap);
DEPRECATED void*   PV_DECL pv_malloc(uns32 size, int16 heap);
DEPRECATED void*   PV_DECL pv_realloc(void* block, uns32 size, int16 heap);
DEPRECATED rs_bool PV_DECL pv_script_set_hook(pm_script_hook* pfn);
DEPRECATED rs_bool PV_DECL pv_ccd_get_accum_capable(int16 hcam, rs_bool* accum_capable);
DEPRECATED rs_bool PV_DECL pv_exp_get_frames(int16 hcam, uns32* exp_frames);
DEPRECATED rs_bool PV_DECL pv_exp_set_frames(int16 hcam, uns32 exp_frames);
DEPRECATED rs_bool PV_DECL pv_exp_set_no_readout_timeout(int16 hcam);
DEPRECATED rs_bool PV_DECL pv_exp_reset_no_readout_timeout(int16 hcam);
DEPRECATED rs_bool PV_DECL pm_cam_write_read(int16 hcam, uns8 c_class, uns16 write_bytes,
                                             uns8* write_array, uns8* read_array);

DEPRECATED rs_bool PV_DECL pl_ddi_get_ver(uns16* ddi_version);
DEPRECATED rs_bool PV_DECL pl_cam_get_diags(int16 hcam);

/** @} */ /* grp_pm_deprecated_functions */

/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*                         Frame metadata functions                          */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/

/**
@addtogroup grp_pm_functions
@{
*/

/**
@brief Decodes a metadata-enabled frame buffer into provided frame descriptor structure.

This function processes the input frame buffer and calculates pointers to frame metadata headers,
ROI headers and ROI image data and stores them to previously allocated @a pDstFrame structure.

@param[out] pDstFrame   A pre-allocated helper structure that will be filled with
                        information from the given raw buffer.
@param[in]  pSrcBuf     A raw frame buffer as retrieved from PVCAM.
@param[in]  srcBufSize  The size of the raw frame buffer.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.
*/
rs_bool PV_DECL pl_md_frame_decode(md_frame* pDstFrame, void* pSrcBuf, uns32 srcBufSize);

/**
@brief Optional function that recomposes a multi-ROI frame into a displayable image buffer.

Every ROI will be copied into its appropriate location in the provided buffer.
Please note that the function will subtract the Implied ROI position from each ROI
position which essentially moves the entire Implied ROI to a [0, 0] position.
Use the Offset arguments to shift all ROIs back to desired positions if needed.
If you use the Implied ROI position for offset arguments the frame will be recomposed
as it appears on the full frame.

The caller is responsible for black-filling the input buffer. Usually this function
is called during live/preview mode where the destination buffer is re-used. If the
ROIs do move during acquisition it is essential to black-fill the destination buffer
before calling this function. This is not needed if the ROIs do not move.
If the ROIs move during live mode it is also recommended to use the offset arguments
and recompose the ROI to a full frame - with moving ROIs the implied ROI may change
with each frame and this may cause undesired ROI "twitching" in the displayable image.

@param[out] pDstBuf     An output buffer, the buffer must be at least the size of the implied
                        ROI that is calculated during the frame decoding process. The buffer
                        must be of type uns16. If offset is set the buffer must be large
                        enough to allow the entire implied ROI to be shifted.
@param[in]  offX        Offset in the destination buffer, in pixels. If 0 the Implied
                        ROI will be shifted to position 0 in the target buffer.
                        Use (ImpliedRoi.s1 / ImplierRoi.sbin) as offset value to
                        disable the shift and keep the ROIs in their absolute positions.
@param[in]  offY        Offset in the destination buffer, in pixels. If 0 the Implied
                        ROI will be shifted to position 0 in the target buffer.
                        Use (ImpliedRoi.p1 / ImplierRoi.pbin) as offset value to
                        disable the shift and keep the ROIs in their absolute positions.
@param[in]  dstWidth    Width, in pixels of the destination image buffer. The buffer
                        must be large enough to hold the entire Implied ROI, including
                        the offsets (if used).
@param[in]  dstHeight   Height, in pixels of the destination image buffer.
@param[in]  pSrcFrame   A helper structure, previously decoded using the frame
                        decoding function.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.
*/
rs_bool PV_DECL pl_md_frame_recompose(void* pDstBuf, uns16 offX, uns16 offY,
                                      uns16 dstWidth, uns16 dstHeight,
                                      md_frame* pSrcFrame);

/**
@brief This method creates an empty md_frame structure for known number of ROIs.

Use this method to prepare and pre-allocate one structure before starting
continous acquisition. Once callback arrives fill the structure with
#pl_md_frame_decode and display the metadata.
Release the structure when not needed.

@param[out] pFrame      A pointer to frame helper structure address where the structure
                        will be allocated.
@param[in]  roiCount    Number of ROIs the structure should be prepared for.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.
*/
rs_bool PV_DECL pl_md_create_frame_struct_cont(md_frame** pFrame, uns16 roiCount);

/**
@brief This method creates an empty md_frame structure from an existing buffer.

Use this method when loading buffers from disk or when performance is not
critical. Do not forget to release the structure when not needed.
For continous acquisition where the number or ROIs is known it is recommended
to use the other provided method to avoid frequent memory allocation.

@param[out] pFrame      A pointer address where the newly created structure will be stored.
@param[in]  pSrcBuf     A raw frame data pointer as returned from the camera
@param[in]  srcBufSize  Size of the raw frame data buffer

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.
*/
rs_bool PV_DECL pl_md_create_frame_struct(md_frame** pFrame, void* pSrcBuf,
                                          uns32 srcBufSize);

/**
@brief Releases the md_frame struct.

@param[in]  pFrame  A pointer to the previously allocated structure.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.
*/
rs_bool PV_DECL pl_md_release_frame_struct(md_frame* pFrame);

/**
@brief Reads all the extended metadata from the given ext. metadata buffer.

@param[out] pOutput     A pre-allocated structure that will be filled with metadata
@param[in]  pExtMdPtr   A pointer to the ext. MD buffer, this can be obtained from
                        the md_frame and md_frame_roi structures.
@param[in]  extMdSize   Size of the ext. MD buffer, also retrievable from the helper
                        structures.

@return #PV_OK for success, #PV_FAIL for a failure. Failure sets #pl_error_code.
*/
rs_bool PV_DECL pl_md_read_extended(md_ext_item_collection* pOutput, void* pExtMdPtr,
                                    uns32 extMdSize);

/** @} */ /* grp_pm_functions */

#ifdef PV_C_PLUS_PLUS
};
#endif

#endif /* PV_EMBEDDED */

/******************************************************************************/
/* End of function prototypes.                                                */
/******************************************************************************/

#endif /* _PVCAM_H */