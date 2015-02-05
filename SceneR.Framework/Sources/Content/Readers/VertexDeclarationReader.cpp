// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/VertexDeclarationReader.hpp>

#include <Graphics/VertexDeclaration.hpp>
#include <Content/ContentReader.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

std::shared_ptr<void> VertexDeclarationReader::Read(ContentReader& input)
{
    auto vertexStride = input.ReadUInt32();
    auto elementCount = input.ReadUInt32();
    auto elements     = std::vector<VertexElement>();

    for (UInt32 i = 0; i < elementCount; i++)
    {
    	elements.push_back({ input.ReadUInt32()                                   // Offset
    			 		   , static_cast<VertexElementFormat>(input.ReadUInt32()) // Element format
    					   , static_cast<VertexElementUsage>(input.ReadUInt32())  // Element usage
    					   , input.ReadUInt32() });	                              // Usage index
    }

    return std::make_shared<VertexDeclaration>(vertexStride, elements);
}
