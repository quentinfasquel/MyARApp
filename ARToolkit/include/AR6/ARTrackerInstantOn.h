/*
 *  ARTrackerInstantOn.h
 *  ARToolKit6
 *
 *  Tracker implementations for InstantOn tracker.
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2013-2016 Daqri, LLC.
 *
 *  Author(s): Philip Lamb, Dan Bell, Nalin Senthamil.
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


#ifndef __AR6_ARTrackerInstantOn_h__
#define __AR6_ARTrackerInstantOn_h__

#include <AR6/AR/config.h>
#if USE_INSTANTON

#include <AR6/ARTracker.h>
#include <AR6/InstantOn/extensions/Vision4d-InstantOn.h>
#include <artvision/cv/geometry/radial_lens_model.h>

/**
 * Implements InstantOn tracker.
 *
 * In user facing messages about events related to this tracker, this tracker
 * should be referred to as the "InstantOn tracker".
 */
class ARTrackerInstantOn : public ARTracker
{

private:
#pragma mark Private types and instance variables
    // ------------------------------------------------------------------------------
    // Private types and instance variables.
    // ------------------------------------------------------------------------------
    
    // InstantOn tracking.
    std::shared_ptr<artvision_instanton::facade::InstantOnTracker> m_Tracker;
    std::shared_ptr<artvision::RadialLensModel<float> > m_2DTrackerLensModel;
    bool m_running;
    bool m_isStereo;
    ARdouble m_transL2R[3][4];

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
    ARTrackerInstantOn();
    
    /**
     * Destructor. Must be virtual.
     */
    virtual ~ARTrackerInstantOn();
    
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

};

#endif // USE_INSTANTON

#endif // !__AR6_ARTrackerInstantOn_h__
