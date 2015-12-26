// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_RENDERER_HPP
#define FRAMEWORK_RENDERER_HPP

#include <memory>
#include <string>
#include <vector>

#include <System/TimeSpan.hpp>
#include <Framework/IComponent.hpp>
#include <Framework/IDrawable.hpp>
#include <Framework/IUpdateable.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/RendererTimer.hpp>

namespace System
{
    namespace Graphics
    {
        class RenderContext;
    }
}

namespace SceneR
{
    namespace Content
    {
        class ContentManager;
    }

    namespace Graphics
    {
        class GraphicsDevice;
    }

    namespace Framework
    {
        class RendererWindow;
        class GraphicsDeviceManager;
        class RendererServiceContainer;

        /**
         * Provides basic graphics device initialization, and rendering code.
         */
        class Renderer
        {
        public:
            /**
             * Initializes a new instance of the Renderer class.
             */
            Renderer(const std::string& rootDirectory);

            /**
             * Releases all resources being used by the current renderer instance
             */
            virtual ~Renderer();

        public:
            /**
             * Gets the current graphics device
             * @return the current graphics device
             */
            SceneR::Graphics::GraphicsDevice* graphics_device() const noexcept;

            /**
             * Gets the underlying operating system window.
             * @return the underlying operating system window.
             */
            RendererWindow* window() const noexcept;

            /**
             * Gets the current content manager
             * @return the current content_manager manager
             */
            SceneR::Content::ContentManager* content_manager() const noexcept;

            /**
             * Gets the collection of services owned by the renderer.
             */
            RendererServiceContainer* services() const noexcept;

            /**
             * Gets the collection of components owned by the renderer.
             */
            std::vector<std::shared_ptr<IComponent>>& components() noexcept;

            /**
             * Call this method to initialize the renderer, begin running the rendering loop,
             * and start processing events.
             */
            virtual void run();

            /**
             * Exits the renderer.
             */
            virtual void exit();

        protected:
            /**
             * Starts the drawing of a frame. This method is followed by calls to draw and end_draw.
             */
            virtual bool begin_draw();

            /**
             * Called after all components are initialized but before the first update in the render loop.
             */
            virtual void begin_run();

            /**
             * Called when the renderer determines it is time to draw a frame.
             */
            virtual void draw(const RenderTime& renderTime);

            /**
             * Ends the drawing of a frame. This method is preceeded by calls to draw and begin_draw.
             */
            virtual void end_draw();

            /**
             * Called after the renderer loop has stopped running before exiting.
             */
            virtual void end_run();

            /**
             * Called after the Renderer and GraphicsDevice are created, but before load_content.
             */
            virtual void initialize();

            /**
             * Called when graphics resources need to be loaded.
             */
            virtual void load_content();

            /**
             * Called when graphics resources need to be unloaded.
             */
            virtual void unload_content();

            /**
             * Called when the renderer has determined that render logic needs to be processed.
             */
            virtual void update(const RenderTime& renderTime);

            /**
             * Updates the renderer's clock and calls update and draw.
             */
            void time_step();

        private:
            void post_process_components();
            void create_device();
            void fixed_time_step();
            void variable_time_step();
            void start_event_loop();

        private:
            Renderer() = delete;
            Renderer(const Renderer& renderer) = delete;
            Renderer& operator=(const Renderer& renderer) = delete;

        public:
            /**
             * Gets a value indicating whether to use fixed time steps.
             * A fixed-step Game tries to call its update method on the fixed interval specified in target_elapsed_time.
             * The default value is true.
             */
            bool is_fixed_time_step { true };

            /**
             * Gets or sets the target time between calls to update when is_fixed_time_step is true.
             */
            System::TimeSpan target_elapsed_time { 10000000L / 60L };

        protected:
            std::vector<std::shared_ptr<IComponent>>  _components              { };
            std::unique_ptr<RendererServiceContainer> _services                { nullptr};
            std::unique_ptr<GraphicsDeviceManager>    _graphics_device_manager { nullptr };

        private:
            bool                                             _is_running_slowly     { false };
            std::string                                      _root_directory        { };
            std::unique_ptr<SceneR::Content::ContentManager> _content_manager       { nullptr };
            std::vector<std::shared_ptr<IDrawable>>          _drawable_components   { };
            std::vector<std::shared_ptr<IUpdateable>>        _updateable_components { };
            RendererTimer                                    _timer                 { };
            RenderTime                                       _render_time           { };
            System::TimeSpan                                 _total_tender_time     { System::TimeSpan::zero };
            std::unique_ptr<System::Graphics::RenderContext> _render_context        { nullptr };
            std::unique_ptr<RendererWindow>                  _renderer_window       { nullptr };

            friend class RendererWindow;
        };
    }
}

#endif  // FRAMEWORK_RENDERER_HPP
