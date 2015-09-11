// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_MATERIALREADER_HPP
#define CONTENT_READERS_MATERIALREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/EffectMaterial.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * EffectMaterial reader
         */
        template <>
        class ContentTypeReader<SceneR::Graphics::EffectMaterial>
        {
        public:
            ContentTypeReader();
            ~ContentTypeReader();

        public:
            std::shared_ptr<SceneR::Graphics::EffectMaterial> read(ContentReader*                              input
                                                                 , const std::pair<std::string, json11::Json>& value);
        };
    }
}

#endif // CONTENT_READERS_MATERIALREADER_HPP
