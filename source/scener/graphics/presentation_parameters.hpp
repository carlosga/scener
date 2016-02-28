// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_PRESENTATIONPARAMETERS_HPP
#define SCENER_GRAPHICS_PRESENTATIONPARAMETERS_HPP

#include <cstddef>
#include <cstdint>

#include "scener/graphics/present_interval.hpp"

namespace scener { namespace graphics {

/// Contains presentation parameters.
/// http://msdn.microsoft.com/en-us/library/windows/desktop/ms885051.aspx
class presentation_parameters final
{
public:
    /// Initializes a new instance of the PresentationParameters class.
    presentation_parameters() noexcept;

public:
    /// Gets or sets a value indicating whether an application is running in a full screen mode.
    bool full_screen;

    /// Gets or sets the height of a swap chain's back buffers, in pixels.
    std::size_t back_buffer_height;

    /// Gets or sets the width of a swap chain's back buffers, in pixels.
    std::size_t back_buffer_width;

    /// Gets or sets the number of sample locations during multisampling.
    std::uint32_t multi_sample_count;

    /// Gets or sets the swap buffer interval.
    graphics::present_interval present_interval;
};

}}

#endif // SCENER_GRAPHICS_PRESENTATIONPARAMETERS_HPP
