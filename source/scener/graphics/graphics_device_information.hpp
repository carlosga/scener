// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_GRAPHICS_DEVICE_INFORMATION
#define SCENER_GRAPHICS_GRAPHICS_DEVICE_INFORMATION

#include "scener/graphics/graphics_adapter.hpp"
#include "scener/graphics/presentation_parameters.hpp"

namespace scener::graphics
{
    struct graphics_device_information
    {
        graphics_adapter        adapter;
        presentation_parameters presentation_params;
    };
}

#endif // SCENER_GRAPHICS_GRAPHICS_DEVICE_INFORMATION
