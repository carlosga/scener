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

#include <Graphics/VertexElement.hpp>
#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>

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
