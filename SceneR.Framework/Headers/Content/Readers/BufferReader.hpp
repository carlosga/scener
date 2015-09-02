#ifndef BUFFERREADER
#define BUFFERREADER

#include "../ContentTypeReader.hpp"

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Buffers reader
         */
        class BufferReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the BufferReader class.
             */
            BufferReader();

            /**
             * Destructor
             */
            ~BufferReader() override;

        public:
            /**
             * Reads the buffers contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input, const json11::Json& value) override;
        };
    }
}

#endif // BUFFERREADER

