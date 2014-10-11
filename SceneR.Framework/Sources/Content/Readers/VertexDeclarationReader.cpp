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
