// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECTPARAMETER_HPP
#define SCENER_GRAPHICS_EFFECTPARAMETER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "SceneR/Graphics/EffectParameterClass.hpp"
#include "SceneR/Graphics/EffectParameterType.hpp"

namespace SceneR { namespace Content { namespace Readers { template <typename T> class ContentTypeReader; } } }

namespace SceneR { namespace Graphics { namespace OpenGL { class ConstantBuffer; } } }

namespace SceneR { namespace Math { struct Matrix; } }

namespace SceneR { namespace Graphics {

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
    EffectParameterClass parameter_class() const noexcept;

    /**
     * Gets the type of the parameter.
     */
    EffectParameterType parameter_type() const noexcept;

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
    T get_value() const noexcept;

    /**
     * Get the effect parameter value.
     */
    template <typename T
            , typename = std::enable_if_t<std::is_assignable<T, SceneR::Math::Matrix>::value
                                       || std::is_assignable<T, std::vector<SceneR::Math::Matrix>>::value>>
    T get_value_transpose() const noexcept;

public:
    /**
     * Sets the value of the EffectParameter.
     * @param value the value to assign to the EffectParameter.
     */
    template <typename T>
    void set_value(const T& value) const noexcept;

    template <typename T
            , typename = std::enable_if_t<std::is_assignable<T, SceneR::Math::Matrix>::value
                                       || std::is_assignable<T, std::vector<SceneR::Math::Matrix>>::value>>
    void set_value_transpose(const T& value) const noexcept;

public:
    EffectParameter& operator=(const EffectParameter& parameter) = default;

private:
    std::size_t             _column_count    { 0 };
    std::size_t             _row_count       { 0 };
    std::size_t             _count           { 0 };
    std::size_t             _offset          { 0 };
    EffectParameterClass    _parameter_class { EffectParameterClass::scalar };
    EffectParameterType     _parameter_type  { EffectParameterType::single };
    OpenGL::ConstantBuffer* _constant_buffer { nullptr };
    std::string             _name            { };
    std::string             _semantic        { };
    std::string             _value           { };
    std::string             _uniform_name    { };

    template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_EFFECTPARAMETER_HPP
