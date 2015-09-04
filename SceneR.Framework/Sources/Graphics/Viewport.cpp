// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Viewport.hpp>

#include <cassert>

#include <System/Graphics/Platform.hpp>

namespace SceneR
{
    namespace Graphics
    {
        Viewport::Viewport()
            : Viewport { 0.0f, 0.0f, 0.0f, 0.0f }
        {
        }

        Viewport::Viewport(const float& x    , const float& y
                         , const float& width, const float& height)
            : Viewport { x, y, width, height, 0.0f, 1.0f }
        {
        }

        Viewport::Viewport(const float& x       , const float& y
                         , const float& width   , const float& height
                         , const float& minDepth, const float& maxDepth)
            : x         { x }
            , y         { y }
            , width     { width }
            , height    { height }
            , min_depth { minDepth }
            , max_depth { maxDepth }
        {
        }

        Viewport::Viewport(const Viewport& viewport)
            : x         { viewport.x }
            , y         { viewport.y }
            , width     { viewport.width }
            , height    { viewport.height }
            , min_depth { viewport.min_depth }
            , max_depth { viewport.max_depth }
        {
        }

        Viewport::~Viewport()
        {
        }

        float Viewport::aspect_ratio() const
        {
            assert(width > 0 && height > 0);

            return (width / height);
        }

        void Viewport::update() const
        {
            glViewportIndexedf(0, x, y, width, height);
            glDepthRangeIndexed(0, min_depth, max_depth);
        }

        Viewport& Viewport::operator=(const Viewport& viewport)
        {
            if (this != &viewport)
            {
                x         = viewport.x;
                y         = viewport.y;
                width     = viewport.width;
                height    = viewport.height;
                min_depth = viewport.min_depth;
                max_depth = viewport.max_depth;
            }

            return *this;
        }
    }
}
