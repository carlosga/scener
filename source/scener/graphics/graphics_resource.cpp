// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/graphics_resource.hpp"

namespace scener { namespace graphics {

graphics_resource::graphics_resource(gsl::not_null<graphics_device*> device) noexcept
    : name             { }
    , _graphics_device { device }
{
}

graphics::graphics_device* graphics_resource::device() const noexcept
{
    return _graphics_device;
}

}}
