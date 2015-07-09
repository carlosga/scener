// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/SkinnedEffectReader.hpp>

#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/SkinnedEffect.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::IGraphicsDeviceService;
        using SceneR::Graphics::SkinnedEffect;
        using SceneR::Graphics::Texture2D;

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

            // Pointer to a separate .xnb file which contains an object of type Texture2D
            auto texture = input.ReadExternalReference<Texture2D>();

            if (texture != nullptr)
            {
                effect->Texture(texture);
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
    }
}
