// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MESHESREADER_HPP
#define MESHESREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <memory>
#include <string>

namespace SceneR
{
    namespace Graphics
    {
        class ModelMesh;
    }
}

namespace SceneR
{
    namespace Content
    {
        /**
         * Meshes reader
         */
        class MeshesReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the MeshesReader class.
             */
            MeshesReader();

            /**
             * Destructor
             */
            ~MeshesReader();

        public:
            /**
             * Reads the buffers contents from the given ContentReader.
             */
            void read(const json11::Json& value, ContentReaderContext& context) override;

        private:
            void read_mesh_part(const json11::Json&                          source
                              , ContentReaderContext&                        context
                              , std::shared_ptr<SceneR::Graphics::ModelMesh> mesh) const;
        };
    }
}

#endif //MESHESREADER_HPP
