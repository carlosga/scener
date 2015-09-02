#ifndef BUFFERVIEWSSREADER
#define BUFFERVIEWSSREADER

#include "../ContentTypeReader.hpp"

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Buffer views reader
         */
        class BufferViewsReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the BufferViewsReader class.
             */
            BufferViewsReader();

            /**
             * Destructor
             */
            ~BufferViewsReader() override;

        public:
            /**
             * Reads the buffers contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input, const json11::Json& value) override;
        };
    }
}

#endif // BUFFERVIEWSSREADER
