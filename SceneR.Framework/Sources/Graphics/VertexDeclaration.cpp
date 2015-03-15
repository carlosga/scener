// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexDeclaration.hpp>

#include <System/Graphics/Platform.hpp>

using namespace System;
using namespace SceneR::Graphics;

VertexDeclaration::VertexDeclaration(const UInt32&                     vertexStride
                                   , const std::vector<VertexElement>& vertexElements)
    : vertexStride   { vertexStride }
    , vertexElements { vertexElements }
{
}

VertexDeclaration::VertexDeclaration(const VertexDeclaration& declaration)
    : vertexStride   { declaration.vertexStride }
    , vertexElements { declaration.vertexElements }
{
}

VertexDeclaration::~VertexDeclaration()
{
}

const UInt32& VertexDeclaration::VertexStride() const
{
    return this->vertexStride;
}

const std::vector<VertexElement>& VertexDeclaration::VertexElements() const
{
    return this->vertexElements;
}

VertexDeclaration& VertexDeclaration::operator=(const VertexDeclaration& declaration)
{
    if (this != &declaration)
    {
        this->vertexStride   = declaration.vertexStride;
        this->vertexElements = declaration.vertexElements;
    }

    return *this;
}

void VertexDeclaration::Declare(const UInt32& vaoId, const UInt32& bindingIndex​) const
{
    // ... declare vertex elements
    for (const auto& ve : this->vertexElements)
    {
        auto elementType  = this->GetElementType(ve.VertexElementFormat());
        auto elementCount = this->GetElementCount(ve.VertexElementFormat());
        auto usageIndex   = static_cast<UInt32>(ve.VertexElementUsage());

        if (elementType == GL_FLOAT)
        {
            glVertexAttribFormat(usageIndex
                               , static_cast<GLint>(elementCount)
                               , elementType
                               , false
                               , ve.Offset());
        }
        else
        {
            glVertexAttribIFormat(usageIndex
                                , static_cast<GLint>(elementCount)
                                , elementType
                                , ve.Offset());
        }

        glEnableVertexAttribArray(usageIndex);
        glVertexAttribBinding(usageIndex, bindingIndex​);

        // glEnableVertexArrayAttrib(vaoId, usageIndex);
        // glVertexArrayAttribBinding(vaoId, usageIndex, bindingIndex​);
    }
}

UInt32 VertexDeclaration::GetElementCount(const VertexElementFormat& vertexFormat) const
{
    // TODO: Review this to see if it can match the XNA VertexElementFormat specificacion.
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

UInt32 VertexDeclaration::GetElementType(const VertexElementFormat& vertexFormat) const
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
