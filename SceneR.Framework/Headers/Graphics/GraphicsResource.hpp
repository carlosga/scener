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

#include <System/Core.hpp>

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
            virtual ~GraphicsResource() = default;

        public:
            /**
             * Gets the graphics associated to this resources
             * @return the graphics associated to this resources
             */
            GraphicsDevice& CurrentGraphicsDevice();

            /**
             * Gets the graphics resource name
             * @return the graphics resource name
             */
            const System::String& Name() const;

            /**
             * Sets the graphics resource name
             * @param name the new graphics resource name
             */
            void Name(const System::String& name);

            /**
             * Gets the graphics resource identifier
             * @return the graphics resource identifier
             */
            const System::String& Tag() const;

            /**
             * Sets the graphics resource tag
             * @param tag the graphics resource tag
             */
            void Tag(const System::String& tag);

        protected:
            GraphicsDevice& graphicsDevice;
            System::String  name;
            System::String  tag;
        };
    }
}

#endif  /* GRAPHICSRESOURCE_HPP */
