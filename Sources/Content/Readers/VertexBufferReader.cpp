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

#include <vector>
#include "Core/Vector2.hpp"
#include "Core/Vector3.hpp"
#include "Content/Readers/VertexBufferReader.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/VertexPositionNormalTexture.hpp"

using namespace SceneR::Core;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

VertexBufferReader::VertexBufferReader()
{
}

const ContentType VertexBufferReader::GetContentType() const
{
    return ContentType::VertextBuffer;
}

std::shared_ptr<void> VertexBufferReader::Read(ContentReader* input)
{
    std::vector<VertexPositionNormalTexture> data;
    int                                      vertexCount = input->ReadUInt32();
    std::shared_ptr<VertexBuffer>            buffer      = std::make_shared<VertexBuffer>(input->GetGraphicsDevice());

    for (int i = 0; i < vertexCount; i++)
    {
        Vector3 position = input->ReadVector3();
        Vector3 normal   = input->ReadVector3();
        Vector2 tcoord   = input->ReadVector2();

        data.push_back(VertexPositionNormalTexture(position, normal, tcoord));
    }

    buffer->SetData(data);

    return buffer;
}
