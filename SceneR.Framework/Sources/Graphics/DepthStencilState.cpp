// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/DepthStencilState.hpp>

#include <Graphics/GraphicsDevice.hpp>

using namespace System;
using namespace SceneR::Graphics;

DepthStencilState::DepthStencilState(GraphicsDevice& graphicsDevice)
    : GraphicsResource                       { graphicsDevice }
    , counterClockwiseStencilDepthBufferFail { StencilOperation::Keep }
    , counterClockwiseStencilFail            { StencilOperation::Keep }
    , counterClockwiseStencilFunction        { CompareFunction::Always }
    , counterClockwiseStencilPass            { StencilOperation::Keep }
    , depthBufferEnable                      { true }
    , depthBufferFunction                    { CompareFunction::LessEqual }
    , depthBufferWriteEnable                 { true }
    , referenceStencil                       { 0 }
    , stencilDepthBufferFail                 { StencilOperation::Keep }
    , stencilEnable                          { false }
    , stencilFail                            { StencilOperation::Keep }
    , stencilFunction                        { CompareFunction::Always }
    , stencilMask                            { -1 }
    , stencilPass                            { StencilOperation::Keep }
    , stencilWriteMask                       { -1 }
    , twoSidedStencilMode                    { false }
{
}

DepthStencilState::~DepthStencilState()
{
}

void DepthStencilState::Dispose()
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

const CompareFunction& SceneR::Graphics::DepthStencilState::DepthBufferFunction() const
{
    return this->depthBufferFunction;
}

void DepthStencilState::DepthBufferFunction(const CompareFunction& depthBufferFunction)
{
    this->depthBufferFunction = depthBufferFunction;
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
        glEnable(GL_DEPTH_TEST);
        glDepthMask(this->depthBufferWriteEnable);
        glDepthFunc(static_cast<GLenum>(this->depthBufferFunction));
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
