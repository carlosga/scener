// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentManager.hpp>

#include <System/IO/FileStream.hpp>
#include <System/IO/File.hpp>
#include <System/IO/Path.hpp>
#include <Content/ContentReader.hpp>

using namespace System;
using namespace System::IO;
using namespace SceneR::Content;
using namespace SceneR::Framework;

ContentResourceManager ContentManager::ResourceManager;

ContentManager::ContentManager(RendererServiceContainer& serviceProvider
                             , const std::u16string&     rootDirectory)
    : serviceProvider ( serviceProvider )
    , rootDirectory   { rootDirectory }
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

const std::u16string& ContentManager::RootDirectory()
{
    return this->rootDirectory;
}

void ContentManager::Unload()
{
    this->ResourceManager.Clear();
}

std::shared_ptr<Stream> ContentManager::OpenStream(const std::u16string& assetName) noexcept(false)
{
    auto filename  = assetName + u".xnb";
    auto path      = Path::Combine(this->rootDirectory, filename);

    if (!File::Exists(path))
    {
        throw ContentLoadException("the asset file doesn't exists.");
    }

    return std::make_shared<FileStream>(path);
}
