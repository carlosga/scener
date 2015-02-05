// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <memory>

#include <Graphics/EffectParameterCollection.hpp>
#include <Graphics/GraphicsResource.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class GrapicsDevice;
        class ShaderProgram;

        /**
         * Used to set and query effects, and to choose techniques.
         */
        class Effect : public GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the Effect class
             *
             * @param graphicsDevice the graphics device
             * @param vertexShader   the vertex shader source code
             * @param fragmentShader the fragment shader source code
             */
            Effect(GraphicsDevice&       graphicsDevice
                 , const System::String& vertexShader
                 , const System::String& fragmentShader);

            /**
             * Initializes a new instance of the Effect class.
             *
             * @param effect the effect to be copied
             */
            Effect(const Effect& effect);

            /**
             * Releases all resources being used by this effect instance.
             */
            virtual ~Effect();

        public:
            /**
             * Gets a collection of parameters used for this effect.
             */
            EffectParameterCollection& Parameters();

            /**
             * Starts the application of the effect state just prior to rendering the effect.
             */
            virtual void Begin();

            /**
             * Ends the application of the effect state just after rendering the effect.
             */
            virtual void End();

        protected:
            /**
             * Computes derived parameter values immediately before applying the effect.
             */
            virtual void OnApply() = 0;

        protected:
            EffectParameterCollection      parameters;
            std::shared_ptr<ShaderProgram> shader;
        };
    }
}

#endif  /* EFFECT_HPP */
