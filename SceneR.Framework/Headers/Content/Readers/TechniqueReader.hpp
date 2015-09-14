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
            ContentTypeReader();
            ~ContentTypeReader();

        public:
            /**
             * Reads the techniques contents.
             */
            std::shared_ptr<SceneR::Graphics::EffectTechnique> read(ContentReader*                              input
                                                                  , const std::pair<std::string, json11::Json>& source);

        private:
            void read_technique_parameters(ContentReader*                                     input
                                         , const json11::Json&                                value
                                         , std::shared_ptr<SceneR::Graphics::EffectTechnique> effect);

            void set_parameter_values(ContentReader*                                     input
                                    , const json11::Json&                                value
                                    , std::shared_ptr<SceneR::Graphics::EffectTechnique> effect);

            void read_technique_passes(ContentReader*                                     input
                                     , const json11::Json&                                value
                                     , std::shared_ptr<SceneR::Graphics::EffectTechnique> effect);

            void read_technique_pass_program(ContentReader*                                     input
                                           , const json11::Json&                                value
                                           , std::shared_ptr<SceneR::Graphics::EffectTechnique> effect
                                           , std::shared_ptr<SceneR::Graphics::EffectPass>      effectPass);

            void read_technique_pass_states(const json11::Json&                           value
                                          , std::shared_ptr<SceneR::Graphics::EffectPass> effectPass);

            void cache_technique_parameters(std::shared_ptr<SceneR::Graphics::EffectTechnique> effect);

            void describe_technique_parameter(std::shared_ptr<SceneR::Graphics::EffectParameter> parameter
                                            , const std::int32_t&                                type);
        };
    }
}

#endif //TECHNIQUEREADER_HPP
