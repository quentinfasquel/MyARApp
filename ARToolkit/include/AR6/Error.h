/*
 *  Error.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2014-2015 ARToolworks, Inc.
 *
 *  Author(s): Philip Lamb
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#ifndef __AR6_Error_h__
#define __AR6_Error_h__

/**
 * \file Error.h
 * Defines error codes used in the library.
 */

#ifdef __cplusplus
extern "C" {
#endif

    enum {
        ARW_ERROR_NONE                        =   0,
        ARW_ERROR_GENERIC                     =  -1,
        ARW_ERROR_OUT_OF_MEMORY               =  -2,
        ARW_ERROR_OVERFLOW                    =  -3,
        ARW_ERROR_NODATA                      =  -4,
        ARW_ERROR_IOERROR                     =  -5,
        ARW_ERROR_EOF                         =  -6,
        ARW_ERROR_TIMEOUT                     =  -7,
        ARW_ERROR_INVALID_COMMAND             =  -8,
        ARW_ERROR_INVALID_ENUM                =  -9,
        ARW_ERROR_THREADS                     = -10,
        ARW_ERROR_FILE_NOT_FOUND              = -11,
        ARW_ERROR_LENGTH_UNAVAILABLE          = -12,
        ARW_ERROR_DEVICE_UNAVAILABLE          = -13,
        ARW_ERROR_INVALID_PARAMETER           = -14,
        ARW_ERROR_2D_IMG_TRACKER_INIT         = -15,
        ARW_ERROR_SQUARE_TRACKER_INIT         = -16,
        ARW_ERROR_INSTANTON_TRACKER_INIT      = -17,
        ARW_ERROR_AR_UNINITIALISED            = -18,
        ARW_ERROR_START_VIDEO_SOURCING        = -19,
        ARW_ERROR_UPDATE_TO_RUN_MARKER_DETECT = -20,
        ARW_ERROR_VIDEO_FRAME_CAPTURE_ERROR   = -21
    };

#ifdef __cplusplus
}
#endif
#endif // !__AR6_Error_h__
