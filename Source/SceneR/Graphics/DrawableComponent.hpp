// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_DRAWABLECOMPONENT_HPP
#define SCENER_GRAPHICS_DRAWABLECOMPONENT_HPP

#include <cstdint>

#include "SceneR/Graphics/IDrawable.hpp"
#include "SceneR/Graphics/Component.hpp"

namespace SceneR { namespace Graphics {

class  GraphicsDevice;
class  Renderer;
struct StepTime;

/**
 * A component that is notified when it needs to draw itself.
 */
class DrawableComponent : public Component, public IDrawable
{
public:
    /**
     * Initializes a new instance of the DrawableComponent class.
     */
    DrawableComponent(gsl::not_null<Renderer*> renderer) noexcept;

    /**
     * Releases all resources being used by this DrawableComponent.
     */
    ~DrawableComponent() override = default;

public:
    /**
     * The GraphicsDevice the DrawableComponent is associated with.
     */
    SceneR::Graphics::GraphicsDevice* graphics_device() noexcept;

    /**
     * Called when the component should be drawn.
     */
    void draw(const StepTime& renderTime) noexcept override;

    /**
     * Gets a value indicating whether this object is enabled.
     */
    bool visible() const noexcept override;

    /**
     * Sets a value indicating whether this object is enabled.
     * @param visible a value indicating whether this object is enabled.
     */
    virtual void visible(bool visible) noexcept;

    /**
     * The order in which to draw this object relative to other objects.
     */
    std::uint32_t draw_order() const noexcept override;

    /**
     * The order in which to draw this object relative to other objects.
     */
    void draw_order(std::uint32_t drawOrder) noexcept;

    /**
     * Called when the component should be initialized.
     * This method can be used for tasks like querying for
     * services the component needs and setting up non-graphics resources.
     */
    void initialize() noexcept override;

protected:
    virtual void load_content() noexcept;
    virtual void unload_content() noexcept;

private:
    bool          _visible    { true };
    std::uint32_t _draw_order { 0 };
};

}}

#endif // SCENER_GRAPHICS_DRAWABLECOMPONENT_HPP
