// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_EFFECTPARAMETER_HPP
#define GRAPHICS_EFFECTPARAMETER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Framework
    {
        struct Matrix;
    }

    namespace Graphics
    {
        class UniformBufferObject;

        /**
         * Represents an EffectTechnique parameter.
         */
        class EffectParameter final
        {
        public:
            /**
             * Initializes a new instance of the EffectParameter class.
             */
            EffectParameter() = default;

            /**
             * Copy constructor.
             */
            EffectParameter(const EffectParameter& parameter) = default;

            /**
             * Destructor
             */
            ~EffectParameter() = default;

        public:
            /**
             * Gets the number of columns in the parameter description.
             */
            std::size_t column_count() const noexcept;

            /**
             * Gets the name of the parameter.
             */
            const std::string& name() const noexcept;

            /**
             * Gets the class of the parameter.
             */
            const EffectParameterClass& parameter_class() const noexcept;

            /**
             * Gets the type of the parameter.
             */
            const EffectParameterType& parameter_type() const noexcept;

            /**
             * Gets the number of rows in the parameter description.
             */
            std::size_t row_count() const noexcept;

            /**
             * Gets the semantic meaning, or usage, of the parameter.
             * @return the semantic meaning, or usage, of the parameter.
             */
            std::string semantic() const noexcept;

        public:
            /**
             * Get the effect parameter value.
             */
            template <typename T>
            T get_value() const;

            /**
             * Get the effect parameter value.
             */
            template <typename T
                    , typename = std::enable_if_t<std::is_assignable<T, SceneR::Framework::Matrix>::value
                                               || std::is_assignable<T, std::vector<SceneR::Framework::Matrix>>::value>>
            T get_value_transpose() const;

        public:
            /**
             * Sets the value of the EffectParameter.
             * @param value the value to assign to the EffectParameter.
             */
            template <typename T>
            void set_value(const T& value) const;

            template <typename T
                    , typename = std::enable_if_t<std::is_assignable<T, SceneR::Framework::Matrix>::value
                                               || std::is_assignable<T, std::vector<SceneR::Framework::Matrix>>::value>>
            void set_value_transpose(const T& value) const;

        public:
            EffectParameter& operator=(const EffectParameter& parameter) = default;

        private:
            std::string _name         { };
            std::size_t _column_count { 0 };
            std::size_t _row_count    { 0 };
            std::size_t _count        { 0 };
            std::size_t _offset       { 0 };
            std::string _semantic     { };
            std::string _node         { };
            std::string _value        { };

            EffectParameterClass _parameter_class = EffectParameterClass::Scalar;
            EffectParameterType  _parameter_type  = EffectParameterType::Single;
            UniformBufferObject* _uniform_buffer  = nullptr;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_EFFECTPARAMETER_HPP
