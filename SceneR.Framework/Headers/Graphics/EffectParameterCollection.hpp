// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECTPARAMETERCOLLECTION_HPP
#define EFFECTPARAMETERCOLLECTION_HPP

#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Effect;
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
            size_t Count() const;

        public:
            EffectParameter& operator[](const size_t& parameterIndex);
            const EffectParameter& operator[](const size_t& parameterIndex) const;
            EffectParameter& operator[](const std::u16string& parameterName);
            const EffectParameter& operator[](const std::u16string& parameterName) const;

        private:
            EffectParameter& Add(const std::u16string&                name
                               , const uint32_t&                      index
                               , const uint32_t&                      offset
                               , const uint32_t&                      type
                               , std::shared_ptr<UniformBufferObject> uniformBuffer);

            void Clear();

        private:
            std::vector<EffectParameter> parameters;

            friend class Effect;
        };
    }
}

#endif /* EFFECTPARAMETERCOLLECTION_HPP */
