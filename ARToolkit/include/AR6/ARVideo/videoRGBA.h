/*
 *  videoRGBA.h
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

#ifndef __ARvideo_videoRGBA_h__
#define __ARvideo_videoRGBA_h__

#include <AR6/AR/ar.h>

#ifdef  __cplusplus
extern "C" {
#endif

int videoRGBA(uint32_t *destRGBA, AR2VideoBufferT *source, int width, int height, AR_PIXEL_FORMAT pixelFormat);

#include <AR6/AR/ar.h>

#ifdef  __cplusplus
}
#endif
#endif // !__ARvideo_videoRGBA_h__

