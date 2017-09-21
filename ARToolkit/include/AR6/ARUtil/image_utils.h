/*
 *  image_indexer.h
 *  ARToolKit6
 *
 *  Implements a basic image indexing system.
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2017 Daqri, LLC.
 *  Copyright 2007-2015 ARToolworks, Inc.
 *
 *  Author(s): Daniel Bell
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

#ifndef image_indexer_h
#define image_indexer_h
#include <stdio.h>
#include <string>
#include <memory>

std::string getFileExtension(const std::string& filename);

bool ReadImageFromFile(const char* fileName, std::shared_ptr<unsigned char*> &refImage, int *cols, int *rows, bool colourImage = false);

bool WriteImageTofile(unsigned char* data, int width, int height, int stride, std::string fileName, bool colourImage = false);

void ReleaseSTBImage(unsigned char* data);


#endif /* image_utils.h */
