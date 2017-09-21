/*
 *  arMulti.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2002-2015 ARToolworks, Inc.
 *
 *  Author(s): Hirokazu Kato, Philip Lamb
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
/*******************************************************
 *
 * Author: Hirokazu Kato
 *
 *         kato@sys.im.hiroshima-cu.ac.jp
 *
 * Revision: 1.0
 * Date: 01/09/05
 *
 *******************************************************/

#ifndef AR_MULTI_H
#define AR_MULTI_H

#include <AR6/AR/ar.h>


#ifdef __cplusplus
extern "C" {
#endif

#define    AR_MULTI_PATTERN_TYPE_TEMPLATE    0
#define    AR_MULTI_PATTERN_TYPE_MATRIX      1

#define    AR_MULTI_PATTERN_DETECTION_MODE_TEMPLATE 0
#define    AR_MULTI_PATTERN_DETECTION_MODE_MATRIX 1
#define    AR_MULTI_PATTERN_DETECTION_MODE_TEMPLATE_AND_MATRIX 2

#define    AR_MULTI_CONFIDENCE_PATTERN_CUTOFF_DEFAULT   0.5
#define    AR_MULTI_CONFIDENCE_MATRIX_CUTOFF_DEFAULT    0.5
#define    AR_MULTI_POSE_ERROR_CUTOFF_EACH_DEFAULT      4.0 // Maximum allowable pose estimation error for each marker.
#define    AR_MULTI_POSE_ERROR_CUTOFF_COMBINED_DEFAULT 20.0 // Maximum allowable pose estimation error for combined marker set.


typedef struct {
    int     patt_id;
    int     patt_type; // Either AR_MULTI_PATTERN_TYPE_TEMPLATE or AR_MULTI_PATTERN_TYPE_MATRIX.
    ARdouble  width;
    ARdouble  trans[3][4];
    ARdouble  itrans[3][4];
    ARdouble  pos3d[4][3];
    int     visible;
    int     visibleR;
    uint64_t globalID;
} ARMultiEachMarkerInfoT;

typedef struct {
    ARMultiEachMarkerInfoT *marker;
    int                     marker_num;
    ARdouble                trans[3][4];
    int                     prevF;
    int                     patt_type;
    ARdouble                cfPattCutoff;
    ARdouble                cfMatrixCutoff;
    int                     min_submarker;
} ARMultiMarkerInfoT;

ARMultiMarkerInfoT *arMultiReadConfigFile( const char *filename, ARPattHandle *pattHandle );

int arMultiFreeConfig( ARMultiMarkerInfoT *config );

ARdouble  arGetTransMatMultiSquare(AR3DHandle *handle, ARMarkerInfo *marker_info, int marker_num,
                                 ARMultiMarkerInfoT *config);

ARdouble  arGetTransMatMultiSquareRobust(AR3DHandle *handle, ARMarkerInfo *marker_info, int marker_num,
                                       ARMultiMarkerInfoT *config);

ARdouble  arGetTransMatMultiSquareStereo(AR3DStereoHandle *handle,
                                       ARMarkerInfo *marker_infoL, int marker_numL,
                                       ARMarkerInfo *marker_infoR, int marker_numR,
                                       ARMultiMarkerInfoT *config);

ARdouble  arGetTransMatMultiSquareStereoRobust(AR3DStereoHandle *handle,
                                             ARMarkerInfo *marker_infoL, int marker_numL,
                                             ARMarkerInfo *marker_infoR, int marker_numR,
                                             ARMultiMarkerInfoT *config);


#ifdef __cplusplus
}
#endif
#endif
