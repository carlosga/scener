// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_DEPTH_STENCIL_STATE_HPP
#define SCENER_GRAPHICS_DEPTH_STENCIL_STATE_HPP

#include <cstdint>

#include "scener/graphics/compare_function.hpp"
#include "scener/graphics/stencil_operation.hpp"

namespace scener::graphics
{
    /// Contains depth-stencil state for the graphics device
    class depth_stencil_state final
    {
    public:
        static const depth_stencil_state default_stencil;
        static const depth_stencil_state depth_read;
        static const depth_stencil_state none;

    public:
        depth_stencil_state() = default;

    public:
        /// Gets or sets the stencil operation to perform if the stencil test passes and the depth-buffer
        /// test fails for a counterclockwise triangle.
        stencil_operation counter_clockwise_stencil_depth_buffer_fail { stencil_operation::keep };

        /// Gets or sets the stencil operation to perform if the stencil test fails for a counterclockwise triangle.
        stencil_operation counter_clockwise_stencil_fail { stencil_operation::keep };

        /// Gets or sets the comparison function to use for counterclockwise stencil tests.
        compare_function counter_clockwise_stencil_function { compare_function::always };

        /// Gets or sets the stencil operation to perform if the stencil and depth-tests pass for a
        /// counterclockwise triangle.
        stencil_operation counter_clockwise_stencil_pass { stencil_operation::keep };

        /// Gets or sets a value indicating where depth buffer is enabled
        bool depth_buffer_enable { true };

        /// Gets or sets the comparison function for the depth-buffer test. The default is CompareFunction.Less
        compare_function depth_buffer_function { compare_function::less };

        /// Gets or sets a value indicating whether writing to the depth buffer is allowed. The default is true.
        bool depth_buffer_write_enable { true };

        /// Gets or sets a reference value to use for the stencil test.
        std::uint32_t reference_stencil { 0 };

        /// Gets or sets the stencil operation to perform if the stencil test passes and the depth-test fails.
        stencil_operation stencil_depth_buffer_fail { stencil_operation::keep };

        /// Enables or disables the stencil test.
        bool stencil_enable { false };

        /// Gets or sets the stencil operation to perform if the stencil test fails.
        stencil_operation stencil_fail { stencil_operation::keep };

        /// Gets or sets the comparison function for the stencil test.
        compare_function stencil_function { compare_function::always };

        /// Gets or sets the mask applied to the reference value and each stencil buffer entry to determine the
        /// significant bits for the stencil test.
        std::uint32_t stencil_mask { 0 };

        /// Gets or sets the stencil operation to perform if the stencil test passes
        stencil_operation stencil_pass { stencil_operation::keep };

        /// Gets or sets the write mask applied to values written into the stencil buffer.
        std::uint32_t stencil_write_mask { 0 };

        /// Enables or disables two-sided stenciling.
        bool two_sided_stencil_mode { false };

    private:
        depth_stencil_state(bool depth_buffer_enabled, bool depth_buffer_write_enabled) noexcept;
    };
}

#endif // SCENER_GRAPHICS_DEPTH_STENCIL_STATE_HPP
