//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <vector>

#include <Content/ContentManager.hpp>
#include <Framework/GraphicsDeviceManager.hpp>
#include <Framework/IComponent.hpp>
#include <Framework/IDrawable.hpp>
#include <Framework/IUpdateable.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Framework/RendererTimer.hpp>
#include <Framework/RendererWindow.hpp>
#include <Framework/RenderTime.hpp>
#include <System/TimeSpan.hpp>
#include <System/Core.hpp>

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
            Renderer(const System::String& rootDirectory);

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
            virtual const System::Boolean& IsFixedTimeStep() const;

            /**
             * Gets a value indicating whether to use fixed time steps.
             * A fixed-step Game tries to call its Update method on the fixed interval specified in TargetElapsedTime.
             * The default value is true.
             */
            virtual void IsFixedTimeStep(const System::Boolean& isFixedTimeStep);

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
            System::Boolean                           isFixedTimeStep;
            System::TimeSpan                          targetElapsedTime;
            RendererTimer                             timer;
            RenderTime                                renderTime;
            System::TimeSpan                          totalRenderTime;
            System::Boolean                           isRunningSlowly;
            std::vector<std::shared_ptr<IDrawable>>   drawableComponents;
            std::vector<std::shared_ptr<IUpdateable>> updateableComponents;

            friend class RendererWindow;
        };
    }
}

#endif  /* RENDERER_HPP */
