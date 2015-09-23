// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/DisplayMode.hpp>

#include <cassert>
#include <cstdint>

namespace SceneR
{
    namespace Graphics
    {
        DisplayMode::DisplayMode(const GLFWvidmode* mode)
            : _aspect_ratio { 0.0f }
            , _format       { SurfaceFormat::Color }
            , _height       ( mode->height )
            , _width        ( mode->width )
        {
            assert(mode->width != 0 && mode->height != 0);

            _aspect_ratio = static_cast<float>(mode->width) / static_cast<float>(mode->height);

            std::int32_t bitDepth = mode->redBits + mode->blueBits + mode->greenBits;

            switch (bitDepth)
            {
              case 16:
              case 8:
                  _format = SurfaceFormat::Bgr565;
                  break;
            }
        }

        float DisplayMode::aspect_ratio() const
        {
            return _aspect_ratio;
        }

        const SurfaceFormat& DisplayMode::format() const
        {
            return _format;
        }

        std::size_t DisplayMode::height() const
        {
            return _height;
        }

        std::size_t DisplayMode::width() const
        {
            return _width;
        }
    }
}
