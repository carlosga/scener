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

#ifndef POINTLIGHTBASE_HPP
#define POINTLIGHTBASE_HPP

#include <System/Core.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/Light.hpp>

namespace SceneR
{
    namespace Framework
    {
        class Color;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Abstract base class that represents a light object that has a position in space
         * and projects its light in all directions.
         */
        class PointLightBase : public Light
        {
        public:
            /**
             * Gets a constant value by which the intensity of the light diminishes over distance.
             * @return a constant value by which the intensity of the light diminishes over distance.
             */
            const System::Single GetConstantAttenuation() const;

            /**
             * Sets a constant value by which the intensity of the light diminishes over distance.
             * @param constantAttenuation a constant value by which the intensity of the light diminishes over distance.
             */
            void SetConstantAttenuation(const System::Single constantAttenuation);

            /**
             * Gets a value that specifies the linear diminution of the light's intensity over distance.
             * @return a value that specifies the linear diminution of the light's intensity over distance.
             */
            const System::Single GetLinearAttenuation() const;

            /**
             * Sets a value that specifies the linear diminution of the light's intensity over distance.
             * @param linearAttenuation a value that specifies the linear diminution of the light's intensity over
             *                          distance.
             */
            void SetLinearAttenuation(const System::Single linearAttenuation);

            /**
             * Gets a value that specifies the diminution of the light's effect over distance,
             * calculated by a quadratic operation.
             * @return a value that specifies the diminution of the light's effect over distance,
             *         calculated by a quadratic operation.
             */
            const System::Single GetQuadraticAttenuation() const;

            /**
             * Gets a value that specifies the diminution of the light's effect over distance,
             * calculated by a quadratic operation.
             * @param quadraticAttenuation a value that specifies the diminution of the light's effect over distance,
             *        calculated by a quadratic operation.
             */
            void SetQuadraticAttenuation(const System::Single quadraticAttenuation);

            /**
             * Gets a Vector3 that specifies the light's position in world space.
             * @return a Vector3 that specifies the light's position in world space.
             */
            const SceneR::Framework::Vector3& GetPosition() const;

            /**
             * Sets a Vector3 that specifies the light's position in world space.
             * @param position a Vector3 that specifies the light's position in world space.
             */
            void SetPosition(const SceneR::Framework::Vector3& position);

            /**
             * Gets the distance beyond which the light has no effect.
             * @return the distance beyond which the light has no effect.
             */
            const System::Single GetRange() const;

            /**
             * Gets the distance beyond which the light has no effect.
             * @param range the distance beyond which the light has no effect.
             */
            void SetRange(const System::Single range);

            /**
             * Gets the total attenuation of this light given a distance as defined by the collada specification.
             * @param distance the distance.
             */
            const System::Single GetTotalAttenuation(const System::Single distance) const;

        protected:
            /**
             * Initializes a new instance of the PointLightBase class.
             */
            PointLightBase();

            /**
             * Initializes a new instance of the PointLightBase class with the given color and position.
             * @param color the light diffuse color.
             * @param position the light position in world space.
             */
            PointLightBase(const SceneR::Framework::Color&   diffuseColor,
                           const SceneR::Framework::Vector3& position);

            /**
             * Releases all resources being used by the current PointLightBase
             */
            virtual ~PointLightBase() = default;

        protected:
            SceneR::Framework::Vector3 position;
            System::Single             range;
            System::Single             constantAttenuation;
            System::Single             linearAttenuation;
            System::Single             quadraticAttenuation;
        };
    }
}

#endif  /* POINTLIGHTBASE_HPP */
