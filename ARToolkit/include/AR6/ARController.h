/*
 *  ARController.h
 *  ARToolKit6
 *
 *  A C++ class encapsulating core controller functionality of ARToolKit.
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

#ifndef __AR6_ARController_h__
#define __AR6_ARController_h__

#include <AR6/Platform.h>

#include <AR6/ARVideoSource.h>
#include <AR6/ARTracker2D.h>
#include <AR6/ARTrackable.h>
#include <AR6/ARTrackable2D.h>
#include <AR6/ARTrackerSquare.h>
#include <AR6/ARTrackableSquare.h>
#include <AR6/ARTrackableMultiSquare.h>
#if USE_INSTANTON
#  include <AR6/ARTrackerInstantOn.h>
#  include <AR6/ARTrackableInstantOn.h>
#endif
#include <AR6/ARView.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#if !defined(_WINRT)
#  include <pthread.h>
#else
#  define pthread_mutex_t               CRITICAL_SECTION
#  define pthread_mutex_init(pm, a)     InitializeCriticalSectionEx(pm, 4000, CRITICAL_SECTION_NO_DEBUG_INFO)
#  define pthread_mutex_lock(pm)        EnterCriticalSection(pm)
#  define pthread_mutex_unlock(pm)      LeaveCriticalSection(pm)
#  define pthread_mutex_destroy(pm)     DeleteCriticalSection(pm)
#endif
#include <vector>
#include <string>

/**
 * Wrapper for ARToolKit functionality. This class handles ARToolKit initialisation, updates,
 * and cleanup. It maintains a collection of markers, providing methods to add and remove them.
 */
class ARController
{

private:
#pragma mark Private types and instance variables
    // ------------------------------------------------------------------------------
    // Private types and instance variables.
    // ------------------------------------------------------------------------------

    enum class State {
        NOTHING_INITIALISED,             ///< No initialisation yet and no resources allocated.
        BASE_INITIALISED,                ///< Marker management initialised, markers can be added.
        WAITING_FOR_VIDEO,               ///< Waiting for video source to become ready.
        DETECTION_RUNNING                ///< Video running, additional initialisation occurred, marker detection running.
    };

    State state;                ///< Current state of operation, progress through initialisation
    bool stateWaitingMessageLogged;

    char* versionString;                 ///< Pointer to ARToolKit version string.

    ARVideoSource *m_videoSources[2];    ///< ARVideoSource(s) providing video frames for tracking
    int m_videoSourceCount;
    //bool m_videoSourceIsStereo;
    ARdouble m_transL2R[3][4];
    
    // Virtual environment parameters.
    ARdouble m_projectionNearPlane;      ///< Near plane distance for projection matrix calculation.
    ARdouble m_projectionFarPlane;       ///< Far plane distance for projection matrix calculation.
    ARdouble m_projectionMatrix0[16];    ///< OpenGL style projection matrix computed from camera parameters.
    ARdouble m_projectionMatrix1[16];    ///< OpenGL style projection matrix computed from camera parameters.
    bool m_projectionMatrixSet;          ///< True once the projection matrix has been computed, which requires an open video source.

    std::vector<ARTrackable *> m_trackables;  ///< List of trackables.
    AR2VideoTimestampT m_updateFrameStamps[2];
    AR2VideoTimestampT m_getFrameTextureFrameStamps[2];

    // 2D tracking.
    bool m_do2DTracking;
    std::unique_ptr<ARTracker2D> m_2DTracker;
    
    // Square tracking.
    bool m_doSquareTracking;
    std::unique_ptr<ARTrackerSquare> m_squareTracker;
    
#if USE_INSTANTON
    // InstantOn tracking.
    bool m_doInstantOnTracking;
    std::unique_ptr<ARTrackerInstantOn> m_instantOnTracker;
#endif

    int m_error;

    // Display frame.
    ARView *m_arViews[2];

#pragma mark Private methods.
    // ------------------------------------------------------------------------------
    // Private methods.
    // ------------------------------------------------------------------------------

    //
    // Internal marker management.
    //

    /**
     * Adds a trackable to the collection.
     * @param trackable    The trackable to add, typically created by ARTrackable::newWithConfig().
     * @return             true if the trackable was added successfully, otherwise false.
     */
    bool addTrackable(ARTrackable* trackable);

    /**
     * Removes the specified trackable.
     * @param trackable    The trackable to remove
     * @return             true if the trackable was removed, false if an error occurred.
     */
    bool removeTrackable(ARTrackable* trackable);

public:
#pragma mark Public API
    // ------------------------------------------------------------------------------
    // Public API
    // ------------------------------------------------------------------------------

    /**
     * Constructor.
     */
    ARController();

    /**
     * Destructor.
     */
    ~ARController();

public:

    /**
     * Returns a pointer to a C string containing the ARToolKit version, such as "4.5.1".
     * The string persists as long as the ARController instance. The caller is not responsible for disposing of the returned pointer.
     * @return        The ARToolKit version
     */
    const char* getARToolKitVersion();

    void setError(int error);

    int getError();

    /** 
     * Start trackable management so trackables can be added and removed.
     * After this call, trackables can be added and removed, any time up until shutdown() is called.
     * @param patternSize For any square template (pattern) markers, the number of rows and columns in the template.
     * @param patternCountMax For any square template (pattern) markers, the maximum number of markers that may be loaded for a single matching pass. Must be > 0.
     * @return       true if initialisation was OK, false if an error occured.
     */
    bool initialiseBase(const int patternSize = AR_PATT_SIZE1, const int patternCountMax = AR_PATT_NUM_MAX);

    ARTracker2D& get2DTracker();
    ARTrackerSquare& getSquareTracker();
#if USE_INSTANTON
    ARTrackerInstantOn& getInstantOnTracker();
#endif

    void setProjectionNearPlane(const ARdouble projectionNearPlane);
    void setProjectionFarPlane(const ARdouble projectionFarPlane);
    ARdouble projectionNearPlane(void);
    ARdouble projectionFarPlane(void);

    /**
     * Start video capture and marker detection. (AR/NFT initialisation will begin on a subsequent call to update().)
     * @param vconf            Video configuration string.
     * @param cparaName        Camera parameters filename, or NULL if camera parameters file not being used.
     * @param cparaBuff        A byte-buffer containing contents of a camera parameters file, or NULL if a camera parameters file is being used.
     * @param cparaBuffLen    Length (in bytes) of cparaBuffLen, or 0 if a camera parameters file is being used.
     * @return                true if video capture and marker detection was started, otherwise false.
     */
    bool startRunning(const char* vconf, const char* cparaName, const char* cparaBuff, const long cparaBuffLen);

    /**
     * Start stereo video capture and marker detection. (AR/NFT initialisation will begin on a subsequent call to update().)
     * @param vconfL        Video configuration string for the "left" video source.
     * @param cparaNameL    Camera parameters filename for the "left" video source, or NULL if camera parameters file not being used.
     * @param cparaBuffL    A byte-buffer containing contents of a camera parameters file for the "left" video source, or NULL if a camera parameters file is being used.
     * @param cparaBuffLenL    Length (in bytes) of cparaBuffLenL, or 0 if a camera parameters file is being used.
     * @param vconfR        Video configuration string for the "right" video source.
     * @param cparaNameR    Camera parameters filename for the "right" video source, or NULL if camera parameters file not being used.
     * @param cparaBuffR    A byte-buffer containing contents of a camera parameters file for the "right" video source, or NULL if a camera parameters file is being used.
     * @param cparaBuffLenR    Length (in bytes) of cparaBuffLenR, or 0 if a camera parameters file is being used.
     * @param transL2RName    Stereo calibration filename, or NULL if stereo calibration file not being used.
     * @param transL2RBuff    A byte-buffer containing contents of a stereo calibration file, or NULL if a stereo calibration file is being used.
     * @param transL2RBuffLen Length (in bytes) of transL2RBuff, or 0 if a stereo calibration file is being used.
     * @return                true if video capture and marker detection was started, otherwise false.
     */
    bool startRunningStereo(const char* vconfL, const char* cparaNameL, const char* cparaBuffL, const long cparaBuffLenL,
                            const char* vconfR, const char* cparaNameR, const char* cparaBuffR, const long cparaBuffLenR,
                            const char* transL2RName, const char* transL2RBuff, const long transL2RBuffLen);

#if TARGET_PLATFORM_ANDROID
    jint androidVideoPushInit(JNIEnv *env, jobject obj, jint videoSourceIndex, jint width, jint height, const char *pixelFormat, jint camera_index, jint camera_face);
    jint androidVideoPush1(JNIEnv *env, jobject obj, jint videoSourceIndex, jbyteArray buf, jint bufSize);
    jint androidVideoPush2(JNIEnv *env, jobject obj, jint videoSourceIndex,
                           jobject buf0, jint buf0PixelStride, jint buf0RowStride,
                           jobject buf1, jint buf1PixelStride, jint buf1RowStride,
                           jobject buf2, jint buf2PixelStride, jint buf2RowStride,
                           jobject buf3, jint buf3PixelStride, jint buf3RowStride);
    jint androidVideoPushFinal(JNIEnv *env, jobject obj, jint videoSourceIndex);
#endif

    /**
     * Reports width, height and pixel format of a video source.
     * To retrieve the size (in bytes) of each pixel, use arUtilGetPixelSize(*pixelFormat);
     * To get a C-string with the name of the pixel format, use arUtilGetPixelFormatName(*pixelFormat);
     * @param videoSourceIndex Index into an array of video sources, specifying which source should be queried.
     * @param width Pointer to an int which will be filled with the width (in pixels) of the video frame, or NULL if this information is not required.
     * @param height Pointer to an int which will be filled with the height (in pixels) of the video frame, or NULL if this information is not required.
     * @param pixelFormat Pointer to an AR_PIXEL_FORMAT which will be filled with the pixel format of the video frame, or NULL if this information is not required.
     * @return        true if the video source(s) is/are open and returning frames, otherwise false.
     */
    bool videoParameters(const int videoSourceIndex, int *width, int *height, AR_PIXEL_FORMAT *pixelFormat);

    /**
     * Returns true if video capture and marker detection is running.
     * @return        true if the video source(s) is/are open and returning frames, otherwise false.
     */
    bool isRunning();

    /**
     * Video capture and marker detection stops, but markers are still valid and can be configured.
     * @return                true if video capture and marker detection was stopped, otherwise false.
     */
    bool stopRunning();

    /**
     * Stop, if running. Remove all markers, clean up all memory.
     * Starting again from this state requires initialiseBase() to be called again.
     * @return                true if shutdown was successful, otherwise false
     */
    bool shutdown();

    /**
     * Populates the provided array with the ARToolKit projection matrix. The projection matrix is computed
     * once the video source has been opened, and camera parameters become available. If this method is called
     * before this happens, then the passed array is untouched and the method will return false.
     * @param videoSourceIndex Index into an array of video sources, specifying which source should be queried.
     * @param proj        Array to populate with OpenGL compatible projection matrix
     * @return            true if the projection matrix has been computed, otherwise false
     */
    bool getProjectionMatrix(const int videoSourceIndex, ARdouble proj[16]);

    /**
     * Adds a trackable as specified in the given configuration string. The format of the string can be
     * one of:
     * - 2D image target: "2d;target_image_pathname;image_height", e.g. "2d;gibraltar.jpg;160.9"
     * - Square marker from pattern file: "square;pattern_file;pattern_width", e.g. "single;data/hiro.patt;80"
     * - Square marker from pattern passed in config: "square;pattern_width;buffer=[]", e.g. "square_buffer;80;buffer=234 221 237..."
     * - Square barcode marker: "square_barcode;barcode_id;pattern_width", e.g. "square_barcode;0;80"
     * - Multi-square marker: "multi;config_file", e.g. "multi;data/multi/marker.dat"
     * @param cfg        The configuration string
     * @return            The UID of the marker instantiated based on the configuration string, or -1 if an error occurred.
     */
    int addTrackable(const char* cfg);

    /**
     * Removes the marker with the given ID.
     * @param UID            The UID of the marker to remove
     * @return                true if the marker was removed, false if an error occurred.
     */
    bool removeTrackable(int UID);

    /**
     * Clears the collection of markers.
     * @return                The number of markers removed
     */
    int removeAllTrackables();

    /**
     * Returns the number of currently loaded trackables.
     * @return                The number of currently loaded markers.
     */
    unsigned int countTrackables() const;
    
    /**
     * Returns the number of currently loaded trackables of the specified type.
     * @return                The number of currently loaded markers.
     */
    unsigned int countTrackables(ARTrackable::TrackableType type) const;

    /**
     * Searches the collection of markers for the given ID.
     * @param UID            The UID of the marker to find
     * @return                The found marker, or NULL if no matching ID was found.
     */
    ARTrackable* findTrackable(int UID);

    /**
     * Requests the capture of a new frame from the video source(s).
     * In the case of stereo video sources, capture from both sources will be attempted.
     * @return                The capture succeeded, or false if no frame was captured.
     */
    bool capture();

    bool displayFrameInit(const int videoSourceIndex);

    bool displayFrameSettings(const int videoSourceIndex, const int width, const int height, const bool rotate90, const bool flipH, const bool flipV, const ARView::HorizontalAlignment hAlign, const ARView::VerticalAlignment vAlign, const ARView::ScalingMode scalingMode, int32_t viewport[4]);

    bool displayFrame(const int videoSourceIndex);

    bool displayFrameFinal(const int videoSourceIndex);

    /**
     * Asks the video source to push the most recent frame into the passed-in buffer.
     * @param videoSourceIndex Index into an array of video sources, specifying which source should
     *      be queried.
     * @param buffer Pointer to a buffer of pixels (of type 'uint32_t') to be filled. It is the
     *      caller's responsibility to ensure that the buffer is of sufficient size. The pixels are
     *      RGBA in little-endian systems, or ABGR in big-endian systems.
     */
    bool getFrameTextureRGBA32(const int videoSourceIndex, uint32_t *buffer);

    /**
     * Performs marker detection and updates all markers. The latest frame from the current 
     * video source is retrieved and analysed. Each marker in the collection is updated with
     * new tracking information. The marker info array is 
     * iterated over, and detected markers are matched up with those in the marker collection. Each matched 
     * marker is updated with visibility and transformation information. Any markers not detected are considered 
     * not currently visible.
     *
     * @return                true if update completed successfully, false if an error occurred
     */
    bool update();

    /**
     * Populates the provided color buffer with the image for the specified pattern.
     * @param    patternID    The ARToolKit pattern ID to use
     * @param    buffer        The color buffer to populate
     * @return                true if successful, false if an error occurred
     */
    bool getPatternImage(int patternID, uint32_t* buffer);
    bool getFeatureImage(int patternID, unsigned char* &buffer, std::string fileName, std::string saveName="");
    
    bool isInited();
    
    bool load2DTrackerImageDatabase(const char* databaseFileName, int* &targetIds, int *targetSize, const char* destPath = nullptr);
    bool save2DTrackerImageDatabase(std::string fileName);
    
};

#endif // !__AR6_ARController_h__
