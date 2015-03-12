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
#include <Graphics/ShaderProgram.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

EffectParameter::EffectParameter()
    : columnCount       { 0 }
    , elements          {  }
    , name              { u"" }
    , parameterClass    { EffectParameterClass::Object }
    , parameterType     { EffectParameterType::Single }
    , rowCount          { 0 }
    , structureMembers  {  }
    , program            { nullptr }
{
}

EffectParameter::EffectParameter(const String&                         name
                               , const EffectParameterClass&           parameterClass
                               , const EffectParameterType&            parameterType
                               , const std::shared_ptr<ShaderProgram>& shader)
    : columnCount       { 0 }
    , elements          {  }
    , name              { name }
    , parameterClass    { parameterClass }
    , parameterType     { parameterType }
    , rowCount          { 0 }
    , structureMembers  {  }
    , program            { shader }
{
}

EffectParameter::EffectParameter(const EffectParameter& parameter)
    : columnCount       { parameter.columnCount }
    , elements          { parameter.elements }
    , name              { parameter.name }
    , parameterClass    { parameter.parameterClass }
    , parameterType     { parameter.parameterType }
    , rowCount          { parameter.rowCount }
    , structureMembers  { parameter.structureMembers }
    , program            { parameter.program }
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

const Boolean& EffectParameter::GetValueBoolean() const
{
    throw std::runtime_error("Not implemented");
}

const std::vector<Boolean>& EffectParameter::GetValueBooleanArray() const
{
    throw std::runtime_error("Not implemented");
}

const Int32& EffectParameter::GetValueInt32() const
{
    throw std::runtime_error("Not implemented");
}

const std::vector<Int32>& EffectParameter::GetValueInt32Array() const
{
    throw std::runtime_error("Not implemented");
}

const Matrix& EffectParameter::GetValueMatrix() const
{
    throw std::runtime_error("Not implemented");
}

const std::vector<Matrix>& EffectParameter::GetValueMatrixArray() const
{
    throw std::runtime_error("Not implemented");
}

const Matrix& EffectParameter::GetValueMatrixTranspose() const
{
    throw std::runtime_error("Not implemented");
}

const std::vector<Matrix>& EffectParameter::GetValueMatrixTransposeArray()
{
    throw std::runtime_error("Not implemented");
}

const Quaternion& EffectParameter::GetValueQuaternion() const
{
    throw std::runtime_error("Not implemented");
}

const std::vector<Quaternion>& EffectParameter::GetValueQuaternionArray() const
{
    throw std::runtime_error("Not implemented");
}

const Single& EffectParameter::GetValueSingle() const
{
    throw std::runtime_error("Not implemented");
}

const std::vector<Single>& EffectParameter::GetValueSingleArray() const
{
    throw std::runtime_error("Not implemented");
}

const String& EffectParameter::GetValueString() const
{
    throw std::runtime_error("Not implemented");
}

const Vector3& EffectParameter::GetValueVector3() const
{
    throw std::runtime_error("Not implemented");
}

const std::vector<Vector3>& EffectParameter::GetValueVector3Array() const
{
    throw std::runtime_error("Not implemented");
}

void EffectParameter::SetValue(const Boolean& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }
    if (this->parameterType != EffectParameterType::Bool)
    {
        throw std::runtime_error("Invalid effect parameter type.");
    }

    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValue(const std::vector<Boolean>& value) const
{
    for (const auto& bValue : value)
    {
        this->SetValue(bValue);
    }
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

    this->program->SetValue(this->name, value);
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

    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValue(const UInt32& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValue(const std::vector<UInt32>& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValue(const Matrix& value) const
{
    if (this->parameterClass != EffectParameterClass::Matrix)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValue(const std::vector<Matrix>& value) const
{
    if (this->parameterClass != EffectParameterClass::Matrix)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValueTranspose(const Matrix& value) const
{
    if (this->parameterClass != EffectParameterClass::Matrix)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValueTranspose(this->name, value);
}

void EffectParameter::SetValueTranspose(const std::vector<Matrix>& value) const
{
    if (this->parameterClass != EffectParameterClass::Matrix)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValueTranspose(this->name, value);
}

void EffectParameter::SetValue(const Quaternion& value) const
{
    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValue(const std::vector<Quaternion>& value) const
{
    this->program->SetValue(this->name, value);
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

    this->program->SetValue(this->name, value);
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

    this->program->SetValue(this->name, value);
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

    this->program->SetValue(this->name, 0);
}

void EffectParameter::SetValue(const SceneR::Framework::Vector2& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValue(const std::vector<SceneR::Framework::Vector2>& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValue(const Vector3& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValue(const std::vector<Vector3>& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValue(const Vector4& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValue(this->name, value);
}

void EffectParameter::SetValue(const std::vector<Vector4>& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Invalid effect parameter class.");
    }

    this->program->SetValue(this->name, value);
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
        this->program           = parameter.program;
    }

    return *this;
}
