// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/DepthStencilState.hpp>

#include <Graphics/GraphicsDevice.hpp>

namespace SceneR
{
    namespace Graphics
    {
        DepthStencilState::DepthStencilState(GraphicsDevice& graphicsDevice)
            : GraphicsResource                            { graphicsDevice }
            , counter_clockwise_stencil_depth_buffer_fail { StencilOperation::Keep }
            , counter_clockwise_stencil_fail              { StencilOperation::Keep }
            , counter_clockwise_stencil_function          { CompareFunction::Always }
            , counter_clockwise_stencil_pass              { StencilOperation::Keep }
            , depth_buffer_enable                         { true }
            , depth_buffer_function                       { CompareFunction::LessEqual }
            , depth_buffer_write_enable                   { true }
            , reference_stencil                           { 0 }
            , stencil_depth_buffer_fail                   { StencilOperation::Keep }
            , stencil_enable                              { false }
            , stencil_fail                                { StencilOperation::Keep }
            , stencil_function                            { CompareFunction::Always }
            , stencil_mask                                { 0 }
            , stencil_pass                                { StencilOperation::Keep }
            , stencil_write_mask                          { 0 }
            , two_sided_stencil_mode                      { false }
        {
        }

        DepthStencilState::DepthStencilState(const DepthStencilState& state)
            : GraphicsResource                            { state._graphics_device }
            , counter_clockwise_stencil_depth_buffer_fail { state.counter_clockwise_stencil_depth_buffer_fail }
            , counter_clockwise_stencil_fail              { state.counter_clockwise_stencil_fail }
            , counter_clockwise_stencil_function          { state.counter_clockwise_stencil_function }
            , counter_clockwise_stencil_pass              { state.counter_clockwise_stencil_pass }
            , depth_buffer_enable                         { state.depth_buffer_enable }
            , depth_buffer_function                       { state.depth_buffer_function }
            , depth_buffer_write_enable                   { state.depth_buffer_write_enable }
            , reference_stencil                           { state.reference_stencil }
            , stencil_depth_buffer_fail                   { state.stencil_depth_buffer_fail }
            , stencil_enable                              { state.stencil_enable }
            , stencil_fail                                { state.stencil_fail }
            , stencil_function                            { state.stencil_function }
            , stencil_mask                                { state.stencil_mask }
            , stencil_pass                                { state.stencil_pass }
            , stencil_write_mask                          { state.stencil_write_mask }
            , two_sided_stencil_mode                      { state.two_sided_stencil_mode }
        {
        }

        DepthStencilState::~DepthStencilState()
        {
        }

        void DepthStencilState::dispose()
        {
        }

        DepthStencilState&DepthStencilState::operator=(const DepthStencilState& state)
        {
            if (this != &state)
            {
                _graphics_device                            = state._graphics_device;
                counter_clockwise_stencil_depth_buffer_fail = state.counter_clockwise_stencil_depth_buffer_fail;
                counter_clockwise_stencil_fail              = state.counter_clockwise_stencil_fail;
                counter_clockwise_stencil_function          = state.counter_clockwise_stencil_function;
                counter_clockwise_stencil_pass              = state.counter_clockwise_stencil_pass;
                depth_buffer_enable                         = state.depth_buffer_enable;
                depth_buffer_function                       = state.depth_buffer_function;
                depth_buffer_write_enable                   = state.depth_buffer_write_enable;
                reference_stencil                           = state.reference_stencil;
                stencil_depth_buffer_fail                   = state.stencil_depth_buffer_fail;
                stencil_enable                              = state.stencil_enable;
                stencil_fail                                = state.stencil_fail;
                stencil_function                            = state.stencil_function;
                stencil_mask                                = state.stencil_mask;
                stencil_pass                                = state.stencil_pass;
                stencil_write_mask                          = state.stencil_write_mask;
                two_sided_stencil_mode                      = state.two_sided_stencil_mode;
            }

            return *this;
        }

        void DepthStencilState::apply() const
        {
            if (depth_buffer_enable)
            {
                glEnable(GL_DEPTH_TEST);
            }
            else
            {
                glDisable(GL_DEPTH_TEST);
            }

            glDepthMask(depth_buffer_write_enable);
            glDepthFunc(static_cast<GLenum>(depth_buffer_function));

            if (stencil_enable)
            {
                glEnable(GL_STENCIL_TEST);
            }
            else
            {
                glDisable(GL_STENCIL_TEST);
            }

            glStencilMask(stencil_write_mask);

            if (two_sided_stencil_mode)
            {
                glStencilFuncSeparate(GL_FRONT
                                    , static_cast<GLenum>(stencil_function)
                                    , reference_stencil
                                    , stencil_mask);

                glStencilFuncSeparate(GL_BACK
                                    , static_cast<GLenum>(counter_clockwise_stencil_function)
                                    , reference_stencil
                                    , stencil_mask);

                glStencilOpSeparate(GL_FRONT
                                  , static_cast<GLenum>(stencil_fail)
                                  , static_cast<GLenum>(stencil_depth_buffer_fail)
                                  , static_cast<GLenum>(stencil_pass));

                glStencilOpSeparate(GL_BACK
                                  , static_cast<GLenum>(counter_clockwise_stencil_fail)
                                  , static_cast<GLenum>(counter_clockwise_stencil_depth_buffer_fail)
                                  , static_cast<GLenum>(counter_clockwise_stencil_pass));
            }
            else
            {
                glStencilFunc(static_cast<GLenum>(stencil_function)
                            , reference_stencil
                            , stencil_mask);

                glStencilOp(static_cast<GLenum>(stencil_fail)
                          , static_cast<GLenum>(stencil_depth_buffer_fail)
                          , static_cast<GLenum>(stencil_pass));
            }
        }
    }
}
