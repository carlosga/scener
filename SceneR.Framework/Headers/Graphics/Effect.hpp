//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <Graphics/EffectParameterCollection.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <System/Core.hpp>
#include <memory>
#include <vector>

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
            Effect(GraphicsDevice&       graphicsDevice,
                   const System::String& vertexShader,
                   const System::String& fragmentShader);

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
            void Begin();

            /**
             * Ends the application of the effect state just after rendering the effect.
             */
            void End();

        protected:
            /**
             * Computes derived parameter values immediately before applying the effect.
             */
            virtual void OnApply() = 0;

        protected:
            std::shared_ptr<ShaderProgram> shaderProgram;
        };
    }
}

#endif  /* EFFECT_HPP */
