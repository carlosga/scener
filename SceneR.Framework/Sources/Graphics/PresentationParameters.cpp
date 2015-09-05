// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/PresentationParameters.hpp>

namespace SceneR
{
    namespace Graphics
    {
        PresentationParameters::PresentationParameters()
            : full_screen        { false }
            , back_buffer_height { 0 }
            , back_buffer_width  { 0 }
            , multi_sample_count { 8 }
            , present_interval   { SceneR::Framework::PresentInterval::Default }
        {
        }

        PresentationParameters::PresentationParameters(const PresentationParameters& parameters)
            : full_screen        { parameters.full_screen }
            , back_buffer_height { parameters.back_buffer_height }
            , back_buffer_width  { parameters.back_buffer_width }
            , multi_sample_count { parameters.multi_sample_count }
            , present_interval   { parameters.present_interval }
        {
        }

        PresentationParameters::~PresentationParameters()
        {
        }

        PresentationParameters&PresentationParameters::operator=(const PresentationParameters& parameters)
        {
            if (this != &parameters)
            {
                full_screen        = parameters.full_screen;
                back_buffer_height = parameters.back_buffer_height;
                back_buffer_width  = parameters.back_buffer_width;
                multi_sample_count = parameters.multi_sample_count;
                present_interval   = parameters.present_interval;
            }

            return *this;
        }
    }
}
