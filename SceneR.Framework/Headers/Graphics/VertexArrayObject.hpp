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

#ifndef VERTEXARRAYOBJECT_HPP
#define VERTEXARRAYOBJECT_HPP

#include <GL/glew.h>
#include <Graphics/VertexElementFormat.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class BufferObject;
        class VertexDeclaration;

        /**
         * Represents an opengl vertex array object
         */
        class VertexArrayObject
        {
        public:
            /**
             * Initializes a new instance of the VertexArrayObject class.
             */
            VertexArrayObject();

            /**
             * Releases all resources being used by this VertexArrayObject.
             */
            virtual ~VertexArrayObject();

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

            /**
             * Deletes this vertex array object.
             */
            void Delete();

            /**
             * Declares the vertex format to be used on drawing operations.
             */
            void DeclareVertexFormat(const BufferObject& vbo, const VertexDeclaration& vDecl) const;

            /**
             * Activates the vertex format to be used on drawing operations.
             */
            void ActivateVertexFormat(const BufferObject& vbo, const VertexDeclaration& vDecl) const;

            /**
             * Deactivates the vertex format to be used on drawing operations.
             */
            void DeactivateVertexFormat(const VertexDeclaration& vDecl) const;

        private:
            void Create();
            GLenum GetElementType(const VertexElementFormat& vertexFormat) const;
            System::UInt32 GetElementCount(const VertexElementFormat& vertexFormat) const;

        private:
            System::UInt32 id;
        };
    }
}

#endif /* VERTEXARRAYOBJECT_HPP */
