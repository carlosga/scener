// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/PresentationParameters.hpp"

namespace scener {  namespace graphics {

PresentationParameters::PresentationParameters() noexcept
    : full_screen        { false }
    , back_buffer_height { 0 }
    , back_buffer_width  { 0 }
    , multi_sample_count { 8 }
    , present_interval   { PresentInterval::one }
{
}

}}
