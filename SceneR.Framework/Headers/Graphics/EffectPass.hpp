// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_EFFECTPASS_HPP
#define GRAPHICS_EFFECTPASS_HPP

#include <memory>
#include <string>
#include <vector>

#include <Graphics/EffectPassStates.hpp>
#include <Graphics/Program.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class EffectParameter;
        class Program;

        /**
         * @brief Contains rendering state for drawing with an effect; an effect can contain one or more passes.
         */
        class EffectPass
        {
        public:
            /**
             * Initializes a new instance of the EffectPass class.
             */
            EffectPass();

            /**
             * Destructor.
             */
            ~EffectPass();

        public:
            /**
             * Gets the name of this pass.
             * @return The name of this pass.
             */
            const std::u16string& name() const;

            /**
             * Begins this pass.
             */
            void apply();

        private:
            std::u16string                                _name;
            std::u16string                                _lighting_model;
            std::vector<std::shared_ptr<EffectParameter>> _parameters;
            std::shared_ptr<Program>                      _program;
            EffectPassStates                              _states;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_EFFECTPASS_HPP
