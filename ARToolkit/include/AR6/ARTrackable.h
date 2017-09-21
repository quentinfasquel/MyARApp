/*
 *  ARTrackable.h
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

#ifndef __AR6_ARTrackable_h__
#define __AR6_ARTrackable_h__

#include <AR6/AR/ar.h>
#include <AR6/AR/arFilterTransMat.h>

#include <AR6/ARTrackableAppearance.h>

#include <vector>

class ARTracker2D;
class ARTrackerInstantOn;
class ARTrackerSquare;

/**
 * Base class for supported marker types.
 */
class ARTrackable {
    
private:
    ARFilterTransMatInfo *m_ftmi;
    ARdouble   m_filterCutoffFrequency;
    ARdouble   m_filterSampleRate;

protected:
    ARdouble trans[3][4];                   ///< Transformation from camera to this marker. If stereo, transform from left camera to this marker.
    /**
     * Allocates space for patterns within this marker.
     * @param count The number of patterns to allocate
     */
    void allocatePatterns(int count);

    /**
     * Frees allocated patterns and resets the pattern count to zero.
     */
    void freePatterns();

    ARdouble m_positionScaleFactor;

public:
    
    enum TrackableType {
        TwoD,                               ///< A rectangular textured marker backed by an 2D tracker data set.
        Square,                             ///< A standard single square marker
        MultiSquare,                        ///< A composite marker made up of multiple single markers
        InstantOn                           ///< A flat textured surface.
    };

    int UID;                                ///< Internal unique ID (note: not the same as ARToolKit pattern ID)
    TrackableType type;                        ///< Type of marker: single, multi, ...
    
    // Inputs from subclasses.
    bool visiblePrev;                       ///< Whether or not the marker was visible prior to last update.
    bool visible;                           ///< Whether or not the marker is visible at current time.
    
    // Output.
    ARdouble transformationMatrix[16];      ///< Transformation suitable for use in OpenGL
    ARdouble transformationMatrixR[16];     ///< Transformation suitable for use in OpenGL
    
    int patternCount;                       ///< Number of patterns in this marker (1 for single)
    ARTrackableAppearance** patterns;       ///< Array of pointers to patterns

    /**
     * Constructor takes the type of this marker.
     */
    ARTrackable(TrackableType type);

    virtual ~ARTrackable();
    
    void setPositionScalefactor(ARdouble scale);
    ARdouble positionScalefactor();
    
    /**
     * Completes an update begun in the parent class, performing filtering, generating
     * OpenGL view matrix and notifying listeners (just a log message at the moment).
     * Subclasses should first do their required updates, set visible, visiblePrev,
     * and trans[3][4] then call ARTrackable::update().
     * @return true if successful, false if an error occurred
     */
    virtual bool update(const ARdouble transL2R[3][4] = NULL);

    /**
     * Returns the specified pattern within this marker.
     * @param n     The pattern to retrieve
     */
    ARTrackableAppearance* getPattern(int n);
    
    // Filter control.
    void setFiltered(bool flag);
    bool isFiltered();
    ARdouble filterSampleRate();
    void setFilterSampleRate(ARdouble rate);
    ARdouble filterCutoffFrequency();
    void setFilterCutoffFrequency(ARdouble freq);

};


#endif // !__AR6_ARTrackable_h__
