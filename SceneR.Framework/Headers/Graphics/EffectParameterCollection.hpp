// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECTPARAMETERCOLLECTION_HPP
#define EFFECTPARAMETERCOLLECTION_HPP

#include <memory>
#include <vector>

#include <System/Core.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class EffectParameter;
        class UniformBufferObject;

        /**
         * Represents a collection of EffectParameter
         */
        class EffectParameterCollection final
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
             * @param index the parameter index.
             * @param offset the parameter offset.
             * @param type the parameter raw type.
             * @param uniformBuffer the uniform buffer object.
             */
            EffectParameter& Add(const System::String&                name
                               , const System::UInt32&                index
                               , const System::UInt32&                offset
                               , const System::UInt32&                type
                               , std::shared_ptr<UniformBufferObject> uniformBuffer);

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
