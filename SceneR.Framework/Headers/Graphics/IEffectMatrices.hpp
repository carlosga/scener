// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IEFFECTMATRICES_HPP
#define IEFFECTMATRICES_HPP

namespace SceneR
{
    namespace Framework
    {
        struct Matrix;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines the transformation matrices for the current effect.
         */
        class IEffectMatrices
        {
        public:
            /**
             * Release all resource being used by the current IIEffectMatrices instance
             */
            virtual ~IEffectMatrices();

        public:
            /**
             * Gets the projection matrix in the current effect.
             */
            virtual const SceneR::Framework::Matrix& projection() const = 0;

            /**
             * Sets the projection matrix in the current effect.
             */
            virtual void projection(const SceneR::Framework::Matrix& projection) = 0;

            /**
             * Gets the view matrix in the current effect.
             */
            virtual const SceneR::Framework::Matrix& view() const = 0;

            /**
             * Sets the view matrix in the current effect.
             */
            virtual void view(const SceneR::Framework::Matrix& view) = 0;

            /**
             * Gets the world matrix in the current effect.
             */
            virtual const SceneR::Framework::Matrix& world() const = 0;

            /**
             * Sets the world matrix in the current effect.
             */
            virtual void world(const SceneR::Framework::Matrix& world) = 0;
        };
    }
}

#endif  /* IEFFECTMATRICES_HPP */
