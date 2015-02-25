// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICSRESOURCE_HPP
#define GRAPHICSRESOURCE_HPP

#include <System/Core.hpp>
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
            virtual ~GraphicsResource();

        public:
            virtual void Dispose() = 0;

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
