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

#include <GL/glew.h>
#include <Graphics/BlendState.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

BlendState::BlendState(GraphicsDevice& graphicsDevice)
    : GraphicsResource(graphicsDevice),
      alphaBlendFunction(BlendFunction::Add),
      alphaDestinationBlend(Blend::Zero),
      alphaSourceBlend(Blend::One),
      blendFactor(Color::White),
      colorBlendFunction(BlendFunction::Add),
      colorDestinationBlend(Blend::Zero),
      colorSourceBlend(Blend::One),
      colorWriteChannels(ColorWriteChannels::None),
      colorWriteChannels1(ColorWriteChannels::None),
      colorWriteChannels2(ColorWriteChannels::None),
      colorWriteChannels3(ColorWriteChannels::None),
      multiSampleMask(0xffffffff)
{
}

BlendState::~BlendState()
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

const UInt32& BlendState::MultiSampleMask() const
{
    return multiSampleMask;
}

void BlendState::MultiSampleMask(const UInt32& multiSampleMask)
{
    this->multiSampleMask = multiSampleMask;
}

void BlendState::Apply() const
{
    // http://www.opengl.org/wiki/Blending
    glEnable(GL_BLEND);

    glBlendColor(this->blendFactor.R() / 255,
                 this->blendFactor.G() / 255,
                 this->blendFactor.B() / 255,
                 this->blendFactor.A() / 255);

    glBlendEquationSeparate(static_cast<GLenum>(this->colorBlendFunction),
                            static_cast<GLenum>(this->alphaBlendFunction));

    glBlendFuncSeparate(static_cast<GLenum>(this->colorSourceBlend),
                        static_cast<GLenum>(this->colorDestinationBlend),
                        static_cast<GLenum>(this->alphaSourceBlend),
                        static_cast<GLenum>(this->alphaDestinationBlend));
}
