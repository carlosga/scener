//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#include <Graphics/DirectionalLight.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/ShaderProgram.hpp>
#include <stdexcept>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

EffectParameter::EffectParameter()
    : columnCount(0),
      elements(0),
      name(u""),
      parameterClass(EffectParameterClass::Matrix),
      parameterType(EffectParameterType::Single),
      rowCount(0),
      structureMembers(0),
      shader(nullptr),
      parameterLocation(-1)
{
}

EffectParameter::EffectParameter(const String&               name,
                                 const EffectParameterClass& parameterClass,
                                 const EffectParameterType&  parameterType)
    : EffectParameter(name, parameterClass, parameterType, -1, nullptr)
{
}

EffectParameter::EffectParameter(const String&                        name,
                                 const EffectParameterClass&          parameterClass,
                                 const EffectParameterType&           parameterType,
                                 const Int32&                         parameterLocation,
                                 const std::shared_ptr<ShaderProgram> shader)
    : columnCount(0),
      elements(0),
      name(name),
      parameterClass(parameterClass),
      parameterType(parameterType),
      rowCount(0),
      structureMembers(0),
      shader(shader),
      parameterLocation(parameterLocation)
{
}

EffectParameter::~EffectParameter()
{
}

const Int32& EffectParameter::ColumnCount() const
{
    return this->columnCount;
}

const std::vector<EffectParameter>& EffectParameter::Elements() const
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

std::vector<EffectParameter>& EffectParameter::StructureMembers()
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
        throw std::runtime_error("Boolean is not a valid value for the current effect parameter class");
    }

    glUniform1i(this->parameterLocation, value);
}

void EffectParameter::SetValue(const std::vector<Boolean>& value) const
{
    for (const auto& bValue : value)
    {
        this->SetValue(bValue);
    }
}

void EffectParameter::SetValue(const SceneR::Graphics::DirectionalLight& value) const
{
    throw std::runtime_error("Not implemented");
}

void EffectParameter::SetValue(const std::vector<SceneR::Graphics::DirectionalLight>& value) const
{
    for (const auto& directionalLight : value)
    {
        this->SetValue(directionalLight);
    }
}

void EffectParameter::SetValue(const Int32& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Int32 is not a valid value for the current effect parameter class");
    }

    glUniform1i(this->parameterLocation, value);
}

void EffectParameter::SetValue(const std::vector<Int32>& value) const
{
    for (const auto& directionalLight : value)
    {
        this->SetValue(directionalLight);
    }
}

void EffectParameter::SetValue(const Matrix& value) const
{
    if (this->parameterClass != EffectParameterClass::Matrix)
    {
        throw std::runtime_error("Matrix is not a valid value for the current effect parameter class");
    }

    glUniformMatrix4fv(this->parameterLocation, 1, GL_FALSE, &value[0]);
}

void EffectParameter::SetValue(const std::vector<Matrix>& value) const
{
    for (const auto& matrix : value)
    {
        this->SetValue(matrix);
    }
}

void EffectParameter::SetValueTranspose(const Matrix& value) const
{
    if (this->parameterClass != EffectParameterClass::Matrix)
    {
        throw std::runtime_error("Matrix is not a valid value for the current effect parameter class");
    }

    this->SetValue(Matrix::Transpose(value));
}

void EffectParameter::SetValueTranspose(const std::vector<Matrix>& value) const
{
    for (const auto& matrix : value)
    {
        this->SetValueTranspose(matrix);
    }
}

void EffectParameter::SetValue(const Quaternion& value) const
{
    glUniform4fv(this->parameterLocation, 1, &value[0]);
}

void EffectParameter::SetValue(const std::vector<Quaternion>& value) const
{
    for (const auto& q : value)
    {
        this->SetValue(q);
    }
}

void EffectParameter::SetValue(const Single& value) const
{
    if (this->parameterClass != EffectParameterClass::Scalar)
    {
        throw std::runtime_error("Matrix is not a valid value for the current effect parameter class");
    }

    glUniform1f(this->parameterLocation, value);
}

void EffectParameter::SetValue(const std::vector<Single>& value) const
{
    for (const auto& scalar : value)
    {
        this->SetValue(scalar);
    }
}

void EffectParameter::SetValue(const String& value) const
{
    throw std::runtime_error("Not implemented");
}

void EffectParameter::SetValue(const Vector3& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Matrix is not a valid value for the current effect parameter class");
    }

    glUniform3fv(this->parameterLocation, 1, &value[0]);
}

void EffectParameter::SetValue(const std::vector<Vector3>& value) const
{
    for (const auto& vector : value)
    {
        this->SetValue(vector);
    }
}

void EffectParameter::SetValue(const Vector4& value) const
{
    if (this->parameterClass != EffectParameterClass::Vector)
    {
        throw std::runtime_error("Matrix is not a valid value for the current effect parameter class");
    }

    glUniform4fv(this->parameterLocation, 1, &value[0]);
}

void EffectParameter::SetValue(const std::vector<Vector4>& value) const
{
    for (const auto& vector : value)
    {
        this->SetValue(vector);
    }
}
