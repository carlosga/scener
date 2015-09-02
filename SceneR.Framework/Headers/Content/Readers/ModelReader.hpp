#ifndef GLTFREADER
#define GLTFREADER

#include "../ContentTypeReader.hpp"

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * GLTF reader
         */
        class ModelReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the ModelReader class.
             */
            ModelReader();

            /**
             * Destructor
             */
            ~ModelReader() override;

        public:
            /**
             * Reads the buffers contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input, const json11::Json& value) override;
        };
    }
}

#endif // GLTFREADER

