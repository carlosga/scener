// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Viewport.hpp"

#include <gsl.h>

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR
{
    namespace Graphics
    {
        Viewport::Viewport() noexcept
            : Viewport { 0.0f, 0.0f, 0.0f, 0.0f }
        {
        }

        Viewport::Viewport(const float& x    , const float& y
                         , const float& width, const float& height) noexcept
            : Viewport { x, y, width, height, 0.0f, 1.0f }
        {
        }

        Viewport::Viewport(const float& x       , const float& y
                         , const float& width   , const float& height
                         , const float& minDepth, const float& maxDepth) noexcept
            : x         { x }
            , y         { y }
            , width     { width }
            , height    { height }
            , min_depth { minDepth }
            , max_depth { maxDepth }
        {
        }

        float Viewport::aspect_ratio() const noexcept
        {
            Expects(width > 0 && height > 0);

            return (width / height);
        }

        void Viewport::update() const
        {
            glViewportIndexedf(0, x, y, width, height);
            glDepthRangeIndexed(0, min_depth, max_depth);
        }
    }
}
