// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_EFFECTPASS_HPP
#define GRAPHICS_EFFECTPASS_HPP

#include <memory>
#include <string>
#include <vector>

#include <gsl.h>

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
            EffectPass(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept;

            /**
             * Destructor.
             */
            ~EffectPass() = default;

        public:
            /**
             * Gets the name of this pass.
             * @return The name of this pass.
             */
            const std::string& name() const noexcept;

            /**
             * Begins this pass.
             */
            void begin() noexcept;

            /**
             * Ends this pass.
             */
            void end() noexcept;

        private:
            GraphicsDevice*                               _graphics_device  { nullptr };
            std::string                                   _name             { };
            std::vector<std::shared_ptr<EffectParameter>> _parameters       { };
            std::shared_ptr<Program>                      _program          { nullptr };

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_EFFECTPASS_HPP
