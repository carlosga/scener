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

#include <Graphics/BufferObject.hpp>
#include <Graphics/VertexArrayObject.hpp>
#include <Graphics/VertexDeclaration.hpp>
#include <Graphics/VertexElement.hpp>

using namespace System;
using namespace SceneR::Graphics;

VertexArrayObject::VertexArrayObject()
    : id(0)
{
    this->Create();
}

VertexArrayObject::~VertexArrayObject()
{
    this->Delete();
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

void VertexArrayObject::DeclareVertexFormat(const BufferObject& vbo, const VertexDeclaration& vDecl) const
{
    this->Activate();
    this->ActivateVertexFormat(vbo, vDecl);
    this->Deactivate();
}

void VertexArrayObject::ActivateVertexFormat(const BufferObject& vbo, const VertexDeclaration& vDecl) const
{
    glBindVertexBuffer(0, vbo.Id(), 0, vDecl.VertexStride());

    // ... declare vertex elements
    for (const VertexElement& ve : vDecl.VertexElements())
    {
        UInt32 elementType  = this->GetElementType(ve.VertexElementFormat());
        UInt32 elementCount = this->GetElementCount(ve.VertexElementFormat());
        UInt32 usageIndex   = this->GetUsageIndex(ve.VertexElementUsage());

        if (elementType == GL_FLOAT)
        {
            glVertexAttribFormat(usageIndex, elementCount, elementType, false, ve.Offset());
        }
        else
        {
            glVertexAttribIFormat(usageIndex, elementCount, elementType, ve.Offset());
        }

        glEnableVertexAttribArray(usageIndex);
        glVertexAttribBinding(usageIndex, 0);
    }
}

void VertexArrayObject::DeactivateVertexFormat(const VertexDeclaration& vDecl) const
{
    // ... declare vertex elements
    for (Size i = 0; i < vDecl.VertexElements().size(); i++)
    {
        glDisableVertexAttribArray(i++);
    }

    glBindVertexBuffer(0, 0, 0, vDecl.VertexStride());

    this->Deactivate();
}

System::UInt32 VertexArrayObject::GetElementCount(const VertexElementFormat& vertexFormat) const
{
    // TODO: Review this to see if it can matchs the XNA VertexElementFormat specificacion.
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
        default:
            return 4;
    }
}

GLenum VertexArrayObject::GetElementType(const VertexElementFormat& vertexFormat) const
{
    switch (vertexFormat)
    {
        case VertexElementFormat::Byte4:
            return GL_UNSIGNED_BYTE;

        case VertexElementFormat::Short2:
        case VertexElementFormat::NormalizedShort2:
        case VertexElementFormat::HalfVector2:
        case VertexElementFormat::Short4:
        case VertexElementFormat::NormalizedShort4:
        case VertexElementFormat::HalfVector4:
            return GL_UNSIGNED_SHORT;

        case VertexElementFormat::Single:
        case VertexElementFormat::Vector2:
        case VertexElementFormat::Vector3:
        case VertexElementFormat::Vector4:
        case VertexElementFormat::Color:
        default:
            return GL_FLOAT;
    }
}

System::UInt32 VertexArrayObject::GetUsageIndex(const VertexElementUsage& usage) const
{
    switch (usage)
    {
        case VertexElementUsage::Position:
            return 0;

        case VertexElementUsage::Normal:
            return 1;

        case VertexElementUsage::TextureCoordinate:
            return 2;

        case VertexElementUsage::BlendIndices:
            return 3;

        case VertexElementUsage::BlendWeight:
            return 4;

        case VertexElementUsage::Tangent:
            return 5;

        case VertexElementUsage::Binormal:
            return 5;

        default:
            return 0;
    }
}
