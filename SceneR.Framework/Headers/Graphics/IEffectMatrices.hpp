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
            virtual ~IEffectMatrices()
            {
            };

        public:
            /**
             * Gets the projection matrix in the current effect.
             */
            virtual const SceneR::Framework::Matrix& GetProjection() const = 0;

            /**
             * Sets the projection matrix in the current effect.
             */
            virtual void SetProjection(const SceneR::Framework::Matrix& projection) = 0;

            /**
             * Gets the view matrix in the current effect.
             */
            virtual const SceneR::Framework::Matrix& GetView() const = 0;

            /**
             * Sets the view matrix in the current effect.
             */
            virtual void SetView(const SceneR::Framework::Matrix& view) = 0;

            /**
             * Gets the world matrix in the current effect.
             */
            virtual const SceneR::Framework::Matrix& GetWorld() const = 0;

            /**
             * Sets the world matrix in the current effect.
             */
            virtual void SetWorld(const SceneR::Framework::Matrix& world) = 0;
        };
    };
}

#endif  /* IEFFECTMATRICES_HPP */
