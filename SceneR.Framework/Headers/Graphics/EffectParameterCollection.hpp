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

#ifndef EFFECTPARAMETERCOLLECTION_HPP
#define EFFECTPARAMETERCOLLECTION_HPP

#include <memory>
#include <vector>

#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class EffectParameter;
        class ShaderProgram;

        /**
         * Represents a collection of EffectParameter
         */
        class EffectParameterCollection
        {
        public:
            /**
             * Initializes a new instance of the EffectParameterCollection class.
             */
            EffectParameterCollection();

            /**
             * Initializes a new instance of the EffectParameterCollection class.
             */
            EffectParameterCollection(const EffectParameterCollection& parameters);

            /**
             * Releases all resources being used by this EffectParameterCollection.
             */
            ~EffectParameterCollection();

        public:
            /**
             * Gets the number of EffectParameter objects in this EffectParameterCollection.
             */
            System::Size Count() const;

            /**
             * Adds a new EffectParamter in this EffectParameterCollection.
             * @param name the parameter name.
             * @param parameterClass the parameter class.
             * @param parameterType the parameter type.
             * @param shader the associated shader.
             */
            EffectParameter& Add(const System::String&                 name
                               , const EffectParameterClass&           parameterClass
                               , const EffectParameterType&            parameterType
                               , const std::shared_ptr<ShaderProgram>& shader);

        public:
            EffectParameter& operator[](const System::Size& parameterIndex);
            const EffectParameter& operator[](const System::Size& parameterIndex) const;
            EffectParameter& operator[](const System::String& parameterName);
            const EffectParameter& operator[](const System::String& parameterName) const;

        private:
            std::vector<EffectParameter> parameters;
        };
    }
}

#endif /* EFFECTPARAMETERCOLLECTION_HPP */
