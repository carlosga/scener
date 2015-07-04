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
            void Dispose() override = 0;

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
            const std::u16string& Name() const;

            /**
             * Sets the graphics resource name
             * @param name the new graphics resource name
             */
            void Name(const std::u16string& name);

            /**
             * Gets the graphics resource identifier
             * @return the graphics resource identifier
             */
            const std::u16string& Tag() const;

            /**
             * Sets the graphics resource tag
             * @param tag the graphics resource tag
             */
            void Tag(const std::u16string& tag);

        protected:
            GraphicsDevice& graphicsDevice;
            std::u16string  name;
            std::u16string  tag;
        };
    }
}

#endif  /* GRAPHICSRESOURCE_HPP */
