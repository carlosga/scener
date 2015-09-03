// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MESHESREADER_HPP
#define MESHESREADER_HPP

#include <Content/ContentTypeReader.hpp>

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
            void Read(const json11::Json&       value
                , System::IO::BinaryReader& reader
                , SceneR::GLTF::Model*      root) override;
        };
    }
}

#endif //MESHESREADER_HPP