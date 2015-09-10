// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_TECHNIQUESREADER_HPP
#define CONTENT_READERS_TECHNIQUESREADER_HPP

#include <memory>
#include <vector>

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Effect;
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
             * Reads the techniques contents.
             */
            void read(const json11::Json& value, ContentReaderContext& context) override;

        private:
            void read_technique_parameters(const json11::Json&                       value
                                         , ContentReaderContext&                     context
                                         , std::shared_ptr<SceneR::Graphics::Effect> effect);

            void set_parameter_values(const json11::Json&                       value
                                    , ContentReaderContext&                     context
                                    , std::shared_ptr<SceneR::Graphics::Effect> effect);

            void read_technique_passes(const json11::Json&                       value
                                     , ContentReaderContext&                     context
                                     , std::shared_ptr<SceneR::Graphics::Effect> effect);

            void read_technique_pass_program(const json11::Json&                           value
                                           , ContentReaderContext&                         context
                                           , std::shared_ptr<SceneR::Graphics::Effect>     effect
                                           , std::shared_ptr<SceneR::Graphics::EffectPass> effectPass);

            void read_technique_pass_states(const json11::Json&                           value
                                          , std::shared_ptr<SceneR::Graphics::EffectPass> effectPass);

            void cache_technique_parameters(std::shared_ptr<SceneR::Graphics::Effect> effect);

            void describe_technique_parameter(std::shared_ptr<SceneR::Graphics::EffectParameter> parameter
                                            , const std::int32_t&                                type);

            void set_parameter_numeric_value(std::shared_ptr<SceneR::Graphics::EffectParameter> parameter
                                           , const json11::Json&                                value);
        };
    }
}

#endif //TECHNIQUESREADER_HPP
