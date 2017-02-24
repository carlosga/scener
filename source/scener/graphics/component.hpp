// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_COMPONENT_HPP
#define SCENER_GRAPHICS_COMPONENT_HPP

#include <cstdint>

#include <gsl/gsl>

#include "scener/graphics/icomponent.hpp"
#include "scener/graphics/iupdateable.hpp"

namespace scener { namespace graphics {

class  renderer;
struct steptime;

/// Base class for all components.
class component : public icomponent, public iupdateable
{
public:
    /// Initializes a new instance of the Component class.
    /// \param renderer the renderer that owns the component.
    component(gsl::not_null<renderer*> renderer) noexcept;

    /// Releases all resources being used by this component instance.
    ~component() override = default;

public:
    /// Gets the Renderer associated with this Component.
    /// \returns a pointer to the Renderer instance associated with this Component.
    graphics::renderer* renderer() noexcept;

    /// Called when the component should be updated.
    void update(const steptime& time) noexcept override;

    /// Gets a value indicating whether the component is enabled.
    /// \returns true if the component is enabled; false otherwise.
    bool enabled() const noexcept override;

    /// Sets a value indicating whether the component is enabled.
    /// \param enabled true if Component.Update should be called; false otherwise.
    void enabled(bool enabled) noexcept;

    /// Gets the order in which to update this object relative to other objects.
    /// \returns the order in which to update this object relative to other objects.
    std::uint32_t update_order() const noexcept override;

    /// Sets the order in which to update this object relative to other objects.
    /// \param order the order in which to update this object relative to other objects.
    void update_order(std::uint32_t order) noexcept;

protected:
    graphics::renderer* _renderer = nullptr;

private:
    bool          _enabled      = true;
    std::uint32_t _update_order = 0;
};

}}

#endif // SCENER_GRAPHICS_COMPONENT_HPP
