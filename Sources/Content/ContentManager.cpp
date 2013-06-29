//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#include "Content/ContentManager.hpp"

using namespace SceneR::Content;
using namespace SceneR::Graphics;

ContentManager::ContentManager(GraphicsDevice& graphicsDevice,
                               const std::string& rootDirectory)
    : graphicsDevice(graphicsDevice),
      rootDirectory(rootDirectory),
      typeReaderManager()
{
}

ContentManager::~ContentManager()
{
    this->Unload();
}

GraphicsDevice& ContentManager::GetGraphicsDevice()
{
    return this->graphicsDevice;
}

/**
 * Disposes all data that was loaded by this ContentManager.
 */
void ContentManager::Unload()
{
}
