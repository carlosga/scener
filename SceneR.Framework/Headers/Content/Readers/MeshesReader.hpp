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
        class Accessor;
        class Material;
        class ModelMeshPart;
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
            void read(const json11::Json&               value
                    , SceneR::Graphics::GraphicsDevice& graphicsDevice
                    , SceneR::Graphics::Model*          root) override;

            std::shared_ptr<SceneR::Graphics::ModelMeshPart> read_mesh_part(const SceneR::Graphics::Model* root
                                                                                , const json11::Json& source) const;

            void read_mesh_part_attribute(std::pair<std::string, json11::Json>             attribute
                                        , const Graphics::Model*                           root
                                        , std::shared_ptr<SceneR::Graphics::ModelMeshPart> meshPart) const;
        };
    }
}

#endif //MESHESREADER_HPP
