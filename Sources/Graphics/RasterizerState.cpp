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

#include "Graphics/GraphicsDevice.hpp"
#include "Graphics/RasterizerState.hpp"
#include "Graphics/Viewport.hpp"

using namespace SceneR::Graphics;

RasterizerState::RasterizerState(GraphicsDevice& graphicsDevice)
    : GraphicsResource(graphicsDevice),
      cullMode(CullMode::CullCounterClockwiseFace),
      depthBias(0),
      fillMode(FillMode::Solid),
      multiSampleAntiAlias(true),
      scissorTestEnable(false),
      slopeScaleDepthBias(0)
{
}

const CullMode& RasterizerState::GetCullMode() const
{
    return this->cullMode;
}

void RasterizerState::SetCullMode(const CullMode& cullMode)
{
    this->cullMode = cullMode;
}

const Single& RasterizerState::GetDepthBias() const
{
    return this->depthBias;
}

void RasterizerState::SetDepthBias(const Single& depthBias)
{
    this->depthBias = depthBias;
}

const FillMode& SceneR::Graphics::RasterizerState::GetFillMode() const
{
    return this->fillMode;
}

void RasterizerState::SetFillMode(const FillMode& fillMode)
{
    this->fillMode = fillMode;
}

const Boolean& RasterizerState::GetMultiSampleAntiAlias() const
{
    return this->multiSampleAntiAlias;
}

void RasterizerState::SetMultiSampleAntiAlias(const Boolean& multiSampleAntiAlias)
{
    this->multiSampleAntiAlias = multiSampleAntiAlias;
}

const Boolean& RasterizerState::GetScissorTestEnable() const
{
    return this->scissorTestEnable;
}

void RasterizerState::SetScissorTestEnable(const Boolean& scissorTestEnable)
{
    this->scissorTestEnable = scissorTestEnable;
}

const Single& RasterizerState::GetSlopeScaleDepthBias() const
{
    return this->slopeScaleDepthBias;
}

void RasterizerState::SetSlopeScaleDepthBias(const Single& slopeScaleDepthBias)
{
    this->slopeScaleDepthBias = slopeScaleDepthBias;
}

void RasterizerState::Apply() const
{
    // Specify whether front- or back-facing facets can be culled
    if (this->cullMode == CullMode::None)
    {
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(static_cast<GLenum>(this->cullMode));
    }

    //  Select a polygon rasterization mode
    if (this->fillMode == FillMode::Solid)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    // Enable or disable the scissor test
    if (this->scissorTestEnable)
    {
        glEnable(GL_SCISSOR_TEST);
    }
    else
    {
        glDisable(GL_SCISSOR_TEST);
    }

    // set the scale and units used to calculate depth values if needed
    if (this->depthBias != 0 || this->slopeScaleDepthBias != 0)
    {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(this->slopeScaleDepthBias, this->depthBias);
    }
    else
    {
        glDisable(GL_POLYGON_OFFSET_FILL);
    }
}
