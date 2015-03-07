// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/ShaderProgram.hpp>

#include <iostream>
#include <cassert>
#include <map>

#include <System/Text/Encoding.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/Shader.hpp>

using namespace System;
using namespace System::Text;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

ShaderProgram::ShaderProgram()
    : id      { 0 }
    , shaders {}
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::Dispose()
{
    if (this->id != 0)
    {
        // Dipose all the shader instances
        if (this->shaders.size() > 0)
        {
            for (auto& shader : this->shaders)
            {
                shader->Dispose();
            }
        }

        glDeleteProgram(this->id);

        this->shaders.clear();
        this->id = 0;
    }
}

void ShaderProgram::AddShader(const String& shaderName, const ShaderType& shaderType, const String& shaderSource)
{
    this->AddShader(shaderName, shaderType, shaderSource, std::map<String, String>());
}

void ShaderProgram::AddShader(const String&                   shaderName
                            , const ShaderType&               shaderType
                            , const String&                   shaderSource
                            , const std::map<String, String>& shaderIncludes)
{
    this->shaders.push_back(std::make_shared<Shader>(shaderType, shaderSource, shaderIncludes));
}

void ShaderProgram::Activate() const
{
    glUseProgram(this->id);
}

void ShaderProgram::ActivateSubroutine(const UInt32& subroutineIndex) const
{
    glUniformSubroutinesuiv(static_cast<GLenum>(ShaderType::Vertex), 1, &subroutineIndex);
    glUniformSubroutinesuiv(static_cast<GLenum>(ShaderType::Fragment), 1, &subroutineIndex);
}

void ShaderProgram::Build()
{
    // Compile the shaders if needed ...
    for (auto &s : this->shaders)
    {
        if (!s->IsCompiled())
        {
            s->Compile();
        }
    }

    // ... Create the program object
    this->id = glCreateProgram();

    if (this->id == 0)
    {
        throw std::runtime_error("glCreateProgram failed");
    }

    // ... attach the shaders to the new shader program
    for (auto &s : this->shaders)
    {
        // Attach the shader
        glAttachShader(this->id, s->object);
    }

    // ... link the shader program
    glLinkProgram(this->id);

    // ... verify program linking
    this->VerifyLinkingState();

    // this->DescribeParameters();
    // this->DescribeUniformBlocks();
}

void ShaderProgram::Deactivate() const
{
    glUseProgram(0);
}

Int32 ShaderProgram::GetParameterLocation(const String& parameterName) const
{
    auto temp     = System::Text::Encoding::Convert(parameterName);
    auto location = glGetUniformLocation(this->id, temp.c_str());

    if (location == -1)
    {
        std::cout << temp + " not found" << std::endl;
    }

    assert(location != -1);

    return location;
}

void ShaderProgram::SetValue(const System::Int32& location, const Boolean& value) const
{
    glProgramUniform1i(this->id, location, value);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Boolean>& value) const
{
    for (const auto& bValue : value)
    {
        this->SetValue(location, bValue);
    }
}

void ShaderProgram::SetValue(const System::Int32& location, const Int32& value) const
{
    glProgramUniform1i(this->id, location, value);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Int32>& value) const
{
    glProgramUniform1iv(this->id, location, value.size(), &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const UInt32& value) const
{
    glProgramUniform1ui(this->id, location, value);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<UInt32>& value) const
{
    glProgramUniform1uiv(this->id, location, value.size(), &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const Matrix& value) const
{
    glProgramUniformMatrix4fv(this->id, location, 1, GL_FALSE, &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Matrix>& value) const
{
    glProgramUniformMatrix4fv(this->id, location, value.size(), GL_FALSE, &value[0][0]);
}

void ShaderProgram::SetValueTranspose(const System::Int32& location, const Matrix& value) const
{
    glProgramUniformMatrix4fv(this->id, location, 1, GL_TRUE, &value[0]);
}

void ShaderProgram::SetValueTranspose(const System::Int32& location, const std::vector<Matrix>& value) const
{
    glProgramUniformMatrix4fv(this->id, location, value.size(), GL_TRUE, &value[0][0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const Quaternion& value) const
{
    glProgramUniform4fv(this->id, location, 1, &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Quaternion>& value) const
{
    glProgramUniform4fv(this->id, location, value.size(), &value[0][0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const Single& value) const
{
    glProgramUniform1f(this->id, location, value);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Single>& value) const
{
    glProgramUniform1fv(this->id, location, value.size(), &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const SceneR::Framework::Vector2& value) const
{
    glProgramUniform2fv(this->id, location, 1, &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<SceneR::Framework::Vector2>& value) const
{
    glProgramUniform2fv(this->id, location, value.size(), &value[0][0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const Vector3& value) const
{
    glProgramUniform3fv(this->id, location, 1, &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Vector3>& value) const
{
    glProgramUniform3fv(this->id, location, value.size(), &value[0][0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const Vector4& value) const
{
    glProgramUniform4fv(this->id, location, 1, &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Vector4>& value) const
{
    glProgramUniform4fv(this->id, location, value.size(), &value[0][0]);
}

void ShaderProgram::VerifyLinkingState()
{
    // ... verify program linking
    GLint status;
    glGetProgramiv(this->id, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        auto msg = std::string("Program linking failure: ");

        GLint infoLogLength;
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength)
        {
            std::string linkErrorMessage("", static_cast<Size>(infoLogLength));

            glGetProgramInfoLog(this->id, infoLogLength, NULL, &linkErrorMessage[0]);

            msg += linkErrorMessage;
        }

        this->Dispose();

        throw std::runtime_error(msg);
    }
}

void ShaderProgram::DescribeParameters()
{
    GLint   uniformCount = 0;
    GLsizei bufSize      = 0;

    std::cout << "shader parameters" << std::endl;

    glGetProgramiv(this->id, GL_ACTIVE_UNIFORMS, &uniformCount);
    glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &bufSize);

    for (Int32 index = 0; index < uniformCount; ++index)
    {
        GLsizei length = 0;
        GLint   size   = 0;
        GLenum  type   = GL_ZERO;
        std::vector<char> name(bufSize);

        glGetActiveUniform(this->id, index, bufSize, &length, &size, &type, &name[0]);

        name.resize(length);

        EffectParameterClass epClass;
        EffectParameterType epType;
        String pname(name.begin(), name.end());

        std::cout << System::Text::Encoding::Convert(pname) << std::endl;

        this->InferParameterClassAndType(type, epClass, epType);
        // this->Parameters().Add(pname, epClass, epType, index);
    }
}

void ShaderProgram::DescribeUniformBlocks()
{
    GLint numBlocks;

    std::cout << "shader uniform blocks" << std::endl;

    glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_BLOCKS, &numBlocks);

    std::vector<std::string> nameList;
    nameList.reserve(numBlocks);

    for (int blockIx = 0; blockIx < numBlocks; ++blockIx)
    {
        GLint nameLen;
        glGetActiveUniformBlockiv(this->id, blockIx, GL_UNIFORM_BLOCK_NAME_LENGTH, &nameLen);

        std::vector<GLchar> name(nameLen);

        glGetActiveUniformBlockName(this->id, blockIx, nameLen, NULL, &name[0]);

        nameList.push_back(std::string(name.begin(), name.end() - 1));
    }

    // glGetActiveUniformBlockiv(this->id, data->block_id, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, data->block_indices);

    GLint uniformCount = -1;
    glGetProgramiv(this->id, GL_ACTIVE_UNIFORMS, &uniformCount);
    std::vector<GLuint> indices(uniformCount);
    std::vector<GLint> offsets(uniformCount);
    std::vector<GLint> types(uniformCount);
    std::vector<GLint> array_sizes(uniformCount);
    std::vector<GLint> array_strides(uniformCount);
    std::vector<GLint> matrix_strides(uniformCount);
    std::vector<GLint> matrix_is_row_major(uniformCount);

    std::vector<std::string> names;

    names.push_back("DirectionalLight[0].DiffuseColor");
    names.push_back("DirectionalLight[0].Direction");
    names.push_back("DirectionalLight[0].Enabled");
    names.push_back("DirectionalLight[0].SpecularColor");
    names.push_back("DirectionalLight[1].DiffuseColor");
    names.push_back("DirectionalLight[1].Direction");
    names.push_back("DirectionalLight[1].Enabled");
    names.push_back("DirectionalLight[1].SpecularColor");
    names.push_back("DirectionalLight[2].DiffuseColor");
    names.push_back("DirectionalLight[2].Direction");
    names.push_back("DirectionalLight[2].Enabled");
    names.push_back("DirectionalLight[2].SpecularColor");
    names.push_back("Ka");
    names.push_back("Kd");
    names.push_back("Ks");
    names.push_back("LightIntensity");
    names.push_back("LightPosition");
    names.push_back("Shininess");
    names.push_back("WorldInverseTranspose");
    names.push_back("WorldView");
    names.push_back("WorldViewProjection");

    const GLchar **cnames = new const GLchar*[names.size()];

    for (unsigned int i = 0; i < names.size(); i++)
    {
         cnames[i] = names[i].c_str();
    }

    glGetUniformIndices(this->id, uniformCount, cnames, &indices[0]);

    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_OFFSET, &offsets[0]);
    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_TYPE, &types[0]);
    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_SIZE, &array_sizes[0]);
    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_ARRAY_STRIDE, &array_strides[0]);
    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_MATRIX_STRIDE, &matrix_strides[0]);
    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_IS_ROW_MAJOR, &matrix_is_row_major[0]);
}

void ShaderProgram::InferParameterClassAndType(const System::UInt32& type
                                             , EffectParameterClass& epClass
                                             , EffectParameterType&  epType) const
{
    switch (type)
    {
        case GL_FLOAT:
            epClass = EffectParameterClass::Scalar;
            epType = EffectParameterType::Single;
            break;

        case GL_FLOAT_VEC2:
        case GL_FLOAT_VEC3:
        case GL_FLOAT_VEC4:
            epClass = EffectParameterClass::Vector;
            epType = EffectParameterType::Single;
            break;

        case GL_INT:
            epClass = EffectParameterClass::Scalar;
            epType = EffectParameterType::Int32;
            break;

        case GL_INT_VEC2:
        case GL_INT_VEC3:
        case GL_INT_VEC4:
            epClass = EffectParameterClass::Vector;
            epType = EffectParameterType::Int32;
            break;

        case GL_BOOL:
            epClass = EffectParameterClass::Scalar;
            epType = EffectParameterType::Bool;
            break;

        case GL_FLOAT_MAT4:
            epClass = EffectParameterClass::Matrix;
            epType = EffectParameterType::Single;
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
