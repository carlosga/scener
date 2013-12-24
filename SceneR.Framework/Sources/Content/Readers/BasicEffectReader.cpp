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
#include <Content/Readers/BasicEffectReader.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/BasicEffect.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/Texture2D.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

BasicEffectReader::BasicEffectReader()
{
}

std::shared_ptr<void> SceneR::Content::BasicEffectReader::Read(ContentReader& input)
{
    auto& gdService = input.ContentManager().ServiceProvider().GetService<IGraphicsDeviceService>();
    auto  effect    = std::make_shared<BasicEffect>(gdService.CurrentGraphicsDevice());

    // Pointer to a separate .xnb file which contains an object of type Texture2D
    String assetName = input.ReadString();

    if (assetName.size() > 0)
    {
        effect->Texture(input.ContentManager().Load<Texture2D>(assetName));
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
