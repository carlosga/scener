// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <vector>

#include <System/TimeSpan.hpp>
#include <Content/ContentManager.hpp>
#include <Framework/IComponent.hpp>
#include <Framework/IDrawable.hpp>
#include <Framework/IUpdateable.hpp>
#include <Framework/GraphicsDeviceManager.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/RendererTimer.hpp>
#include <Framework/RendererWindow.hpp>
#include <Graphics/ShaderManager.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;
    }
}

namespace SceneR
{
    namespace Framework
    {
        /**
         * Provides basic graphics device initialization, and rendering code.
         */
        class Renderer
        {
        public:
            /**
             * Initializes a new instance of the Renderer class.
             */
            Renderer(const std::u16string& rootDirectory);

            /**
             * Releases all resources being used by the current renderer instance
             */
            virtual ~Renderer();

        public:
            /**
             * Gets the current graphics device
             * @return the current graphics device
             */
            SceneR::Graphics::GraphicsDevice& CurrentGraphicsDevice();

            /**
             * Gets the underlying operating system window.
             * @return the underlying operating system window.
             */
            RendererWindow& Window();

            /**
             * Gets the current content manager
             * @return the current content manager
             */
            SceneR::Content::ContentManager& Content();

            /**
             * Gets the collection of components owned by the renderer.
             */
            std::vector<std::shared_ptr<IComponent>>& Components();

            /**
             * Gets the collection of services owned by the renderer.
             */
            RendererServiceContainer& Services();

            /**
             * Call this method to initialize the renderer, begin running the rendering loop,
             * and start processing events.
             */
            virtual void Run();

            /**
             * Exits the renderer.
             */
            virtual void Exit();

        protected:
            /**
             * Starts the drawing of a frame. This method is followed by calls to Draw and EndDraw.
             */
            virtual bool BeginDraw();

            /**
             * Called after all components are initialized but before the first update in the render loop.
             */
            virtual void BeginRun();

            /**
             * Called when the renderer determines it is time to draw a frame.
             */
            virtual void Draw(const RenderTime& renderTime);

            /**
             * Ends the drawing of a frame. This method is preceeded by calls to Draw and BeginDraw.
             */
            virtual void EndDraw();

            /**
             * Called after the renderer loop has stopped running before exiting.
             */
            virtual void EndRun();

            /**
             * Called after the Renderer and GraphicsDevice are created, but before LoadContent.
             */
            virtual void Initialize();

            /**
             * Gets a value indicating whether to use fixed time steps.
             * A fixed-step Game tries to call its Update method on the fixed interval specified in TargetElapsedTime.
             * The default value is true.
             */
            virtual bool IsFixedTimeStep() const;

            /**
             * Gets a value indicating whether to use fixed time steps.
             * A fixed-step Game tries to call its Update method on the fixed interval specified in TargetElapsedTime.
             * The default value is true.
             */
            virtual void IsFixedTimeStep(const bool& isFixedTimeStep);

            /**
             * Called when graphics resources need to be loaded.
             */
            virtual void LoadContent();

            /**
             * Gets the target time between calls to Update when IsFixedTimeStep is true.
             */
            virtual const System::TimeSpan& TargetElapsedTime() const;

            /**
             * Gets the target time between calls to Update when IsFixedTimeStep is true.
             */
            virtual void TargetElapsedTime(const System::TimeSpan& targetElapsedTime);

            /**
             * Called when graphics resources need to be unloaded.
             */
            virtual void UnloadContent();

            /**
             * Called when the renderer has determined that render logic needs to be processed.
             */
            virtual void Update(const RenderTime& renderTime);

            /**
             * Updates the renderer's clock and calls Update and Draw.
             */
            void TimeStep();

        private:
            void PostProcessComponents();
            void CreateDevice();
            void FixedTimeStep();
            void VariableTimeStep();
            void StartEventLoop();

        private:
            Renderer() = delete;
            Renderer(const Renderer& renderer) = delete;
            Renderer& operator=(const Renderer& renderer) = delete;

        protected:
            std::vector<std::shared_ptr<IComponent>>  components;
            RendererServiceContainer                  services;
            GraphicsDeviceManager                     graphicsDeviceManager;

        private:
            RendererWindow                            rendererWindow;
            SceneR::Content::ContentManager           contentManager;
            SceneR::Graphics::ShaderManager           shaderManager;
            bool                                      isFixedTimeStep;
            System::TimeSpan                          targetElapsedTime;
            RendererTimer                             timer;
            RenderTime                                renderTime;
            System::TimeSpan                          totalRenderTime;
            bool                                      isRunningSlowly;
            std::vector<std::shared_ptr<IDrawable>>   drawableComponents;
            std::vector<std::shared_ptr<IUpdateable>> updateableComponents;

            friend class RendererWindow;
        };
    }
}

#endif  /* RENDERER_HPP */
