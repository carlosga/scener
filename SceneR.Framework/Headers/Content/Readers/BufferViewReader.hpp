#ifndef BUFFERVIEWREADER
#define BUFFERVIEWREADER

#include "../ContentTypeReader.hpp"

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Buffers view reader
         */
        class BufferViewReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the BufferViewReader class.
             */
            BufferViewReader();

            /**
             * Destructor
             */
            ~BufferViewReader() override;

        public:
            /**
             * Reads the buffer view contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input, const json11::Json& value) override;
        };
    }
}

#endif // BUFFERVIEWREADER

