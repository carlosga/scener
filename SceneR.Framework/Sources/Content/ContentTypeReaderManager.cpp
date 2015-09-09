// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentTypeReaderManager.hpp>

#include <Content/Readers/AccessorsReader.hpp>
#include <Content/Readers/AnimationsReader.hpp>
#include <Content/Readers/BuffersReader.hpp>
#include <Content/Readers/BufferViewsReader.hpp>
#include <Content/Readers/ImagesReader.hpp>
#include <Content/Readers/MaterialsReader.hpp>
#include <Content/Readers/MeshesReader.hpp>
#include <Content/Readers/NodesReader.hpp>
#include <Content/Readers/ProgramsReader.hpp>
#include <Content/Readers/SamplersReader.hpp>
#include <Content/Readers/ShadersReader.hpp>
#include <Content/Readers/SkinsReader.hpp>
#include <Content/Readers/TechniquesReader.hpp>
#include <Content/Readers/TexturesReader.hpp>

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
            register_type_reader<AccessorsReader>("accessors");
            register_type_reader<AnimationsReader>("animations");
            register_type_reader<BuffersReader>("buffers");
            register_type_reader<BufferViewsReader>("bufferViews");
            register_type_reader<ImagesReader>("images");
            register_type_reader<MaterialsReader>("materials");
            register_type_reader<MeshesReader>("meshes");
            register_type_reader<NodesReader>("nodes");
            register_type_reader<ProgramsReader>("programs");
            register_type_reader<SamplersReader>("samplers");
            register_type_reader<ShadersReader>("shaders");
            register_type_reader<SkinsReader>("skins");
            register_type_reader<TechniquesReader>("techniques");
            register_type_reader<TexturesReader>("textures");
        }
    }
}
