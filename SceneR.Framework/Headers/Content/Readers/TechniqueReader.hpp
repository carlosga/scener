// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_TECHNIQUEREADER_HPP
#define CONTENT_READERS_TECHNIQUEREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/EffectTechnique.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class EffectParameter;
        class EffectPass;
    }

    namespace Content
    {
        /**
         * Techniques reader
         */
        template <>
        class ContentTypeReader<SceneR::Graphics::EffectTechnique>
        {
        public:
            ContentTypeReader() = default;

            ~ContentTypeReader() = default;

        public:
            /**
             * Reads the techniques contents.
             */
            std::shared_ptr<SceneR::Graphics::EffectTechnique> read(gsl::not_null<ContentReader*>               input
                                                                  , const std::pair<std::string, json11::Json>& source) const;

        private:
            void read_parameters(ContentReader*                     input
                               , const json11::Json&                value
                               , SceneR::Graphics::EffectTechnique* effect) const;

            void set_parameter_values(ContentReader*                     input
                                    , const json11::Json&                value
                                    , SceneR::Graphics::EffectTechnique* effect) const;

            void add_default_pass(ContentReader*      input
                                , const json11::Json& source
                                , SceneR::Graphics::EffectTechnique* effect) const;

            void read_pass_program(ContentReader*                input
                                 , const std::string&            programName
                                 , SceneR::Graphics::EffectPass* effectPass) const;

            void cache_parameters(SceneR::Graphics::EffectTechnique* effect) const;

            void describe_parameter(SceneR::Graphics::EffectParameter* parameter, const std::int32_t& type) const;
        };
    }
}

#endif //TECHNIQUEREADER_HPP
