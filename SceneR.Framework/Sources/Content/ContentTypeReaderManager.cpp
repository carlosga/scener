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
            register_known_type_readers();
        }

        ContentTypeReaderManager::~ContentTypeReaderManager()
        {
            if (_readers.size() > 0)
            {
                for (auto& reader : _readers)
                {
                    delete reader.second;
                }

                _readers.clear();
            }
        }

        ContentTypeReader* ContentTypeReaderManager::get_by_reader_name(const std::string& name)
        {
            return _readers[name];
        }

        void ContentTypeReaderManager::register_known_type_readers()
        {
            register_type_reader<BuffersReader>("buffers");
            register_type_reader<BufferViewsReader>("bufferViews");
            register_type_reader<AccessorsReader>("accessors");
            register_type_reader<MeshesReader>("meshes");
            register_type_reader<MaterialsReader>("materials");
            register_type_reader<TechniquesReader>("techniques");

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
