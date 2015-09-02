#include <Content/Readers/BuffersReader.hpp>

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
        using SceneR::GLTF::Buffer;

        BuffersReader::BuffersReader()
        {
        }

        BuffersReader::~BuffersReader()
        {
        }

        std::shared_ptr<void> BuffersReader::Read(ContentReader& input, const json11::Json& value)
        {
            auto buffers = std::make_shared<std::vector<Buffer>>();

            for (const auto& item : value.object_items())
            {
                buffers->push_back(*input.ReadObject<Buffer>("buffer", item.second));
            }

            return buffers;
        }
    }
}
