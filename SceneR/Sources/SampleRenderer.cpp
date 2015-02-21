// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <SampleRenderer.hpp>

#include <Marcus.hpp>
#include <SampleModel.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Sample;

SampleRenderer::SampleRenderer()
    : Renderer(u"/home/carlos/development/projects/cpp/opengl/scener/SceneR/Content/")
{
}

void SampleRenderer::BeginRun()
{
    this->graphicsDeviceManager.PreferredBackBufferWidth(1600);
    this->graphicsDeviceManager.PreferredBackBufferHeight(900);
    this->graphicsDeviceManager.WindowTitle(u"SceneR");

    this->Components().push_back(std::make_shared<Marcus>(*this));
    // this->Components().push_back(std::make_shared<SampleModel>(*this));

    Renderer::BeginRun();
}

void SampleRenderer::Draw(const RenderTime& renderTime)
{
    this->graphicsDeviceManager.CurrentGraphicsDevice().Clear(Color::Black);

    Renderer::Draw(renderTime);
}
