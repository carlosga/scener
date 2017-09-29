// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/graphics_pipeline.hpp"

#include "scener/graphics/graphics_device.hpp"

namespace scener::graphics
{
    graphics_pipeline::graphics_pipeline(gsl::not_null<graphics_device*> device) noexcept
        : _device              { device }
    {
    }

}
