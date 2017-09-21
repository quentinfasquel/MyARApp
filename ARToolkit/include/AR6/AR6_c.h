/*
 *  AR6_c.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2010-2015 ARToolworks, Inc.
 *
 *  Author(s): Philip Lamb, Julian Looser.
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

#ifndef __AR6_AR6_c_h__
#define __AR6_AR6_c_h__

#include <AR6/Platform.h>
#include <AR6/Error.h>
#include <stdint.h>
#include <stdbool.h>
/**
 * \file AR6_c.h
 * Defines functions that provide a C-compatible API. These functions are accessible to 
 * other C, C++, and Objective-C applications, as well as languages like C# via P/Invoke,
 * and Java via JNI.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Registers a callback function to use when a message is logged.
 * If the callback is to become invalid, be sure to call this function with NULL
 * first so that the callback is unregistered.
 */
EXPORT_API void arwRegisterLogCallback(PFN_LOGCALLBACK callback);

/**
 * Sets the severity level. Log messages below the set severity level are not logged.
 * All calls to ARToolKit's logging facility include a "log level" parameter, which specifies
 * the severity of the log message. (The severities are defined in %lt;AR6/AR/config.h&gt;.)
 * Setting this allows for filtering of log messages. All log messages lower than
 * the set level will not be logged.
 * Note that debug log messages created using the native ARLOGd() macro will be logged only in
 * debug builds, irrespective of the log level.
 * @param logLevel The log level below which log messages should be ignored.
 */
EXPORT_API void arwSetLogLevel(const int logLevel);

// ----------------------------------------------------------------------------------------------------
#pragma mark  ARToolKit lifecycle functions
// ----------------------------------------------------------------------------------------------------
/**
 * Initialises the ARToolKit to use default pattern size and number of square markers.
 * For any square template (pattern) markers, the number of rows and columns in the template defaults to AR_PATT_SIZE1 and the maximum number of markers that may be loaded for a single matching pass defaults to AR_PATT_NUM_MAX.
 * @return          true if successful, false if an error occurred
 * @see             arwShutdownAR()
 */
EXPORT_API bool arwInitialiseAR();

/**
 * Initialises the ARToolKit with non-default options for size and number of square markers.
 * @param pattSize For any square template (pattern) markers, the number of rows and columns in the template. May not be less than 16 or more than AR_PATT_SIZE1_MAX. Pass AR_PATT_SIZE1 for the same behaviour as arwInitialiseAR().
 * @param pattCountMax For any square template (pattern) markers, the maximum number of markers that may be loaded for a single matching pass. Must be > 0. Pass AR_PATT_NUM_MAX for the same behaviour as arwInitialiseAR().
 * @return          true if successful, false if an error occurred
 * @see             arwShutdownAR()
 */
EXPORT_API bool arwInitialiseARWithOptions(const int pattSize, const int pattCountMax);

/**
 * Gets the ARToolKit version as a string, such as "4.5.1".
 * Must not be called prior to arwInitialiseAR().
 * @param buffer    The character buffer to populate
 * @param length    The maximum number of characters to set in buffer
 * @return          true if successful, false if an error occurred
 */
EXPORT_API bool arwGetARToolKitVersion(char *buffer, int length);

/**
 * Return error information
 * Returns the value of the error flag.  Each detectable error
 * is assigned a numeric code and symbolic name.  When  an  error  occurs,
 * the  error  flag  is set to the appropriate error code value.  No other
 * errors are recorded until arwGetError  is  called,  the  error  code  is
 * returned,  and  the  flag  is  reset  to  ARW_ERROR_NONE.   If  a  call to
 * arwGetError returns ARW_ERROR_NONE, there  has  been  no  detectable  error
 * since the last call to arwGetError, or since the the library was initialized.
 *
 * To  allow  for  distributed implementations, there may be several error
 * flags.  If any single error flag has recorded an error,  the  value  of
 * that  flag  is  returned  and  that  flag  is reset to ARW_ERROR_NONE when
 * arwGetError is called.  If more than one flag  has  recorded  an  error,
 * arwGetError  returns  and  clears  an arbitrary error flag value.  Thus,
 * arwGetError should  always  be  called  in  a  loop,  until  it  returns
 * ARW_ERROR_NONE, if all error flags are to be reset.
 *
 * Initially, all error flags are set to ARW_ERROR_NONE.
 * @return          enum with error code.
 */
EXPORT_API int arwGetError();

/**
 * Changes the working directory to the resources directory used by ARToolKit.
 * Normally, this would be called immediately after arwInitialiseAR() but
 * a preceding call of arwInitialiseAR() is not required for a successful return.
 * A subsequent call to arwInitliseAR() does not reset the currently set resource path.
 * If arwChangeToResourcesDir() is never called or a NULL or empty resource parameter
 * path is passed, the default behavior AR_UTIL_RESOURCES_DIRECTORY_BEHAVIOR_BEST
 * is set.
 * @return          true if successful, false if an error occurred
 * @see             arwInitialiseAR()
 */
EXPORT_API bool arwChangeToResourcesDir(const char *resourcesDirectoryPath);

/**
 * Initialises and starts video capture (sourcing).
 * @param vconf     The video configuration string
 * @param cparaName The camera parameter file, which is used to form the projection matrix
 * @param nearPlane The distance to the near plane of the viewing frustum formed by the camera parameters.
 * @param farPlane  The distance to the far plane of the viewing frustum formed by the camera parameters.
 * @return          true if successful, false if an error occurred
 * @see             arwStopRunning()
 */
EXPORT_API bool arwStartRunning(const char *vconf, const char *cparaName, const float nearPlane, const float farPlane);

/**
 * Initialises and starts video capture (sourcing).
 * @param vconf     The video configuration string
 * @param cparaBuff A string containing the contents of a camera parameter file, which is used to form the projection matrix.
 * @param cparaBuffLen  Number of characters in cparaBuff.
 * @param nearPlane The distance to the near plane of the viewing frustum formed by the camera parameters.
 * @param farPlane  The distance to the far plane of the viewing frustum formed by the camera parameters.
 * @return          true if successful, false if an error occurred
 * @see             arwStopRunning()
 */
EXPORT_API bool arwStartRunningB(const char *vconf, const char *cparaBuff, const int cparaBuffLen, const float nearPlane, const float farPlane);

EXPORT_API bool arwStartRunningStereo(const char *vconfL, const char *cparaNameL, const char *vconfR, const char *cparaNameR, const char *transL2RName, const float nearPlane, const float farPlane);

EXPORT_API bool arwStartRunningStereoB(const char *vconfL, const char *cparaBuffL, const int cparaBuffLenL, const char *vconfR, const char *cparaBuffR, int cparaBuffLenR, const char *transL2RBuff, const int transL2RBuffLen, const float nearPlane, const float farPlane);

/**
 * Returns true is ARToolKit is initialized which should be the case if arwInitialiseAR() or arwInitialiseARWithOptions() has been called.
 * @return      true when initialized, otherwise false
 * @see         arwInitialiseARWithOptions(), arwInitialiseAR()
 */
EXPORT_API bool arwIsInited();
    
/**
 * Returns true if ARToolKit started video capture (sourcing) and marker detection is enabled.
 * Only possible encountered error is ARW_ERROR_AR_UNINITIALISED
 * @return          true if both video capture (sourcing) started and marker detection is enabled, otherwise false
 */
EXPORT_API bool arwIsRunning();

/**
 * ARToolKit stops - disables marker detection, stops video capture, closes the video source(s) and frees related resources.
 * @return          true if successful, false if an error occurred
 * @see             arwStartRunning()
 */
EXPORT_API bool arwStopRunning();

/**
 * ARToolKit calls arwStopRunning and transitions to an uninitialise state.
 * N.B.: If this is being called from the destructor of the same module which
 * supplied the log callback, be sure to set the logCallback = NULL
 * prior to calling this function.
 * @return          true if successful, false if an error occurred
 * @see             arwInitialiseAR()
 */
EXPORT_API bool arwShutdownAR();

// ----------------------------------------------------------------------------------------------------
#pragma mark  Video stream management
// ----------------------------------------------------------------------------------------------------

/**
 * Populates the given float array with the projection matrix computed from camera parameters for the video source.
 * @param p         Float array to populate with OpenGL compatible projection matrix.
 * @return          true if successful, false if an error occurred
 */
EXPORT_API bool arwGetProjectionMatrix(float p[16]);

/**
 * Populates the given float arrays with the projection matrices computed from camera parameters for each of the stereo video sources.
 * @param pL        Float array to populate with OpenGL compatible projection matrix for the left camera of the stereo video pair.
 * @param pR        Float array to populate with OpenGL compatible projection matrix for the right camera of the stereo video pair.
 * @return          true if successful, false if an error occurred
 */
EXPORT_API bool arwGetProjectionMatrixStereo(float pL[16], float pR[16]);

/**
 * Returns the parameters of the video source frame.
 * @param width Pointer to an int which will be filled with the width (in pixels) of the video frame, or NULL if this information is not required.
 * @param height Pointer to an int which will be filled with the height (in pixels) of the video frame, or NULL if this information is not required.
 * @param pixelSize Pointer to an int which will be filled with the numbers of bytes per pixel of the source frame.
 * @param pixelFormatStringBuffer Pointer to a buffer which will be filled with the symolic name of the pixel format (as a nul-terminated C-string) of the video frame, or NULL if this information is not required. The name will be of the form "AR_PIXEL_FORMAT_xxx".
 * @param pixelFormatStringBufferLen Length (in bytes) of pixelFormatStringBuffer, or 0 if this information is not required.
 * @return          True if the values were returned OK, false if there is currently no video source or an error int[] .
 * @see             arwGetVideoParamsStereo
 */
EXPORT_API bool arwGetVideoParams(int *width, int *height, int *pixelSize, char *pixelFormatStringBuffer, int pixelFormatStringBufferLen);

/**
 * Returns the parameters of the video source frames.
 * @param widthL Pointer to an int which will be filled with the width (in pixels) of the video frame, or NULL if this information is not required.
 * @param widthR Pointer to an int which will be filled with the width (in pixels) of the video frame, or NULL if this information is not required.
 * @param heightL Pointer to an int which will be filled with the height (in pixels) of the video frame, or NULL if this information is not required.
 * @param heightR Pointer to an int which will be filled with the height (in pixels) of the video frame, or NULL if this information is not required.
 * @param pixelSizeL Pointer to an int which will be filled with the numbers of bytes per pixel of the source frame, or NULL if this information is not required.
 * @param pixelSizeR Pointer to an int which will be filled with the numbers of bytes per pixel of the source frame, or NULL if this information is not required.
 * @param pixelFormatStringBufferL Pointer to a buffer which will be filled with the symbolic name of the pixel format (as a nul-terminated C-string) of the video frame, or NULL if this information is not required. The name will be of the form "AR_PIXEL_FORMAT_xxx".
 * @param pixelFormatStringBufferR Pointer to a buffer which will be filled with the symbolic name of the pixel format (as a nul-terminated C-string) of the video frame, or NULL if this information is not required. The name will be of the form "AR_PIXEL_FORMAT_xxx".
 * @param pixelFormatStringBufferLenL Length (in bytes) of pixelFormatStringBufferL, or 0 if this information is not required.
 * @param pixelFormatStringBufferLenR Length (in bytes) of pixelFormatStringBufferR, or 0 if this information is not required.
 * @return          True if the values were returned OK, false if there is currently no stereo video source or an error int[] .
 * @see             arwGetVideoParams
 */
EXPORT_API bool arwGetVideoParamsStereo(int *widthL, int *heightL, int *pixelSizeL, char *pixelFormatStringBufferL, int pixelFormatStringBufferLenL, int *widthR, int *heightR, int *pixelSizeR, char *pixelFormatStringBufferR, int pixelFormatStringBufferLenR);

/**
 * Captures a newest frame from the video source.
 * @return          true if successful, false if a warning or an error occurred. To determine whether a warning or an
 *                  error occurred, call arwGetError(). For warnings, arwGetError() returns ARW_ERROR_NONE (0).
 *                  If false and ARW_ERROR_NONE are respectively returned, this simply indicates a video frame was
 *                  not captured which is not considered an error.
 */
EXPORT_API bool arwCapture();

/**
 * Performs detection and marker updates. The newest frame from the video source is retrieved and
 * analysed. All loaded markers are updated.
 * @return          true if successful, false if an error occurred
 */
EXPORT_API bool arwUpdateAR();

/**
 * Populates the provided floating-point RGBA32 buffer with the current video frame.
 * @param buffer    Pointer to a buffer of pixels (of type 'uint32_t') to be filled. It is the
 *      caller's responsibility to ensure that the buffer is of sufficient size. The pixels are
 *      RGBA in little-endian systems, or ABGR in big-endian systems.
 * @return          true if successful, false if an error occurred
 */
EXPORT_API bool arwUpdateTexture32(uint32_t *buffer);

/**
 * Populates the provided floating-point RGBA32 buffers with the current stereo video frame.
 * @param bufferL   Pointer to a buffer of pixels (of type 'uint32_t') to be filled. It is the
 *      caller's responsibility to ensure that the buffer is of sufficient size. The pixels are
 *      RGBA in little-endian systems, or ABGR in big-endian systems.
 * @param bufferR   Pointer to a buffer of pixels (of type 'uint32_t') to be filled. It is the
 *      caller's responsibility to ensure that the buffer is of sufficient size. The pixels are
 *      RGBA in little-endian systems, or ABGR in big-endian systems.
 * @return          true if successful, false if an error occurred
 */
EXPORT_API bool arwUpdateTexture32Stereo(uint32_t *bufferL, uint32_t *bufferR);

// ----------------------------------------------------------------------------------------------------
#pragma mark  Display of the video frame.
// ----------------------------------------------------------------------------------------------------

/**
 * Initialise display of video frames in a graphics context.
 *
 * If rendering of video frames into a graphics context is desired,
 * this function must be called from the rendering thread to initialise
 * graphics library structures for future display of video frames.
 *
 * This function must be called only with a valid graphics context
 * active (typically from the rendering thread) and only when the
 * function arwIsRunning() returns true.
 *
 * When display of video frames is no longer required, the function
 * arwDisplayFrameFinal must be called to clean up structures allocated
 * by this call.
 *
 * @param videoSourceIndex The 0-based index of the video source which
 *     will supply frames for display.
 * @return true if successful, false if an error occurred.
 * @see arwIsRunning
 * @see arwDisplayFrameFinal
 */
EXPORT_API bool arwDisplayFrameInit(const int videoSourceIndex);

/**
 * Specifies desired horizontal alignement of video frames in display graphics context.
 */
enum {
    ARW_H_ALIGN_LEFT,       ///< Align the left edge of the video frame with the left edge of the context.
    ARW_H_ALIGN_CENTRE,     ///< Align the centre of the video frame with the centre of the context.
    ARW_H_ALIGN_RIGHT       ///< Align the right edge of the video frame with the right edge of the context.
};

/**
 * Specifies desired vertical alignement of video frames in display graphics context.
 */
enum {
    ARW_V_ALIGN_TOP,        ///< Align the top edge of the video frame with the top edge of the context.
    ARW_V_ALIGN_CENTRE,     ///< Align the centre of the video frame with the centre of the context.
    ARW_V_ALIGN_BOTTOM      ///< Align the bottom edge of the video frame with the bottom edge of the context.
};

/**
 * Specifies desired scaling of video frames to display graphics context.
 */
enum {
    ARW_SCALE_MODE_FIT,     ///< Scale the video frame proportionally up or down so that it fits visible in its entirety in the graphics context. When the graphics context is wider than the frame, it will be pillarboxed. When the graphics context is taller than the frame, it will be letterboxed.
    ARW_SCALE_MODE_FILL,    ///< Scale the video frame proportionally up or down so that it fills the entire in the graphics context. When the graphics context is wider than the frame, it will be cropped top and/or bottom. When the graphics context is taller than the frame, it will be cropped left and/or right.
    ARW_SCALE_MODE_STRETCH, ///< Scale the video frame un-proportionally up or down so that it matches exactly the size of the graphics context.
    ARW_SCALE_MODE_1_TO_1   ///< Do not scale the video frame. One pixel of the video frame will be represented by one pixel of the graphics context.
};

/**
 * Specify the layout of the graphics context in which display of video frames will occur.
 *
 * As the layout of the graphics context may (e.g. size, orientation) may
 * differ widely from the format of the video frames which are to be
 * displayed, this function specifies the layout of the graphics context
 * and the desired scaling and positioning of the video frames within
 * this context. Optionally, a calculated OpenGL-style viewport can be
 * returned to the caller.
 *
 * This function must only be called with a graphics context active
 * (typically from the rendering thread) and only while arwIsRunning is true
 * and only between calls to arwDisplayFrameInit and arwDisplayFrameFinal.
 *
 * @param videoSourceIndex The 0-based index of the video source which
 *     is supplying frames for display.
 * @param width The width in pixels of the graphics context.
 * @param height The height in pixels of the graphics context.
 * @param rotate90 If true, content should be rendered in the graphics
 *     context rotated 90-degrees.
 * @param flipH If true, content should be rendered in the graphics
 *     context mirrored (flipped) in the horizontal dimension.
 * @param flipV If true, content should be rendered in the graphics
 *     context mirrored (flipped) in the vertical dimension.
 * @param hAlign An enum ARW_H_ALIGN_* specifying the desired horizontal
 *     alignment of video frames in the graphics context.
 *     If unsure, pass ARW_H_ALIGN_CENTRE.
 * @param vAlign An enum ARW_V_ALIGN_* specifying the desired vertical
 *     alignment of video frames in the graphics context.
 *     If unsure, pass ARW_V_ALIGN_CENTRE.
 * @param scalingMode An enum ARW_SCALE_MODE_* specifying the desired
 *     scaling of the video frames to the graphics context.
 *     If unsure, pass ARW_SCALE_MODE_FIT.
 * @param viewport If non-NULL, must point to an array of 4 32-bit signed
 *     integers, in which the calculated OpenGL-style viewport parameters will
 *     be returned. The order of the parameters is: x-coordinate of the left
 *     edge of the viewport (may be negative), the y-coordinate of the bottom
 *     edge of the viewport (may be negative), the width of the viewport in the
 *     x-axis in pixels, and the height of the viewport in the y-axis in pixels.
 * @return true if successful, false if an error occurred.
 * @see arwIsRunning
 * @see arwDisplayFrameInit
 * @see arwDisplayFrameFinal
 */
EXPORT_API bool arwDisplayFrameSettings(int videoSourceIndex, int width, int height, bool rotate90, bool flipH, bool flipV, int hAlign, int vAlign, int scalingMode, int32_t viewport[4]);

/**
 * Displays the latest frame from the video source in the active graphics context.
 *
 * This function performs actual display of the latest video frame.
 *
 * This function must only be called with a graphics context active
 * (typically from the rendering thread) and only while arwIsRunning is true
 * and only between calls to arwDisplayFrameInit and arwDisplayFrameFinal,
 * and after at least one call to arwDisplayFrameSettings.
 *
 * @param videoSourceIndex The 0-based index of the video source which
 *     is supplying frames for display.
 * @return          true if successful, false if an error occurred.
 * @see arwIsRunning
 * @see arwDisplayFrameInit
 * @see arwDisplayFrameFinal
 * @see arwDisplayFrameSettings
 */
EXPORT_API bool arwDisplayFrame(const int videoSourceIndex);

/**
 * Finalise display of video frames in a graphics context.
 *
 * When display of video frames is no longer required, this function
 * must be called to clean up structures allocated by the call to
 * arwDisplayFrameInit.
 *
 * This function must only be called with a graphics context active
 * (typically from the rendering thread).
 *
 * @param videoSourceIndex The 0-based index of the video source which
 *     supplied frames for display.
 * @return true if successful, false if an error occurred.
 * @see arwDisplayFrameInit
 */
EXPORT_API bool arwDisplayFrameFinal(const int videoSourceIndex);

// ----------------------------------------------------------------------------------------------------
#pragma mark  Tracking configuration
// ----------------------------------------------------------------------------------------------------

/**
 * Constants for use with tracker option setters/getters.
 */
enum {
    ARW_TRACKER_OPTION_2D_MAX_IMAGES = 0,                          ///< int.
    ARW_TRACKER_OPTION_SQUARE_THRESHOLD = 1,                       ///< Threshold value used for image binarization. int in range [0-255].
    ARW_TRACKER_OPTION_SQUARE_THRESHOLD_MODE = 2,                  ///< Threshold mode used for image binarization. int.
    ARW_TRACKER_OPTION_SQUARE_LABELING_MODE = 3,                   ///< int.
    ARW_TRACKER_OPTION_SQUARE_PATTERN_DETECTION_MODE = 4,          ///< int.
    ARW_TRACKER_OPTION_SQUARE_BORDER_SIZE = 5,                     ///< float in range (0-0.5).
    ARW_TRACKER_OPTION_SQUARE_MATRIX_CODE_TYPE = 6,                ///< int.
    ARW_TRACKER_OPTION_SQUARE_IMAGE_PROC_MODE = 7,                 ///< int.
    ARW_TRACKER_OPTION_SQUARE_DEBUG_MODE = 8,                      ///< Enables or disable state of debug mode in the tracker. When enabled, a black and white debug image is generated during marker detection. The debug image is useful for visualising the binarization process and choosing a threshold value. bool.
};

/**
 * Set boolean options associated with a tracker.
 * @param option Symbolic constant identifying tracker option to set.
 * @param value The value to set it to.
 */
EXPORT_API void arwSetTrackerOptionBool(int option, bool value);

/**
 * Set integer options associated with a tracker.
 * @param option Symbolic constant identifying tracker option to set.
 * @param value The value to set it to.
 */
EXPORT_API void arwSetTrackerOptionInt(int option, int value);

/**
 * Set floating-point options associated with a tracker.
 * @param option Symbolic constant identifying tracker option to set.
 * @param value The value to set it to.
 */
EXPORT_API void arwSetTrackerOptionFloat(int option, float value);

/**
 * Get boolean options associated with a tracker.
 * @param option Symbolic constant identifying tracker option to get.
 * @return true if option is set, false if option is not set or an error occurred.
 */
EXPORT_API bool arwGetTrackerOptionBool(int option);

/**
 * Get integer options associated with a tracker.
 * @param option Symbolic constant identifying tracker option to get.
 * @return integer value of option, or INT_MIN if an error occurred.
 */
EXPORT_API int arwGetTrackerOptionInt(int option);

/**
 * Get floating-point options associated with a tracker.
 * @param option Symbolic constant identifying tracker option to get.
 * @return floating-point value of option, or NAN if an error occurred.
 */
EXPORT_API float arwGetTrackerOptionFloat(int option);

// ----------------------------------------------------------------------------------------------------
#pragma mark  Marker management
// ----------------------------------------------------------------------------------------------------
/**
 * Adds a trackable as specified in the given configuration string. The format of the string can be
 * one of:
 * - 2D image target:     "2d;target_image_pathname;image_height", e.g. "2d;gibraltar.jpg;160.9"
 * - Square marker:       "square;pattern_file;pattern_width", e.g. "single;data/hiro.patt;80"
 * - Multi-square marker: "multi;config_file", e.g. "multi;data/multi/marker.dat"
 * @param cfg       The configuration string
 * @return          The unique identifier (UID) of the marker instantiated based on the configuration string, or -1 if an error occurred
 */
EXPORT_API int arwAddMarker(const char *cfg);

/**
 * Removes the marker with the given unique identifier (UID).
 * @param markerUID The unique identifier (UID) of the marker to remove
 * @return          true if the marker was removed, false if an error occurred
 */
EXPORT_API bool arwRemoveMarker(int markerUID);

/**
 * Clears the collection of markers.
 * @return          The number of markers removed
 */
EXPORT_API int arwRemoveAllMarkers();

EXPORT_API bool arwLoad2DTrackerImageDatabase(const char* databaseName, int* trackableIds, int* targetSize, const char* destPath);
    
/**
 * Returns the visibility status of the specified marker. After a call to arwUpdate, all marker 
 * information will be current. Any marker can then be checked for visibility in the current frame.
 * @param markerUID The unique identifier (UID) of the marker to query
 * @return          true if the specified marker is visible, false if not, or an error occurred
 */
EXPORT_API bool arwQueryMarkerVisibility(int markerUID);

/**
 * Populates the provided float array with the current transformation for the specified marker. After 
 * a call to arwUpdate, all marker information will be current. Marker transformations can then be 
 * checked. If the specified marker is not found the last good transformation is used, and false is 
 * returned.
 * @param markerUID The unique identifier (UID) of the marker to query
 * @param matrix    The float array to populate with an OpenGL compatible transformation matrix
 * @return          true if the specified marker is visible, false if not, or an error occurred
 */
EXPORT_API bool arwQueryMarkerTransformation(int markerUID, float matrix[16]);

/**
 * Populates the provided float arrays with the current transformations for the specified marker. After
 * a call to arwUpdate, all marker information will be current. Marker transformations can then be
 * checked. If the specified marker is not found the last good transformation is used, and false is
 * returned.
 * @param markerUID The unique identifier (UID) of the marker to query
 * @param matrixL   The float array to populate with an OpenGL compatible transformation matrix for the left camera.
 * @param matrixR   The float array to populate with an OpenGL compatible transformation matrix for the right camera.
 * @return          true if the specified marker is visible, false if not, or an error occurred
 */
EXPORT_API bool arwQueryMarkerTransformationStereo(int markerUID, float matrixL[16], float matrixR[16]);

/**
 * Returns the number of pattern images associated with the specified marker. A single marker has one pattern
 * image. A multimarker has one or more pattern images.
 * Images of NFT markers are not currently supported, so at present this function will return 0 for NFT markers.
 * @param markerUID The unique identifier (UID) of the marker
 * @return          The number of pattern images
 */
EXPORT_API int arwGetTrackableAppearanceCount(int markerUID);

/**
 * Gets configuration of a pattern associated with a marker.
 * @param trackableUID The unique identifier (UID) of the trackable
 * @param patternID The id of the pattern within the marker, in range from 0 to arwGetTrackableAppearanceCount() - 1, inclusive. Ignored for single markers and NFT markers (i.e. 0 assumed).
 * @param matrix    The float array to populate with the 4x4 transformation matrix of the pattern (column-major order).
 * @param width     Float value to set to the width of the pattern
 * @param height    Float value to set to the height of the pattern.
 * @param imageSizeX Int value to set to the width of the pattern image (in pixels).
 * @param imageSizeY Int value to set to the height of the pattern image (in pixels).
 * @return          true if successful, false if an error occurred
 */
EXPORT_API bool arwGetTrackableAppearanceConfig(int trackableUID, int patternID, float matrix[16], float *width, float *height, int *imageSizeX, int *imageSizeY);

/**
 * Gets a pattern image associated with a marker. The provided color buffer is populated with the image of the 
 * pattern for the specified marker. If the marker is a multimarker, then the pattern image specified by patternID is 
 * used.
 * Images of NFT markers are not currently supported, so at present this function will return no image for NFT markers.
 * @param markerUID The unique identifier (UID) of the marker
 * @param patternID The id for the pattern within that marker. Ignored for single markers and NFT markers.
 * @param buffer    Pointer to a buffer of pixels (of type 'uint32_t') to be filled with pattern image.
 *      It is the caller's responsibility to ensure that the buffer is of sufficient size.
 *      Use arwGetTrackableAppearanceConfig to get the required size of this array (imageSizeX * imageSizeY elements).
 *      The pixels are RGBA in little-endian systems, or ABGR in big-endian systems.
 * @return          true if successful, false if an error occurred
 */
EXPORT_API bool arwGetTrackableAppearanceImage(int trackableUID, int patternID, uint32_t *buffer);

/**
 * Constants for use with marker option setters/getters.
 */
enum {
    ARW_TRACKABLE_OPTION_FILTERED = 1,                         ///< bool, true for filtering enabled.
    ARW_TRACKABLE_OPTION_FILTER_SAMPLE_RATE = 2,               ///< float, sample rate for filter calculations.
    ARW_TRACKABLE_OPTION_FILTER_CUTOFF_FREQ = 3,               ///< float, cutoff frequency of filter.
    ARW_TRACKABLE_OPTION_SQUARE_USE_CONT_POSE_ESTIMATION = 4,  ///< bool, true to use continuous pose estimate.
    ARW_TRACKABLE_OPTION_SQUARE_CONFIDENCE = 5,                ///< float, confidence value of most recent marker match
    ARW_TRACKABLE_OPTION_SQUARE_CONFIDENCE_CUTOFF = 6,         ///< float, minimum allowable confidence value used in marker matching.
    ARW_TRACKABLE_OPTION_IMAGE_HEIGHT = 7,                     ///< float, height of image.
    ARW_TRACKABLE_OPTION_MULTI_MIN_SUBMARKERS = 8,             ///< int, minimum number of submarkers for tracking to be valid.
    ARW_TRACKABLE_OPTION_MULTI_MIN_CONF_MATRIX = 9,            ///< float, minimum confidence value for submarker matrix tracking to be valid.
    ARW_TRACKABLE_OPTION_MULTI_MIN_CONF_PATTERN = 10,          ///< float, minimum confidence value for submarker pattern tracking to be valid.
};

/**
 * Set boolean options associated with a marker.
 * @param markerUID The unique identifier (UID) of the marker
 * @param option Symbolic constant identifying marker option to set.
 * @param value The value to set it to.
 */
EXPORT_API void arwSetTrackableOptionBool(int markerUID, int option, bool value);

/**
 * Set integer options associated with a marker.
 * @param markerUID The unique identifier (UID) of the marker
 * @param option Symbolic constant identifying marker option to set.
 * @param value The value to set it to.
 */
EXPORT_API void arwSetTrackableOptionInt(int markerUID, int option, int value);

/**
 * Set floating-point options associated with a marker.
 * @param markerUID The unique identifier (UID) of the marker
 * @param option Symbolic constant identifying marker option to set.
 * @param value The value to set it to.
 */
EXPORT_API void arwSetTrackableOptionFloat(int markerUID, int option, float value);

/**
 * Get boolean options associated with a marker.
 * @param markerUID The unique identifier (UID) of the marker
 * @param option Symbolic constant identifying marker option to get.
 * @return true if option is set, false if option is not set or an error occurred.
 */
EXPORT_API bool arwGetTrackableOptionBool(int markerUID, int option);

/**
 * Get integer options associated with a marker.
 * @param markerUID The unique identifier (UID) of the marker
 * @param option Symbolic constant identifying marker option to get.
 * @return integer value of option, or INT_MIN if an error occurred.
 */
EXPORT_API int arwGetTrackableOptionInt(int markerUID, int option);

/**
 * Get floating-point options associated with a marker.
 * @param markerUID The unique identifier (UID) of the marker
 * @param option Symbolic constant identifying marker option to get.
 * @return floating-point value of option, or NAN if an error occurred.
 */
EXPORT_API float arwGetTrackableOptionFloat(int markerUID, int option);

#ifdef __cplusplus
}
#endif
#endif // !__AR6_AR6_c_h__
