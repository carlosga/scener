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
#include <Content/Readers/SkinnedEffectReader.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/SkinnedEffect.hpp>
#include <Graphics/Texture2D.hpp>
#include <System/Core.hpp>
#include <System/IO/Path.hpp>
#include <memory>

using namespace System;
using namespace System::IO;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

SkinnedEffectReader::SkinnedEffectReader()
{
}

std::shared_ptr<void> SkinnedEffectReader::Read(ContentReader& input)
{
    auto& gdService = input.ContentManager().ServiceProvider().GetService<IGraphicsDeviceService>();
    auto  effect    = std::make_shared<SkinnedEffect>(gdService.CurrentGraphicsDevice());

    effect->EnableDefaultLighting();

    // Pointer to a separate .xnb file which contains an object of type Texture2D
    String assetName = input.ReadString();

    if (assetName.size() > 0)
    {
        assetName = Path::GetDirectoryName(input.AssetName()) + Path::DirectorySeparator() + assetName;

        effect->Texture(input.ContentManager().Load<Texture2D>(assetName));
        effect->TextureEnabled(true);
    }

    // Weights per vertex (1, 2, or 4)
    effect->WeightsPerVertex(input.ReadUInt32());

    // Diffuse color
    effect->DiffuseColor(input.ReadVector3());

    // Emissive color
    effect->EmissiveColor(input.ReadVector3());

    // Specular color
    effect->SpecularColor(input.ReadVector3());

    // Specular power
    effect->SpecularPower(input.ReadSingle());

    // Alpha
    effect->Alpha(input.ReadSingle());

    return effect;
}
