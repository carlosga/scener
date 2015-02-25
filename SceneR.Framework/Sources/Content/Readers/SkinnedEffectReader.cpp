// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/SkinnedEffectReader.hpp>

#include <Graphics/IGraphicsDeviceService.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/SkinnedEffect.hpp>
#include <System/IO/Path.hpp>
#include <Content/ContentManager.hpp>

using namespace System;
using namespace System::IO;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

SkinnedEffectReader::SkinnedEffectReader()
{
}

SkinnedEffectReader::~SkinnedEffectReader()
{
}

std::shared_ptr<void> SkinnedEffectReader::Read(ContentReader& input)
{
    auto& gdService = input.ContentManager().ServiceProvider().GetService<IGraphicsDeviceService>();
    auto  effect    = std::make_shared<SkinnedEffect>(gdService.CurrentGraphicsDevice());

    effect->EnableDefaultLighting();

    // Pointer to a separate .xnb file which contains an object of type Texture2D
    auto assetName = input.ReadString();

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
