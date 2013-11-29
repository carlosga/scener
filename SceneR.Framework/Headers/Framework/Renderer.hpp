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

#include <Content/ContentManager.hpp>
#include <System/Core.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Framework/GraphicsDeviceManager.hpp>
#include <Framework/RendererTimer.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/RendererWindow.hpp>
#include <memory>
#include <vector>

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
        class IComponent;
        class RenderTime;

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
            SceneR::Graphics::GraphicsDevice& GetGraphicsDevice();

            /**
             * Gets the underlying operating system window.
             * @return the underlying operating system window.
             */
            RendererWindow& GetRendererWindow();

            /**
             * Gets the current content manager
             * @return the current content manager
             */
            SceneR::Content::ContentManager& GetContentManager();

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
             * Allows a Renderer to attempt to free resources and perform other
             * cleanup operations before garbage collection reclaims the Renderer.
             */
            virtual void Finalize();

            /**
             * Called after the Renderer and GraphicsDevice are created, but before LoadContent.
             */
            virtual void Initialize();

            /**
             * Called when graphics resources need to be loaded.
             */
            virtual void LoadContent();

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
            void Tick();

        private:
            void StartEventLoop();

        protected:
            std::vector<std::shared_ptr<IComponent>> components;
            RendererServiceContainer                 services;
            GraphicsDeviceManager                    graphicsDeviceManager;
            RendererWindow                           rendererWindow;
            SceneR::Content::ContentManager          contentManager;
            RendererTimer                            timer;
            RenderTime                               renderTime;
            System::Duration                         totalRenderTime;
        };
    }
}

#endif  /* RENDERER_HPP */
