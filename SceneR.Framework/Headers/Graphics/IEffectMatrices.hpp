// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

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
            virtual ~IEffectMatrices() = default;

        public:
            /**
             * Gets the projection matrix in the current effect.
             */
            virtual const SceneR::Framework::Matrix& Projection() const = 0;

            /**
             * Sets the projection matrix in the current effect.
             */
            virtual void Projection(const SceneR::Framework::Matrix& projection) = 0;

            /**
             * Gets the view matrix in the current effect.
             */
            virtual const SceneR::Framework::Matrix& View() const = 0;

            /**
             * Sets the view matrix in the current effect.
             */
            virtual void View(const SceneR::Framework::Matrix& view) = 0;

            /**
             * Gets the world matrix in the current effect.
             */
            virtual const SceneR::Framework::Matrix& World() const = 0;

            /**
             * Sets the world matrix in the current effect.
             */
            virtual void World(const SceneR::Framework::Matrix& world) = 0;
        };
    };
}

#endif  /* IEFFECTMATRICES_HPP */
