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

#include <Graphics/DepthStencilState.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Viewport.hpp>

using namespace SceneR::Graphics;

DepthStencilState::DepthStencilState(GraphicsDevice& graphicsDevice)
    : GraphicsResource(graphicsDevice),
      depthBufferEnable(true),
      depthBufferFunction(CompareFunction::LessEqual),
      depthBufferWriteEnable(true)
{
}

DepthStencilState::~DepthStencilState()
{
}

const Boolean& DepthStencilState::GetDepthBufferEnable() const
{
    return this->depthBufferEnable;
}

void DepthStencilState::SetDepthBufferEnable(const Boolean& depthBufferEnable)
{
    this->depthBufferEnable = depthBufferEnable;
}

const Boolean& DepthStencilState::GetDepthBufferWriteEnable() const
{
    return this->depthBufferWriteEnable;
}

void DepthStencilState::SetDepthBufferWriteEnable(const Boolean& depthBufferWriteEnable)
{
    this->depthBufferWriteEnable = depthBufferWriteEnable;
}

void DepthStencilState::Apply() const
{
    if (this->depthBufferEnable)
    {
        Viewport& currentViewport = this->graphicsDevice.GetViewport();

        glEnable(GL_DEPTH_TEST);
        glDepthMask(this->depthBufferWriteEnable);
        glDepthFunc(static_cast<GLenum>(this->depthBufferFunction));
        glDepthRange(currentViewport.GetMinDepth(), currentViewport.GetMaxDepth());
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
}
