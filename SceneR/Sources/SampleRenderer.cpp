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

#include <AstroBoy.hpp>
#include <System/Core.hpp>
#include <Framework/RendererWindow.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/PresentationParameters.hpp>
#include <SampleRenderer.hpp>
#include <memory>
#include <vector>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;
using namespace SceneR::Sample;

SampleRenderer::SampleRenderer(const String& rootDirectory)
    : Renderer(rootDirectory)
{
}

void SampleRenderer::BeginRun()
{
    PresentationParameters& parameters = this->GetGraphicsDevice().GetPresentationParameters();

    parameters.SetBackBufferWidth(1500);
    parameters.SetBackBufferHeight(943);

    this->GetRendererWindow().SetTitle(u"SceneR");

    Renderer::BeginRun();

    this->components.push_back(std::make_shared<AstroBoy>(*this));
}
