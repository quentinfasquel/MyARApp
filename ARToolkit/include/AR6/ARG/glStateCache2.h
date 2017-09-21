/*
 *  glStateCache2.h
 *  ARToolKit6
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2009-2015 ARToolworks, Inc.
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

// glStateCache optimises OpenGL ES on implementations where
// changes in GL state are expensive, by eliminating redundant
// changes to state.

#ifndef __AR6_ARG_glStateCache2_h__
#define __AR6_ARG_glStateCache2_h__

#include <AR6/AR/config.h>

#if USE_GL_STATE_CACHE

#if defined ANDROID
#  include <GLES2/gl2.h>
#  include <GLES2/gl2ext.h>
#else
#  include <OpenGLES/ES2/gl.h>
#  include <OpenGLES/ES2/glext.h>
#endif

#endif

#ifdef __cplusplus
extern "C" {
#endif

//
// Use of the state cache:
//
// Prior to drawing, a given piece of code should set the state
// it prefers using the calls below. All code that uses the state
// cache should refrain from querying state, and refrain from saving
// and restoring state. The state cache maintains track of the current
// state and no GL calls to make state changes will be made if the
// requested state is already set.
//
// One additional note: If you have some code in your application
// which does NOT use the state cache routines, then the state cache's
// record of the state of the GL machine may be erroneous. In this
// case you will have to call glStateCacheFlush() at the beginning
// of the section of your code which DOES cache state.
//

// Tells the state cache that changes to state have been made
// elsewhere, and that the cache should be emptied.
#if !USE_GL_STATE_CACHE
#define glStateCacheFlush()
#else
void glStateCacheFlush();
#endif
#define glStateCacheBeginAgain glStateCacheFlush // Deprecated name.

#if !USE_GL_STATE_CACHE
#define glStateCacheEnableDepthTest() glEnable(GL_DEPTH_TEST)
#define glStateCacheDisableDepthTest() glDisable(GL_DEPTH_TEST)
#define glStateCacheEnableBlend() glEnable(GL_BLEND)
#define glStateCacheDisableBlend() glDisable(GL_BLEND)
#else
void glStateCacheEnableDepthTest();
void glStateCacheDisableDepthTest();
void glStateCacheEnableBlend();
void glStateCacheDisableBlend();
#endif

#if !USE_GL_STATE_CACHE
#define glStateCacheActiveTexture(texture) glActiveTexture(texture)
#else
#define GLSTATECACHE_MAX_COMBINED_TEXTURE_IMAGE_UNITS 8 // Minimum value for GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS is 8
void glStateCacheActiveTexture(GLuint texture);
#endif

#if !USE_GL_STATE_CACHE
#define glStateCacheBindTexture2D(name) glBindTexture(GL_TEXTURE_2D, name)
#else
void glStateCacheBindTexture2D(GLuint name);
#endif

#if !USE_GL_STATE_CACHE
#define glStateCacheBlendFunc(sfactor, dfactor) glBlendFunc(sfactor, dfactor)
#else
void glStateCacheBlendFunc(GLenum sfactor, GLenum dfactor);
#endif

#if !USE_GL_STATE_CACHE
#define glStateCacheColorMask(red, green, blue, alpha) glColorMask(red, green, blue, alpha)
#else
void glStateCacheColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
#endif
    
#if !USE_GL_STATE_CACHE
#define glStateCacheDepthMask(flag) glDepthMask(flag)
#else
void glStateCacheDepthMask(GLboolean flag);
#endif
    
#if !USE_GL_STATE_CACHE
#define glStateCachePixelStoreUnpackAlignment(param) glPixelStorei(GL_UNPACK_ALIGNMENT, param)
#else
void glStateCachePixelStoreUnpackAlignment(GLint param);
#endif

#ifdef __cplusplus
}
#endif
        
#endif // !__AR6_ARG_glStateCache2_h__
