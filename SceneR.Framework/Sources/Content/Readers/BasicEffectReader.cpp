// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BasicEffectReader.hpp>

#include <System/Core.hpp>
#include <System/IO/Path.hpp>
#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/BasicEffect.hpp>

using namespace System;
using namespace System::IO;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

BasicEffectReader::BasicEffectReader()
{
}

BasicEffectReader::~BasicEffectReader()
{
}

std::shared_ptr<void> SceneR::Content::BasicEffectReader::Read(ContentReader& input)
{
    auto& gdService = input.ContentManager().ServiceProvider().GetService<IGraphicsDeviceService>();
    auto  effect    = std::make_shared<BasicEffect>(gdService.CurrentGraphicsDevice());

    // Pointer to a separate .xnb file which contains an object of type Texture2D
    auto texture = input.ReadExternalReference<Texture2D>();

    if (texture != nullptr)
    {
        effect->Texture(texture);
        effect->TextureEnabled(true);
    }

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

    // Vertex color enabled
    effect->VertexColorEnabled(input.ReadBoolean());

    return effect;
}
