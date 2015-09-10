// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_TECHNIQUESREADER_HPP
#define CONTENT_READERS_TECHNIQUESREADER_HPP

#include <memory>
#include <vector>

#include <Content/ContentTypeReader.hpp>
#include <Graphics/EffectTechnique.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class EffectParameter;
        class EffectPass;
    }
}

namespace SceneR
{
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
            std::shared_ptr<SceneR::Graphics::EffectTechnique> read(const std::pair<std::string, json11::Json>& source
                                                                  , ContentReaderContext&                       context);

        private:
            void read_technique_parameters(const json11::Json&                       value
                                         , ContentReaderContext&                     context
                                         , std::shared_ptr<SceneR::Graphics::EffectTechnique> effect);

            void set_parameter_values(const json11::Json&                       value
                                    , ContentReaderContext&                     context
                                    , std::shared_ptr<SceneR::Graphics::EffectTechnique> effect);

            void read_technique_passes(const json11::Json&                       value
                                     , ContentReaderContext&                     context
                                     , std::shared_ptr<SceneR::Graphics::EffectTechnique> effect);

            void read_technique_pass_program(const json11::Json&                           value
                                           , ContentReaderContext&                         context
                                           , std::shared_ptr<SceneR::Graphics::EffectTechnique>     effect
                                           , std::shared_ptr<SceneR::Graphics::EffectPass> effectPass);

            void read_technique_pass_states(const json11::Json&                           value
                                          , std::shared_ptr<SceneR::Graphics::EffectPass> effectPass);

            void cache_technique_parameters(std::shared_ptr<SceneR::Graphics::EffectTechnique> effect);

            void describe_technique_parameter(std::shared_ptr<SceneR::Graphics::EffectParameter> parameter
                                            , const std::int32_t&                                type);
        };
    }
}

#endif //TECHNIQUESREADER_HPP
