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

using namespace System;
using namespace SceneR::Graphics;

DepthStencilState::DepthStencilState(GraphicsDevice& graphicsDevice)
    : GraphicsResource(graphicsDevice),
      counterClockwiseStencilDepthBufferFail(StencilOperation::Keep),
      counterClockwiseStencilFail(StencilOperation::Keep),
      counterClockwiseStencilFunction(CompareFunction::Always),
      counterClockwiseStencilPass(StencilOperation::Keep),
      depthBufferEnable(true),
      depthBufferFunction(CompareFunction::LessEqual),
      depthBufferWriteEnable(true),
      referenceStencil(0),
      stencilDepthBufferFail(StencilOperation::Keep),
      stencilEnable(false),
      stencilFail(StencilOperation::Keep),
      stencilFunction(CompareFunction::Always),
      stencilMask(-1),
      stencilPass(StencilOperation::Keep),
      stencilWriteMask(-1),
      twoSidedStencilMode(false)
{
}

DepthStencilState::~DepthStencilState()
{
}

const StencilOperation& DepthStencilState::CounterClockwiseStencilDepthBufferFail() const
{
    return counterClockwiseStencilDepthBufferFail;
}

void DepthStencilState::CounterClockwiseStencilDepthBufferFail(const StencilOperation& counterClockwiseStencilDepthBufferFail)
{
    this->counterClockwiseStencilDepthBufferFail = counterClockwiseStencilDepthBufferFail;
}

const StencilOperation& DepthStencilState::CounterClockwiseStencilFail() const
{
    return this->counterClockwiseStencilFail;
}

void DepthStencilState::CounterClockwiseStencilFail(const StencilOperation& counterClockwiseStencilFail)
{
    this->counterClockwiseStencilFail = counterClockwiseStencilFail;
}

const CompareFunction& DepthStencilState::CounterClockwiseStencilFunction() const
{
    return this->counterClockwiseStencilFunction;
}

void DepthStencilState::CounterClockwiseStencilFunction(const CompareFunction& counterClockwiseStencilFunction)
{
    this->counterClockwiseStencilFunction = counterClockwiseStencilFunction;
}

const StencilOperation& DepthStencilState::CounterClockwiseStencilPass() const
{
    return this->counterClockwiseStencilPass;
}

void DepthStencilState::CounterClockwiseStencilPass(const StencilOperation& counterClockwiseStencilPass)
{
    this->counterClockwiseStencilPass = counterClockwiseStencilPass;
}

const Boolean& DepthStencilState::DepthBufferEnable() const
{
    return this->depthBufferEnable;
}

void DepthStencilState::DepthBufferEnable(const Boolean& depthBufferEnable)
{
    this->depthBufferEnable = depthBufferEnable;
}

const Boolean& DepthStencilState::DepthBufferWriteEnable() const
{
    return this->depthBufferWriteEnable;
}

void DepthStencilState::DepthBufferWriteEnable(const Boolean& depthBufferWriteEnable)
{
    this->depthBufferWriteEnable = depthBufferWriteEnable;
}

const System::Int32& DepthStencilState::ReferenceStencil() const
{
    return this->referenceStencil;
}

void DepthStencilState::ReferenceStencil(const System::Int32& referenceStencil)
{
    this->referenceStencil = referenceStencil;
}

const StencilOperation& DepthStencilState::StencilDepthBufferFail() const
{
    return this->stencilDepthBufferFail;
}

void DepthStencilState::StencilDepthBufferFail(const StencilOperation& stencilDepthBufferFail)
{
    this->stencilDepthBufferFail = stencilDepthBufferFail;
}

const System::Boolean& DepthStencilState::StencilEnable() const
{
    return this->stencilEnable;
}

void DepthStencilState::StencilEnable(const System::Boolean& stencilEnable)
{
    this->stencilEnable = stencilEnable;
}

const StencilOperation& DepthStencilState::StencilFail() const
{
    return this->stencilFail;
}

void DepthStencilState::StencilFail(const StencilOperation& stencilFail)
{
    this->stencilFail = stencilFail;
}

const CompareFunction& DepthStencilState::StencilFunction() const
{
    return this->stencilFunction;
}

void DepthStencilState::StencilFunction(const CompareFunction& stencilFunction)
{
    this->stencilFunction = stencilFunction;
}

const System::Int32& DepthStencilState::StencilMask() const
{
    return this->stencilMask;
}

void DepthStencilState::StencilMask(const System::Int32& stencilMask)
{
    this->stencilMask = stencilMask;
}

const StencilOperation& DepthStencilState::StencilPass() const
{
    return this->stencilPass;
}

void DepthStencilState::StencilPass(const StencilOperation& stencilPass)
{
    this->stencilPass = stencilPass;
}

const System::Int32& DepthStencilState::StencilWriteMask() const
{
    return this->stencilWriteMask;
}

void DepthStencilState::StencilWriteMask(const System::Int32& stencilWriteMask)
{
    this->stencilWriteMask = stencilWriteMask;
}

const System::Boolean& DepthStencilState::TwoSidedStencilMode() const
{
    return this->twoSidedStencilMode;
}

void DepthStencilState::TwoSidedStencilMode(const System::Boolean& twoSidedStencilMode)
{
    this->twoSidedStencilMode = twoSidedStencilMode;
}

void DepthStencilState::Apply() const
{
    if (this->depthBufferEnable)
    {
        Viewport& currentViewport = this->graphicsDevice.Viewport();

        glEnable(GL_DEPTH_TEST);
        glDepthMask(this->depthBufferWriteEnable);
        glDepthFunc(static_cast<GLenum>(this->depthBufferFunction));
        glDepthRange(currentViewport.MinDepth(), currentViewport.MaxDepth());
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }

    if (this->stencilEnable)
    {
        glEnable(GL_STENCIL_TEST);
        glStencilMask(this->stencilWriteMask);

        if (this->twoSidedStencilMode)
        {
            glStencilFunc(static_cast<GLenum>(this->stencilFunction)
                        , this->referenceStencil
                        , this->stencilMask);
            glStencilOp(static_cast<GLenum>(this->stencilFail)
                      , static_cast<GLenum>(this->stencilDepthBufferFail)
                      , static_cast<GLenum>(this->stencilPass));
        }
        else
        {
            glStencilFuncSeparate(GL_FRONT
                                , static_cast<GLenum>(this->stencilFunction)
                                , this->referenceStencil
                                , this->stencilMask);
            glStencilOpSeparate(GL_FRONT
                              , static_cast<GLenum>(this->stencilFail)
                              , static_cast<GLenum>(this->stencilDepthBufferFail)
                              , static_cast<GLenum>(this->stencilPass));

            glStencilFuncSeparate(GL_BACK
                                , static_cast<GLenum>(this->counterClockwiseStencilFunction)
                                , this->referenceStencil
                                , this->stencilMask);
            glStencilOpSeparate(GL_BACK
                              , static_cast<GLenum>(this->counterClockwiseStencilFail)
                              , static_cast<GLenum>(this->counterClockwiseStencilDepthBufferFail)
                              , static_cast<GLenum>(this->counterClockwiseStencilPass));
        }
    }
    else
    {
        glDisable(GL_STENCIL_TEST);
    }
}
