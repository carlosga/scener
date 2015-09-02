#include <Content/Readers/BufferViewsReader.hpp>

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
        using SceneR::GLTF::BufferView;

        BufferViewsReader::BufferViewsReader()
        {
        }

        BufferViewsReader::~BufferViewsReader()
        {
        }

        std::shared_ptr<void> BufferViewsReader::Read(ContentReader& input, const json11::Json& value)
        {
            auto bufferViews = std::make_shared<std::vector<BufferView>>();

            for (const auto& item : value.object_items())
            {
                bufferViews->push_back(*input.ReadObject<BufferView>("bufferView", item.second));
            }

            return bufferViews;
        }
    }
}
