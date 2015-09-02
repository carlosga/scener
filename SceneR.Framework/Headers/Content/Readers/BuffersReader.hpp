#ifndef BUFFERSREADER
#define BUFFERSREADER

#include "../ContentTypeReader.hpp"

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Buffers reader
         */
        class BuffersReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the BuffersReader class.
             */
            BuffersReader();

            /**
             * Destructor
             */
            ~BuffersReader() override;

        public:
            /**
             * Reads the buffers contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input, const json11::Json& value) override;
        };
    }
}

#endif // BUFFERSREADER

