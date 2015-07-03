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

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

EffectParameter::EffectParameter()
    : EffectParameter { u"", 0, 0, 0, nullptr }
{
}

EffectParameter::EffectParameter(const System::String&                      name
                               , const System::UInt32&                      index
                               , const System::UInt32&                      offset
                               , const System::UInt32&                      type
                               , const std::shared_ptr<UniformBufferObject> uniformBuffer)
    : columnCount       { 0 }
    , elements          {  }
    , name              { name }
    , parameterClass    { EffectParameterClass::Object }
    , parameterType     { EffectParameterType::Single }
    , rowCount          { 0 }
    , structureMembers  {  }
    , index             { index }
    , offset            { offset }
    , uniformBuffer     { uniformBuffer }
{
    this->Describe(type);
}

EffectParameter::EffectParameter(const EffectParameter& parameter)
    : columnCount      { parameter.columnCount }
    , elements         { parameter.elements }
    , name             { parameter.name }
    , parameterClass   { parameter.parameterClass }
    , parameterType    { parameter.parameterType }
    , rowCount         { parameter.rowCount }
    , structureMembers { parameter.structureMembers }
    , index            { parameter.index }
    , offset           { parameter.offset }
    , uniformBuffer    { parameter.uniformBuffer }
{
}

EffectParameter::~EffectParameter()
{
}

const Int32& EffectParameter::ColumnCount() const
{
    return this->columnCount;
}

EffectParameterCollection& EffectParameter::Elements()
{
    return this->elements;
}

const String& EffectParameter::Name() const
{
    return this->name;
}

const EffectParameterClass& EffectParameter::ParameterClass() const
{
    return this->parameterClass;
}

const EffectParameterType& EffectParameter::ParameterType() const
{
    return this->parameterType;
}

const Int32& EffectParameter::RowCount() const
{
    return this->rowCount;
}

EffectParameterCollection& EffectParameter::StructureMembers()
{
    return this->structureMembers;
}

bool EffectParameter::GetValueBoolean() const
{
    throw std::runtime_error("Not implemented");
}

std::vector<bool> EffectParameter::GetValueBooleanArray() const
{
    throw std::runtime_error("Not implemented");
}

Int32 EffectParameter::GetValueInt32() const
{
    throw std::runtime_error("Not implemented");
}

std::vector<Int32> EffectParameter::GetValueInt32Array() const
{
    throw std::runtime_error("Not implemented");
}

Matrix EffectParameter::GetValueMatrix() const
{
    throw std::runtime_error("Not implemented");
}

std::vector<Matrix> EffectParameter::GetValueMatrixArray() const
{
    throw std::runtime_error("Not implemented");
}

Matrix EffectParameter::GetValueMatrixTranspose() const
{
    throw std::runtime_error("Not implemented");
}

std::vector<Matrix> EffectParameter::GetValueMatrixTransposeArray()
{
    throw std::runtime_error("Not implemented");
}

Quaternion EffectParameter::GetValueQuaternion() const
{
    throw std::runtime_error("Not implemented");
}

std::vector<Quaternion> EffectParameter::GetValueQuaternionArray() const
{
    throw std::runtime_error("Not implemented");
}

Single EffectParameter::GetValueSingle() const
{
    throw std::runtime_error("Not implemented");
}

std::vector<Single> EffectParameter::GetValueSingleArray() const
{
    throw std::runtime_error("Not implemented");
}

String EffectParameter::GetValueString() const
{
    throw std::runtime_error("Not implemented");
}

Vector3 EffectParameter::GetValueVector3() const
{
    throw std::runtime_error("Not implemented");
}

std::vector<Vector3> EffectParameter::GetValueVector3Array() const
{
    throw std::runtime_error("Not implemented");
}

void EffectParameter::SetValue(const bool& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }
    if (this->parameterType != EffectParameterType::Bool)
    {
        throw std::runtime_error("Invalid effect parameter type.");
    }

    this->uniformBuffer->SetData(this->offset, 1, &value);
}

void EffectParameter::SetValue(const std::vector<bool>& value) const
{
    if (this->parameterType != EffectParameterType::Bool)
    {
        throw std::runtime_error("Invalid effect parameter type.");
    }

    //this->uniformBuffer->SetData(this->offset, value.size(), value.data());
}

void EffectParameter::SetValue(const Int32& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }
    if (this->parameterType != EffectParameterType::Int32)
    {
        throw std::runtime_error("Invalid effect parameter type.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Int32), &value);
}

void EffectParameter::SetValue(const std::vector<Int32>& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }
    if (this->parameterType != EffectParameterType::Int32)
    {
        throw std::runtime_error("Invalid effect parameter type.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Int32) * value.size(), value.data());
}

void EffectParameter::SetValue(const UInt32& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(UInt32), &value);
}

void EffectParameter::SetValue(const std::vector<UInt32>& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(UInt32) * value.size(), value.data());
}

void EffectParameter::SetValue(const Matrix& value) const
{
    if (this->parameterClass != EffectParameterClass::Matrix)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Matrix), &value[0]);
}

void EffectParameter::SetValue(const std::vector<Matrix>& value) const
{
    if (this->parameterClass != EffectParameterClass::Matrix)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Matrix) * value.size(), value.data());
}

void EffectParameter::SetValueTranspose(const Matrix& value) const
{
    if (this->parameterClass != EffectParameterClass::Matrix)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    const auto transpose = Matrix::Transpose(value);

    this->uniformBuffer->SetData(this->offset, sizeof(Matrix), &transpose[0]);
}

void EffectParameter::SetValueTranspose(const std::vector<Matrix>& value) const
{
    if (this->parameterClass != EffectParameterClass::Matrix)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    std::vector<Matrix> transposed;

    transposed.reserve(value.size());

    for (const auto& matrix : value)
    {
        transposed.push_back(Matrix::Transpose(matrix));
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Matrix) * transposed.size(), transposed.data());
}

void EffectParameter::SetValue(const Quaternion& value) const
{
    this->uniformBuffer->SetData(this->offset, sizeof(Quaternion), &value[0]);
}

void EffectParameter::SetValue(const std::vector<Quaternion>& value) const
{
    this->uniformBuffer->SetData(this->offset, sizeof(Quaternion) * value.size(), value.data());
}

void EffectParameter::SetValue(const Single& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }
    if (this->parameterType != EffectParameterType::Single)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Single), &value);
}

void EffectParameter::SetValue(const std::vector<Single>& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }
    if (this->parameterType != EffectParameterType::Single)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Single) * value.size(), value.data());
}

void EffectParameter::SetValue(const String& value) const
{
    throw std::runtime_error("Not implemented");
}

void EffectParameter::SetValue(const SceneR::Graphics::Texture& value) const
{
    if (this->parameterClass != EffectParameterClass::Object)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }
    if (this->parameterType != EffectParameterType::Texture
     && this->parameterType != EffectParameterType::Texture1D
     && this->parameterType != EffectParameterType::Texture2D
     && this->parameterType != EffectParameterType::Texture3D
     && this->parameterType != EffectParameterType::TextureCube)
    {
        throw std::runtime_error("Invalid effect parameter type.");
    }

    // this->uniformBuffer->SetData(this->offset,(this->name, 0);
}

void EffectParameter::SetValue(const SceneR::Framework::Vector2& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Vector2), &value[0]);
}

void EffectParameter::SetValue(const std::vector<SceneR::Framework::Vector2>& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Vector2) * value.size(), value.data());
}

void EffectParameter::SetValue(const Vector3& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Vector3), &value[0]);
}

void EffectParameter::SetValue(const std::vector<Vector3>& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Vector3) * value.size(), value.data());
}

void EffectParameter::SetValue(const Vector4& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Vector4), &value[0]);
}

void EffectParameter::SetValue(const std::vector<Vector4>& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->uniformBuffer->SetData(this->offset, sizeof(Vector4) * value.size(), value.data());
}

EffectParameter&EffectParameter::operator=(const EffectParameter& parameter)
{
    if (this != &parameter)
    {
        this->columnCount       = parameter.columnCount;
        this->elements          = parameter.elements;
        this->name              = parameter.name;
        this->parameterClass    = parameter.parameterClass;
        this->parameterType     = parameter.parameterType;
        this->rowCount          = parameter.rowCount;
        this->structureMembers  = parameter.structureMembers;
        this->index             = parameter.index;
        this->offset            = parameter.offset;
        this->uniformBuffer     = parameter.uniformBuffer;
    }

    return *this;
}

void EffectParameter::Describe(const Int32& type)
{
    switch (type)
    {
        case GL_FLOAT:
            this->parameterClass = EffectParameterClass::Scalar;
            this->parameterType  = EffectParameterType::Single;
            break;

        case GL_FLOAT_VEC2:
            this->parameterClass = EffectParameterClass::Vector;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 1;
            this->columnCount    = 2;
            break;

        case GL_FLOAT_VEC3:
            this->parameterClass = EffectParameterClass::Vector;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 1;
            this->columnCount    = 3;
            break;

        case GL_FLOAT_VEC4:
            this->parameterClass = EffectParameterClass::Vector;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 1;
            this->columnCount    = 4;
            break;

        case GL_INT:
            this->parameterClass = EffectParameterClass::Scalar;
            this->parameterType  = EffectParameterType::Int32;
            break;

        case GL_INT_VEC2:
            this->parameterClass = EffectParameterClass::Vector;
            this->parameterType  = EffectParameterType::Int32;
            this->rowCount       = 1;
            this->columnCount    = 2;
            break;

        case GL_INT_VEC3:
            this->parameterClass = EffectParameterClass::Vector;
            this->parameterType  = EffectParameterType::Int32;
            this->rowCount       = 1;
            this->columnCount    = 3;
            break;

        case GL_INT_VEC4:
            this->parameterClass = EffectParameterClass::Vector;
            this->parameterType  = EffectParameterType::Int32;
            this->rowCount       = 1;
            this->columnCount    = 4;
            break;

        case GL_BOOL:
            this->parameterClass = EffectParameterClass::Scalar;
            this->parameterType  = EffectParameterType::Bool;
            break;

        case GL_FLOAT_MAT2	: // mat2
            this->parameterClass = EffectParameterClass::Matrix;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 2;
            this->columnCount    = 2;
            break;

        case GL_FLOAT_MAT3	: // mat3
            this->parameterClass = EffectParameterClass::Matrix;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 3;
            this->columnCount    = 3;
            break;

        case GL_FLOAT_MAT4	: // mat4
            this->parameterClass = EffectParameterClass::Matrix;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 4;
            this->columnCount    = 4;
            break;

        case GL_FLOAT_MAT2x3: // mat2x3
            this->parameterClass = EffectParameterClass::Matrix;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 3;
            this->columnCount    = 2;
            break;

        case GL_FLOAT_MAT2x4: // mat2x4
            this->parameterClass = EffectParameterClass::Matrix;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 4;
            this->columnCount    = 2;
            break;

        case GL_FLOAT_MAT3x2: // mat3x2
            this->parameterClass = EffectParameterClass::Matrix;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 2;
            this->columnCount    = 3;
            break;

        case GL_FLOAT_MAT3x4: // mat3x4
            this->parameterClass = EffectParameterClass::Matrix;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 4;
            this->columnCount    = 3;
            break;

        case GL_FLOAT_MAT4x2: // mat4x2
            this->parameterClass = EffectParameterClass::Matrix;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 2;
            this->columnCount    = 4;
            break;

        case GL_FLOAT_MAT4x3: // mat4x3
            this->parameterClass = EffectParameterClass::Matrix;
            this->parameterType  = EffectParameterType::Single;
            this->rowCount       = 3;
            this->columnCount    = 4;
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
