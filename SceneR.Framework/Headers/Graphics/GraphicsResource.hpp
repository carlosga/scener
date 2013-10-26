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

#ifndef GRAPHICSRESOURCE_HPP
#define GRAPHICSRESOURCE_HPP

#include <memory>
#include <string>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;

        /**
         * Queries and prepares resources.
         */
        class GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the GraphicsResource class
             * @param graphicsDevice the graphics associated to this resources
             */
            GraphicsResource(GraphicsDevice& graphicsDevice);

            /**
             * Releases all resources being used by this GraphicsResource
             */
            ~GraphicsResource();

        public:
            /**
             * Gets the graphics associated to this resources
             * @return the graphics associated to this resources
             */
            GraphicsDevice& GetGraphicsDevice();

            /**
             * Gets the graphics resource name
             * @return the graphics resource name
             */
            const std::wstring& GetName() const;

            /**
             * Sets the graphics resource name
             * @param name the new graphics resource name
             */
            void SetName(const std::wstring& name);

            /**
             * Gets the graphics resource identifier
             * @return the graphics resource identifier
             */
            const std::wstring& GetTag() const;

            /**
             * Sets the graphics resource tag
             * @param tag the graphics resource tag
             */
            void SetTag(const std::wstring& tag);

        protected:
            GraphicsDevice& graphicsDevice;
            std::wstring    name;
            std::wstring    tag;
        };
    }
}

#endif  /* GRAPHICSRESOURCE_HPP */
