// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHNIQUESREADER_HPP
#define TECHNIQUESREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Techniques reader
         */
        class TechniquesReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the TechniquesReader class.
             */
            TechniquesReader();

            /**
             * Destructor
             */
            ~TechniquesReader();

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

#endif //TECHNIQUESREADER_HPP
