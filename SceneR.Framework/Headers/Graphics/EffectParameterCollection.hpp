/*
 * EffectParameterCollection.hpp
 *
 *  Created on: Dec 11, 2013
 *      Author: carlos
 */

#ifndef EFFECTPARAMETERCOLLECTION_HPP
#define EFFECTPARAMETERCOLLECTION_HPP

#include <Graphics/EffectParameter.hpp>
#include <System/Core.hpp>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
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
            virtual ~EffectParameterCollection();

        public:
            System::Size Count() const;

            void Add(const System::String&                 name,
                     const EffectParameterClass&           parameterClass,
                     const EffectParameterType&            parameterType,
                     const std::shared_ptr<ShaderProgram>& shaderProgram);

        public:
            EffectParameter& operator[](const System::Int32& parameterIndex);
            const EffectParameter& operator[](const System::Int32& parameterIndex) const;
            EffectParameter& operator[](const System::String& parameterName);
            const EffectParameter& operator[](const System::String& parameterName) const;

        private:
            std::vector<EffectParameter> parameters;
        };
    }
}

#endif /* EFFECTPARAMETERCOLLECTION_HPP */
