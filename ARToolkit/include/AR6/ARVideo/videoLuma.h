/*
 *  videoLuma.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
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

#ifndef __ARvideo_videoLuma_h__
#define __ARvideo_videoLuma_h__

#include <AR6/AR/ar.h>

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct _ARVideoLumaInfo ARVideoLumaInfo;

ARVideoLumaInfo *arVideoLumaInit(int xsize, int ysize, AR_PIXEL_FORMAT pixFormat);

ARUint8 *__restrict arVideoLuma(ARVideoLumaInfo *vli, const ARUint8 *__restrict dataPtr);

int arVideoLumaFinal(ARVideoLumaInfo **vli_p);

#ifdef  __cplusplus
}
#endif
#endif // !__ARvideo_videoLuma_h__
