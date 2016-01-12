// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/EffectParameter.hpp"

#include "SceneR/Graphics/Texture.hpp"
#include "SceneR/Graphics/OpenGL/ConstantBuffer.hpp"
#include "SceneR/Math/Matrix.hpp"
#include "SceneR/Math/Quaternion.hpp"
#include "SceneR/Math/Vector2.hpp"
#include "SceneR/Math/Vector3.hpp"
#include "SceneR/Math/Vector4.hpp"

namespace SceneR { namespace Graphics {

using SceneR::Graphics::OpenGL::ConstantBuffer;
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

EffectParameterClass EffectParameter::parameter_class() const noexcept
{
    return _parameter_class;
}

EffectParameterType EffectParameter::parameter_type() const noexcept
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
std::vector<bool> EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
std::int32_t EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
std::vector<std::int32_t> EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
Matrix EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
std::vector<Matrix> EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
Matrix EffectParameter::get_value_transpose() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
std::vector<Matrix> EffectParameter::get_value_transpose() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
Quaternion EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
std::vector<Quaternion> EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
float EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
std::vector<float> EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
Vector3 EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
std::vector<Vector3> EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
void EffectParameter::set_value(const bool& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::boolean);

    // _uniform_buffer->set_data(_offset, 1, &value);
}

template<>
void EffectParameter::set_value(const std::vector<bool>& value) const noexcept
{
    Expects(_parameter_type == EffectParameterType::boolean);

    // _uniform_buffer->set_data(_offset, value.size(), value.data());
}

template<>
void EffectParameter::set_value(const std::int8_t& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::byte);

    // _uniform_buffer->set_data(_offset, sizeof(std::int8_t), &value);
}

template<>
void EffectParameter::set_value(const std::vector<std::int8_t>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::byte);

    // _uniform_buffer->set_data(_offset, sizeof(std::int8_t) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const std::uint8_t& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);

    // _uniform_buffer->set_data(_offset, sizeof(std::uint8_t), &value);
}

template<>
void EffectParameter::set_value(const std::vector<std::uint8_t>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);

    // _uniform_buffer->set_data(_offset, sizeof(std::uint8_t) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const std::int16_t& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::int16);

    _constant_buffer->set_data(_offset, sizeof(std::int16_t), &value);
}

template<>
void EffectParameter::set_value(const std::vector<std::int16_t>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::int16);

    _constant_buffer->set_data(_offset, sizeof(std::int16_t) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const std::uint16_t& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);

    _constant_buffer->set_data(_offset, sizeof(std::uint16_t), &value);
}

template<>
void EffectParameter::set_value(const std::vector<std::uint16_t>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);

    _constant_buffer->set_data(_offset, sizeof(std::uint16_t) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const std::int32_t& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::int32);

    _constant_buffer->set_data(_offset, sizeof(std::int32_t), &value);
}

template<>
void EffectParameter::set_value(const std::vector<std::int32_t>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::int32);

    _constant_buffer->set_data(_offset, sizeof(std::int32_t) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const std::uint32_t& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);

    _constant_buffer->set_data(_offset, sizeof(std::uint32_t), &value);
}

template<>
void EffectParameter::set_value(const std::vector<std::uint32_t>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);

    _constant_buffer->set_data(_offset, sizeof(std::uint32_t) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const Matrix& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::matrix);

    _constant_buffer->set_data(_offset, sizeof(Matrix), &value[0]);
}

template<>
void EffectParameter::set_value(const std::vector<Matrix>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::matrix);

    _constant_buffer->set_data(_offset, sizeof(Matrix) * value.size(), value.data());
}

template<>
void EffectParameter::set_value_transpose(const Matrix& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::matrix);

    const auto transpose = Matrix::transpose(value);

    _constant_buffer->set_data(_offset, sizeof(Matrix), &transpose[0]);
}

template<>
void EffectParameter::set_value_transpose(const std::vector<Matrix>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::matrix);

    std::vector<Matrix> transposed;

    transposed.reserve(value.size());

    for (const auto& matrix : value)
    {
        transposed.push_back(Matrix::transpose(matrix));
    }

    _constant_buffer->set_data(_offset, sizeof(Matrix) * transposed.size(), transposed.data());
}

template<>
void EffectParameter::set_value(const Quaternion& value) const noexcept
{
    _constant_buffer->set_data(_offset, sizeof(Quaternion), &value[0]);
}

template<>
void EffectParameter::set_value(const std::vector<Quaternion>& value) const noexcept
{
    _constant_buffer->set_data(_offset, sizeof(Quaternion) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const float& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::single);

    _constant_buffer->set_data(_offset, sizeof(float), &value);
}

template<>
void EffectParameter::set_value(const std::vector<float>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::single);

    _constant_buffer->set_data(_offset, sizeof(float) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const std::string& value) const noexcept
{
    Expects(_parameter_type  == EffectParameterType::string);

    throw std::runtime_error("not implemented");
}

template<>
void EffectParameter::set_value(const Vector2& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(Vector2), &value[0]);
}

template<>
void EffectParameter::set_value(const std::vector<Vector2>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(Vector2) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const Vector3& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(Vector3), &value[0]);
}

template<>
void EffectParameter::set_value(const std::vector<Vector3>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(Vector3) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const Vector4& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(Vector4), &value[0]);
}

template<>
void EffectParameter::set_value(const std::vector<Vector4>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(Vector4) * value.size(), value.data());
}

}}
