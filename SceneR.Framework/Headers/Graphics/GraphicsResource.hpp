// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_GRAPHICSRESOURCE_HPP
#define GRAPHICS_GRAPHICSRESOURCE_HPP

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
             * Gets the GraphicsDevice associated with this GraphicsResource.
             * @return The GraphicsDevice associated with this GraphicsResource.
             */
            GraphicsDevice& graphics_device() const;

        public:
            /**
             * Gets or sets the name of the resource.
             */
            std::u16string name;

        protected:
            GraphicsDevice& _graphics_device;
        };
    }
}

#endif  // GRAPHICS_GRAPHICSRESOURCE_HPP
