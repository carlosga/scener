// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_DRAWABLE_COMPONENT_HPP
#define SCENER_GRAPHICS_DRAWABLE_COMPONENT_HPP

#include <cstdint>

#include "scener/graphics/idrawable.hpp"
#include "scener/graphics/component.hpp"

namespace scener::graphics
{
    class  graphics_device;
    class  renderer;
    struct steptime;

    /// A component that is notified when it needs to draw itself.
    class drawable_component : public component, public idrawable
    {
    public:
        /// Initializes a new instance of the DrawableComponent class.
        /// \param renderer the renderer that owns the component.
        drawable_component(gsl::not_null<graphics::renderer*> renderer) noexcept;

    public:
        /// The graphics device the drawable component is associated with.
        graphics_device* device() noexcept;

        /// Called when the component should be drawn.
        /// \param time time passed since the last call to Draw.
        void draw([[maybe_unused]] const steptime& time) noexcept override;

        /// Gets a value indicating whether Draw should be called.
        /// \returns true if Draw should be called; false otherwise.
        bool visible() const noexcept override;

        /// Sets a value indicating whether Draw should be called.
        /// @param visible a value indicating whether Draw should be called.
        virtual void visible(bool visible) noexcept;

        /// The order in which to draw this object relative to other objects.
        std::uint32_t draw_order() const noexcept override;

        /// The order in which to draw this object relative to other objects.
        /// \param order Order in which the component should be drawn.
        void draw_order(std::uint32_t order) noexcept;

        /// Called when the component should be initialized.
        /// This method can be used for tasks like querying for services
        /// the component needs and setting up non-graphics resources.
        void initialize() noexcept override;

    protected:
        virtual void load_content() noexcept;
        virtual void unload_content() noexcept;

    private:
        bool          _visible    { true };
        std::uint32_t _draw_order { 0 };
    };
}

#endif // SCENER_GRAPHICS_DRAWABLE_COMPONENT_HPP
