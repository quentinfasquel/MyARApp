/*
 *  ARTrackableSquare.h
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

#ifndef ARMARKERSQUARE_H
#define ARMARKERSQUARE_H

#include <AR6/ARTrackable.h>

#define    AR_PATTERN_TYPE_TEMPLATE    0
#define    AR_PATTERN_TYPE_MATRIX      1

/**
 * Single marker type of ARTrackable.
 */
class ARTrackableSquare : public ARTrackable {

private:
    bool m_loaded;
    
protected:
    ARPattHandle *m_arPattHandle;
    ARdouble m_width;
    ARdouble m_cf;
    ARdouble m_cfMin;
    
    bool unload();
    
public:
	
	int patt_id;							///< Unique pattern ID provided by ARToolKit
    int patt_type;

	ARTrackableSquare();
	~ARTrackableSquare();
    
    bool useContPoseEstimation;
    ARdouble getConfidence();
    ARdouble getConfidenceCutoff();
    void setConfidenceCutoff(ARdouble value);
    
	bool initWithPatternFile(const char* path, ARdouble width, ARPattHandle *arPattHandle);
	bool initWithPatternFromBuffer(const char* buffer, ARdouble width, ARPattHandle *arPattHandle);
    bool initWithBarcode(int barcodeID, ARdouble width);

	/**
	 * Updates the marker with new tracking info.
     * Then calls ARTrackable::update()
     * @param markerInfo		Array containing detected marker information
     * @param markerNum			Number of items in the array
     * @param ar3DHandle        AR3DHandle used to extract marker pose.
     */
	bool updateWithDetectedMarkers(ARMarkerInfo* markerInfo, int markerNum, AR3DHandle *ar3DHandle);

    bool updateWithDetectedMarkersStereo(ARMarkerInfo* markerInfoL, int markerNumL, ARMarkerInfo* markerInfoR, int markerNumR, AR3DStereoHandle *handle, ARdouble transL2R[3][4]);
};


#endif // !ARMARKERSQUARE_H
