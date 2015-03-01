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
    , stencilMask                            { 0 }
    , stencilPass                            { StencilOperation::Keep }
    , stencilWriteMask                       { 0 }
    , twoSidedStencilMode                    { false }
{
}

DepthStencilState::DepthStencilState(const DepthStencilState& depthStencilState)
    : GraphicsResource                       { depthStencilState.graphicsDevice }
    , counterClockwiseStencilDepthBufferFail { depthStencilState.counterClockwiseStencilDepthBufferFail }
    , counterClockwiseStencilFail            { depthStencilState.counterClockwiseStencilFail }
    , counterClockwiseStencilFunction        { depthStencilState.counterClockwiseStencilFunction }
    , counterClockwiseStencilPass            { depthStencilState.counterClockwiseStencilPass }
    , depthBufferEnable                      { depthStencilState.depthBufferEnable }
    , depthBufferFunction                    { depthStencilState.depthBufferFunction }
    , depthBufferWriteEnable                 { depthStencilState.depthBufferWriteEnable }
    , referenceStencil                       { depthStencilState.referenceStencil }
    , stencilDepthBufferFail                 { depthStencilState.stencilDepthBufferFail }
    , stencilEnable                          { depthStencilState.stencilEnable }
    , stencilFail                            { depthStencilState.stencilFail }
    , stencilFunction                        { depthStencilState.stencilFunction }
    , stencilMask                            { depthStencilState.stencilMask }
    , stencilPass                            { depthStencilState.stencilPass }
    , stencilWriteMask                       { depthStencilState.stencilWriteMask }
    , twoSidedStencilMode                    { depthStencilState.twoSidedStencilMode }
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
    return this->counterClockwiseStencilDepthBufferFail;
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

Boolean DepthStencilState::DepthBufferEnable() const
{
    return this->depthBufferEnable;
}

void DepthStencilState::DepthBufferEnable(const Boolean& depthBufferEnable)
{
    this->depthBufferEnable = depthBufferEnable;
}

Boolean DepthStencilState::DepthBufferWriteEnable() const
{
    return this->depthBufferWriteEnable;
}

void DepthStencilState::DepthBufferWriteEnable(const Boolean& depthBufferWriteEnable)
{
    this->depthBufferWriteEnable = depthBufferWriteEnable;
}

System::Int32 DepthStencilState::ReferenceStencil() const
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

System::Boolean DepthStencilState::StencilEnable() const
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

System::UInt32 DepthStencilState::StencilMask() const
{
    return this->stencilMask;
}

void DepthStencilState::StencilMask(const System::UInt32& stencilMask)
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

System::UInt32 DepthStencilState::StencilWriteMask() const
{
    return this->stencilWriteMask;
}

void DepthStencilState::StencilWriteMask(const System::UInt32& stencilWriteMask)
{
    this->stencilWriteMask = stencilWriteMask;
}

System::Boolean DepthStencilState::TwoSidedStencilMode() const
{
    return this->twoSidedStencilMode;
}

void DepthStencilState::TwoSidedStencilMode(const System::Boolean& twoSidedStencilMode)
{
    this->twoSidedStencilMode = twoSidedStencilMode;
}

DepthStencilState&DepthStencilState::operator=(const DepthStencilState& depthStencilState)
{
    if (this != &depthStencilState)
    {
        this->graphicsDevice                         = depthStencilState.graphicsDevice;
        this->counterClockwiseStencilDepthBufferFail = depthStencilState.counterClockwiseStencilDepthBufferFail;
        this->counterClockwiseStencilFail            = depthStencilState.counterClockwiseStencilFail;
        this->counterClockwiseStencilFunction        = depthStencilState.counterClockwiseStencilFunction;
        this->counterClockwiseStencilPass            = depthStencilState.counterClockwiseStencilPass;
        this->depthBufferEnable                      = depthStencilState.depthBufferEnable;
        this->depthBufferFunction                    = depthStencilState.depthBufferFunction;
        this->depthBufferWriteEnable                 = depthStencilState.depthBufferWriteEnable;
        this->referenceStencil                       = depthStencilState.referenceStencil;
        this->stencilDepthBufferFail                 = depthStencilState.stencilDepthBufferFail;
        this->stencilEnable                          = depthStencilState.stencilEnable;
        this->stencilFail                            = depthStencilState.stencilFail;
        this->stencilFunction                        = depthStencilState.stencilFunction;
        this->stencilMask                            = depthStencilState.stencilMask;
        this->stencilPass                            = depthStencilState.stencilPass;
        this->stencilWriteMask                       = depthStencilState.stencilWriteMask;
        this->twoSidedStencilMode                    = depthStencilState.twoSidedStencilMode;
    }

    return *this;
}

void DepthStencilState::Apply() const
{
    if (this->depthBufferEnable)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }

    glDepthMask(this->depthBufferWriteEnable);
    glDepthFunc(static_cast<GLenum>(this->depthBufferFunction));

    if (this->stencilEnable)
    {
        glEnable(GL_STENCIL_TEST);
    }
    else
    {
        glDisable(GL_STENCIL_TEST);
    }

    glStencilMask(this->stencilWriteMask);

    if (this->twoSidedStencilMode)
    {
        glStencilFuncSeparate(GL_FRONT
                            , static_cast<GLenum>(this->stencilFunction)
                            , this->referenceStencil
                            , this->stencilMask);

        glStencilFuncSeparate(GL_BACK
                            , static_cast<GLenum>(this->counterClockwiseStencilFunction)
                            , this->referenceStencil
                            , this->stencilMask);

        glStencilOpSeparate(GL_FRONT
                          , static_cast<GLenum>(this->stencilFail)
                          , static_cast<GLenum>(this->stencilDepthBufferFail)
                          , static_cast<GLenum>(this->stencilPass));

        glStencilOpSeparate(GL_BACK
                          , static_cast<GLenum>(this->counterClockwiseStencilFail)
                          , static_cast<GLenum>(this->counterClockwiseStencilDepthBufferFail)
                          , static_cast<GLenum>(this->counterClockwiseStencilPass));
    }
    else
    {
        glStencilFunc(static_cast<GLenum>(this->stencilFunction)
                    , this->referenceStencil
                    , this->stencilMask);

        glStencilOp(static_cast<GLenum>(this->stencilFail)
                  , static_cast<GLenum>(this->stencilDepthBufferFail)
                  , static_cast<GLenum>(this->stencilPass));
    }
}
