// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IUPDATEABLE_HPP
#define SCENER_GRAPHICS_IUPDATEABLE_HPP

#include <cstdint>

namespace SceneR { namespace Graphics {

struct StepTime;

/// Defines an interface for a component that should be updated in Renderer.update.
class IUpdateable
{
public:
    /// Virtual destructor.
    virtual ~IUpdateable() = default;

public:
    /// Gets a value indicating whether the component's Update method should be called.
    /// \returns true if Update should be called; false otherwise.
    virtual bool enabled() const noexcept = 0;

    /// Gets the order in which to update this object relative to other objects.
    /// \returns when the game component should be updated.
    virtual std::uint32_t update_order() const noexcept = 0;

    /// Called when the component should be updated.
    /// \param stepTime snapshot of the rendering timing state.
    virtual void update(const StepTime& stepTime) noexcept = 0;
};

}}

#endif // SCENER_GRAPHICS_IUPDATEABLE_HPP
