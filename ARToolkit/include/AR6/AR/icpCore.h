/*
 *	icpCore.h
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

#ifndef ICP_CORE_H
#define ICP_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef  M_PI
#define  M_PI    3.14159265358979323846F
#endif

#define      ICP_DEBUG                           0
#define      ICP_MAX_LOOP                        10
#define      ICP_BREAK_LOOP_ERROR_THRESH         0.1F
#define      ICP_BREAK_LOOP_ERROR_RATIO_THRESH   0.99F
#define      ICP_BREAK_LOOP_ERROR_THRESH2        4.0F
#define      ICP_INLIER_PROBABILITY              0.50F

typedef struct {
    ARdouble    x;
    ARdouble    y;
} ICP2DCoordT;

typedef struct {
    ARdouble    x;
    ARdouble    y;
    ARdouble    z;
} ICP3DCoordT;

typedef struct {
    ARdouble    a;
    ARdouble    b;
    ARdouble    c;
} ICP2DLineT;

typedef struct {
    ICP2DCoordT  p1;
    ICP2DCoordT  p2;
} ICP2DLineSegT;

typedef struct {
    ICP3DCoordT  p1;
    ICP3DCoordT  p2;
} ICP3DLineSegT;


int        icpGetXc_from_Xw_by_MatXw2Xc( ICP3DCoordT *Xc, ARdouble matXw2Xc[3][4], ICP3DCoordT *Xw );
int        icpGetU_from_X_by_MatX2U( ICP2DCoordT *u, ARdouble matX2U[3][4], ICP3DCoordT *coord3d );
int        icpGetJ_U_S( ARdouble J_U_S[2][6], ARdouble matXc2U[3][4], ARdouble matXw2Xc[3][4], ICP3DCoordT *worldCoord );
int        icpGetDeltaS( ARdouble S[6], ARdouble dU[], ARdouble J_U_S[][6], int n );
int        icpUpdateMat( ARdouble matXw2Xc[3][4], ARdouble dS[6] );

void       icpDispMat( char *title, ARdouble *mat, int row, int clm );

#ifdef __cplusplus
}
#endif
#endif
