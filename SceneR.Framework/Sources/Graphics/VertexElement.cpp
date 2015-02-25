// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexElement.hpp>

using namespace System;
using namespace SceneR::Graphics;

VertexElement::VertexElement(const UInt32&                                offset
                           , const SceneR::Graphics::VertexElementFormat& vertexElementFormat
                           , const SceneR::Graphics::VertexElementUsage&  vertexElementUsage
                           , const UInt32&                                usageIndex)
    : offset              { offset }
    , vertexElementFormat { vertexElementFormat }
    , vertexElementUsage  { vertexElementUsage }
    , usageIndex          { usageIndex }
{
}

VertexElement::VertexElement(const VertexElement& element)
    : offset              { element.offset }
    , vertexElementFormat { element.vertexElementFormat }
    , vertexElementUsage  { element.vertexElementUsage }
    , usageIndex          { element.usageIndex }
{
}

VertexElement::~VertexElement()
{
}

const UInt32& VertexElement::Offset() const
{
    return this->offset;
}

const UInt32& VertexElement::UsageIndex() const
{
    return this->usageIndex;
}

const SceneR::Graphics::VertexElementFormat& VertexElement::VertexElementFormat() const
{
    return this->vertexElementFormat;
}

const SceneR::Graphics::VertexElementUsage& VertexElement::VertexElementUsage() const
{
    return this->vertexElementUsage;
}

VertexElement& VertexElement::operator=(const VertexElement& element)
{
    if (this != &element)
    {
        this->offset              = element.offset;
        this->vertexElementFormat = element.vertexElementFormat;
        this->vertexElementUsage  = element.vertexElementUsage;
        this->usageIndex          = element.usageIndex;
    }

    return *this;
}
