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

#ifndef RENDERERWINDOW_HPP
#define RENDERERWINDOW_HPP

#include <string>
#include "Core/Core.hpp"

namespace SceneR
{
    namespace Graphics
    {
        class Renderer;
        
        /**
         * The window associated with a renderer.
         */
        class RendererWindow        
        {
        public:
            /**
             * Initializes a new instance of the RendererWindow class
             * @param renderer the renderer that owns this RendererWindow instance
             */
            RendererWindow(Renderer& renderer);
            
            /**
             * Releases all resource being used by the current RendererWindow
             */
            ~RendererWindow();
            
        public:
            /**
             * Gets the window handle
             * @return the window handle
             */
            GLFWwindow* GetHandle() const;

            /**
             * Gets the renderer window title
             * @return the renderer window title
             */
            const std::wstring& GetTitle() const;
            
            /**
             * Sets the renderer window title
             * @param title the renderer window title
             */
            void SetTitle(const std::wstring& title);
            
            /**
             * Specifies whether to allow the user to resize the renderer window.
             * @return whether to allow the user to resize the renderer window.
             */
            const Boolean& GetAllowUserResizing() const;

            /**
             * Specifies whether to allow the user to resize the renderer window.
             */
            void SetAllowUserResizing(const Boolean &allowUserResizing);
                                    
        private:
            void Open();
            void Close();
            
        private:
            std::wstring title;
            Renderer&    renderer;
            Boolean      allowUserResizing;
            GLFWwindow*  window;
            
            friend class Renderer;
        };
    }
}

#endif  /* RENDERERWINDOW_HPP */
