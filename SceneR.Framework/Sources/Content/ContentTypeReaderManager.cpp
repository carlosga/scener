// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentTypeReaderManager.hpp>

#include <Content/Readers/ModelReader.hpp>
#include <Content/Readers/BuffersReader.hpp>
#include <Content/Readers/BufferReader.hpp>
#include <Content/Readers/BufferViewsReader.hpp>
#include <Content/Readers/BufferViewReader.hpp>

namespace SceneR
{
    namespace Content
    {
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
                    delete reader.second;
                }

                this->readers.clear();
            }
        }

        ContentTypeReader* ContentTypeReaderManager::GetByReaderName(const std::string& name)
        {
            return this->readers[name];
        }

        void ContentTypeReaderManager::RegisterKnownTypeReaders()
        {
            this->RegisterTypeReader<ModelReader>("gltf");
            this->RegisterTypeReader<BuffersReader>("buffers");
            this->RegisterTypeReader<BufferReader>("buffer");
            this->RegisterTypeReader<BufferViewsReader>("bufferViews");
            this->RegisterTypeReader<BufferViewReader>("bufferView");

//            this->RegisterTypeReader<AccessorsReader>(u"accessors");
//            this->RegisterTypeReader<AnimationsReader>(u"animations");
//            this->RegisterTypeReader<BufferViewsReader>(u"bufferViews");
//            this->RegisterTypeReader<CamerasReader>(u"cameras");
//            this->RegisterTypeReader<LightsReader>(u"lights");
//            this->RegisterTypeReader<ImagesReader>(u"images");
//            this->RegisterTypeReader<MaterialsReader>(u"materials");
//            this->RegisterTypeReader<MeshesReader>(u"meshes");
//            this->RegisterTypeReader<NodesReader>(u"nodes");
//            this->RegisterTypeReader<ProgramsReader>(u"programs");
//            this->RegisterTypeReader<SamplersReader>(u"samplers");
//            this->RegisterTypeReader<ShadersReader>(u"shaders");
//            this->RegisterTypeReader<SkinsReader>(u"skins");
//            this->RegisterTypeReader<TechniquesReader>(u"techniques");
//            this->RegisterTypeReader<TexturesReader>(u"textures");
        }
    }
}
