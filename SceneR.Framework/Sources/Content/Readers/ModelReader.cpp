#include <Content/Readers/ModelReader.hpp>

#include <cstdint>
#include <vector>

#include <Content/ContentReader.hpp>
#include <Content/json11.hpp>

#include <GLTF/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::GLTF::Model;
        using SceneR::GLTF::Buffer;
        using SceneR::GLTF::BufferView;

        ModelReader::ModelReader()
        {
        }

        ModelReader::~ModelReader()
        {

        }

        std::shared_ptr<void> ModelReader::Read(ContentReader& input, const json11::Json& value)
        {
            auto gltf = std::make_shared<Model>();
            auto keys = std::vector<std::string> { "buffers"
                                                 , "bufferViews"
                                                 , "accessors"
                                                 , "meshes"
                                                 , "lights"
                                                 , "cameras"
                                                 , "nodes"
                                                 , "images"
                                                 , "textures"
                                                 , "shaders"
                                                 , "programs"
                                                 , "samplers"
                                                 , "techniques"
                                                 , "materials"
                                                 , "animations"
                                                 , "skins" };


            //
            // buffers
            auto buffers = input.ReadObject<std::vector<Buffer>>("buffers", value["buffers"]);

            if (buffers != nullptr)
            {
                gltf->buffers = *buffers;
            }

            // buffer views

            auto bufferViews = input.ReadObject<std::vector<BufferView>>("bufferViews", value["bufferViews"]);

            if (buffers != nullptr)
            {
                gltf->bufferViews = *bufferViews;
            }

            return gltf;
        }
    }
}
