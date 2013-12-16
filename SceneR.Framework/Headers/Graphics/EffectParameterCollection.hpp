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
             * Releases all resources being used by this EffectParameterCollection.
             */
            virtual ~EffectParameterCollection();

        public:
            const System::Size Count() const;

        public:
            EffectParameter& operator[](const System::Int32& parameterIndex);
            const EffectParameter& operator[](const System::Int32& parameterIndex) const;
            EffectParameter& operator[](const System::String& parameterName);
            const EffectParameter& operator[](const System::String& parameterName) const;

        private:
            void Add(const System::String&       name,
                     const EffectParameterClass& parameterClass,
                     const EffectParameterType&  parameterType,
                     const System::Int32&        parameterLocation);

        private:
            std::vector<EffectParameter> parameters;

            friend class ShaderProgram;
        };
    }
}

#endif /* EFFECTPARAMETERCOLLECTION_HPP */
