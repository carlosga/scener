// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/effect_parameter.hpp"

#include "scener/graphics/texture.hpp"
#include "scener/graphics/vulkan/constant_buffer.hpp"
#include "scener/math/basic_quaternion.hpp"
#include "scener/math/basic_vector.hpp"

namespace scener::graphics
{
    using scener::graphics::vulkan::constant_buffer;
    using scener::math::matrix4;
    using scener::math::quaternion;
    using scener::math::vector2;
    using scener::math::vector3;
    using scener::math::vector4;

    std::size_t effect_parameter::column_count() const noexcept
    {
        return _column_count;
    }

    const std::string& effect_parameter::name() const noexcept
    {
        return _name;
    }

    effect_parameter_class effect_parameter::parameter_class() const noexcept
    {
        return _parameter_class;
    }

    effect_parameter_type effect_parameter::parameter_type() const noexcept
    {
        return _parameter_type;
    }

    std::size_t effect_parameter::row_count() const noexcept
    {
        return _row_count;
    }

    const std::string& effect_parameter::semantic() const noexcept
    {
        return _semantic;
    }

    template <>
    std::vector<bool> effect_parameter::get_value() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    std::int32_t effect_parameter::get_value() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    std::vector<std::int32_t> effect_parameter::get_value() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    matrix4 effect_parameter::get_value() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    std::vector<matrix4> effect_parameter::get_value() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    matrix4 effect_parameter::get_value_transpose() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    std::vector<matrix4> effect_parameter::get_value_transpose() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    quaternion effect_parameter::get_value() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    std::vector<quaternion> effect_parameter::get_value() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    float effect_parameter::get_value() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    std::vector<float> effect_parameter::get_value() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    vector3 effect_parameter::get_value() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    std::vector<vector3> effect_parameter::get_value() const noexcept
    {
        throw std::runtime_error("Not implemented");
    }

    template<>
    void effect_parameter::set_value(const bool& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);
        Expects(_parameter_type  == effect_parameter_type::boolean);

        _constant_buffer->set_data(_offset, 1, &value);
    }

    template<>
    void effect_parameter::set_value(const std::int8_t& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);
        Expects(_parameter_type  == effect_parameter_type::byte);

        _constant_buffer->set_data(_offset, sizeof(std::int8_t), &value);
    }

    template<>
    void effect_parameter::set_value(const std::vector<std::int8_t>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);

        _constant_buffer->set_data(_offset, sizeof(std::int8_t) * value.size(), value.data());
    }

    template<>
    void effect_parameter::set_value(const std::uint8_t& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);
        Expects(_parameter_type  == effect_parameter_type::byte);

        _constant_buffer->set_data(_offset, sizeof(std::uint8_t), &value);
    }

    template<>
    void effect_parameter::set_value(const std::vector<std::uint8_t>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);

        _constant_buffer->set_data(_offset, sizeof(std::uint8_t) * value.size(), value.data());
    }

    template<>
    void effect_parameter::set_value(const std::int16_t& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);
        Expects(_parameter_type  == effect_parameter_type::int16);

        _constant_buffer->set_data(_offset, sizeof(std::int16_t), &value);
    }

    template<>
    void effect_parameter::set_value(const std::vector<std::int16_t>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);
        Expects(_parameter_type  == effect_parameter_type::int16);

        _constant_buffer->set_data(_offset, sizeof(std::int16_t) * value.size(), value.data());
    }

    template<>
    void effect_parameter::set_value(const std::uint16_t& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);

        _constant_buffer->set_data(_offset, sizeof(std::uint16_t), &value);
    }

    template<>
    void effect_parameter::set_value(const std::vector<std::uint16_t>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);

        _constant_buffer->set_data(_offset, sizeof(std::uint16_t) * value.size(), value.data());
    }

    template<>
    void effect_parameter::set_value(const std::int32_t& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);
        Expects(_parameter_type  == effect_parameter_type::int32);

        _constant_buffer->set_data(_offset, sizeof(std::int32_t), &value);
    }

    template<>
    void effect_parameter::set_value(const std::vector<std::int32_t>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);
        Expects(_parameter_type  == effect_parameter_type::int32);

        _constant_buffer->set_data(_offset, sizeof(std::int32_t) * value.size(), value.data());
    }

    template<>
    void effect_parameter::set_value(const std::uint32_t& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);

        _constant_buffer->set_data(_offset, sizeof(std::uint32_t), &value);
    }

    template<>
    void effect_parameter::set_value(const std::vector<std::uint32_t>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);

        _constant_buffer->set_data(_offset, sizeof(std::uint32_t) * value.size(), value.data());
    }

    template<>
    void effect_parameter::set_value(const matrix4& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::matrix);

        _constant_buffer->set_data(_offset, sizeof(matrix4), value.data());
    }

    template<>
    void effect_parameter::set_value(const std::vector<matrix4>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::matrix);

        _constant_buffer->set_data(_offset, sizeof(matrix4) * value.size(), value.data());
    }

    template<>
    void effect_parameter::set_value_transpose(const matrix4& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::matrix);

        const auto transpose = scener::math::matrix::transpose(value);

        _constant_buffer->set_data(_offset, sizeof(matrix4), transpose.data());
    }

    template<>
    void effect_parameter::set_value_transpose(const std::vector<matrix4>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::matrix);

        std::vector<matrix4> transposed;

        transposed.reserve(value.size());

        for (const auto& matrix : value)
        {
            transposed.push_back(scener::math::matrix::transpose(matrix));
        }

        _constant_buffer->set_data(_offset, sizeof(matrix4) * transposed.size(), transposed.data());
    }

    template<>
    void effect_parameter::set_value(const quaternion& value) const noexcept
    {
        _constant_buffer->set_data(_offset, sizeof(quaternion), value.data());
    }

    template<>
    void effect_parameter::set_value(const std::vector<quaternion>& value) const noexcept
    {
        _constant_buffer->set_data(_offset, sizeof(quaternion) * value.size(), value.data());
    }

    template<>
    void effect_parameter::set_value(const float& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);
        Expects(_parameter_type  == effect_parameter_type::single);

        _constant_buffer->set_data(_offset, sizeof(float), &value);
    }

    template<>
    void effect_parameter::set_value(const std::vector<float>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::scalar);
        Expects(_parameter_type  == effect_parameter_type::single);

        _constant_buffer->set_data(_offset, sizeof(float) * value.size(), value.data());
    }

    template<>
    void effect_parameter::set_value(const std::string& value) const noexcept
    {
        Expects(_parameter_type  == effect_parameter_type::string);

        throw std::runtime_error("not implemented");
    }

    template<>
    void effect_parameter::set_value(const vector2& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::vector);

        _constant_buffer->set_data(_offset, sizeof(vector2), value.data());
    }

    template<>
    void effect_parameter::set_value(const std::vector<vector2>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::vector);

        _constant_buffer->set_data(_offset, sizeof(vector2) * value.size(), value.data());
    }

    template<>
    void effect_parameter::set_value(const vector3& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::vector);

        _constant_buffer->set_data(_offset, sizeof(vector3), value.data());
    }

    template<>
    void effect_parameter::set_value(const std::vector<vector3>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::vector);

        _constant_buffer->set_data(_offset, sizeof(vector3) * value.size(), value.data());
    }

    template<>
    void effect_parameter::set_value(const vector4& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::vector);

        _constant_buffer->set_data(_offset, sizeof(vector4), value.data());
    }

    template<>
    void effect_parameter::set_value(const std::vector<vector4>& value) const noexcept
    {
        Expects(_parameter_class == effect_parameter_class::vector);

        _constant_buffer->set_data(_offset, sizeof(vector4) * value.size(), value.data());
    }
}
