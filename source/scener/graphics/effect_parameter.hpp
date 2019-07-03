// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECT_PARAMETER_HPP
#define SCENER_GRAPHICS_EFFECT_PARAMETER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "scener/graphics/effect_parameter_class.hpp"
#include "scener/graphics/effect_parameter_type.hpp"
#include "scener/math/matrix.hpp"

namespace scener::content::readers { template <typename T> class content_type_reader; }

namespace scener::graphics
{
    class constant_buffer;

    /// Represents an EffectTechnique parameter.
    class effect_parameter final
    {
    public:
        /// Gets the number of columns in the parameter description.
        std::size_t column_count() const noexcept;

        /// Gets the name of the parameter.
        const std::string& name() const noexcept;

        /// Gets the class of the parameter.
        effect_parameter_class parameter_class() const noexcept;

        /// Gets the type of the parameter.
        effect_parameter_type parameter_type() const noexcept;

        /// Gets the number of rows in the parameter description.
        std::size_t row_count() const noexcept;

        /// Gets the semantic meaning, or usage, of the parameter.
        /// \returns the semantic meaning, or usage, of the parameter.
        const std::string& semantic() const noexcept;

    public:
        /// Get the effect parameter value.
        template <typename T>
        T get_value() const noexcept;

        /// Gets the value of the EffectParameter as a Matrix transpose.
        template <typename T
                , typename = std::enable_if_t<std::is_assignable<T, scener::math::matrix4>::value
                                        || std::is_assignable<T, std::vector<scener::math::matrix4>>::value>>
        T get_value_transpose() const noexcept;

    public:
        /// Sets the value of the EffectParameter.
        /// @param value the value to assign to the EffectParameter.
        template <typename T>
        void set_value(const T& value) const noexcept;

        /// Sets the value of the EffectParameter to the transpose of a Matrix.
        template <typename T
                , typename = std::enable_if_t<std::is_assignable<T, scener::math::matrix4>::value
                                        || std::is_assignable<T, std::vector<scener::math::matrix4>>::value>>
        void set_value_transpose(const T& value) const noexcept;

    private:
        std::uint32_t          _column_count    { 0 };
        std::uint32_t          _row_count       { 0 };
        std::uint32_t          _count           { 0 };
        std::uint32_t          _offset          { 0 };
        effect_parameter_class _parameter_class { effect_parameter_class::scalar };
        effect_parameter_type  _parameter_type  { effect_parameter_type::single };
        constant_buffer*       _constant_buffer { nullptr };
        std::string            _name            { };
        std::string            _semantic        { };
        std::string            _value           { };
        std::string            _uniform_name    { };

        template <typename T> friend class scener::content::readers::content_type_reader;
    };
}

#endif // SCENER_GRAPHICS_EFFECT_PARAMETER_HPP
