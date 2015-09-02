#include <Content/Readers/BufferViewReader.hpp>

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
        using SceneR::GLTF::BufferViewTarget;

        BufferViewReader::BufferViewReader()
        {
        }

        BufferViewReader::~BufferViewReader()
        {

        }

        std::shared_ptr<void> BufferViewReader::Read(ContentReader& input, const json11::Json& value)
        {
            auto bufferView = std::make_shared<BufferView>();

            bufferView->buffer     = value["buffer"].string_value();
            bufferView->byteOffset = value["byteOffset"].int_value();
            bufferView->byteLength = value["byteLength"].int_value();

            const auto& target = value["target"];

            if (target.is_null())
            {
                bufferView->target = BufferViewTarget::AnimationOrSkin;
            }
            else
            {
                bufferView->target = static_cast<BufferViewTarget>(target.int_value());
            }

            return bufferView;
        }
    }
}
