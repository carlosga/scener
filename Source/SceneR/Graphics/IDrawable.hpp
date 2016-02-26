// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IDRAWABLE_HPP
#define SCENER_GRAPHICS_IDRAWABLE_HPP

#include <cstdint>

namespace scener { namespace graphics {

struct StepTime;

/// Defines the interface for a drawable game component.
class IDrawable
{
public:
    /// Virtual destructor.
    virtual ~IDrawable() = default;

public:
    /// Gets a value indicating whether this object is visible.
    virtual bool visible() const noexcept = 0;

    /// The order in which to draw this object relative to other objects.
    /// \returns the order in which to draw this object relative to other objects.
    virtual std::uint32_t draw_order() const noexcept = 0;

    /// Called when the component should be drawn.
    /// \param stepTime snapshot of the rendering timing state.
    virtual void draw(const StepTime& stepTime) noexcept = 0;
};

}}

#endif // SCENER_GRAPHICS_IDRAWABLE_HPP
