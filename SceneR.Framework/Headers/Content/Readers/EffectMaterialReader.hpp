// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECTMATERIALREADER_HPP
#define EFFECTMATERIALREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * EffectMaterial reader
         */
        class EffectMaterialReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the EffectMaterialReader class.
             */
            EffectMaterialReader();

            /**
             * Destructor
             */
            ~EffectMaterialReader() override;

        public:
            /**
             * Reads the effect material contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* EFFECTMATERIALREADER_HPP */
