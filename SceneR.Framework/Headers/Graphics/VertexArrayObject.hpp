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
            VertexArrayObject() = default;

            /**
             * Releases all resources being used by this VertexArrayObject.
             */
            ~VertexArrayObject() = default;

        public:
            void dispose() override;

        public:
            /**
             * Gets the vertex array object identifier.
             */
            std::uint32_t id() const noexcept;

            /**
             * Activates this vertex array object.
             */
            void bind() const;

            /**
             * Creates the vertex array object.
             */
            void create();

            /**
             * Deactivates this vertex array object.
             */
            void unbind() const;

        private:
            std::uint32_t _id = 0;
        };
    }
}

#endif  // GRAPHICS_VERTEXARRAYOBJECT_HPP
