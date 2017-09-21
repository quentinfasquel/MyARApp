/*
 *  system.h
 *  ARToolKit6
 *
 *  Functions to query various system-related parameters.
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2007-2015 ARToolworks, Inc.
 *
 *  Author(s): Hirokazu Kato, Philip Lamb
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

#ifndef __AR6_ARUtil_system_h__
#define __AR6_ARUtil_system_h__

#ifdef __cplusplus
extern "C" {
#endif

/*!
    @brief   Get a string holding a descriptive name of the current operating system.
    @details
        For applications requiring some information on operating system, this function
        provides the type of the operating system currently executing. It is defined
        to be one of the following values: "macos", "ios", "linux", "android", "windows",
        or "unknown" if the current OS cannot be determined.
    @result     A c-string holding a descriptive name of the current operating system.
        It is the responsibility of the caller to dispose of the string (by calling free()).
 */
char *arUtilGetOSName(void);

/*!
    @brief   Get a string holding a descriptive name of current operating system version.
    @details
        For applications requiring some information on operating system, this function
        provides the version of the operating system currently executing. It is determined
        in an operating system-dependent manner.
 
        If the version cannot be determined, the string "unknown" will be returned.
    @result     A c-string holding a descriptive name of the current operating system version.
        It is the responsibility of the caller to dispose of the string (by calling free()).
 */
char *arUtilGetOSVersion(void);

/*!
    @brief   Get a string holding a descriptive name of the current CPU type.
    @details
        For applications requiring some information on CPU type, this function
        provides the type of the CPU currently executing. It is determined in an
        operating system-dependent manner, and thus the results may not be directly
        comparable between different operating systems running on the same
        hardware.
 
        If the CPU type cannot be determined, the string "unknown" will be returned.
    @result     A c-string holding a descriptive name of the current CPU type.
        It is the responsibility of the caller to dispose of the string (by calling free()).
 */
char *arUtilGetCPUName(void);

#ifdef __cplusplus
}
#endif
#endif // !__AR6_ARUtil_system_h__
