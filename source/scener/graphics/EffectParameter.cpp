// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/EffectParameter.hpp"

#include "scener/graphics/Texture.hpp"
#include "scener/graphics/opengl/ConstantBuffer.hpp"
#include "scener/math/basic_quaternion.hpp"
#include "scener/math/basic_vector.hpp"

namespace scener { namespace graphics {

namespace sml = scener::math;

using scener::graphics::opengl::ConstantBuffer;
using sml::matrix4;
using sml::quaternion;
using sml::vector2;
using sml::vector3;
using sml::vector4;

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

const std::string& EffectParameter::semantic() const noexcept
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
matrix4 EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
std::vector<matrix4> EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
matrix4 EffectParameter::get_value_transpose() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
std::vector<matrix4> EffectParameter::get_value_transpose() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
quaternion EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
std::vector<quaternion> EffectParameter::get_value() const noexcept
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
vector3 EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
std::vector<vector3> EffectParameter::get_value() const noexcept
{
    throw std::runtime_error("Not implemented");
}

template<>
void EffectParameter::set_value(const bool& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::boolean);

    _constant_buffer->set_data(_offset, 1, &value);
}

template<>
void EffectParameter::set_value(const std::int8_t& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::byte);

    _constant_buffer->set_data(_offset, sizeof(std::int8_t), &value);
}

template<>
void EffectParameter::set_value(const std::vector<std::int8_t>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);

    _constant_buffer->set_data(_offset, sizeof(std::int8_t) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const std::uint8_t& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);
    Expects(_parameter_type  == EffectParameterType::byte);

    _constant_buffer->set_data(_offset, sizeof(std::uint8_t), &value);
}

template<>
void EffectParameter::set_value(const std::vector<std::uint8_t>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::scalar);

    _constant_buffer->set_data(_offset, sizeof(std::uint8_t) * value.size(), value.data());
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
void EffectParameter::set_value(const matrix4& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::matrix);

    _constant_buffer->set_data(_offset, sizeof(matrix4), value.data());
}

template<>
void EffectParameter::set_value(const std::vector<matrix4>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::matrix);

    _constant_buffer->set_data(_offset, sizeof(matrix4) * value.size(), value.data());
}

template<>
void EffectParameter::set_value_transpose(const matrix4& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::matrix);

    const auto transpose = sml::matrix::transpose(value);

    _constant_buffer->set_data(_offset, sizeof(matrix4), transpose.data());
}

template<>
void EffectParameter::set_value_transpose(const std::vector<matrix4>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::matrix);

    std::vector<matrix4> transposed;

    transposed.reserve(value.size());

    for (const auto& matrix4 : value)
    {
        transposed.push_back(sml::matrix::transpose(matrix4));
    }

    _constant_buffer->set_data(_offset, sizeof(matrix4) * transposed.size(), transposed.data());
}

template<>
void EffectParameter::set_value(const quaternion& value) const noexcept
{
    _constant_buffer->set_data(_offset, sizeof(quaternion), value.data());
}

template<>
void EffectParameter::set_value(const std::vector<quaternion>& value) const noexcept
{
    _constant_buffer->set_data(_offset, sizeof(quaternion) * value.size(), value.data());
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
void EffectParameter::set_value(const vector2& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(vector2), value.data());
}

template<>
void EffectParameter::set_value(const std::vector<vector2>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(vector2) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const vector3& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(vector3), value.data());
}

template<>
void EffectParameter::set_value(const std::vector<vector3>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(vector3) * value.size(), value.data());
}

template<>
void EffectParameter::set_value(const vector4& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(vector4), value.data());
}

template<>
void EffectParameter::set_value(const std::vector<vector4>& value) const noexcept
{
    Expects(_parameter_class == EffectParameterClass::vector);

    _constant_buffer->set_data(_offset, sizeof(vector4) * value.size(), value.data());
}

}}
