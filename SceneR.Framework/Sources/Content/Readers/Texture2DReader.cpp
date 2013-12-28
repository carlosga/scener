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
#include <Content/ContentReader.hpp>
#include <Content/Readers/Texture2DReader.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/SurfaceFormat.hpp>
#include <Graphics/Texture2D.hpp>
#include <vector>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

Texture2DReader::Texture2DReader()
{
}

std::shared_ptr<void> Texture2DReader::Read(ContentReader& input)
{
    auto& gdService   = input.ContentManager().ServiceProvider().GetService<IGraphicsDeviceService>();
    auto  format      = input.ReadUInt32();
    auto  width       = input.ReadUInt32();
    auto  height      = input.ReadUInt32();
    auto  mipmapCount = input.ReadUInt32();
    auto  texture     = std::make_shared<Texture2D>(gdService.CurrentGraphicsDevice(),
                                                    width,
                                                    height,
                                                    (mipmapCount >= 1),
                                                    static_cast<SurfaceFormat>(this->DecodeFormat(format)));

    texture->DeclareStorage(mipmapCount);

    for (UInt32 i = 0; i < mipmapCount; i++)
    {
        auto data = input.ReadBytes(input.ReadUInt32());

        texture->SetData(i, data.size(), data.data());
    }

    return texture;
}

SurfaceFormat Texture2DReader::DecodeFormat(const System::UInt32& format) const
{
    switch (format)
    {
        case 0: // Color
            return SurfaceFormat::Color;

        case 1: // Bgr565
            return SurfaceFormat::Bgr565;

        case 2: // Bgra5551
            return SurfaceFormat::Bgra5551;

        case 3: // Bgra4444
            return SurfaceFormat::Bgra4444;

        case 4: // Dxt1
            return SurfaceFormat::Dxt1;

        case 5: // Dxt3
            return SurfaceFormat::Dxt3;

        case 6: // Dxt5
            return SurfaceFormat::Dxt5;

        case 7: // NormalizedByte2
            return SurfaceFormat::NormalizedByte2;

        case 8: // NormalizedByte4
            return SurfaceFormat::NormalizedByte4;

        case 9: // Rgba1010102
            return SurfaceFormat::Rgba1010102;

        case 10: // Rg32
            return SurfaceFormat::Rg32;

        case 11: // Rgba64
            return SurfaceFormat::Rgba64;

        case 12: // Alpha8
        case 13: // Single
        case 14: // Vector2
        case 15: // Vector4
        case 16: // HalfSingle
        case 17: // HalfVector2
        case 18: // HalfVector4
        case 19: // HdrBlendable
        default:
            throw std::runtime_error("Unsuported texture format");
    }
}
