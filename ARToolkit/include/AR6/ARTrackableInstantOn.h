/*
 *  ARTrackableInstantOn.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2013-2016 Daqri, LLC.
 *
 *  Author(s): Philip Lamb
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

#ifndef __AR6_ARTrackableInstantOn_h__
#define __AR6_ARTrackableInstantOn_h__

#include <AR6/AR/config.h>
#if USE_INSTANTON

#include <AR6/ARTrackable.h>

#include "Platform.h"

#include <artvision/cv/geometry/camera.h>

/**
 * ARTrackable2D marker type of ARTrackable.
 */
class ARTrackableInstantOn : public ARTrackable {

private:

protected:

public:
    ARTrackableInstantOn();
    ~ARTrackableInstantOn();

    bool updateWithInstantOnTrackingResults(const bool tracked, const artvision::ProjectionMatrix<float>& P, const ARdouble transL2R[3][4]);
};

#endif // USE_INSTANTON

#endif // !__AR6_ARTrackableInstantOn_h__
