/*
 *  ARTrackableMultiSquare.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2010-2015 ARToolworks, Inc.
 *
 *  Author(s): Philip Lamb.
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

#ifndef ARMARKERMULTI_H
#define ARMARKERMULTI_H

#include <AR6/ARTrackable.h>

#include <AR6/AR/arMulti.h>

/**
 * Multiple marker type of ARTrackable.
 */
class ARTrackableMultiSquare : public ARTrackable {

private:
    bool m_loaded;
    
protected:
    bool unload();

public:

	ARMultiMarkerInfoT *config;							///< Structure holding information about the multimarker patterns
	bool robustFlag;									///< Flag specifying which pose estimation approach to use
	
	ARTrackableMultiSquare();
	~ARTrackableMultiSquare();

	bool load(const char *multiConfig, ARPattHandle *arPattHandle);

	/**
	 * Updates the marker with new tracking info.
     * Then calls ARTrackable::update()
     * @param markerInfo		Array containing detected marker information
     * @param markerNum			Number of items in the array
     * @param ar3DHandle        AR3DHandle used to extract marker pose.
     */
	bool updateWithDetectedMarkers(ARMarkerInfo *markerInfo, int markerNum, AR3DHandle *ar3DHandle);

    bool updateWithDetectedMarkersStereo(ARMarkerInfo* markerInfoL, int markerNumL, ARMarkerInfo* markerInfoR, int markerNumR, AR3DStereoHandle *handle, ARdouble transL2R[3][4]);
};

#endif // !ARMARKERMULTI_H
