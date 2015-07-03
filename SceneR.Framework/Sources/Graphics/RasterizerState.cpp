// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/RasterizerState.hpp>

#include <Graphics/GraphicsDevice.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

RasterizerState::RasterizerState(GraphicsDevice& graphicsDevice)
    : GraphicsResource     { graphicsDevice }
    , cullMode             { SceneR::Graphics::CullMode::CullCounterClockwiseFace }
    , depthBias            { 0.0f }
    , fillMode             { SceneR::Graphics::FillMode::Solid }
    , multiSampleAntiAlias { true }
    , scissorTestEnable    { false }
    , slopeScaleDepthBias  { 0.0f }
{
}

RasterizerState::RasterizerState(const RasterizerState& rasterizerState)
    : GraphicsResource     { rasterizerState.graphicsDevice }
    , cullMode             { rasterizerState.cullMode }
    , depthBias            { rasterizerState.depthBias }
    , fillMode             { rasterizerState.fillMode }
    , multiSampleAntiAlias { rasterizerState.multiSampleAntiAlias }
    , scissorTestEnable    { rasterizerState.scissorTestEnable }
    , slopeScaleDepthBias  { rasterizerState.slopeScaleDepthBias }
{
}

RasterizerState::~RasterizerState()
{
}

void RasterizerState::Dispose()
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

bool RasterizerState::MultiSampleAntiAlias() const
{
    return this->multiSampleAntiAlias;
}

void RasterizerState::MultiSampleAntiAlias(const bool& multiSampleAntiAlias)
{
    this->multiSampleAntiAlias = multiSampleAntiAlias;
}

bool RasterizerState::ScissorTestEnable() const
{
    return this->scissorTestEnable;
}

void RasterizerState::ScissorTestEnable(const bool& scissorTestEnable)
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

RasterizerState&RasterizerState::operator=(const RasterizerState& rasterizerState)
{
    if (this != &rasterizerState)
    {
        this->graphicsDevice       = rasterizerState.graphicsDevice;
        this->cullMode             = rasterizerState.cullMode;
        this->depthBias            = rasterizerState.depthBias;
        this->fillMode             = rasterizerState.fillMode;
        this->multiSampleAntiAlias = rasterizerState.multiSampleAntiAlias;
        this->scissorTestEnable    = rasterizerState.scissorTestEnable;
        this->slopeScaleDepthBias  = rasterizerState.slopeScaleDepthBias;
    }

    return *this;
}

void RasterizerState::Apply() const
{
     glDisable(GL_DITHER);

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
    }
    else
    {
        glDisable(GL_MULTISAMPLE);
    }
}
