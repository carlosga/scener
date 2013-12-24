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

#include <GL/glew.h>
#include <Graphics/Shader.hpp>
#include <Graphics/ShaderProgram.hpp>
#include <System/Text/Unicode.hpp>
#include <stdexcept>
#include <string>

using namespace System;
using namespace System::Text;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

ShaderProgram::ShaderProgram(std::vector<std::shared_ptr<Shader>>& shaders)
    : id(0), shaders(shaders)
{
}

ShaderProgram::~ShaderProgram()
{
    this->Release();
}

void ShaderProgram::Activate() const
{
    glUseProgram(this->id);
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

//    GLint uniformCount = 0;
//    GLsizei bufSize = 0;
//    glGetProgramiv(this->id, GL_ACTIVE_UNIFORMS, &uniformCount);
//    glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &bufSize);
//
//    for (Int32 index = 0; index < uniformCount; ++index)
//    {
//        GLsizei length = 0;
//        GLint   size   = 0;
//        GLenum  type   = GL_ZERO;
//        std::vector<char> name(bufSize);
//
//        glGetActiveUniform(this->id, index, bufSize, &length, &size, &type, &name[0]);
//
//        name.resize(length);
//
//        std::string pname(name.begin(), name.end());
//
//        std::cout << "name " << pname << " index " << index << std::endl;
//    }
}

void ShaderProgram::Deactivate() const
{
    glUseProgram(0);
}

Int32 ShaderProgram::GetParameterLocation(const String& parameterName) const
{
    std::string temp = System::Text::Unicode::Narrow(parameterName);
    System::Int32 location = glGetUniformLocation(this->id, temp.c_str());

    if (location == -1)
    {
        throw std::runtime_error("Unknown parameter with name " + temp);
    }

    return location;
}

void ShaderProgram::Release()
{
    if (this->id != 0)
    {
        glDeleteProgram(this->id);
        this->id = 0;
    }
}

void ShaderProgram::VerifyLinkingState()
{
    // ... verify program linking
    GLint status;
    glGetProgramiv(this->id, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        std::string msg("Program linking failure: ");

        GLint infoLogLength;
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength)
        {
            std::string linkErrorMessage("", infoLogLength);

            glGetProgramInfoLog(this->id, infoLogLength, NULL, &linkErrorMessage[0]);

            msg += linkErrorMessage;
        }

        this->Release();

        throw std::runtime_error(msg);
    }
}

//void ShaderProgram::DescribeParameters()
//{
//    GLint uniformCount = 0;
//    GLsizei bufSize = 0;
//    glGetProgramiv(this->id, GL_ACTIVE_UNIFORMS, &uniformCount);
//    glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &bufSize);
//
//    for (Int32 index = 0; index < uniformCount; ++index)
//    {
//        GLsizei length = 0;
//        GLint   size   = 0;
//        GLenum  type   = GL_ZERO;
//        std::vector<char> name(bufSize);
//
//        glGetActiveUniform(this->id, index, bufSize, &length, &size, &type, &name[0]);
//
//        name.resize(length);
//
//        EffectParameterClass epClass;
//        EffectParameterType epType;
//        String pname(name.begin(), name.end());
//
//        this->InferParameterClassAndType(type, epClass, epType);
//        this->Parameters().Add(pname, epClass, epType, index);
//    }
//}
//
//void ShaderProgram::DescribeUniformBlocks()
//{
//    GLint numBlocks;
//
//    glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_BLOCKS, &numBlocks);
//
//    std::vector<std::string> nameList;
//    nameList.reserve(numBlocks);
//
//    for (int blockIx = 0; blockIx < numBlocks; ++blockIx)
//    {
//        GLint nameLen;
//        glGetActiveUniformBlockiv(this->id, blockIx, GL_UNIFORM_BLOCK_NAME_LENGTH, &nameLen);
//
//        std::vector<GLchar> name(nameLen);
//
//        glGetActiveUniformBlockName(this->id, blockIx, nameLen, NULL, &name[0]);
//
//        nameList.push_back(std::string(name.begin(), name.end() - 1));
//    }
//
//    // glGetActiveUniformBlockiv(this->id, data->block_id, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, data->block_indices);
//
//    GLint uniformCount = -1;
//    glGetProgramiv(this->id, GL_ACTIVE_UNIFORMS, &uniformCount);
//    std::vector<GLuint> indices(uniformCount);
//    std::vector<GLint> offsets(uniformCount);
//    std::vector<GLint> types(uniformCount);
//    std::vector<GLint> array_sizes(uniformCount);
//    std::vector<GLint> array_strides(uniformCount);
//    std::vector<GLint> matrix_strides(uniformCount);
//    std::vector<GLint> matrix_is_row_major(uniformCount);
//
//    std::vector<std::string> names;
//
//    names.push_back("DirectionalLight[0].DiffuseColor");
//    names.push_back("DirectionalLight[0].Direction");
//    names.push_back("DirectionalLight[0].Enabled");
//    names.push_back("DirectionalLight[0].SpecularColor");
//    names.push_back("DirectionalLight[1].DiffuseColor");
//    names.push_back("DirectionalLight[1].Direction");
//    names.push_back("DirectionalLight[1].Enabled");
//    names.push_back("DirectionalLight[1].SpecularColor");
//    names.push_back("DirectionalLight[2].DiffuseColor");
//    names.push_back("DirectionalLight[2].Direction");
//    names.push_back("DirectionalLight[2].Enabled");
//    names.push_back("DirectionalLight[2].SpecularColor");
//    names.push_back("Ka");
//    names.push_back("Kd");
//    names.push_back("Ks");
//    names.push_back("LightIntensity");
//    names.push_back("LightPosition");
//    names.push_back("Shininess");
//    names.push_back("WorldInverseTranspose");
//    names.push_back("WorldView");
//    names.push_back("WorldViewProjection");
//
//    const GLchar **cnames = new const GLchar*[names.size()];
//
//    for (unsigned int i = 0; i < names.size(); i++)
//    {
//         cnames[i] = names[i].c_str();
//    }
//
//    glGetUniformIndices(this->id, uniformCount, cnames, &indices[0]);
//
//    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_OFFSET, &offsets[0]);
//    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_TYPE, &types[0]);
//    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_SIZE, &array_sizes[0]);
//    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_ARRAY_STRIDE, &array_strides[0]);
//    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_MATRIX_STRIDE, &matrix_strides[0]);
//    glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_IS_ROW_MAJOR, &matrix_is_row_major[0]);
//}
//
//void ShaderProgram::InferParameterClassAndType(const GLenum& type, EffectParameterClass& epClass,
//                                               EffectParameterType& epType) const
//{
//    switch (type)
//    {
//        case GL_FLOAT:
//            epClass = EffectParameterClass::Scalar;
//            epType = EffectParameterType::Single;
//            break;
//
//        case GL_FLOAT_VEC2:
//        case GL_FLOAT_VEC3:
//        case GL_FLOAT_VEC4:
//            epClass = EffectParameterClass::Vector;
//            epType = EffectParameterType::Single;
//            break;
//
//        case GL_INT:
//            epClass = EffectParameterClass::Scalar;
//            epType = EffectParameterType::Int32;
//            break;
//
//        case GL_INT_VEC2:
//        case GL_INT_VEC3:
//        case GL_INT_VEC4:
//            epClass = EffectParameterClass::Vector;
//            epType = EffectParameterType::Int32;
//            break;
//
//        case GL_BOOL:
//            epClass = EffectParameterClass::Scalar;
//            epType = EffectParameterType::Bool;
//            break;
//
//        case GL_FLOAT_MAT4:
//            epClass = EffectParameterClass::Matrix;
//            epType = EffectParameterType::Single;
//            break;
//    }
//
//    //GL_SAMPLER_1D   sampler1D
//    //GL_SAMPLER_2D   sampler2D
//    //GL_SAMPLER_3D   sampler3D
//    //GL_SAMPLER_CUBE samplerCube
//    //GL_SAMPLER_1D_SHADOW    sampler1DShadow
//    //GL_SAMPLER_2D_SHADOW    sampler2DShadow
//    //GL_SAMPLER_1D_ARRAY sampler1DArray
//    //GL_SAMPLER_2D_ARRAY sampler2DArray
//    //GL_SAMPLER_1D_ARRAY_SHADOW  sampler1DArrayShadow
//    //GL_SAMPLER_2D_ARRAY_SHADOW  sampler2DArrayShadow
//    //GL_SAMPLER_2D_MULTISAMPLE   sampler2DMS
//    //GL_SAMPLER_2D_MULTISAMPLE_ARRAY sampler2DMSArray
//    //GL_SAMPLER_CUBE_SHADOW  samplerCubeShadow
//    //GL_SAMPLER_BUFFER   samplerBuffer
//    //GL_SAMPLER_2D_RECT  sampler2DRect
//    //GL_SAMPLER_2D_RECT_SHADOW   sampler2DRectShadow
//    //GL_INT_SAMPLER_1D   isampler1D
//    //GL_INT_SAMPLER_2D   isampler2D
//    //GL_INT_SAMPLER_3D   isampler3D
//    //GL_INT_SAMPLER_CUBE isamplerCube
//    //GL_INT_SAMPLER_1D_ARRAY isampler1DArray
//    //GL_INT_SAMPLER_2D_ARRAY isampler2DArray
//    //GL_INT_SAMPLER_2D_MULTISAMPLE   isampler2DMS
//    //GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY isampler2DMSArray
//    //GL_INT_SAMPLER_BUFFER   isamplerBuffer
//    //GL_INT_SAMPLER_2D_RECT  isampler2DRect
//    //GL_UNSIGNED_INT_SAMPLER_1D  usampler1D
//    //GL_UNSIGNED_INT_SAMPLER_2D  usampler2D
//    //GL_UNSIGNED_INT_SAMPLER_3D  usampler3D
//    //GL_UNSIGNED_INT_SAMPLER_CUBE    usamplerCube
//    //GL_UNSIGNED_INT_SAMPLER_1D_ARRAY    usampler2DArray
//    //GL_UNSIGNED_INT_SAMPLER_2D_ARRAY    usampler2DArray
//    //GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE  usampler2DMS
//    //GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY    usampler2DMSArray
//    //GL_UNSIGNED_INT_SAMPLER_BUFFER  usamplerBuffer
//    //GL_UNSIGNED_INT_SAMPLER_2D_RECT usampler2DRect
//    //GL_IMAGE_1D image1D
//    //GL_IMAGE_2D image2D
//    //GL_IMAGE_3D image3D
//    //GL_IMAGE_2D_RECT    image2DRect
//    //GL_IMAGE_CUBE   imageCube
//    //GL_IMAGE_BUFFER imageBuffer
//    //GL_IMAGE_1D_ARRAY   image1DArray
//    //GL_IMAGE_2D_ARRAY   image2DArray
//    //GL_IMAGE_2D_MULTISAMPLE image2DMS
//    //GL_IMAGE_2D_MULTISAMPLE_ARRAY   image2DMSArray
//    //GL_INT_IMAGE_1D iimage1D
//    //GL_INT_IMAGE_2D iimage2D
//    //GL_INT_IMAGE_3D iimage3D
//    //GL_INT_IMAGE_2D_RECT    iimage2DRect
//    //GL_INT_IMAGE_CUBE   iimageCube
//    //GL_INT_IMAGE_BUFFER iimageBuffer
//    //GL_INT_IMAGE_1D_ARRAY   iimage1DArray
//    //GL_INT_IMAGE_2D_ARRAY   iimage2DArray
//    //GL_INT_IMAGE_2D_MULTISAMPLE iimage2DMS
//    //GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY   iimage2DMSArray
//    //GL_UNSIGNED_INT_IMAGE_1D    uimage1D
//    //GL_UNSIGNED_INT_IMAGE_2D    uimage2D
//    //GL_UNSIGNED_INT_IMAGE_3D    uimage3D
//    //GL_UNSIGNED_INT_IMAGE_2D_RECT   uimage2DRect
//    //GL_UNSIGNED_INT_IMAGE_CUBE  uimageCube
//    //GL_UNSIGNED_INT_IMAGE_BUFFER    uimageBuffer
//    //GL_UNSIGNED_INT_IMAGE_1D_ARRAY  uimage1DArray
//    //GL_UNSIGNED_INT_IMAGE_2D_ARRAY  uimage2DArray
//    //GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE    uimage2DMS
//    //GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY  uimage2DMSArray
//    //GL_UNSIGNED_INT_ATOMIC_COUNTER  atomic_uint
//}
