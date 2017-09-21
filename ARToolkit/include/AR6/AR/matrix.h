/*
 *	matrix.h
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

#ifndef AR_MATRIX_H
#define AR_MATRIX_H

#include <math.h>


#ifdef __cplusplus
extern "C" {
#endif


/* === matrix definition ===

  <---- clm --->
  [ 10  20  30 ] ^
  [ 20  10  15 ] |
  [ 12  23  13 ] row
  [ 20  10  15 ] |
  [ 13  14  15 ] v

=========================== */

typedef struct {
	ARdouble *m;
	int      row;
	int      clm;
} ARMat;

#ifdef ARDOUBLE_IS_FLOAT
#  define ARMatf ARMat
#else
typedef struct {
	float   *m;
	int      row;
	int      clm;
} ARMatf;
#endif
    
typedef struct {
    ARdouble *v;
    int      clm;
} ARVec;


/* 0 origin */
#define ARELEM0(mat,r,c) ((mat)->m[(r)*((mat)->clm)+(c)])
/* 1 origin */
#define ARELEM1(mat,row,clm) ARELEM0(mat,row-1,clm-1)



ARMat  *arMatrixAlloc(int row, int clm);
int    arMatrixFree(ARMat *m);
#ifdef ARDOUBLE_IS_FLOAT
#  define arMatrixAllocf arMatrixAlloc
#  define arMatrixFreef arMatrixFree
#else
ARMatf *arMatrixAllocf(int row, int clm);
int    arMatrixFreef(ARMatf *m);
#endif

int    arMatrixDup(ARMat *dest, ARMat *source);
ARMat  *arMatrixAllocDup(ARMat *source);

int    arMatrixUnit(ARMat *unit);
ARMat  *arMatrixAllocUnit(int dim);

int    arMatrixMul(ARMat *dest, ARMat *a, ARMat *b);
ARMat  *arMatrixAllocMul(ARMat *a, ARMat *b);

#ifdef ARDOUBLE_IS_FLOAT
#  define arMatrixMulf arMatrixMul
#  define arMatrixAllocMulf arMatrixAllocMul
#else
int    arMatrixMulf(ARMatf *dest, ARMatf *a, ARMatf *b);
ARMatf *arMatrixAllocMulf(ARMatf *a, ARMatf *b);
#endif

int    arMatrixTrans(ARMat *dest, ARMat *source); // Transpose source, place result in dest.
ARMat  *arMatrixAllocTrans(ARMat *source);        // Transpose source, place result in newly allocated matrix.

#ifdef ARDOUBLE_IS_FLOAT
#  define arMatrixTransf arMatrixTrans
#  define arMatrixAllocTransf arMatrixAllocTrans
#else
int    arMatrixTransf(ARMatf *dest, ARMatf *source);
ARMatf *arMatrixAllocTransf(ARMatf *source);
#endif

int    arMatrixInv(ARMat *dest, ARMat *source);
int    arMatrixSelfInv(ARMat *m);
ARMat  *arMatrixAllocInv(ARMat *source);

#ifdef ARDOUBLE_IS_FLOAT
#  define arMatrixSelfInvf arMatrixSelfInv
#else
int    arMatrixSelfInvf(ARMatf *m);
#endif

ARdouble arMatrixDet(ARMat *m);

int    arMatrixPCA( ARMat *input, ARMat *evec, ARVec *ev, ARVec *mean );
int    arMatrixPCA2( ARMat *input, ARMat *evec, ARVec *ev );

int    arMatrixDisp(ARMat *m);


ARVec  *arVecAlloc( int clm );
int    arVecFree( ARVec *v );
int    arVecDisp( ARVec *v );
ARdouble arVecHousehold( ARVec *x );
ARdouble arVecInnerproduct( ARVec *x, ARVec *y );
int    arVecTridiagonalize( ARMat *a, ARVec *d, ARVec *e );


#ifdef __cplusplus
}
#endif
#endif
