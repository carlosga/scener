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

#include <Graphics/VertexDeclaration.hpp>
#include <System/Graphics/Platform.hpp>

using namespace System;
using namespace SceneR::Graphics;

VertexDeclaration::VertexDeclaration(const Size&                       vertexStride
                                   , const std::vector<VertexElement>& vertexElements)
    : vertexStride(vertexStride)
    , vertexElements(vertexElements)
{
}

const Size& VertexDeclaration::VertexStride() const
{
    return this->vertexStride;
}

const std::vector<VertexElement>& VertexDeclaration::VertexElements() const
{
    return this->vertexElements;
}

void VertexDeclaration::Activate() const
{
    // ... declare vertex elements
    for (const auto& ve : this->vertexElements)
    {
        auto elementType  = this->GetElementType(ve.VertexElementFormat());
        auto elementCount = this->GetElementCount(ve.VertexElementFormat());
        auto usageIndex   = this->GetUsageIndex(ve.VertexElementUsage());

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

void VertexDeclaration::Deactivate() const
{
    // ... disable vertex elements
    for (const auto& ve : this->vertexElements)
    {
        glDisableVertexAttribArray(this->GetUsageIndex(ve.VertexElementUsage()));
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

UInt32 VertexDeclaration::GetUsageIndex(const VertexElementUsage& usage) const
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
            return 6;

        default:
            return 0;
    }
}
