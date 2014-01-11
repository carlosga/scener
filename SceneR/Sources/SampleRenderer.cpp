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
//#include <BumbleBee.hpp>
//#include <Felicia.hpp>
#include <Marcus.hpp>
//#include <WarForrest.hpp>
#include <Framework/GraphicsDeviceManager.hpp>
#include <Framework/RenderTime.hpp>
#include <SampleRenderer.hpp>
#include <memory>

using namespace SceneR::Sample;
using namespace SceneR::Framework;

SampleRenderer::SampleRenderer()
    : Renderer(u"/home/carlos/development/projects/cpp/opengl/workspace/SceneR/Content/")
{
}

void SampleRenderer::BeginRun()
{
    this->graphicsDeviceManager.PreferredBackBufferWidth(1600);
    this->graphicsDeviceManager.PreferredBackBufferHeight(900);
    this->graphicsDeviceManager.WindowTitle(u"SceneR");

    // this->Components().push_back(std::make_shared<AstroBoy>(*this));
    // this->Components().push_back(std::make_shared<BumbleBee>(*this));
    // this->Components().push_back(std::make_shared<Felicia>(*this));
    this->Components().push_back(std::make_shared<Marcus>(*this));
    // this->Components().push_back(std::make_shared<WarForrest>(*this));

    Renderer::BeginRun();
}

void SampleRenderer::Draw(const RenderTime& renderTime)
{
    this->graphicsDeviceManager.CurrentGraphicsDevice().Clear(Color::Black);

    Renderer::Draw(renderTime);
}
