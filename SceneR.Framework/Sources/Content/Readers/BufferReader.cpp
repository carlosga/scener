#include <Content/Readers/BufferReader.hpp>

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
        using SceneR::GLTF::BufferType;

        BufferReader::BufferReader()
        {
        }

        BufferReader::~BufferReader()
        {

        }

        std::shared_ptr<void> BufferReader::Read(ContentReader& input, const json11::Json& value)
        {
            auto buffer = std::make_shared<Buffer>();

            buffer->uri        = value["uri"].string_value();
            buffer->byteLength = value["byteLength"].int_value();

            const auto type = value["type"].string_value();

            if (type == "arraybuffer")
            {
                buffer->type = BufferType::ArrayBuffer;
            }
            else
            {
                buffer->type = BufferType::Text;
            }

            return buffer;
        }
    }
}
