// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/BlendState.hpp>
#include <Graphics/GraphicsDevice.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

BlendState::BlendState(GraphicsDevice& graphicsDevice)
    : GraphicsResource      { graphicsDevice }
    , alphaBlendFunction    { BlendFunction::Add }
    , alphaDestinationBlend { Blend::Zero }
    , alphaSourceBlend      { Blend::One }
    , blendFactor           { Color::White }
    , colorBlendFunction    { BlendFunction::Add }
    , colorDestinationBlend { Blend::Zero }
    , colorSourceBlend      { Blend::One }
    , colorWriteChannels    { SceneR::Graphics::ColorWriteChannels::All }
    , colorWriteChannels1   { SceneR::Graphics::ColorWriteChannels::All }
    , colorWriteChannels2   { SceneR::Graphics::ColorWriteChannels::All }
    , colorWriteChannels3   { SceneR::Graphics::ColorWriteChannels::All }
    , multiSampleMask       { 0 }
{
}

BlendState::BlendState(const BlendState& blendState)
    : GraphicsResource      { blendState.graphicsDevice }
    , alphaBlendFunction    { blendState.alphaBlendFunction }
    , alphaDestinationBlend { blendState.alphaDestinationBlend }
    , alphaSourceBlend      { blendState.alphaSourceBlend }
    , blendFactor           { blendState.blendFactor }
    , colorBlendFunction    { blendState.colorBlendFunction }
    , colorDestinationBlend { blendState.colorDestinationBlend }
    , colorSourceBlend      { blendState.colorSourceBlend }
    , colorWriteChannels    { blendState.colorWriteChannels }
    , colorWriteChannels1   { blendState.colorWriteChannels1 }
    , colorWriteChannels2   { blendState.colorWriteChannels2 }
    , colorWriteChannels3   { blendState.colorWriteChannels3 }
    , multiSampleMask       { blendState.multiSampleMask }
{
}

BlendState::~BlendState()
{
}

void BlendState::Dispose()
{
}

const BlendFunction& BlendState::AlphaBlendFunction() const
{
    return this->alphaBlendFunction;
}

void BlendState::AlphaBlendFunction(const BlendFunction& alphaBlendFunction)
{
    this->alphaBlendFunction = alphaBlendFunction;
}

const Blend& BlendState::AlphaDestinationBlend() const
{
    return this->alphaDestinationBlend;
}

void BlendState::AlphaDestinationBlend(const Blend& alphaDestinationBlend)
{
    this->alphaDestinationBlend = alphaDestinationBlend;
}

const Blend& BlendState::AlphaSourceBlend() const
{
    return this->alphaSourceBlend;
}

void BlendState::AlphaSourceBlend(const Blend& alphaSourceBlend)
{
    this->alphaSourceBlend = alphaSourceBlend;
}

const Color& BlendState::BlendFactor() const
{
    return blendFactor;
}

void BlendState::BlendFactor(const Color& blendFactor)
{
    this->blendFactor = blendFactor;
}

const BlendFunction& BlendState::ColorBlendFunction() const
{
    return colorBlendFunction;
}

void BlendState::ColorBlendFunction(const BlendFunction& colorBlendFunction)
{
    this->colorBlendFunction = colorBlendFunction;
}

const Blend& BlendState::ColorDestinationBlend() const
{
    return colorDestinationBlend;
}

void BlendState::ColorDestinationBlend(const Blend& colorDestinationBlend)
{
    this->colorDestinationBlend = colorDestinationBlend;
}

const Blend& BlendState::ColorSourceBlend() const
{
    return colorSourceBlend;
}

void BlendState::ColorSourceBlend(const Blend& colorSourceBlend)
{
    this->colorSourceBlend = colorSourceBlend;
}

const SceneR::Graphics::ColorWriteChannels& BlendState::ColorWriteChannels() const
{
    return colorWriteChannels;
}

void BlendState::ColorWriteChannels(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels)
{
    this->colorWriteChannels = colorWriteChannels;
}

const SceneR::Graphics::ColorWriteChannels& BlendState::ColorWriteChannels1() const
{
    return colorWriteChannels1;
}

void BlendState::ColorWriteChannels1(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels1)
{
    this->colorWriteChannels1 = colorWriteChannels1;
}

const SceneR::Graphics::ColorWriteChannels& BlendState::ColorWriteChannels2() const
{
    return colorWriteChannels2;
}

void BlendState::ColorWriteChannels2(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels2)
{
    this->colorWriteChannels2 = colorWriteChannels2;
}

const SceneR::Graphics::ColorWriteChannels& BlendState::ColorWriteChannels3() const
{
    return colorWriteChannels3;
}

void BlendState::ColorWriteChannels3(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels3)
{
    this->colorWriteChannels3 = colorWriteChannels3;
}

uint32_t BlendState::MultiSampleMask() const
{
    return this->multiSampleMask;
}

void BlendState::MultiSampleMask(const uint32_t& multiSampleMask)
{
    this->multiSampleMask = multiSampleMask;
}

BlendState&BlendState::operator=(const BlendState& blendState)
{
    if (this != &blendState)
    {
        this->graphicsDevice        = blendState.graphicsDevice;
        this->alphaBlendFunction    = blendState.alphaBlendFunction;
        this->alphaDestinationBlend = blendState.alphaDestinationBlend;
        this->alphaSourceBlend      = blendState.alphaSourceBlend;
        this->blendFactor           = blendState.blendFactor;
        this->colorBlendFunction    = blendState.colorBlendFunction;
        this->colorDestinationBlend = blendState.colorDestinationBlend;
        this->colorSourceBlend      = blendState.colorSourceBlend;
        this->colorWriteChannels    = blendState.colorWriteChannels;
        this->colorWriteChannels1   = blendState.colorWriteChannels1;
        this->colorWriteChannels2   = blendState.colorWriteChannels2;
        this->colorWriteChannels3   = blendState.colorWriteChannels3;
        this->multiSampleMask       = blendState.multiSampleMask;
    }

    return *this;
}

void BlendState::Apply() const
{
    // http://www.opengl.org/wiki/Blending

    auto blendEnabled = !(this->colorSourceBlend      == Blend::One
                       && this->colorDestinationBlend == Blend::Zero
                       && this->alphaSourceBlend      == Blend::One
                       && this->alphaDestinationBlend == Blend::Zero);

    if (!blendEnabled)
    {
        glDisable(GL_BLEND);
    }
    else
    {
        glEnable(GL_BLEND);
    }

    glBlendEquationSeparate(static_cast<GLenum>(this->colorBlendFunction)
                          , static_cast<GLenum>(this->alphaBlendFunction));

    glBlendFuncSeparate(static_cast<GLenum>(this->colorSourceBlend)
                      , static_cast<GLenum>(this->colorDestinationBlend)
                      , static_cast<GLenum>(this->alphaSourceBlend)
                      , static_cast<GLenum>(this->alphaDestinationBlend));

    glColorMask((this->colorWriteChannels & SceneR::Graphics::ColorWriteChannels::Red)   == SceneR::Graphics::ColorWriteChannels::Red
              , (this->colorWriteChannels & SceneR::Graphics::ColorWriteChannels::Green) == SceneR::Graphics::ColorWriteChannels::Green
              , (this->colorWriteChannels & SceneR::Graphics::ColorWriteChannels::Blue)  == SceneR::Graphics::ColorWriteChannels::Blue
              , (this->colorWriteChannels & SceneR::Graphics::ColorWriteChannels::Alpha) == SceneR::Graphics::ColorWriteChannels::Alpha);

    glBlendColor(this->blendFactor.R() / 255
               , this->blendFactor.G() / 255
               , this->blendFactor.B() / 255
               , this->blendFactor.A() / 255);

    if (this->multiSampleMask != 0)
    {
        glSampleCoverage(this->multiSampleMask, GL_FALSE);
    }
}
