// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_RENDERER_HPP
#define SCENER_GRAPHICS_RENDERER_HPP

#include <memory>
#include <string>
#include <vector>

#include "scener/graphics/IComponent.hpp"
#include "scener/graphics/IDrawable.hpp"
#include "scener/graphics/IUpdateable.hpp"
#include "scener/graphics/StepTime.hpp"
#include "scener/graphics/StepTimer.hpp"

namespace scener { namespace content { class content_manager; } }

namespace scener { namespace graphics { namespace opengl { class RenderContext; } } }

namespace scener { namespace graphics {

class GraphicsDevice;
class GraphicsDeviceManager;
class RendererServiceContainer;
class RendererWindow;

/// Provides basic graphics device initialization, and rendering code.
class Renderer
{
public:
    /// Initializes a new instance of the Renderer class.
    /// \param rootDirectory the root directory to search for content.
    Renderer(const std::string& rootDirectory) noexcept;

    /// Releases all resources being used by the current renderer instance
    virtual ~Renderer();

public:
    /// Gets the current graphics device
    /// \returns the current graphics device
    GraphicsDevice* graphics_device() const noexcept;

    /// Gets the underlying operating system window.
    /// \returns the underlying operating system window.
    RendererWindow* window() const noexcept;

    /// Gets the current content manager
    /// \returns the current content_manager manager
    content::content_manager* content_manager() const noexcept;

    /// Gets the collection of services owned by the renderer.
    /// \returns the collection of services owned by the renderer.
    RendererServiceContainer* services() const noexcept;

    /// Gets the collection of components owned by the renderer.
    /// \returns the collection of components owned by the renderer.
    std::vector<std::shared_ptr<IComponent>>& components() noexcept;

    /// Call this method to initialize the renderer, begin running the rendering loop, and start processing events.
    virtual void run() noexcept;

    /// Exits the renderer.
    virtual void exit() noexcept;

protected:
    /// Starts the drawing of a frame. This method is followed by calls to draw and end_draw.
    virtual bool begin_draw() noexcept;

    /// Called after all components are initialized but before the first update in the render loop.
    virtual void begin_run() noexcept;

    /// Called when the renderer determines it is time to draw a frame.
    virtual void draw(const StepTime& renderTime) noexcept;

    /// Ends the drawing of a frame. This method is preceeded by calls to draw and begin_draw.
    virtual void end_draw() noexcept;

    /// Called after the renderer loop has stopped running before exiting.
    virtual void end_run() noexcept;

    /// Called after the Renderer and GraphicsDevice are created, but before load_content.
    virtual void initialize() noexcept;

    /// Called when graphics resources need to be loaded.
    virtual void load_content() noexcept;

    /// Called when graphics resources need to be unloaded.
    virtual void unload_content() noexcept;

    /// Called when the renderer has determined that render logic needs to be processed.
    virtual void update(const StepTime& renderTime) noexcept;

    /// Updates the renderer's clock and calls update and draw.
    void time_step() noexcept;

private:
    void post_process_components() noexcept;
    void create_device() noexcept;
    void fixed_time_step() noexcept;
    void variable_time_step() noexcept;
    void start_event_loop() noexcept;

private:
    Renderer() = delete;
    Renderer(const Renderer& renderer) = delete;
    Renderer& operator=(const Renderer& renderer) = delete;

public:
    /// Gets or sets a value indicating whether to use fixed time steps.
    /// A fixed-step Game tries to call its update method on the fixed interval specified in target_elapsed_time.
    /// The default value is true.
    bool is_fixed_time_step { true };

    /// Gets or sets the target time between calls to update when is_fixed_time_step is true.
    scener::timespan target_elapsed_time { 10000000L / 60L };

protected:
    GraphicsDeviceManager* graphics_device_manager() const;
    void add_component(std::shared_ptr<IComponent> component);

private:
    std::unique_ptr<RendererWindow>                          _renderer_window         { nullptr };
    std::unique_ptr<scener::graphics::opengl::RenderContext> _render_context          { nullptr };
    std::unique_ptr<scener::content::content_manager>         _content_manager         { nullptr };
    std::unique_ptr<GraphicsDeviceManager>                   _graphics_device_manager { nullptr };
    std::vector<std::shared_ptr<IDrawable>>                  _drawable_components     { };
    std::vector<std::shared_ptr<IUpdateable>>                _updateable_components   { };
    std::vector<std::shared_ptr<IComponent>>                 _components              { };
    std::unique_ptr<RendererServiceContainer>                _services                { nullptr };
    StepTimer                                                _timer                   { };
    StepTime                                                 _render_time             { };
    scener::timespan                                         _total_tender_time       { timespan::zero() };
    bool                                                     _is_running_slowly       { false };
    std::string                                              _root_directory          { };

    friend class RendererWindow;
};

}}

#endif // SCENER_GRAPHICS_RENDERER_HPP
