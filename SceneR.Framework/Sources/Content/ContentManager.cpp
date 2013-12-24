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

#include <Content/ContentManager.hpp>
#include <System/IO/File.hpp>
#include <System/IO/FileStream.hpp>
#include <System/IO/Path.hpp>

using namespace System;
using namespace System::IO;
using namespace SceneR::Content;
using namespace SceneR::Framework;

ContentManager::ContentManager(RendererServiceContainer& serviceProvider,
                               const String&             rootDirectory)
    : serviceProvider(serviceProvider),
      rootDirectory(rootDirectory)
{
}

ContentManager::~ContentManager()
{
    this->Unload();
}

RendererServiceContainer& ContentManager::ServiceProvider()
{
    return this->serviceProvider;
}

const String ContentManager::RootDirectory()
{
    return this->rootDirectory;
}

void ContentManager::Unload()
{
}

std::shared_ptr<Stream> ContentManager::OpenStream(const String& assetName) throw(ContentLoadException)
{
    auto filename = Path::ChangeExtension(assetName, u"xnb");
    auto path     = Path::Combine(this->rootDirectory, filename);

    if (!File::Exists(path))
    {
        throw ContentLoadException("the asset file doesn't exists.");
    }

    return std::make_shared<FileStream>(path);
}
