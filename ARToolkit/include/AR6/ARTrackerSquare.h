/*
 *  ARTrackerSquare.h
 *  ARToolKit6
 *
 *  Tracker implementation for ARToolKit's square marker tracker.
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


#ifndef __AR6_ARTrackerSquare_h__
#define __AR6_ARTrackerSquare_h__

#include <AR6/ARTracker.h>

#include <AR6/ARTrackable.h>
#include <AR6/ARTrackableSquare.h>
#include <AR6/ARTrackableMultiSquare.h>

#include <vector>

/**
 * Implements ARToolKit's square marker tracker.
 *
 * In user facing messages about events related to this tracker, this tracker
 * should be referred to as the "square marker tracker".
 */
class ARTrackerSquare : public ARTracker
{

private:
#pragma mark Private types and instance variables
    // ------------------------------------------------------------------------------
    // Private types and instance variables.
    // ------------------------------------------------------------------------------

    // Square tracking configuration. These allow for configuration prior to starting.
    int m_threshold;
    AR_LABELING_THRESH_MODE m_thresholdMode;
    int m_imageProcMode;
    int m_labelingMode;
    ARdouble m_pattRatio;
    int m_patternDetectionMode;
    AR_MATRIX_CODE_TYPE m_matrixCodeType;
    bool m_debugMode;

    // Square tracking data.
    ARHandle *m_arHandle0;                ///< Structure containing general ARToolKit tracking information.
    ARHandle *m_arHandle1;                ///< Structure containing general ARToolKit tracking information.
    ARPattHandle *m_arPattHandle;         ///< Structure containing information about trained patterns.
    AR3DHandle *m_ar3DHandle;             ///< Structure used to compute 3D poses from tracking data.
    ARdouble m_transL2R[3][4];
    AR3DStereoHandle *m_ar3DStereoHandle;

#pragma mark Private methods.
    // ------------------------------------------------------------------------------
    // Private methods.
    // ------------------------------------------------------------------------------


public:
#pragma mark Public API
    // ------------------------------------------------------------------------------
    // Public API
    // ------------------------------------------------------------------------------
    
    /**
     * Constructor.
     */
    ARTrackerSquare();
    
    /**
     * Destructor. Must be virtual.
     */
    virtual ~ARTrackerSquare();

    /**
     * Initialise so markers can be added and removed.
     * After this call, markers can be added and removed, any time up until final() is called.
     * @param patternSize For any square template (pattern) markers, the number of rows and columns in the template.
     * @param patternCountMax For any square template (pattern) markers, the maximum number of markers that may be loaded for a single matching pass. Must be > 0.
     * @return       true if initialisation was OK, false if an error occured.
     */
    virtual bool init(const int patternSize, const int patternCountMax);
    
    virtual bool init() override;
    
    virtual bool startWithCameraParameters(ARParamLT *paramLT, AR_PIXEL_FORMAT pixelFormat) override;
    
    virtual bool startWithStereoCameraParameters(ARParamLT *paramLT0, AR_PIXEL_FORMAT pixelFormat0, ARParamLT *param1, AR_PIXEL_FORMAT pixelFormat1, const ARdouble transL2R[3][4]) override;
    
    virtual bool isRunning() override;
    
    virtual bool update(AR2VideoBufferT *buff0, AR2VideoBufferT *buff1, std::vector<ARTrackable *>& trackables) override;
    
    virtual bool stop() override;
    
    virtual bool final() override;

    virtual ARTrackable *newWithConfig(std::vector<std::string> config) override;

    void setImageProcMode(int mode);
    
    int getImageProcMode() const;
    
    /**
     * Sets the threshold value used for image binarization.
     * @param    thresh    The new threshold value to use
     * @see                    getThreshold()
     */
    void setThreshold(int thresh);
    
    /**
     * Returns the current threshold value used for image binarization.
     * @return                The current threshold value
     * @see                    setThreshold()
     */
    int getThreshold() const;
    
    /**
     * Sets the thresholding mode to use.
     * @param mode            The new thresholding mode to use.
     * @see                    getThresholdMode()
     */
    void setThresholdMode(int mode);
    
    /**
     * Returns the current thresholding mode.
     * @return                The current thresholding mode.
     * @see                    setThresholdMode()
     */
    int getThresholdMode() const;
    
    /**
     * Sets the labeling mode to use.
     * @param mode            The new labeling mode to use.
     * @see                    getLabelingMode()
     */
    void setLabelingMode(int mode);
    
    /**
     * Returns the current labeling mode.
     * @return                The current labeling mode.
     * @see                    setLabelingMode()
     */
    int getLabelingMode() const;
    
    void setPatternDetectionMode(int mode);
    
    int getPatternDetectionMode() const;
    
    void setPattRatio(float ratio);
    
    float getPattRatio() const;
    
    void setMatrixCodeType(int type);
    
    int getMatrixCodeType() const;
    
    /**
     * Enables or disables debug mode in the tracker. When enabled, a black and white debug
     * image is generated during marker detection. The debug image is useful for visualising
     * the binarization process and choosing a threshold value.
     * @param    debug        true to enable debug mode, false to disable debug mode
     * @see                    getDebugMode()
     */
    void setDebugMode(bool debug);
    
    /**
     * Returns whether debug mode is currently enabled.
     * @return                true when debug mode is enabled, false when debug mode is disabled
     * @see                    setDebugMode()
     */
    bool getDebugMode() const;
    
    /**
     * Populates the provided buffer with the current contents of the debug image.
     * @param videoSourceIndex Index into an array of video sources, specifying which source should
     *      be queried.
     * @param buffer Pointer to a buffer of pixels (of type 'uint32_t') to be filled. It is the
     *      caller's responsibility to ensure that the buffer is of sufficient size. The pixels are
     *      RGBA in little-endian systems, or ABGR in big-endian systems.
     */
    bool getDebugTextureRGBA32(const int videoSourceIndex, uint32_t* buffer);

    /**
     * Populates the provided color buffer with the image for the specified pattern.
     * @param    patternID    The ARToolKit pattern ID to use
     * @param    buffer        The color buffer to populate
     * @return                true if successful, false if an error occurred
     */
    bool getPatternImage(int patternID, uint32_t* buffer);
};


#endif // !__AR6_ARTrackerSquare_h__
