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
            VertexArrayObject();
            virtual ~VertexArrayObject();

        public:
            const System::UInt32& Id() const;
            void Activate() const;
            void Deactivate() const;
            void Delete();
            void ActivateVertexFormat(const BufferObject& vbo, const VertexDeclaration& vDecl) const;
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
