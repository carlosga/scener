#ifndef GLTFMODEL
#define GLTFMODEL

#include <cstddef>
#include <string>
#include <vector>

namespace SceneR
{
    namespace GLTF
    {
        enum class BufferType : std::uint8_t
        {
            ArrayBuffer = 0
          , Text        = 1
        };

        enum class BufferViewTarget : std::uint32_t
        {
            ArrayBuffer        = 34962
          , ElementArrayBuffer = 34963
          , AnimationOrSkin    = 0
        };

        class Buffer
        {
        public:
            Buffer();
            ~Buffer();

        public:
            std::string   uri;
            std::uint64_t byteLength;
            BufferType    type;
        };

        class BufferView
        {
        public:
            BufferView();
            ~BufferView();

        public:
            std::string      buffer;
            std::uint64_t    byteOffset;
            std::uint64_t    byteLength;
            BufferViewTarget target;
        };

        class Model
        {
        public:
            Model();

            ~Model();

        public:
            std::vector<Buffer>     buffers;
            std::vector<BufferView> bufferViews;
        };
    }
}

#endif // GLTFMODEL

