// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATERIALREADER_HPP
#define MATERIALREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Material reader
         */
        class MaterialsReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the MeshesReader class.
             */
            MaterialsReader();

            /**
             * Destructor
             */
            ~MaterialsReader();

        public:
            /**
             * Reads the buffers contents from the given ContentReader.
             */
            void read(const json11::Json&               value
                    , SceneR::Graphics::GraphicsDevice& graphicsDevice
                    , SceneR::Graphics::Model*          root) override;
        };
    }
}

#endif // MATERIALREADER_HPP
