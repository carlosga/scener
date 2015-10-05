// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/DepthStencilState.hpp>

#include <Graphics/GraphicsDevice.hpp>

namespace SceneR
{
    namespace Graphics
    {
        DepthStencilState::DepthStencilState(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept
            : GraphicsResource { graphicsDevice }
        {
        }

        void DepthStencilState::dispose()
        {
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
            glDepthRange(0.0f, 1.0f);

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
                glStencilFuncSeparate(GL_FRONT, static_cast<GLenum>(stencil_function), reference_stencil, stencil_mask);

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
                glStencilFunc(static_cast<GLenum>(stencil_function), reference_stencil, stencil_mask);

                glStencilOp(static_cast<GLenum>(stencil_fail)
                          , static_cast<GLenum>(stencil_depth_buffer_fail)
                          , static_cast<GLenum>(stencil_pass));
            }
        }
    }
}
