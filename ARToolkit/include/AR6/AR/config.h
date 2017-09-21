/*
 *  config.h
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
	@file config.h
	@brief ARToolKit core configuration.
	@version 6.0
	@details
	@copyright 2015-2016 Daqri, LLC.
 */


#ifndef AR_CONFIG0_H
#define AR_CONFIG0_H

//
// As of version 2.72 and 4.1, ARToolKit supports an OpenGL-like
// versioning system, with both header versions (for the version
// of the ARToolKit SDK installed) and runtime version reporting
// via arGetVersion().
//

/*@
    The MAJOR version number defines non-backwards compatible
    changes in the ARToolKit API. Range: [0-99].
 */
#define AR_HEADER_VERSION_MAJOR     6

/*@
    The MINOR version number defines additions to the ARToolKit
    API, or (occsasionally) other significant backwards-compatible
    changes in runtime functionality. Range: [0-99].
 */
#define AR_HEADER_VERSION_MINOR     0

/*@
    The TINY version number defines bug-fixes to existing
    functionality. Range: [0-99].
 */
#define AR_HEADER_VERSION_TINY      2

/*@
    The DEV version number will always be zero in releases,
    but may be non-zero in post-release development builds,
    version-control repository-sourced code, or other. Range: [0-99].
 */
#define AR_HEADER_VERSION_DEV       0

/*@
    The string representation below must match the major, minor
    and tiny release numbers.
 */
#define AR_HEADER_VERSION_STRING    "6.0.2"

/*@
    Convenience macros to enable use of certain ARToolKit header
    functionality by the release version in which it appeared.
    Each time the major version number is incremented, all
    existing macros must be removed, and just one new one
    added for the new major version.
    Each time the minor version number is incremented, a new
    AR_HAVE_HEADER_VERSION_ macro definition must be added.
    Tiny version numbers (being bug-fix releases, by definition)
    are NOT included in the AR_HAVE_HEADER_VERSION_ system.
 */
#define AR_HAVE_HEADER_VERSION_6

//
// End version definitions.
//

/*
#undef   AR_BIG_ENDIAN
#undef   AR_LITTLE_ENDIAN
*/

/*!
    @typedef AR_PIXEL_FORMAT
	@brief ARToolKit pixel-format specifiers.
	@details
		ARToolKit functions can accept pixel data in a variety of formats.
		This enumerations provides a set of constants you can use to request
		data in a particular pixel format from an ARToolKit function that
		returns data to you, or to specify that data you are providing to an
		ARToolKit function is in a particular pixel format.
 */
typedef enum {
    /*@
        Value indicating pixel format is invalid or unset.
     */
    AR_PIXEL_FORMAT_INVALID = -1,
    /*@
        Each pixel is represented by 24 bits. Eight bits per each Red, Green,
        and Blue component. This is the native 24 bit format for the Mac platform.
     */
    AR_PIXEL_FORMAT_RGB = 0,
    /*@
		Each pixel is represented by 24 bits. Eight bits per each Blue, Red, and
		Green component. This is the native 24 bit format for the Win32 platform.
     */
	AR_PIXEL_FORMAT_BGR,
    /*@
		Each pixel is represented by 32 bits. Eight bits per each Red, Green,
		Blue, and Alpha component.
     */
    AR_PIXEL_FORMAT_RGBA,
    /*@
		Each pixel is represented by 32 bits. Eight bits per each Blue, Green,
		Red, and Alpha component. This is the native 32 bit format for the Win32
		and Mac Intel platforms.
     */
    AR_PIXEL_FORMAT_BGRA,
    /*@
		Each pixel is represented by 32 bits. Eight bits per each Alpha, Blue,
		Green, and Red component. This is the native 32 bit format for the SGI
		platform.
     */
    AR_PIXEL_FORMAT_ABGR,
    /*@
		Each pixel is represented by 8 bits of luminance information.
     */
    AR_PIXEL_FORMAT_MONO,
    /*@
		Each pixel is represented by 32 bits. Eight bits per each Alpha, Red,
		Green, and Blue component. This is the native 32 bit format for the Mac
		PowerPC platform.
     */
    AR_PIXEL_FORMAT_ARGB,
    /*@
		8-bit 4:2:2 Component Y'CbCr format. Each 16 bit pixel is represented
		by an unsigned eight bit luminance component and two unsigned eight bit
		chroma components. Each pair of pixels shares a common set of chroma
		values. The components are ordered in memory; Cb, Y0, Cr, Y1. The
		luminance components have a range of [16, 235], while the chroma value
		has a range of [16, 240]. This is consistent with the CCIR601 spec.
		This format is fairly prevalent on both Mac and Win32 platforms.
		'2vuy' is the Apple QuickTime four-character code for this pixel format.
		The equivalent Microsoft fourCC is 'UYVY'.
     */
    AR_PIXEL_FORMAT_2vuy,
    /*@
		8-bit 4:2:2 Component Y'CbCr format. Identical to the AR_PIXEL_FORMAT_2vuy except
		each 16 bit word has been byte swapped. This results in a component
		ordering of; Y0, Cb, Y1, Cr.
		This is most prevalent yuv 4:2:2 format on both Mac and Win32 platforms.
		'yuvs' is the Apple QuickTime four-character code for this pixel format.
		The equivalent Microsoft fourCC is 'YUY2'.
     */
    AR_PIXEL_FORMAT_yuvs,
    /*@
        A packed-pixel format. Each 16 bit pixel consists of 5 bits of red color
        information in bits 15-11, 6 bits of green color information in bits 10-5,
        and 5 bits of blue color information in bits 4-0. Byte ordering is big-endian.
     */
    AR_PIXEL_FORMAT_RGB_565,
    /*@
        A packed-pixel format. Each 16 bit pixel consists of 5 bits of red color
        information in bits 15-11, 5 bits of green color information in bits 10-6,
        5 bits of blue color information in bits 5-1, and a single alpha bit in bit 0.
        Byte ordering is big-endian.
     */
    AR_PIXEL_FORMAT_RGBA_5551,
    /*@
        A packed-pixel format. Each 16 bit pixel consists of 4 bits of red color
        information in bits 15-12, 6 bits of green color information in bits 11-8,
        4 bits of blue color information in bits 7-4, and 4 bits of alpha information
        in bits 3-0. Byte ordering is big-endian.
     */
    AR_PIXEL_FORMAT_RGBA_4444,
    /*@
         8-bit 4:2:0 Component Y'CbCr format. Each 2x2 pixel block is represented
         by 4 unsigned eight bit luminance values and two unsigned eight bit
         chroma values. The chroma plane and luma plane are separated in memory. The
         luminance components have a range of [16, 235], while the chroma value
         has a range of [16, 240]. This is consistent with the CCIR601 spec.
         '420v' is the Apple Core Video four-character code for this pixel format.
     */
    AR_PIXEL_FORMAT_420v,
    /*@
         8-bit 4:2:0 Component Y'CbCr format. Each 2x2 pixel block is represented
         by 4 unsigned eight bit luminance components and two unsigned eight bit
         chroma components. The chroma plane and luma plane are separated in memory. The
         luminance components have a range of [0, 255], while the chroma value
         has a range of [1, 255].
         '420f' is the Apple Core Video four-character code for this pixel format.
         The equivalent Microsoft fourCC is 'NV12'.
     */
    AR_PIXEL_FORMAT_420f,
    /*@
        8-bit 4:2:0 Component Y'CbCr format. Each 2x2 pixel block is represented
        by 4 unsigned eight bit luminance components and two unsigned eight bit
        chroma components. The chroma plane and luma plane are separated in memory. The
        luminance components have a range of [0, 255], while the chroma value
        has a range of [1, 255].
     */
    AR_PIXEL_FORMAT_NV21
} AR_PIXEL_FORMAT;
#define       AR_PIXEL_FORMAT_UYVY      AR_PIXEL_FORMAT_2vuy
#define       AR_PIXEL_FORMAT_YUY2      AR_PIXEL_FORMAT_yuvs

// Note if making changes to the above table:
// If the number of pixel formats supported changes, AR_PIXEL_FORMAT_MAX must too.
// The functions arVideoUtilGetPixelSize(), arVideoUtilGetPixelFormatName()
// and arUtilGetPixelSize() arUtilGetPixelFormatName() must also be edited.
#define       AR_PIXEL_FORMAT_MAX       AR_PIXEL_FORMAT_NV21

//
// Top-level config.
//

#define HAVE_GL 0
#define HAVE_GLES2 1
#define HAVE_GL3 0

#define USE_CPARAM_SEARCH 1
#define USE_GL_STATE_CACHE 1
#define USE_INSTANTON 0


//
//  For Linux
//

#ifdef EMSCRIPTEN
#  define __linux
#endif

#if defined(__linux) && !defined(ANDROID)

#define AR_CALLBACK

// Determine architecture endianess using gcc's macro, or assume little-endian by default.
#  if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) || defined(__BIG_ENDIAN__)
#    define  AR_BIG_ENDIAN  // Most Significant Byte has greatest address in memory (ppc).
#    undef   AR_LITTLE_ENDIAN
#  elif (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || defined (__LITTLE_ENDIAN__)
#    undef   AR_BIG_ENDIAN   // Least significant Byte has greatest address in memory (x86).
#    define  AR_LITTLE_ENDIAN
#  else
#    define  AR_LITTLE_ENDIAN
#  endif

// Other Linux-only configuration.
#define HAVE_LIBJPEG 1
#define HAVE_INTEL_SIMD 1

#endif // __linux

// Default pixel formats.

#ifdef AR6_ARVIDEO_INPUT_V4L2
//#define  AR6_ARVIDEO_INPUT_V4L2_DEFAULT_PIXEL_FORMAT   AR_PIXEL_FORMAT_BGR 
//#define  AR6_ARVIDEO_INPUT_V4L2_DEFAULT_PIXEL_FORMAT   AR_PIXEL_FORMAT_BGRA
#define AR6_ARVIDEO_INPUT_V4L2_DEFAULT_PIXEL_FORMAT   AR_PIXEL_FORMAT_BGR
#endif

#ifdef  AR6_ARVIDEO_INPUT_DV
//#define  AR6_ARVIDEO_INPUT_DV_DEFAULT_PIXEL_FORMAT    AR_PIXEL_FORMAT_RGB 
//#define  AR6_ARVIDEO_INPUT_DV_DEFAULT_PIXEL_FORMAT    AR_PIXEL_FORMAT_BGRA
#define AR6_ARVIDEO_INPUT_DV_DEFAULT_PIXEL_FORMAT    AR_PIXEL_FORMAT_RGB
#endif

#ifdef AR6_ARVIDEO_INPUT_LIBDC1394
#undef AR6_ARVIDEO_INPUT_LIBDC1394_USE_LIBDC1394_V2
//#define  AR6_ARVIDEO_INPUT_LIBDC1394_DEFAULT_PIXEL_FORMAT   AR_PIXEL_FORMAT_MONO
//#define  AR6_ARVIDEO_INPUT_LIBDC1394_DEFAULT_PIXEL_FORMAT   AR_PIXEL_FORMAT_RGB 
#define   AR6_ARVIDEO_INPUT_LIBDC1394_DEFAULT_PIXEL_FORMAT   AR_PIXEL_FORMAT_MONO
#undef   AR6_ARVIDEO_INPUT_LIBDC1394_USE_DRAGONFLY
#undef   AR6_ARVIDEO_INPUT_LIBDC1394_USE_DF_EXPRESS
#undef   AR6_ARVIDEO_INPUT_LIBDC1394_USE_FLEA
#undef   AR6_ARVIDEO_INPUT_LIBDC1394_USE_FLEA_XGA
#undef   AR6_ARVIDEO_INPUT_LIBDC1394_USE_DFK21AF04
#endif

#ifdef AR6_ARVIDEO_INPUT_GSTREAMER
#define AR6_ARVIDEO_INPUT_GSTREAMER_PIXEL_FORMAT   AR_PIXEL_FORMAT_RGB 
#endif



//
//  For Windows                                              
//
#ifdef _WIN32

// Include Windows API.
#ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#endif
#include <sdkddkver.h> // Minimum supported version. See http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745.aspx
#include <windows.h>

#define AR_CALLBACK __stdcall
#define strdup _strdup

// Define _WINRT for support Windows Runtime platforms.
#if defined(WINAPI_FAMILY)
#  if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP) // Windows Phone 8.1 and later.
#    if (_WIN32_WINNT >= 0x0603) // (_WIN32_WINNT_WINBLUE)
#      define _WINRT
#      define LIBARVIDEO_STATIC
#      define ARDOUBLE_IS_FLOAT
#    else
#      error ARToolKit for Windows Phone requires Windows Phone 8.1 or later. Please compile with Visual Studio 2013 or later with Windows Phone 8.1 SDK installed and with _WIN32_WINNT=0x0603 in your project compiler settings (setting /D_WIN32_WINNT=0x0603).
#    endif
#  elif (WINAPI_FAMILY == WINAPI_FAMILY_PC_APP) // Windows Store 8.1 and later.
#    if (_WIN32_WINNT >= 0x0603) // (_WIN32_WINNT_WINBLUE)
#      define _WINRT
#      define LIBARVIDEO_STATIC
#      define ARDOUBLE_IS_FLOAT
#    else
#      error ARToolKit for Windows Store requires Windows 8.1 or later. Please compile with Visual Studio 2013 or later with Windows 8.1 SDK installed and with _WIN32_WINNT=0x0603 in your project compiler settings (setting /D_WIN32_WINNT=0x0603).
#    endif
#  endif
#endif

// Endianness.
// Windows on x86, x86-64 and ARM all run little-endian.
#undef   AR_BIG_ENDIAN
#define  AR_LITTLE_ENDIAN

// Other Windows-only configuration.
#define HAVE_LIBJPEG 1

#if defined(_M_IX86) || defined(_M_X64)
#  define HAVE_INTEL_SIMD 1
#elif defined(_M_ARM)
#  undef HAVE_ARM_NEON // MSVC doesn't support inline assembly on ARM platform.
#endif

#endif // _WIN32

// Default pixel formats.

#ifdef AR6_ARVIDEO_INPUT_WINDOWS_MEDIA_FOUNDATION
#define  AR6_ARVIDEO_INPUT_WINDOWS_MEDIA_FOUNDATION_PIXEL_FORMAT   AR_PIXEL_FORMAT_BGRA
#endif

#ifdef AR6_ARVIDEO_INPUT_WINDOWS_MEDIA_CAPTURE
#define  AR6_ARVIDEO_INPUT_WINDOWS_MEDIA_CAPTURE_PIXEL_FORMAT   AR_PIXEL_FORMAT_BGRA
#endif

//
//  For Android                                              
//    Note that Android NDK also defines __linux             
//

#if defined ANDROID

// Determine architecture endianess using gcc's macro, or assume little-endian by default.
#  if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) || defined(__BIG_ENDIAN__)
#    define  AR_BIG_ENDIAN  // Most Significant Byte has greatest address in memory (ppc).
#    undef   AR_LITTLE_ENDIAN
#  elif (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || defined (__LITTLE_ENDIAN__)
#    undef   AR_BIG_ENDIAN   // Least significant Byte has greatest address in memory (x86).
#    define  AR_LITTLE_ENDIAN
#  else
#    define  AR_LITTLE_ENDIAN
#  endif

#define AR_CALLBACK
#define ARDOUBLE_IS_FLOAT

#define HAVE_LIBJPEG 1
#define USE_OPENGL_ES 1

#endif // _ANDROID

// Default pixel formats.

#ifdef AR6_ARVIDEO_INPUT_ANDROID
#define  AR6_ARVIDEO_INPUT_ANDROID_PIXEL_FORMAT   AR_PIXEL_FORMAT_NV21
#endif

//
//  For Mac OS X                                             
//
#if __APPLE__

#  include <TargetConditionals.h>
#  include <AvailabilityMacros.h>

#  define AR_CALLBACK

// Endianness.
#  if TARGET_RT_BIG_ENDIAN
#    define  AR_BIG_ENDIAN  // Most Significant Byte has greatest address in memory (ppc).
#    undef   AR_LITTLE_ENDIAN
#  elif TARGET_RT_LITTLE_ENDIAN
#    undef   AR_BIG_ENDIAN
#    define  AR_LITTLE_ENDIAN
#  else
#    error
#  endif

#if TARGET_IPHONE_SIMULATOR

#error This release does not support the simulator. Please target an iOS device.

#elif TARGET_OS_IPHONE

#define ARDOUBLE_IS_FLOAT
#define HAVE_LIBJPEG 1
#define USE_OPENGL_ES 1
#ifdef __LP64__
#  define HAVE_ARM64_NEON 1
#else
#  define HAVE_ARM_NEON 1
#endif

#elif TARGET_OS_MAC

#define HAVE_LIBJPEG 1
#define HAVE_INTEL_SIMD 1

#endif

#endif // __APPLE__

//
//  Emscripten input                                         
//

#ifdef EMSCRIPTEN
#define AR6_ARVIDEO_INPUT_DEFAULT_EMSCRIPTEN
#define AR6_ARVIDEO_INPUT_EMSCRIPTEN_PIXEL_FORMAT   AR_PIXEL_FORMAT_RGBA
#endif

//
// If trying to minimize memory footprint, disable a few things.
//

#if AR_ENABLE_MINIMIZE_MEMORY_FOOTPRINT
#define AR_DISABLE_THRESH_MODE_AUTO_ADAPTIVE 1
#define AR_DISABLE_NON_CORE_FNS 1
#define AR_DISABLE_LABELING_DEBUG_MODE 1
#endif

#endif // !AR_CONFIG0_H
