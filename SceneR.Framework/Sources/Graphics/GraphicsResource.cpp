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

#include <Graphics/GraphicsResource.hpp>

using namespace System;
using namespace SceneR::Graphics;

GraphicsResource::GraphicsResource(GraphicsDevice& graphicsDevice)
    : graphicsDevice ( graphicsDevice )
    , name           { u""  }
    , tag            { u""  }
{
}

GraphicsDevice& GraphicsResource::CurrentGraphicsDevice()
{
    return this->graphicsDevice;
}

const String& GraphicsResource::Name() const
{
    return this->name;
}

void GraphicsResource::Name(const String& name)
{
    this->name = name;
}

const String& GraphicsResource::Tag() const
{
    return this->tag;
}

void GraphicsResource::Tag(const String& tag)
{
    this->tag = tag;
}
