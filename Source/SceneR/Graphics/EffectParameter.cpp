// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/EffectParameter.hpp>

#include <Math/Matrix.hpp>
#include <Math/Quaternion.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/UniformBufferObject.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Math::Matrix;
        using SceneR::Math::Quaternion;
        using SceneR::Math::Vector2;
        using SceneR::Math::Vector3;
        using SceneR::Math::Vector4;

        std::size_t EffectParameter::column_count() const noexcept
        {
            return _column_count;
        }

        const std::string& EffectParameter::name() const noexcept
        {
            return _name;
        }

        const EffectParameterClass& EffectParameter::parameter_class() const noexcept
        {
            return _parameter_class;
        }

        const EffectParameterType& EffectParameter::parameter_type() const noexcept
        {
            return _parameter_type;
        }

        std::size_t EffectParameter::row_count() const noexcept
        {
            return _row_count;
        }

        std::string EffectParameter::semantic() const noexcept
        {
            return _semantic;
        }

        template <>
        std::vector<bool> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        std::int32_t EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        std::vector<std::int32_t> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        Matrix EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        std::vector<Matrix> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        Matrix EffectParameter::get_value_transpose() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        std::vector<Matrix> EffectParameter::get_value_transpose() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        Quaternion EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        std::vector<Quaternion> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        float EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        std::vector<float> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        Vector3 EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        std::vector<Vector3> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        void EffectParameter::set_value(const bool& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);
            Expects(_parameter_type  == EffectParameterType::Bool);

            // _uniform_buffer->set_data(_offset, 1, &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<bool>& value) const
        {
            Expects(_parameter_type == EffectParameterType::Bool);

            // _uniform_buffer->set_data(_offset, value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const std::int8_t& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);
            Expects(_parameter_type  == EffectParameterType::Byte);

            // _uniform_buffer->set_data(_offset, sizeof(std::int8_t), &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<std::int8_t>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);
            Expects(_parameter_type  == EffectParameterType::Byte);

            // _uniform_buffer->set_data(_offset, sizeof(std::int8_t) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const std::uint8_t& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);

            // _uniform_buffer->set_data(_offset, sizeof(std::uint8_t), &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<std::uint8_t>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);

            // _uniform_buffer->set_data(_offset, sizeof(std::uint8_t) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const std::int16_t& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);
            Expects(_parameter_type  == EffectParameterType::Int16);

            _uniform_buffer->set_data(_offset, sizeof(std::int16_t), &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<std::int16_t>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);
            Expects(_parameter_type  == EffectParameterType::Int16);

            _uniform_buffer->set_data(_offset, sizeof(std::int16_t) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const std::uint16_t& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);

            _uniform_buffer->set_data(_offset, sizeof(std::uint16_t), &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<std::uint16_t>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);

            _uniform_buffer->set_data(_offset, sizeof(std::uint16_t) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const std::int32_t& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);
            Expects(_parameter_type  == EffectParameterType::Int32);

            _uniform_buffer->set_data(_offset, sizeof(std::int32_t), &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<std::int32_t>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);
            Expects(_parameter_type  == EffectParameterType::Int32);

            _uniform_buffer->set_data(_offset, sizeof(std::int32_t) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const std::uint32_t& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);

            _uniform_buffer->set_data(_offset, sizeof(std::uint32_t), &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<std::uint32_t>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);

            _uniform_buffer->set_data(_offset, sizeof(std::uint32_t) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const Matrix& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Matrix);

            _uniform_buffer->set_data(_offset, sizeof(Matrix), &value[0]);
        }

        template<>
        void EffectParameter::set_value(const std::vector<Matrix>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Matrix);

            _uniform_buffer->set_data(_offset, sizeof(Matrix) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value_transpose(const Matrix& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Matrix);

            const auto transpose = Matrix::transpose(value);

            _uniform_buffer->set_data(_offset, sizeof(Matrix), &transpose[0]);
        }

        template<>
        void EffectParameter::set_value_transpose(const std::vector<Matrix>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Matrix);

            std::vector<Matrix> transposed;

            transposed.reserve(value.size());

            for (const auto& matrix : value)
            {
                transposed.push_back(Matrix::transpose(matrix));
            }

            _uniform_buffer->set_data(_offset, sizeof(Matrix) * transposed.size(), transposed.data());
        }

        template<>
        void EffectParameter::set_value(const Quaternion& value) const
        {
            _uniform_buffer->set_data(_offset, sizeof(Quaternion), &value[0]);
        }

        template<>
        void EffectParameter::set_value(const std::vector<Quaternion>& value) const
        {
            _uniform_buffer->set_data(_offset, sizeof(Quaternion) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const float& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);
            Expects(_parameter_type  == EffectParameterType::Single);

            _uniform_buffer->set_data(_offset, sizeof(float), &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<float>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Scalar);
            Expects(_parameter_type  == EffectParameterType::Single);

            _uniform_buffer->set_data(_offset, sizeof(float) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const std::string& value) const
        {
            Expects(_parameter_type  == EffectParameterType::String);

            throw std::runtime_error("not implemented");
        }

        template<>
        void EffectParameter::set_value(const Vector2& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Vector);

            _uniform_buffer->set_data(_offset, sizeof(Vector2), &value[0]);
        }

        template<>
        void EffectParameter::set_value(const std::vector<Vector2>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Vector);

            _uniform_buffer->set_data(_offset, sizeof(Vector2) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const Vector3& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Vector);

            _uniform_buffer->set_data(_offset, sizeof(Vector3), &value[0]);
        }

        template<>
        void EffectParameter::set_value(const std::vector<Vector3>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Vector);

            _uniform_buffer->set_data(_offset, sizeof(Vector3) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const Vector4& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Vector);

            _uniform_buffer->set_data(_offset, sizeof(Vector4), &value[0]);
        }

        template<>
        void EffectParameter::set_value(const std::vector<Vector4>& value) const
        {
            Expects(_parameter_class == EffectParameterClass::Vector);

            _uniform_buffer->set_data(_offset, sizeof(Vector4) * value.size(), value.data());
        }
    }
}
