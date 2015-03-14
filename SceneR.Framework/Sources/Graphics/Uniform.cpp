#include <System/Graphics/Platform.hpp>
#include <Graphics/Uniform.hpp>

using namespace System;
using namespace SceneR::Graphics;

Uniform::Uniform()
    : name        { u"" }
    , index       { 0 }
    , offset      { 0 }
    , columnCount { 0 }
    , rowCount    { 0 }
{
}

Uniform::Uniform(const System::String& name
               , const System::UInt32& index
               , const System::UInt32& offset
               , const System::UInt32& type)
    : name        { name }
    , index       { index }
    , offset      { offset }
    , columnCount { 0 }
    , rowCount    { 0 }
{
    this->Describe(type);
}

Uniform::Uniform(const Uniform& uniform)
    : name           { uniform.name }
    , index          { uniform.index }
    , offset         { uniform.offset }
    , columnCount    { uniform.columnCount }
    , rowCount       { uniform.rowCount }
    , parameterClass { uniform.parameterClass }
    , parameterType  { uniform.parameterType }
{
}

Uniform::~Uniform()
{
}

const String& Uniform::Name() const
{
    return this->name;
}

UInt32 Uniform::Index() const
{
    return this->index;
}

Int32 Uniform::Offset() const
{
    return this->offset;
}

const EffectParameterClass&Uniform::ParameterClass() const
{
    return this->parameterClass;
}

const EffectParameterType& Uniform::ParameterType() const
{
    return this->parameterType;
}

System::UInt32 Uniform::RowCount() const
{
    return rowCount;
}

Uniform& Uniform::operator=(const Uniform& uniform)
{
    if (this != &uniform)
    {
        this->name           = uniform.name;
        this->index          = uniform.index;
        this->offset         = uniform.offset;
        this->columnCount    = uniform.columnCount;
        this->rowCount       = uniform.rowCount;
        this->parameterClass = uniform.parameterClass;
        this->parameterType  = uniform.parameterType;
    }

    return *this;
}

System::UInt32 Uniform::ColumnCount() const
{
    return columnCount;
}

void Uniform::Describe(const Int32& type)
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
