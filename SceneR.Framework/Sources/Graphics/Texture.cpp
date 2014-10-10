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

#include <Graphics/Texture.hpp>
#include <Graphics/GraphicsDevice.hpp>

using namespace SceneR::Graphics;

System::Boolean Texture::IsCompressedSurfaceFormat(const SurfaceFormat& format)
{
    return (format == SurfaceFormat::Dxt1
         || format == SurfaceFormat::Dxt3
         || format == SurfaceFormat::Dxt5);
}

Texture::Texture(GraphicsDevice& graphicsDevice)
    : GraphicsResource { graphicsDevice }
{
}
