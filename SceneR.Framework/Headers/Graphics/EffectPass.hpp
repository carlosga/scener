// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_EFFECTPASS_HPP
#define GRAPHICS_EFFECTPASS_HPP

#include <memory>
#include <string>
#include <vector>

#include <gsl.h>

#include <Graphics/EffectPassStates.hpp>
#include <Graphics/Program.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
        class EffectParameter;
        class GraphicsDevice;
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
            EffectPass(Guide::not_null<GraphicsDevice*> graphicsDevice);

            /**
             * Destructor.
             */
            ~EffectPass() = default;

        public:
            /**
             * Gets the name of this pass.
             * @return The name of this pass.
             */
            const std::string& name() const;

            /**
             * Begins this pass.
             */
            void begin();

            /**
             * Ends this pass.
             */
            void end();

        private:
            GraphicsDevice*                               _graphics_device  = nullptr;
            std::string                                   _name             = { };
            std::string                                   _lighting_model   = { };
            std::vector<std::shared_ptr<EffectParameter>> _parameters       = { };
            std::shared_ptr<Program>                      _program          = nullptr;
            EffectPassStates                              _states           = { };

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_EFFECTPASS_HPP
