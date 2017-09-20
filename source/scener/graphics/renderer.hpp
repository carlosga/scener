// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_RENDERER_HPP
#define SCENER_GRAPHICS_RENDERER_HPP

#include <memory>
#include <string>
#include <vector>

#include "scener/content/content_manager.hpp"
#include "scener/graphics/icomponent.hpp"
#include "scener/graphics/idrawable.hpp"
#include "scener/graphics/iupdateable.hpp"
#include "scener/graphics/presentation_parameters.hpp"
#include "scener/graphics/service_container.hpp"
#include "scener/graphics/steptime.hpp"
#include "scener/graphics/steptimer.hpp"

namespace scener::graphics
{
    class graphics_device;
    class graphics_device_manager;
    class window;

    /// Provides basic graphics device initialization, and rendering code.
    class renderer
    {
    public:
        /// Initializes a new instance of the renderer class.
        /// \param root_directory the root directory to search for content.
        renderer(const std::string& root_directory) noexcept;

        /// Releases all resources being used by the current renderer instance
        virtual ~renderer();

    public:
        /// Gets the current graphics device.
        /// \returns the current graphics device.
        graphics_device* device() const noexcept;

        /// Gets the underlying operating system window.
        /// \returns the underlying operating system window.
        graphics::window* window() const noexcept;

        /// Gets the current content manager
        /// \returns the current content_manager manager
        content::content_manager* content_manager() const noexcept;

        /// Gets the collection of services owned by the renderer.
        /// \returns the collection of services owned by the renderer.
        service_container* services() const noexcept;

        /// Gets the collection of components owned by the renderer.
        /// \returns the collection of components owned by the renderer.
        std::vector<std::shared_ptr<icomponent>>& components() noexcept;

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
        virtual void draw(const steptime& time) noexcept;

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
        virtual void update(const steptime& time) noexcept;

        /// Called when the graphics_device_manager is changing the graphics_device settings
        /// (during reset or recreation of the GraphicsDevice).
        virtual void prepare_device_settings(presentation_parameters*) const noexcept;

        /// Updates the renderer's clock and calls update and draw.
        void time_step() noexcept;

    private:
        void create_device() noexcept;
        void post_process_components() noexcept;
        void fixed_time_step() noexcept;
        void variable_time_step() noexcept;
        void start_event_loop() noexcept;

    private:
        renderer() = delete;
        renderer(const renderer& renderer) = delete;
        renderer& operator=(const renderer& renderer) = delete;

    public:
        /// Gets or sets a value indicating whether to use fixed time steps.
        /// A fixed-step Game tries to call its update method on the fixed interval specified in target_elapsed_time.
        /// The default value is true.
        bool is_fixed_time_step { true };

        /// Gets or sets the target time between calls to update when is_fixed_time_step is true.
        scener::timespan target_elapsed_time { 10000000L / 60L };

    protected:
        graphics_device_manager* device_manager() const;
        void add_component(std::shared_ptr<icomponent> component);

    private:
        std::unique_ptr<graphics::window>         _window                { nullptr };
        std::unique_ptr<content::content_manager> _content_manager       { nullptr };
        std::unique_ptr<graphics_device_manager>  _device_manager        { nullptr };
        std::vector<std::shared_ptr<idrawable>>   _drawable_components   { };
        std::vector<std::shared_ptr<iupdateable>> _updateable_components { };
        std::vector<std::shared_ptr<icomponent>>  _components            { };
        std::unique_ptr<service_container>        _services              { nullptr };
        steptimer                                 _timer                 { };
        steptime                                  _time                  { };
        scener::timespan                          _total_tender_time     { timespan::zero() };
        bool                                      _is_running_slowly     { false };
        std::string                               _root_directory        { };

        friend class window;
    };
}

#endif // SCENER_GRAPHICS_RENDERER_HPP
