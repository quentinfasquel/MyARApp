/*
 *  ARTracker2D.h
 *  ARToolKit6
 *
 *  Wrapper for TrackingPipeline2D.
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


#ifndef __AR6_ARTracker2D_h__
#define __AR6_ARTracker2D_h__

#include <AR6/ARTracker.h>
#include <AR6/ARTrackable2D.h>
#include <map>

/**
 * Wraps TrackerPipeline2D for image tracker.
 *
 * In user facing messages about events related to this tracker, this tracker
 * should be referred to as the "2D image tracker".
 */

class TrackerPipeline;

class ARTracker2D : public ARTracker
{

private:
#pragma mark Private types and instance variables
    // ------------------------------------------------------------------------------
    // Private types and instance variables.
    // ------------------------------------------------------------------------------
    
    // 2D image tracking.
    bool m_running;
    bool m_2DTrackerDataLoaded;
    int m_2DTrackerMaxSimultaneousTrackedImages;
    int m_2DTrackerDetectedImageCount;
    TrackerPipeline *m_2DTrackingPipeline;
    bool m_isStereo;
    ARdouble m_transL2R[3][4];
#pragma mark Private methods.
    // ------------------------------------------------------------------------------
    // Private methods.
    // ------------------------------------------------------------------------------
    
    bool unload2DTrackerData(void);

    bool load2DTrackerData(std::vector<ARTrackable *>& trackables, size_t width, size_t height);

public:
#pragma mark Public API
    // ------------------------------------------------------------------------------
    // Public API
    // ------------------------------------------------------------------------------
    
    /**
     * Constructor.
     */
    ARTracker2D();
    
    /**
     * Destructor. Must be virtual.
     */
    virtual ~ARTracker2D();
    
    /**
     * Initialise so trackables can be added and removed.
     * After this call, trackables can be added and removed, any time up until final() is called.
     * @return       true if initialisation was OK, false if an error occured.
     */
    virtual bool init() override;
    
    virtual bool startWithCameraParameters(ARParamLT *paramLT, AR_PIXEL_FORMAT pixelFormat) override;
    
    virtual bool startWithStereoCameraParameters(ARParamLT *paramLT0, AR_PIXEL_FORMAT pixelFormat0, ARParamLT *paramLT1, AR_PIXEL_FORMAT pixelFormat1, const ARdouble transL2R[3][4]) override;
    
    virtual bool isRunning() override;
    
    virtual bool update(AR2VideoBufferT *buff0, AR2VideoBufferT *buff1, std::vector<ARTrackable *>& trackables) override;
    
    virtual bool stop() override;
    
    virtual bool final() override;
    
    virtual ARTrackable *newWithConfig(std::vector<std::string> config) override;

    void setMaxSimultaneousTrackedImages(int noOfMarkers);
    
    int getMaxSimultaneousTrackedImages() const;
    
    int getFeatureCount(int imageId);

    unsigned char* drawFeatures(ARTrackable* markerInfo, std::string fileName, std::string saveName);
    
    bool saveTrackerImageDatabase(std::string fileName);
    
    bool loadTrackerImageDatabase(std::string fileName, std::string targetImageDirectory, std::map<int, std::string> imageArchive);
};


#endif // !__AR6_ARTracker2D_h__
