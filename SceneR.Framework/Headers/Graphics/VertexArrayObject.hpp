// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_VERTEXARRAYOBJECT_HPP
#define GRAPHICS_VERTEXARRAYOBJECT_HPP

#include <cstdint>

#include <System/IDisposable.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Represents an opengl vertex array object
         */
        class VertexArrayObject : System::IDisposable
        {
        public:
            /**
             * Initializes a new instance of the VertexArrayObject class.
             */
            VertexArrayObject();

            /**
             * Releases all resources being used by this VertexArrayObject.
             */
            ~VertexArrayObject();

        public:
            void dispose() override;

        public:
            /**
             * Gets the vertex array object identifier.
             */
            std::uint32_t id() const;

            /**
             * Activates this vertex array object.
             */
            void activate() const;

            /**
             * Creates the vertex array object.
             */
            void create();

            /**
             * Deactivates this vertex array object.
             */
            void deactivate() const;

        private:
            std::uint32_t _id;
        };
    }
}

#endif  // GRAPHICS_VERTEXARRAYOBJECT_HPP
