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

#include <Content/ContentReader.hpp>
#include <Content/Readers/Texture2DReader.hpp>
#include <Framework/Core.hpp>
#include <Graphics/SurfaceFormat.hpp>
#include <Graphics/Texture2D.hpp>
#include <Graphics/TextureMipMap.hpp>
#include <vector>

using namespace SceneR::Content;
using namespace SceneR::Graphics;

Texture2DReader::Texture2DReader()
{
}

const ContentType Texture2DReader::GetContentType() const
{
    return ContentType::Texture2D;
}

std::shared_ptr<void> Texture2DReader::Read(ContentReader* input)
{
    std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(input->GetGraphicsDevice(), 0, 0);

    texture->format = static_cast<SurfaceFormat>(input->ReadUInt32());
    texture->width  = input->ReadUInt32();
    texture->height = input->ReadUInt32();

    UInt32 mipmapCount = input->ReadUInt32();

    for (UInt32 i = 0; i < mipmapCount; i++)
    {
        TextureMipMap mipmap;

        mipmap.data = input->ReadBytes(input->ReadUInt32());

        texture->mipmaps.push_back(mipmap);
    }

    return texture;
}
