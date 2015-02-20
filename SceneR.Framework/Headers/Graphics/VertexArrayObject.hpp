// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VERTEXARRAYOBJECT_HPP
#define VERTEXARRAYOBJECT_HPP

#include <System/Core.hpp>
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
            virtual ~VertexArrayObject() = default;

        public:
            virtual void Dispose() override;

        public:
            /**
             * Gets the vertex array object identifier.
             */
            const System::UInt32& Id() const;

            /**
             * Activates this vertex array object.
             */
            void Activate() const;

            /**
             * Deactivates this vertex array object.
             */
            void Deactivate() const;

        private:
            void Create();

        private:
            System::UInt32 id;
        };
    }
}

#endif /* VERTEXARRAYOBJECT_HPP */
