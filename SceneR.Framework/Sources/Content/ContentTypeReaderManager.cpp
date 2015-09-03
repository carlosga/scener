// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentTypeReaderManager.hpp>

#include <Content/Readers/AccessorsReader.hpp>
#include <Content/Readers/BuffersReader.hpp>
#include <Content/Readers/BufferViewsReader.hpp>
#include <Content/Readers/MaterialsReader.hpp>
#include <Content/Readers/MeshesReader.hpp>
#include <Content/Readers/TechniquesReader.hpp>

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
            this->RegisterTypeReader<BuffersReader>("buffers");
            this->RegisterTypeReader<BufferViewsReader>("bufferViews");
            this->RegisterTypeReader<AccessorsReader>("accessors");
            this->RegisterTypeReader<MeshesReader>("meshes");
            this->RegisterTypeReader<MaterialsReader>("materials");
            this->RegisterTypeReader<TechniquesReader>("techniques");

//            this->RegisterTypeReader<AnimationsReader>(u"animations");
//            this->RegisterTypeReader<BufferViewsReader>(u"bufferViews");
//            this->RegisterTypeReader<CamerasReader>(u"cameras");
//            this->RegisterTypeReader<LightsReader>(u"lights");
//            this->RegisterTypeReader<ImagesReader>(u"images");
//            this->RegisterTypeReader<NodesReader>(u"nodes");
//            this->RegisterTypeReader<ProgramsReader>(u"programs");
//            this->RegisterTypeReader<SamplersReader>(u"samplers");
//            this->RegisterTypeReader<ShadersReader>(u"shaders");
//            this->RegisterTypeReader<SkinsReader>(u"skins");

//            this->RegisterTypeReader<TexturesReader>(u"textures");
        }
    }
}
