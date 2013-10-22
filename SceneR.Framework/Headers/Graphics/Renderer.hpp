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

#include <string>
#include <Core/Core.hpp>
#include "Content/ContentManager.hpp"
#include "Graphics/GraphicsDeviceManager.hpp"
#include "Graphics/RendererWindow.hpp"

namespace SceneR
{
    namespace Graphics
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
            Renderer(const std::string& rootDirectory);
            
            /**
             * Releases all resources being used by the current renderer instance
             */
            virtual ~Renderer();
            
        public:
            /**
             * Call this method to initialize the renderer, begin running the rendering loop, 
             * and start processing events.
             */
            void Run();
            
            /**
             * Exits the renderer.
             */
            void Exit();
            
            /**
             * Gets the current graphics device
             * @return the current graphics device
             */
            GraphicsDevice& GetGraphicsDevice();
            
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
            virtual void Draw(/*GameTime gameTime*/);

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
            virtual void Update(/*GameTime gameTime*/);            

        private:
            void StartEventLoop();
            
        private:
            GraphicsDeviceManager           graphicsDeviceManager;
            SceneR::Content::ContentManager contentManager;
            RendererWindow                  rendererWindow;
        };
    }
}

#endif  /* RENDERER_HPP */
