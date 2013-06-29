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

#include "Graphics/GraphicsResource.hpp"
#include "Graphics/Texture2D.hpp"

using namespace SceneR::Graphics;

Texture2D::Texture2D(GraphicsDevice& graphicsDevice,
                     const Int32&    width,
                     const Int32&    height)
    : Texture2D(graphicsDevice,
                width,
                height,
                false,
                SurfaceFormat::Color)
{
}

Texture2D::Texture2D(GraphicsDevice&      graphicsDevice,
                     const Int32&         width,
                     const Int32&         height,
                     const Boolean&       mipMap,
                     const SurfaceFormat& format)
    : Texture(graphicsDevice),
      format(format),
      height(height),
      mipmaps(0),
      width(width)
{
}

const SurfaceFormat& Texture2D::Format() const
{
    return this->format;
}

const Int32& Texture2D::Height() const
{
    return this->height;
}

const Int32 Texture2D::LevelCount() const
{
    return this->mipmaps.size();
}

const Int32& Texture2D::Width() const
{
    return this->width;
}
