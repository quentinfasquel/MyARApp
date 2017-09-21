/*
 *  image_indexer.h
 *  ARToolKit6
 *
 *  Implements a basic image indexing system.
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2007-2015 ARToolworks, Inc.
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

#ifndef image_indexer_h
#define image_indexer_h

#include <vector>
#include <string>
#include <sstream>
#include <map>

static const std::string imageIndexFileName = "imageIndex.dat";
static const std::string recognizerFileName = "recognizer.dat";
static const std::string unzipTargetDirectory = "/tmp/";
static const std::string processedTargetImageDirectory = "2DTrackerImages";

#include "file_utils.h"

class TrackableDatabaseInfo
{
public:
    TrackableDatabaseInfo() : index(-1), name(), fileSize(0.0f), height(0.0f), numberOfFeatures(0)
    {
    }
    int index;
    std::string name;
    std::string path;
    float fileSize;
    float height;
    int imageWidth;
    int imageHeight;
    int numberOfFeatures;
};

typedef std::map<int, TrackableDatabaseInfo>::iterator it_type;

void writeIndexToStream(std::string fileName, std::map<int, TrackableDatabaseInfo> indexMap);

void readIndexFromStream(std::string fileName, std::string imageDirectory, std::map<int, TrackableDatabaseInfo>& indexMap);

#endif /* image_indexer_h */
