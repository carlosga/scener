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

#include <Content/ContentType.hpp>
#include <Content/ContentTypeReaderManager.hpp>
#include <Content/Readers/IndexBufferReader.hpp>
#include <Content/Readers/ModelReader.hpp>
#include <Content/Readers/Texture2DReader.hpp>
#include <Content/Readers/VertexBufferReader.hpp>
#include <stdexcept>

using namespace SceneR::Content;

ContentTypeReaderManager::ContentTypeReaderManager()
{
    this->RegisterKnownTypeReaders();
}

ContentTypeReaderManager::~ContentTypeReaderManager()
{
    if (this->readers.size() > 0)
    {
        for (auto& reader : this->readers)
        {
            delete reader;
        }
    }

    this->readers.clear();
}

ContentTypeReader* ContentTypeReaderManager::GetReaderForContentType(const ContentType& contentType)
{
    for (auto& typeReader : this->readers)
    {
        if (typeReader->ContentType() == contentType)
        {
            return typeReader;
        }
    }

    throw std::runtime_error("Unknown content type reader");
};

void ContentTypeReaderManager::RegisterKnownTypeReaders()
{
    this->RegisterTypeReader<ModelReader>();
    this->RegisterTypeReader<VertexBufferReader>();
    this->RegisterTypeReader<IndexBufferReader>();
    this->RegisterTypeReader<Texture2DReader>();
}
