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

#include <Graphics/VertexArrayObject.hpp>
#include <Graphics/VertexDeclaration.hpp>
#include <Graphics/VertexElement.hpp>
#include <Graphics/VertexElementFormat.hpp>

using namespace System;
using namespace SceneR::Graphics;

VertexArrayObject::VertexArrayObject()
    : id(0)
{
    this->Create();
}

VertexArrayObject::~VertexArrayObject()
{
}

const UInt32& VertexArrayObject::Id() const
{
    return this->id;
}

void VertexArrayObject::Create()
{
    glGenVertexArrays(1, &this->id);
}

void VertexArrayObject::Activate() const
{
    glBindVertexArray(this->id);
}

void VertexArrayObject::Deactivate() const
{
    if (this->id != 0)
    {
        glBindVertexArray(0);
    }
}

void VertexArrayObject::Delete()
{
    if (this->id != 0)
    {
        this->Deactivate();
        glDeleteVertexArrays(1, &this->id);
        this->id = 0;
    }
}

void VertexArrayObject::DeclareVertexFormat(const VertexDeclaration& vDecl) const
{
    System::UInt32 usageIndex = 0;

    // Activate the vertex array object...
    this->Activate();

    // ... declare vertex elements
    for (const VertexElement& ve : vDecl.VertexElements())
    {
        glVertexAttribFormat(usageIndex,
                             this->GetComponentCount(ve.VertexElementFormat()),
                             this->GetComponentType(ve.VertexElementFormat()),
                             false,
                             ve.Offset());

        glVertexAttribBinding(usageIndex, 0);
        glEnableVertexAttribArray(usageIndex++);
    }

    // ... and finally deactivate the vertex array object
    this->Deactivate();
}

GLenum VertexArrayObject::GetComponentType(const VertexElementFormat& vertexFormat) const
{
    switch (vertexFormat)
    {
        case VertexElementFormat::Single:
            return GL_FLOAT;

        case VertexElementFormat::Vector2:
            return GL_FLOAT;

        case VertexElementFormat::Short2:
        case VertexElementFormat::NormalizedShort2:
        case VertexElementFormat::HalfVector2:
            return GL_UNSIGNED_SHORT;

        case VertexElementFormat::Vector3:
            return GL_FLOAT;

        case VertexElementFormat::Vector4:
        case VertexElementFormat::Color:
            return GL_FLOAT;

        case VertexElementFormat::Byte4:
            return GL_UNSIGNED_BYTE;

        case VertexElementFormat::Short4:
        case VertexElementFormat::NormalizedShort4:
        case VertexElementFormat::HalfVector4:
            return GL_UNSIGNED_SHORT;
    }
}

System::UInt32 VertexArrayObject::GetComponentCount(const VertexElementFormat& vertexFormat) const
{
    switch (vertexFormat)
    {
        case VertexElementFormat::Single:
            return 1;

        case VertexElementFormat::Vector2:
        case VertexElementFormat::Short2:
        case VertexElementFormat::NormalizedShort2:
        case VertexElementFormat::HalfVector2:
            return 2;

        case VertexElementFormat::Vector3:
            return 3;

        case VertexElementFormat::Vector4:
        case VertexElementFormat::Color:
        case VertexElementFormat::Byte4:
        case VertexElementFormat::Short4:
        case VertexElementFormat::NormalizedShort4:
        case VertexElementFormat::HalfVector4:
            return 4;
    }
}
