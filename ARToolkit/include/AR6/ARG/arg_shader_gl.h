/*
 *  arg_shader_gl.h
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

#ifndef __AR6_ARG_arg_shader_gl_h__
#define __AR6_ARG_arg_shader_gl_h__

// ============================================================================
//  Public includes.
// ============================================================================

#include <AR6/AR/ar.h>      // ARUint8, AR_PIXEL_FORMAT, ARParam, arParamObserv2Ideal()

#if (HAVE_GLES2 || HAVE_GL3)

#if HAVE_GLES2
#  include <AR6/ARG/glStateCache2.h>
#elif HAVE_GL3
#  ifdef __APPLE__
#    include <OpenGL/gl3.h>
#  else
#    define GL_GLEXT_PROTOTYPES
#    include <GL/glcorearb.h>
#  endif
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
// ============================================================================
//  Public types and definitions.
// ============================================================================


// ============================================================================
//  Public functions.
// ============================================================================


/* Shader Utilities */
GLint arglGLCompileShaderFromFile(GLuint *shader, GLenum type, const char *pathname);
GLint arglGLCompileShaderFromString(GLuint *shader, GLenum type, const char *s);
GLint arglGLLinkProgram(GLuint prog);
GLint arglGLValidateProgram(GLuint prog);
void arglGLDestroyShaders(GLuint vertShader, GLuint fragShader, GLuint prog);

#ifdef __cplusplus
}
#endif

#endif // HAVE_GLES2 || HAVE_GL3

#endif // !__AR6_ARG_arg_shader_gl_h__
