// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHNIQUESREADER_HPP
#define TECHNIQUESREADER_HPP

#include <memory>

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
             * Reads the buffers contents from the given ContentReader.
             */
            void read(const json11::Json&               value
                    , SceneR::Graphics::GraphicsDevice& graphicsDevice
                    , SceneR::Graphics::Model*          root) override;

        private:
            void read_technique_parameters(const json11::Json&                       value
                                         , std::shared_ptr<SceneR::Graphics::Effect> technique);

            void read_technique_passes(const json11::Json& value, std::shared_ptr<SceneR::Graphics::Effect> technique);

            void read_technique_pass_program(const json11::Json&                           value
                                           , std::shared_ptr<SceneR::Graphics::Effect>     technique
                                           , std::shared_ptr<SceneR::Graphics::EffectPass> pass);

            void read_technique_pass_states(const json11::Json&                           value
                                          , std::shared_ptr<SceneR::Graphics::EffectPass> pass);

            void cache_parameters(std::shared_ptr<SceneR::Graphics::Effect> technique);

            void describe_parameter(const std::int32_t&                                type
                                  , std::shared_ptr<SceneR::Graphics::EffectParameter> parameter);
        };
    }
}

#endif //TECHNIQUESREADER_HPP
