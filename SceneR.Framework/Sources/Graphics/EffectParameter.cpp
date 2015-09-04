// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/EffectParameter.hpp>

#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/EffectParameterCollection.hpp>
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
            : EffectParameter { u"", 0, 0, 0, nullptr }
        {
        }

        EffectParameter::EffectParameter(const std::u16string&                      name
                                       , const std::size_t&                         index
                                       , const std::size_t&                         offset
                                       , const std::int32_t&                        type
                                       , const std::shared_ptr<UniformBufferObject> uniformBuffer)
            : _column_count    { 0 }
            , _name            { name }
            , _parameter_class { EffectParameterClass::Object }
            , _parameter_type  { EffectParameterType::Single }
            , _row_count       { 0 }
            , _index           { index }
            , _offset          { offset }
            , _uniform_buffer  { uniformBuffer }
        {
            describe(type);
        }

        EffectParameter::EffectParameter(const EffectParameter& parameter)
            : _column_count    { parameter._column_count }
            , _name            { parameter._name }
            , _parameter_class { parameter._parameter_class }
            , _parameter_type  { parameter._parameter_type }
            , _row_count       { parameter._row_count }
            , _index           { parameter._index }
            , _offset          { parameter._offset }
            , _uniform_buffer  { parameter._uniform_buffer }
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

        template <>
        std::vector<bool> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as an int32_t.
         */
        template<>
        std::int32_t EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         *  Gets the value of the EffectParameter as an array of int32_t.
         */
        template<>
        std::vector<std::int32_t> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as a Matrix.
         */
        template<>
        SceneR::Framework::Matrix EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as an array of Matrix.
         */
        template<>
        std::vector<SceneR::Framework::Matrix> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as a Matrix transpose.
         */
        template<>
        SceneR::Framework::Matrix EffectParameter::get_value_transpose() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as an array of Matrix transpose.
         */
        template<>
        std::vector<SceneR::Framework::Matrix> EffectParameter::get_value_transpose() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as a Quaternion.
         */
        template<>
        SceneR::Framework::Quaternion EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as an array of Quaternion.
         */
        template<>
        std::vector<SceneR::Framework::Quaternion> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as a float.
         */
        template<>
        float EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as an array of float.
         */
        template<>
        std::vector<float> EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as an String.
         */
        template<>
        std::u16string EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as a Vector3.
         */
        template<>
        SceneR::Framework::Vector3 EffectParameter::get_value() const
        {
            throw std::runtime_error("Not implemented");
        }

        /**
         * Gets the value of the EffectParameter as an array of Vector3.
         */
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

            const auto transpose = Matrix::Transpose(value);

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
                transposed.push_back(Matrix::Transpose(matrix));
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
            if (_parameter_type != EffectParameterType::Sampler2D)
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
                _column_count    = parameter._column_count;
                _name            = parameter._name;
                _parameter_class = parameter._parameter_class;
                _parameter_type  = parameter._parameter_type;
                _row_count       = parameter._row_count;
                _index           = parameter._index;
                _offset          = parameter._offset;
                _uniform_buffer  = parameter._uniform_buffer;
            }

            return *this;
        }

        void EffectParameter::describe(const std::int32_t& type)
        {
            switch (type)
            {
                case GL_FLOAT:
                    _parameter_class = EffectParameterClass::Scalar;
                    _parameter_type  = EffectParameterType::Single;
                    break;

                case GL_FLOAT_VEC2:
                    _parameter_class = EffectParameterClass::Vector;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 1;
                    _column_count    = 2;
                    break;

                case GL_FLOAT_VEC3:
                    _parameter_class = EffectParameterClass::Vector;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 1;
                    _column_count    = 3;
                    break;

                case GL_FLOAT_VEC4:
                    _parameter_class = EffectParameterClass::Vector;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 1;
                    _column_count    = 4;
                    break;

                case GL_INT:
                    _parameter_class = EffectParameterClass::Scalar;
                    _parameter_type  = EffectParameterType::Int32;
                    break;

                case GL_INT_VEC2:
                    _parameter_class = EffectParameterClass::Vector;
                    _parameter_type  = EffectParameterType::Int32;
                    _row_count       = 1;
                    _column_count    = 2;
                    break;

                case GL_INT_VEC3:
                    _parameter_class = EffectParameterClass::Vector;
                    _parameter_type  = EffectParameterType::Int32;
                    _row_count       = 1;
                    _column_count    = 3;
                    break;

                case GL_INT_VEC4:
                    _parameter_class = EffectParameterClass::Vector;
                    _parameter_type  = EffectParameterType::Int32;
                    _row_count       = 1;
                    _column_count    = 4;
                    break;

                case GL_BOOL:
                    _parameter_class = EffectParameterClass::Scalar;
                    _parameter_type  = EffectParameterType::Bool;
                    break;

                case GL_FLOAT_MAT2	: // mat2
                    _parameter_class = EffectParameterClass::Matrix;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 2;
                    _column_count    = 2;
                    break;

                case GL_FLOAT_MAT3	: // mat3
                    _parameter_class = EffectParameterClass::Matrix;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 3;
                    _column_count    = 3;
                    break;

                case GL_FLOAT_MAT4	: // mat4
                    _parameter_class = EffectParameterClass::Matrix;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 4;
                    _column_count    = 4;
                    break;

                case GL_FLOAT_MAT2x3: // mat2x3
                    _parameter_class = EffectParameterClass::Matrix;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 3;
                    _column_count    = 2;
                    break;

                case GL_FLOAT_MAT2x4: // mat2x4
                    _parameter_class = EffectParameterClass::Matrix;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 4;
                    _column_count    = 2;
                    break;

                case GL_FLOAT_MAT3x2: // mat3x2
                    _parameter_class = EffectParameterClass::Matrix;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 2;
                    _column_count    = 3;
                    break;

                case GL_FLOAT_MAT3x4: // mat3x4
                    _parameter_class = EffectParameterClass::Matrix;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 4;
                    _column_count    = 3;
                    break;

                case GL_FLOAT_MAT4x2: // mat4x2
                    _parameter_class = EffectParameterClass::Matrix;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 2;
                    _column_count    = 4;
                    break;

                case GL_FLOAT_MAT4x3: // mat4x3
                    _parameter_class = EffectParameterClass::Matrix;
                    _parameter_type  = EffectParameterType::Single;
                    _row_count       = 3;
                    _column_count    = 4;
                    break;
            }
        }

        //GL_SAMPLER_1D   sampler1D
        //GL_SAMPLER_2D   sampler2D
        //GL_SAMPLER_3D   sampler3D
        //GL_SAMPLER_CUBE samplerCube
        //GL_SAMPLER_1D_SHADOW    sampler1DShadow
        //GL_SAMPLER_2D_SHADOW    sampler2DShadow
        //GL_SAMPLER_1D_ARRAY sampler1DArray
        //GL_SAMPLER_2D_ARRAY sampler2DArray
        //GL_SAMPLER_1D_ARRAY_SHADOW  sampler1DArrayShadow
        //GL_SAMPLER_2D_ARRAY_SHADOW  sampler2DArrayShadow
        //GL_SAMPLER_2D_MULTISAMPLE   sampler2DMS
        //GL_SAMPLER_2D_MULTISAMPLE_ARRAY sampler2DMSArray
        //GL_SAMPLER_CUBE_SHADOW  samplerCubeShadow
        //GL_SAMPLER_BUFFER   samplerBuffer
        //GL_SAMPLER_2D_RECT  sampler2DRect
        //GL_SAMPLER_2D_RECT_SHADOW   sampler2DRectShadow
        //GL_INT_SAMPLER_1D   isampler1D
        //GL_INT_SAMPLER_2D   isampler2D
        //GL_INT_SAMPLER_3D   isampler3D
        //GL_INT_SAMPLER_CUBE isamplerCube
        //GL_INT_SAMPLER_1D_ARRAY isampler1DArray
        //GL_INT_SAMPLER_2D_ARRAY isampler2DArray
        //GL_INT_SAMPLER_2D_MULTISAMPLE   isampler2DMS
        //GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY isampler2DMSArray
        //GL_INT_SAMPLER_BUFFER   isamplerBuffer
        //GL_INT_SAMPLER_2D_RECT  isampler2DRect
        //GL_UNSIGNED_INT_SAMPLER_1D  usampler1D
        //GL_UNSIGNED_INT_SAMPLER_2D  usampler2D
        //GL_UNSIGNED_INT_SAMPLER_3D  usampler3D
        //GL_UNSIGNED_INT_SAMPLER_CUBE    usamplerCube
        //GL_UNSIGNED_INT_SAMPLER_1D_ARRAY    usampler2DArray
        //GL_UNSIGNED_INT_SAMPLER_2D_ARRAY    usampler2DArray
        //GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE  usampler2DMS
        //GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY    usampler2DMSArray
        //GL_UNSIGNED_INT_SAMPLER_BUFFER  usamplerBuffer
        //GL_UNSIGNED_INT_SAMPLER_2D_RECT usampler2DRect
        //GL_IMAGE_1D image1D
        //GL_IMAGE_2D image2D
        //GL_IMAGE_3D image3D
        //GL_IMAGE_2D_RECT    image2DRect
        //GL_IMAGE_CUBE   imageCube
        //GL_IMAGE_BUFFER imageBuffer
        //GL_IMAGE_1D_ARRAY   image1DArray
        //GL_IMAGE_2D_ARRAY   image2DArray
        //GL_IMAGE_2D_MULTISAMPLE image2DMS
        //GL_IMAGE_2D_MULTISAMPLE_ARRAY   image2DMSArray
        //GL_INT_IMAGE_1D iimage1D
        //GL_INT_IMAGE_2D iimage2D
        //GL_INT_IMAGE_3D iimage3D
        //GL_INT_IMAGE_2D_RECT    iimage2DRect
        //GL_INT_IMAGE_CUBE   iimageCube
        //GL_INT_IMAGE_BUFFER iimageBuffer
        //GL_INT_IMAGE_1D_ARRAY   iimage1DArray
        //GL_INT_IMAGE_2D_ARRAY   iimage2DArray
        //GL_INT_IMAGE_2D_MULTISAMPLE iimage2DMS
        //GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY   iimage2DMSArray
        //GL_UNSIGNED_INT_IMAGE_1D    uimage1D
        //GL_UNSIGNED_INT_IMAGE_2D    uimage2D
        //GL_UNSIGNED_INT_IMAGE_3D    uimage3D
        //GL_UNSIGNED_INT_IMAGE_2D_RECT   uimage2DRect
        //GL_UNSIGNED_INT_IMAGE_CUBE  uimageCube
        //GL_UNSIGNED_INT_IMAGE_BUFFER    uimageBuffer
        //GL_UNSIGNED_INT_IMAGE_1D_ARRAY  uimage1DArray
        //GL_UNSIGNED_INT_IMAGE_2D_ARRAY  uimage2DArray
        //GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE    uimage2DMS
        //GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY  uimage2DMSArray
        //GL_UNSIGNED_INT_ATOMIC_COUNTER  atomic_uint
    }
}
