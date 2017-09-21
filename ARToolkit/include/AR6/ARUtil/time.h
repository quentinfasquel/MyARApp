/*
 *  time.h
 *  ARToolKit6
 *
 *  Time-related functions.
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

#ifndef __AR6_ARUtil_time_h__
#define __AR6_ARUtil_time_h__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
    @brief Get the time in seconds since midnight (00:00:00), January 1, 1970, coordinated universal time (UTC).
    @param sec Pointer to an unsigned 64-bit interger which will be filled with the seconds portion of the time, or NULL if this value is not required.
    @param sec Pointer to an unsigned 32-bit interger which will be filled with the microseconds portion the time or NULL if this value is not required.
        N.B.: The resolution of the returned time is system-specific, and is not guaranteed to have microsecond-resolution.
 */
void           arUtilTimeSinceEpoch(uint64_t *sec, uint32_t *usec);

/*!
    @brief Read the timer.
    @return Elapsed seconds since last invocation of arUtilTimerReset().
    @see arUtilTimerReset
 */
double         arUtilTimer(void);

/*!
    @brief Reset the timer.
    @see arUtilTimer
 */
void           arUtilTimerReset(void);

#ifndef _WINRT
/*!
    @brief   Relinquish CPU to the system for specified number of milliseconds.
    @details
        This function calls the native system-provided sleep routine to relinquish
        CPU control to the system for the specified time.
    @param      msec Sleep time in milliseconds (thousandths of a second).
    @since Not available on Windows Runtime (WinRT).
 */
void           arUtilSleep( int msec );
#endif // !_WINRT


#ifdef __cplusplus
}
#endif
#endif // !__AR6_ARUtil_time_h__
