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

#include "Content/Readers/IndexBufferReader.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/IndexElementSize.hpp"

using namespace SceneR::Content;
using namespace SceneR::Graphics;

IndexBufferReader::IndexBufferReader()
{
}

const ContentType IndexBufferReader::GetContentType() const
{
    return ContentType::IndexBuffer;
}

std::shared_ptr<void> IndexBufferReader::Read(ContentReader* input)
{
    std::vector<UInt32>          data(0);
    UInt32                       indexCount = input->ReadUInt32();
    std::shared_ptr<IndexBuffer> buffer     = std::make_shared<IndexBuffer>(input->GetGraphicsDevice(),
                                                                            IndexElementSize::ThirtyTwoBits,
                                                                            indexCount);

    for (UInt32 i = 0; i < indexCount; i++)
    {
        data.push_back(input->ReadUInt32());
    }

    buffer->SetData(data);

    return buffer;
}
