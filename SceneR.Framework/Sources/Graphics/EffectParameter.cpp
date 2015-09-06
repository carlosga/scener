// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/EffectParameter.hpp>

#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/UniformBufferObject.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Quaternion;
        using SceneR::Framework::Vector2;
        using SceneR::Framework::Vector3;
        using SceneR::Framework::Vector4;

        EffectParameter::EffectParameter()
            : _name             { }
            , _column_count     { 0 }
            , _row_count        { 0 }
            , _count            { 0 }
            , _offset           { 0 }
            , _semantic         {  }
            , _node             {  }
            , _value            {  }
            , _parameter_class  { EffectParameterClass::Scalar }
            , _parameter_type   { EffectParameterType::Single }
            , _uniform_buffer   { nullptr }
        {
        }

        EffectParameter::EffectParameter(const EffectParameter& parameter)
            : _name             { parameter._name }
            , _column_count     { parameter._column_count }
            , _row_count        { parameter._row_count }
            , _count            { parameter._count }
            , _offset           { parameter._offset }
            , _semantic         { parameter._semantic }
            , _node             { parameter._node }
            , _value            { parameter._value }
            , _parameter_class  { parameter._parameter_class }
            , _parameter_type   { parameter._parameter_type }
            , _uniform_buffer   { parameter._uniform_buffer }
        {
        }

        EffectParameter::~EffectParameter()
        {
        }

        std::size_t EffectParameter::column_count() const
        {
            return _column_count;
        }

        const std::u16string& EffectParameter::name() const
        {
            return _name;
        }

        const EffectParameterClass& EffectParameter::parameter_class() const
        {
            return _parameter_class;
        }

        const EffectParameterType& EffectParameter::parameter_type() const
        {
            return _parameter_type;
        }

        std::size_t EffectParameter::row_count() const
        {
            return _row_count;
        }

        std::u16string EffectParameter::semantic() const
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
        SceneR::Framework::Matrix EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        std::vector<SceneR::Framework::Matrix> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        SceneR::Framework::Matrix EffectParameter::get_value_transpose() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        std::vector<SceneR::Framework::Matrix> EffectParameter::get_value_transpose() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        SceneR::Framework::Quaternion EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        std::vector<SceneR::Framework::Quaternion> EffectParameter::get_value() const
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
        std::u16string EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        SceneR::Framework::Vector3 EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        std::vector<SceneR::Framework::Vector3> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        void EffectParameter::set_value(const bool& value) const
        {
            if (_parameter_class != EffectParameterClass::Scalar)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }
            if (_parameter_type != EffectParameterType::Bool)
            {
                throw std::runtime_error("Invalid effect parameter type.");
            }

            _uniform_buffer->set_data(_offset, 1, &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<bool>& value) const
        {
            if (_parameter_type != EffectParameterType::Bool)
            {
                throw std::runtime_error("Invalid effect parameter type.");
            }

            //_uniform_buffer->set_data(_offset, value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const std::int32_t& value) const
        {
            if (_parameter_class != EffectParameterClass::Scalar)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }
            if (_parameter_type != EffectParameterType::Int32)
            {
                throw std::runtime_error("Invalid effect parameter type.");
            }

            _uniform_buffer->set_data(_offset, sizeof(std::int32_t), &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<std::int32_t>& value) const
        {
            if (_parameter_class != EffectParameterClass::Scalar)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }
            if (_parameter_type != EffectParameterType::Int32)
            {
                throw std::runtime_error("Invalid effect parameter type.");
            }

            _uniform_buffer->set_data(_offset, sizeof(std::int32_t) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const std::uint32_t& value) const
        {
            if (_parameter_class != EffectParameterClass::Scalar)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(std::uint32_t), &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<std::uint32_t>& value) const
        {
            if (_parameter_class != EffectParameterClass::Scalar)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(std::uint32_t) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const Matrix& value) const
        {
            if (_parameter_class != EffectParameterClass::Matrix)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(Matrix), &value[0]);
        }

        template<>
        void EffectParameter::set_value(const std::vector<Matrix>& value) const
        {
            if (_parameter_class != EffectParameterClass::Matrix)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(Matrix) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value_transpose(const Matrix& value) const
        {
            if (_parameter_class != EffectParameterClass::Matrix)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            const auto transpose = Matrix::transpose(value);

            _uniform_buffer->set_data(_offset, sizeof(Matrix), &transpose[0]);
        }

        template<>
        void EffectParameter::set_value_transpose(const std::vector<Matrix>& value) const
        {
            if (_parameter_class != EffectParameterClass::Matrix)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

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
            if (_parameter_class != EffectParameterClass::Scalar)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }
            if (_parameter_type != EffectParameterType::Single)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(float), &value);
        }

        template<>
        void EffectParameter::set_value(const std::vector<float>& value) const
        {
            if (_parameter_class != EffectParameterClass::Scalar)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }
            if (_parameter_type != EffectParameterType::Single)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(float) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const std::u16string& value) const
        {
            throw std::runtime_error("Not implemented");
        }

        template<>
        void EffectParameter::set_value(const SceneR::Graphics::Texture& value) const
        {
            if (_parameter_class != EffectParameterClass::Object)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }
            if (_parameter_type != EffectParameterType::Texture2D)
            {
                throw std::runtime_error("Invalid effect parameter type.");
            }

            // _uniform_buffer->set_data(_offset,(_name, 0);
        }

        template<>
        void EffectParameter::set_value(const SceneR::Framework::Vector2& value) const
        {
            if (_parameter_class != EffectParameterClass::Vector)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(Vector2), &value[0]);
        }

        template<>
        void EffectParameter::set_value(const std::vector<SceneR::Framework::Vector2>& value) const
        {
            if (_parameter_class != EffectParameterClass::Vector)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(Vector2) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const Vector3& value) const
        {
            if (_parameter_class != EffectParameterClass::Vector)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(Vector3), &value[0]);
        }

        template<>
        void EffectParameter::set_value(const std::vector<Vector3>& value) const
        {
            if (_parameter_class != EffectParameterClass::Vector)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(Vector3) * value.size(), value.data());
        }

        template<>
        void EffectParameter::set_value(const Vector4& value) const
        {
            if (_parameter_class != EffectParameterClass::Vector)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(Vector4), &value[0]);
        }

        template<>
        void EffectParameter::set_value(const std::vector<Vector4>& value) const
        {
            if (_parameter_class != EffectParameterClass::Vector)
            {
                throw std::runtime_error("Invalid effect parameter class.");
            }

            _uniform_buffer->set_data(_offset, sizeof(Vector4) * value.size(), value.data());
        }

        EffectParameter&EffectParameter::operator=(const EffectParameter& parameter)
        {
            if (this != &parameter)
            {
                _name             = parameter._name;
                _column_count     = parameter._column_count;
                _row_count        = parameter._row_count;
                _count            = parameter._count;
                _offset           = parameter._offset;
                _semantic         = parameter._semantic;
                _node             = parameter._node;
                _value            = parameter._value;
                _parameter_class  = parameter._parameter_class;
                _parameter_type   = parameter._parameter_type;
                _uniform_buffer   = parameter._uniform_buffer;
            }

            return *this;
        }
    }
}
