/*
 *  ARTrackable2D.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2011-2015 ARToolworks, Inc.
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

#ifndef __AR6_ARTrackable2D_h__
#define __AR6_ARTrackable2D_h__

#include <AR6/ARTrackable.h>

#include "Platform.h"

/**
 * ARTrackable2D marker type of ARTrackable.
 */
class ARTrackable2D : public ARTrackable {

private:
    bool m_loaded;
    float m_height;

protected:
    bool unload();
    std::shared_ptr<unsigned char*> m_refImage;
    int m_refImageX, m_refImageY;
    
public:
    int getRefImageWidth() { return m_refImageX; }
    int getRefImageHeight() { return m_refImageY; }
    std::shared_ptr<unsigned char*> getRefImage() { return m_refImage; }
    int pageNo;
    char *datasetPathname;
    ARTrackable2D();
    ~ARTrackable2D();

    bool load(const char* dataSetPathname_in, int trackableId);

    bool updateWith2DTrackingResults(int detectedPage, float P[3][4], const ARdouble transL2R[3][4]);

    void setHeight(const float height);
    float getHeight();
    
    friend class ARTracker2D;
};

#endif // !__AR6_ARTrackable2D_h__
