// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICSRESOURCE_HPP
#define GRAPHICSRESOURCE_HPP

#include <string>

#include <System/IDisposable.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;

        /**
         * Queries and prepares resources.
         */
        class GraphicsResource : System::IDisposable
        {
        public:
            /**
             * Initializes a new instance of the GraphicsResource class
             * @param graphicsDevice the graphics associated to this resources
             */
            GraphicsResource(GraphicsDevice& graphicsDevice);

            /**
             * Destructor
             */
            ~GraphicsResource() override;

        public:
            void dispose() override = 0;

        public:
            /**
             * Gets the graphics associated to this resources
             * @return the graphics associated to this resources
             */
            GraphicsDevice& graphics_device() const;

        public:
            std::u16string name;
            std::u16string tag;

        protected:
            GraphicsDevice& _graphics_device;
        };
    }
}

#endif  /* GRAPHICSRESOURCE_HPP */
