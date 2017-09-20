// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/presentation_parameters.hpp"

namespace scener::graphics
{
    presentation_parameters::presentation_parameters() noexcept
        : full_screen          { false }
        , back_buffer_height   { 0 }
        , back_buffer_width    { 0 }
        , multi_sample_count   { 8 }
        , present_interval     { present_interval::one }
        , device_window_handle { nullptr }
    {
    }
}
