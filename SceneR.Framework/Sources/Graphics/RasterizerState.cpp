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

#include <Graphics/RasterizerState.hpp>

#include <Framework/Vector3.hpp>
#include <Graphics/GraphicsDevice.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

RasterizerState::RasterizerState(GraphicsDevice& graphicsDevice)
    : GraphicsResource     { graphicsDevice }
    , cullMode             { CullMode::CullCounterClockwiseFace }
    , depthBias            { 0.0f }
    , fillMode             { FillMode::Solid }
    , multiSampleAntiAlias { true }
    , scissorTestEnable    { false }
    , slopeScaleDepthBias  { 0.0f }
{
}

const SceneR::Graphics::CullMode& RasterizerState::CullMode() const
{
    return this->cullMode;
}

void RasterizerState::CullMode(const SceneR::Graphics::CullMode& cullMode)
{
    this->cullMode = cullMode;
}

const Single& RasterizerState::DepthBias() const
{
    return this->depthBias;
}

void RasterizerState::DepthBias(const Single& depthBias)
{
    this->depthBias = depthBias;
}

const SceneR::Graphics::FillMode& RasterizerState::FillMode() const
{
    return this->fillMode;
}

void RasterizerState::FillMode(const SceneR::Graphics::FillMode& fillMode)
{
    this->fillMode = fillMode;
}

const Boolean& RasterizerState::MultiSampleAntiAlias() const
{
    return this->multiSampleAntiAlias;
}

void RasterizerState::MultiSampleAntiAlias(const Boolean& multiSampleAntiAlias)
{
    this->multiSampleAntiAlias = multiSampleAntiAlias;
}

const Boolean& RasterizerState::ScissorTestEnable() const
{
    return this->scissorTestEnable;
}

void RasterizerState::ScissorTestEnable(const Boolean& scissorTestEnable)
{
    this->scissorTestEnable = scissorTestEnable;
}

const Single& RasterizerState::SlopeScaleDepthBias() const
{
    return this->slopeScaleDepthBias;
}

void RasterizerState::SlopeScaleDepthBias(const Single& slopeScaleDepthBias)
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
        glFrontFace(static_cast<GLenum>(this->cullMode));

        switch (this->cullMode)
        {
            case SceneR::Graphics::CullMode::CullClockwiseFace:
                glCullFace(GL_BACK);
                break;

            case SceneR::Graphics::CullMode::CullCounterClockwiseFace:
                glCullFace(GL_FRONT);
                break;

            default:
                glCullFace(GL_FRONT_AND_BACK);
                break;
        }
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
    if (this->depthBias != 0.0f || this->slopeScaleDepthBias != 0.0f)
    {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(this->slopeScaleDepthBias, this->depthBias);
    }
    else
    {
        glDisable(GL_POLYGON_OFFSET_FILL);
    }

    // Enable multisample
    if (this->multiSampleAntiAlias)
    {
        glEnable(GL_MULTISAMPLE);
        // glEnable(GL_FRAMEBUFFER_SRGB_EXT);
    }
    else
    {
        glDisable(GL_MULTISAMPLE);
        // glDisable(GL_FRAMEBUFFER_SRGB_EXT);
    }
}
