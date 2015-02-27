// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECTMATERIAL_HPP
#define EFFECTMATERIAL_HPP

#include <Graphics/Effect.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class DirectionalLight;
        class GraphicsDevice;

        /**
         * Contains an effect subclass which is used to load data for an EffectMaterialContent type.
         * https://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.effectmaterial(v=xnagamestudio.40).aspx
         */
        class EffectMaterial final : public Effect
        {
        public:
            /**
             * Initializes a new instance of the EffectMaterial class.
             *
             * @param graphicsDevice the graphics device
             */
            EffectMaterial(GraphicsDevice& graphicsDevice);

            /**
             * Initializes a new instance of the EffectMaterial class.
             */
            EffectMaterial(const EffectMaterial& effect);

            /**
             * Releases all resources being used by this EffectMaterial.
             */
            ~EffectMaterial() override;

        public:
            void Dispose() override;

        protected:
            /**
             * Starts the application of the effect state just prior to rendering the effect.
             */
            void Begin() override;

            /**
             * Ends the application of the effect state just after rendering the effect.
             */
            void End() override;

            /**
             * Computes derived parameter values immediately before applying the effect.
             */
            void OnApply() override;

        private:
            void Initialize();
        };
    }
}

#endif  /* EFFECTMATERIAL_HPP */
