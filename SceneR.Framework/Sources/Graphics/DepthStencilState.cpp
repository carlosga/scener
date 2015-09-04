// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/DepthStencilState.hpp>

#include <Graphics/GraphicsDevice.hpp>

namespace SceneR
{
    namespace Graphics
    {
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
            : GraphicsResource                       { depthStencilState._graphics_device }
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

        void DepthStencilState::dispose()
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

        bool DepthStencilState::DepthBufferEnable() const
        {
            return this->depthBufferEnable;
        }

        void DepthStencilState::DepthBufferEnable(const bool& depthBufferEnable)
        {
            this->depthBufferEnable = depthBufferEnable;
        }

        bool DepthStencilState::DepthBufferWriteEnable() const
        {
            return this->depthBufferWriteEnable;
        }

        void DepthStencilState::DepthBufferWriteEnable(const bool& depthBufferWriteEnable)
        {
            this->depthBufferWriteEnable = depthBufferWriteEnable;
        }

        std::int32_t DepthStencilState::ReferenceStencil() const
        {
            return this->referenceStencil;
        }

        void DepthStencilState::ReferenceStencil(const std::int32_t& referenceStencil)
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

        bool DepthStencilState::StencilEnable() const
        {
            return this->stencilEnable;
        }

        void DepthStencilState::StencilEnable(const bool& stencilEnable)
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

        std::uint32_t DepthStencilState::StencilMask() const
        {
            return this->stencilMask;
        }

        void DepthStencilState::StencilMask(const std::uint32_t& stencilMask)
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

        std::uint32_t DepthStencilState::StencilWriteMask() const
        {
            return this->stencilWriteMask;
        }

        void DepthStencilState::StencilWriteMask(const std::uint32_t& stencilWriteMask)
        {
            this->stencilWriteMask = stencilWriteMask;
        }

        bool DepthStencilState::TwoSidedStencilMode() const
        {
            return this->twoSidedStencilMode;
        }

        void DepthStencilState::TwoSidedStencilMode(const bool& twoSidedStencilMode)
        {
            this->twoSidedStencilMode = twoSidedStencilMode;
        }

        DepthStencilState&DepthStencilState::operator=(const DepthStencilState& depthStencilState)
        {
            if (this != &depthStencilState)
            {
                this->_graphics_device                       = depthStencilState._graphics_device;
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
    }
}
