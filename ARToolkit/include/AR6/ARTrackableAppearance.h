/*
 *  ARTrackableAppearance.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2010-2015 ARToolworks, Inc.
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

#ifndef __AR6_ARTrackableAppearance_h__
#define __AR6_ARTrackableAppearance_h__

#include <AR6/AR/ar.h>
#include <memory>

/**
 * Encapsulates information about a sub-component of a marker useful for
 * presentation to a user. For a single square marker, there will be one
 * pattern per marker. For a multimarker (multiple square markers), there
 * will be one or more patterns per marker.
 *
 * Currently, the encapsulated information is the pose relative to the marker
 * origin, and (for template markers only) the visual appearance of the pattern.
 */
class ARTrackableAppearance {

public:
    
    enum TRACKABLE_APPEARANCE_TYPE {
        TRACKABLE_APPEARANCE_TYPE_NONE = 0,
        TRACKABLE_APPEARANCE_TYPE_SQUARE_TEMPLATE,
        TRACKABLE_APPEARANCE_TYPE_SQUARE_MATRIX,
        TRACKABLE_APPEARANCE_TYPE_2D_TRACKER_IMAGE
    };

    ARTrackableAppearance();
    ~ARTrackableAppearance();

    bool loadTemplate(int patternID, const ARPattHandle *arPattHandle, float width);
    bool loadMatrix(int barcodeID, AR_MATRIX_CODE_TYPE type, float width);
    bool load2DTrackerImage(std::shared_ptr<unsigned char*> arImage, float imageX, float imageY, float width, float height);

    ARdouble m_matrix[16];  ///< Transform of the pattern from origin.
    float m_width;          ///< Width of the pattern in mm.
    float m_height;         ///< Height of the pattern in mm.
    int m_imageSizeX;
    int m_imageSizeY;
    uint32_t *m_image;      ///< RGBA32 image of the pattern.
    
private:

    TRACKABLE_APPEARANCE_TYPE m_pattType;

    bool loadImage(ARPattHandle *arPattHandle);
    void freeImage();
    
    // Template/matrix.
    int m_patternID;        ///< ID of the pattern (ARToolKit internal ID)

};

#endif // !__AR6_ARTrackableAppearance_h__
