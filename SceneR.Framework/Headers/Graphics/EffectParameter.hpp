// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECTPARAMETER_HPP
#define EFFECTPARAMETER_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <Graphics/Effect.hpp>
#include <Graphics/EffectParameterCollection.hpp>

namespace SceneR
{
    namespace Content
    {
        class TechniquesReader;
    }

    namespace Framework
    {
        struct Matrix;
        struct Quaternion;
        struct Vector2;
        struct Vector3;
        struct Vector4;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Texture;
        class UniformBufferObject;

        /**
         * Represents an Effect parameter.
         */
        class EffectParameter final
        {
        public:
            /**
             * Initializes a new instance of the EffectParameter class.
             */
            EffectParameter();

            /**
             * Copy constructor.
             */
            EffectParameter(const EffectParameter& parameter);

            /**
             * Destructor
             */
            ~EffectParameter();

        public:
            /**
             * Gets the number of columns in the parameter description.
             */
            std::size_t column_count() const;

            /**
             * Gets the name of the parameter.
             */
            const std::u16string& name() const;

            /**
             * Gets the class of the parameter.
             */
            const EffectParameterClass& parameter_class() const;

            /**
             * Gets the type of the parameter.
             */
            const EffectParameterType& parameter_type() const;

            /**
             * Gets the number of rows in the parameter description.
             */
            std::size_t row_count() const;

            /**
             * Gets the semantic meaning, or usage, of the parameter.
             * @return the semantic meaning, or usage, of the parameter.
             */
            std::u16string semantic() const;

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
            EffectParameter& operator=(const EffectParameter& parameter);

        private:
            void describe(const std::int32_t& type);

        private:
            std::u16string _name;
            std::size_t    _column_count;
            std::size_t    _row_count;
            std::size_t    _count;
            std::size_t    _offset;
            std::u16string _semantic;
            std::u16string _node;
            std::u16string _value;

            EffectParameterClass _parameter_class;
            EffectParameterType  _parameter_type;

            std::shared_ptr<UniformBufferObject> _uniform_buffer;

            friend class SceneR::Content::TechniquesReader;
        };
    }
}

#endif  /* EFFECTPARAMETER_HPP */
