/*
 *  log.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2002-2015 ARToolworks, Inc.
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

/*!
	@file log.h
	@brief Logging utilities.
	@details
        Various routines to format and redirect log output.
	@Copyright 2015-2017 Daqri, LLC.
 */

#ifndef ARUTIL_LOG_H
#define ARUTIL_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#ifndef _WIN32 // errno is defined in stdlib.h on Windows.
#  ifdef EMSCRIPTEN // errno is not in sys/
#    include <errno.h>
#  else
#    include <sys/errno.h>
#  endif
#endif
#ifdef __ANDROID__
#  include <android/log.h>
#endif
#ifdef _WIN32
#  define ARUTIL_CALLBACK __stdcall
#else
#  define ARUTIL_CALLBACK
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum {
    AR_LOG_LEVEL_DEBUG = 0,
    AR_LOG_LEVEL_INFO,
    AR_LOG_LEVEL_WARN,
    AR_LOG_LEVEL_ERROR,
    AR_LOG_LEVEL_REL_INFO
};
#define AR_LOG_LEVEL_DEFAULT AR_LOG_LEVEL_INFO

/*!
    @var int arLogLevel
    @brief   Sets the severity level. Log messages below the set severity level are not logged.
	@details
        All calls to ARToolKit's logging facility include a "log level" parameter, which specifies
        the severity of the log message. (The severities are defined in &lt;AR6/ARUtil/log.h&gt;.)
        Setting this global allows for filtering of log messages. All log messages lower than
        the set level will not be logged by arLog().
        Note that debug log messages created using the ARLOGd() macro will be logged only in
        debug builds, irrespective of the log level.
    @see arLog
*/
extern int arLogLevel;

/*!
    @brief   Write a string to the current logging facility.
	@details
        The default logging facility varies by platform, but on Unix-like platforms is typically
        the standard error file descriptor. However, logging may be redirected to some other
        facility by arLogSetLogger.

        Newlines are not automatically appended to log output.
    @param      tag A tag to supply to an OS-specific logging function to specify the source
        of the error message. May be NULL, in which case "libAR" will be used.
    @param      logLevel The severity of the log message. Defined in %lt;AR6/ARUtil/log.h&gt;.
        Log output is written to the logging facility provided the logLevel meets or
        exceeds the minimum level specified in global arLogLevel.
    @param      format Log format string, in the form of printf().
    @see arLogLevel
    @see arLogSetLogger
*/

void arLog(const char *tag, const int logLevel, const char *format, ...);
void arLogv(const char *tag, const int logLevel, const char *format, va_list ap);

typedef void (ARUTIL_CALLBACK *AR_LOG_LOGGER_CALLBACK)(const char *logMessage);

/*!
    @brief   Divert logging to a callback, or revert to default logging.
	@details
        The default logging facility varies by platform, but on Unix-like platforms is typically
        the standard error file descriptor. However, logging may be redirected to some other
        facility by this function.
    @param      callback The function which will be called with the log output, or NULL to
        cancel redirection.
    @param      callBackOnlyIfOnSameThread If non-zero, then the callback will only be called
        if the call to arLog is made on the same thread as the thread which called this function,
        and if the arLog call is made on a different thread, log output will be buffered until
        the next call to arLog on the original thread.

        The purpose of this is to prevent logging from secondary threads in cases where the
        callback model of the target platform precludes this.
    @see arLog
*/
void arLogSetLogger(AR_LOG_LOGGER_CALLBACK callback, int callBackOnlyIfOnSameThread);

#ifdef DEBUG
#  define ARLOGd(...) arLog(NULL, AR_LOG_LEVEL_DEBUG, __VA_ARGS__)
#else
#  define ARLOGd(...)
#endif
#define ARLOGi(...) arLog(NULL, AR_LOG_LEVEL_INFO, __VA_ARGS__)
#define ARLOGw(...) arLog(NULL, AR_LOG_LEVEL_WARN, __VA_ARGS__)
#define ARLOGe(...) arLog(NULL, AR_LOG_LEVEL_ERROR, __VA_ARGS__)
#define ARLOGperror(s) arLog(NULL, AR_LOG_LEVEL_ERROR, ((s != NULL) ? "%s: %s\n" : "%s%s\n"), ((s != NULL) ? s : ""), strerror(errno))

#ifdef __ANDROID__
#  define ARLOG(...)  __android_log_print(ANDROID_LOG_INFO, "artoolkit", __VA_ARGS__)
#else
#  define ARLOG(...)  printf(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif
#endif //#ifndef ARUTIL_LOG_H
