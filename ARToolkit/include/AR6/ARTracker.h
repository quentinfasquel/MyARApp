/*
 *  ARTracker.h
 *  ARToolKit6
 *
 *  Base class for tracker implementations.
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


#ifndef __AR6_ARTracker_h__
#define __AR6_ARTracker_h__

#include <AR6/Platform.h>
#include <AR6/AR/ar.h>
#include <AR6/ARTrackable.h>

#include <vector>

/**
 * Abstract tracker functionality, providing methods for tracker initialisation, updates,
 * and cleanup.
 */
class ARTracker
{

public:
    
    /**
     * Initialise so trackables can be added and removed.
     * After this call, trackables can be added and removed, any time up until final() is called.
     * @return       true if initialisation was OK, false if an error occured.
     */
    virtual bool init() = 0;
    
    virtual bool startWithCameraParameters(ARParamLT *paramLT, AR_PIXEL_FORMAT pixelFormat) = 0;
    
    virtual bool startWithStereoCameraParameters(ARParamLT *paramLT0, AR_PIXEL_FORMAT pixelFormat0, ARParamLT *paramLT1, AR_PIXEL_FORMAT pixelFormat1, const ARdouble transL2R[3][4]) = 0;
    
    virtual bool isRunning() = 0;
    
    virtual bool update(AR2VideoBufferT *buff0, AR2VideoBufferT *buff1, std::vector<ARTrackable *>& trackables) = 0;
    
    virtual bool stop() = 0;
    
    virtual bool final() = 0;

    /**
     * ARTrackable factory method.
     */
    virtual ARTrackable *newWithConfig(std::vector<std::string> config) = 0;
};


#endif // !__AR6_ARTracker_h__
