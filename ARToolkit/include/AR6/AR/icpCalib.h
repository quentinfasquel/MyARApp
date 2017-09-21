/*
 *	icpCalib.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2004-2015 ARToolworks, Inc.
 *
 *  Author(s): Hirokazu Kato
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

#ifndef ICP_CALIB_H
#define ICP_CALIB_H

#include <AR6/AR/icpCore.h>

#ifdef __cplusplus
extern "C" {
#endif

#define      ICP_CALIB_STEREO_MAX_LOOP                        100
#define      ICP_CALIB_STEREO_BREAK_LOOP_ERROR_THRESH         0.001
#define      ICP_CALIB_STEREO_BREAK_LOOP_ERROR_RATIO_THRESH   0.99


typedef struct {
    ICP2DCoordT   *screenCoordL;
    ICP2DCoordT   *screenCoordR;
    ICP3DCoordT   *worldCoordL;
    ICP3DCoordT   *worldCoordR;
    int            numL;
    int            numR;
    ARdouble       initMatXw2Xcl[3][4];
} ICPCalibDataT;

int icpCalibStereo( ICPCalibDataT data[], int num,
                    ARdouble matXcl2Ul[3][4], ARdouble matXcr2Ur[3][4], ARdouble initTransL2R[3][4],
                    ARdouble matTransL2R[3][4],
                    ARdouble *err );

#ifdef __cplusplus
}
#endif
#endif
