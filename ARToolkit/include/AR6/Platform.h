/*
 *  Platform.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2011-2015 ARToolworks, Inc.
 *
 *  Author(s): Julian Looser, Philip Lamb
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

#ifndef __AR6_Platform_h__
#define __AR6_Platform_h__

// Determine the platform on which the code is being built

#if TARGET_PLATFORM_WINDOWS
// Include Windows API.
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#  endif
#  include <sdkddkver.h> // Minimum supported version. See http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745.aspx
#  include <windows.h>
#  if defined(WINAPI_FAMILY)
#    if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP) // Windows Phone 8.1 and later.
#      if (_WIN32_WINNT >= 0x0603) // (_WIN32_WINNT_WINBLUE)
#        define TARGET_PLATFORM_WINRT 1
#      else
#        error ARToolKit for Windows Phone requires Windows Phone 8.1 or later. Please compile with Visual Studio 2013 or later with Windows Phone 8.1 SDK installed and with _WIN32_WINNT=0x0603 in your project compiler settings (setting /D_WIN32_WINNT=0x0603).
#      endif
#    elif (WINAPI_FAMILY == WINAPI_FAMILY_PC_APP) // Windows Store 8.1 and later.
#      if (_WIN32_WINNT >= 0x0603) // (_WIN32_WINNT_WINBLUE)
#        define TARGET_PLATFORM_WINRT 1
#      else
#        error ARToolKit for Windows Store requires Windows 8.1 or later. Please compile with Visual Studio 2013 or later with Windows 8.1 SDK installed and with _WIN32_WINNT=0x0603 in your project compiler settings (setting /D_WIN32_WINNT=0x0603).
#      endif
#    endif
#  endif
#endif

// Configure preprocessor definitions for current platform

#if TARGET_PLATFORM_WINDOWS

#  define EXPORT_API __declspec(dllexport) 
#  define CALL_CONV __stdcall

#elif TARGET_PLATFORM_WINRT

#  ifndef LIBARCONTROLLER_STATIC
#    ifdef LIBARCONTROLLER_EXPORTS
#      define EXPORT_API __declspec(dllexport)
#    else
#      define EXPORT_API __declspec(dllimport)
#    endif
#  else
#    define EXPORT_API extern
#  endif
#  define CALL_CONV __stdcall

#elif TARGET_PLATFORM_MACOS || TARGET_PLATFORM_IOS || TARGET_PLATFORM_LINUX

#  define EXPORT_API
#  define CALL_CONV

#elif TARGET_PLATFORM_ANDROID

#  define EXPORT_API
#  define CALL_CONV

// Utility preprocessor directive so only one change needed if Java class name changes
#  define JNIFUNCTION(sig) Java_org_artoolkit_ar6_base_NativeInterface_##sig

#else
#  error Must define one of: TARGET_PLATFORM_MACOS TARGET_PLATFORM_IOS TARGET_PLATFORM_LINUX TARGET_PLATFORM_ANDROID TARGET_PLATFORM_WINDOWS TARGET_PLATFORM_WINRT
#endif

typedef void (CALL_CONV *PFN_LOGCALLBACK)(const char* msg);


#endif // !__AR6_Platform_h__
