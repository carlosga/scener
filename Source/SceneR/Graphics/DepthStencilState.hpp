// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_DEPTHSTENCILSTATE_HPP
#define SCENER_GRAPHICS_DEPTHSTENCILSTATE_HPP

#include <cstdint>

#include "SceneR/Graphics/CompareFunction.hpp"
#include "SceneR/Graphics/StencilOperation.hpp"
#include "SceneR/Graphics/GraphicsResource.hpp"

namespace SceneR { namespace Graphics {

class GraphicsDevice;
class GraphicsDeviceManager;

/// Contains depth-stencil state for the graphics device
class DepthStencilState : GraphicsResource
{
public:
    /// Initializes a new instance of the DepthStencilState class with the given GraphcisDevice
    /// \param graphicsDevice
    DepthStencilState(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept;

public:
    /// Gets or sets the stencil operation to perform if the stencil test passes and the depth-buffer
    /// test fails for a counterclockwise triangle.
    StencilOperation counter_clockwise_stencil_depth_buffer_fail { StencilOperation::keep };

    /// Gets or sets the stencil operation to perform if the stencil test fails for a counterclockwise triangle.
    StencilOperation counter_clockwise_stencil_fail { StencilOperation::keep };

    /// Gets or sets the comparison function to use for counterclockwise stencil tests.
    CompareFunction counter_clockwise_stencil_function { CompareFunction::always };

    /// Gets or sets the stencil operation to perform if the stencil and depth-tests pass for a
    /// counterclockwise triangle.
    StencilOperation counter_clockwise_stencil_pass { StencilOperation::keep };

    /// Gets or sets a value indicating where depth buffer is enabled
    bool depth_buffer_enable { true };

    /// Gets or sets the comparison function for the depth-buffer test. The default is CompareFunction.Less
    CompareFunction depth_buffer_function { CompareFunction::less };

    /// Gets or sets a value indicating whether writing to the depth buffer is allowed. The default is true.
    bool depth_buffer_write_enable { true };

    /// Gets or sets a reference value to use for the stencil test.
    std::int32_t reference_stencil { 0 };

    /// Gets or sets the stencil operation to perform if the stencil test passes and the depth-test fails.
    StencilOperation stencil_depth_buffer_fail { StencilOperation::keep };

    /// Enables or disables the stencil test.
    bool stencil_enable { false };

    /// Gets or sets the stencil operation to perform if the stencil test fails.
    StencilOperation stencil_fail { StencilOperation::keep };

    /// Gets or sets the comparison function for the stencil test.
    CompareFunction stencil_function { CompareFunction::always };

    /// Gets or sets the mask applied to the reference value and each stencil buffer entry to determine the
    /// significant bits for the stencil test.
    std::uint32_t stencil_mask { 0 };

    /// Gets or sets the stencil operation to perform if the stencil test passes
    StencilOperation stencil_pass { StencilOperation::keep };

    /// Gets or sets the write mask applied to values written into the stencil buffer.
    std::uint32_t stencil_write_mask { 0 };

    /// Enables or disables two-sided stenciling.
    bool two_sided_stencil_mode { false };

private:
    void apply() const noexcept;

    friend class GraphicsDeviceManager;
};

}}

#endif // SCENER_GRAPHICS_DEPTHSTENCILSTATE_HPP
