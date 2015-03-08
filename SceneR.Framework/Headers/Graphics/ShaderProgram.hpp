// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <memory>
#include <map>
#include <vector>

#include <System/Core.hpp>
#include <System/IDisposable.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <Graphics/ShaderType.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct Matrix;
        struct Quaternion;
        struct Vector2;
        struct Vector3;
        struct Vector4;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Shader;

        /**
         * Represents a shader program.
         */
        class ShaderProgram final : System::IDisposable
        {
        public:
            /**
             * Intializes a new instance of the ShaderProgram class.
             */
            ShaderProgram();

            /**
             * Destructor
             */
            ~ShaderProgram() override;

        public:
            void Dispose() override;

        public:
            /**
             * @brief Adds the given shader sources to the shader program for later compilation.
             * @param shaderName the name of the shader.
             * @param shaderType the type of the shader.
             * @param shaderSource the shader sources.
             */
            void AddShader(const System::String& shaderName
                         , const ShaderType&     shaderType
                         , const std::string&    shaderSource);

            /**
             * @brief Adds the given shader sources and includes to the shader program for later compilation
             * @param shaderName the name of the shader.
             * @param shaderType the type of the shader.
             * @param shaderSource the shader sources.
             * @param shaderIncludes the shader sources for "include" files.
             */
            void AddShader(const System::String&           shaderName
                         , const ShaderType&               shaderType
                         , const std::string&              shaderSource
                         , const std::vector<std::string>& shaderIncludes);

            /**
             * Activates the shader program.
             */
            void Activate() const;

            /**
             *
             */
            void ActivateSubroutine(const System::UInt32& subroutineIndex) const;

            /**
             * Compiles and links the shader program sources.
             */
            void Build();

            /**
             * Deactivates the shader program.
             */
            void Deactivate() const;

            /**
             * Gets the location of the shader parameter with the given name within the shader program.
             * @return the location of the shader parameter with the given name within the shader program.
             */
            System::Int32 GetParameterLocation(const System::String& parameterName) const;

        public:
            /**
             * Sets the value of the EffectParameter as a System::Boolean.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const System::Boolean& value) const;

            /**
             * Gets the value of the EffectParameter as an array of System::Boolean.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const std::vector<System::Boolean>& value) const;

            /**
             * Sets the value of the EffectParameter as an System::Int32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const System::Int32& value) const;

            /**
             * Sets the value of the EffectParameter as an array of System::Int32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const std::vector<System::Int32>& value) const;

            /**
             * Sets the value of the EffectParameter as an System::UInt32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const System::UInt32& value) const;

            /**
             * Sets the value of the EffectParameter as an array of System::UInt32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const std::vector<System::UInt32>& value) const;

            /**
             * Sets the value of the EffectParameter as a Matrix.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const SceneR::Framework::Matrix& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Matrix.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const std::vector<SceneR::Framework::Matrix>& value) const;

            /**
             * Sets the value of the EffectParameter as a Matrix transpose.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValueTranspose(const System::Int32& location, const SceneR::Framework::Matrix& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Matrix transpose.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValueTranspose(const System::Int32& location, const std::vector<SceneR::Framework::Matrix>& value) const;

            /**
             * Sets the value of the EffectParameter as a Quaternion.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const SceneR::Framework::Quaternion& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Quaternion.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const std::vector<SceneR::Framework::Quaternion>& value) const;

            /**
             * Sets the value of the EffectParameter as a System::Single.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const System::Single& value) const;

            /**
             * Sets the value of the EffectParameter as an array of System::Single.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const std::vector<System::Single>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector2.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const SceneR::Framework::Vector2& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector2.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const std::vector<SceneR::Framework::Vector2>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector3.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const SceneR::Framework::Vector3& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector3.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const std::vector<SceneR::Framework::Vector3>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector4.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const SceneR::Framework::Vector4& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector4.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::Int32& location, const std::vector<SceneR::Framework::Vector4>& value) const;

        private:
            void DescribeUniformBlocks();
            void DescribeParameters();
            void VerifyLinkingState();
            void InferParameterClassAndType(const System::UInt32&                   type
                                          , SceneR::Graphics::EffectParameterClass& epClass
                                          , SceneR::Graphics::EffectParameterType&  epType) const;

        private:
            System::UInt32                       id;
            std::vector<std::shared_ptr<Shader>> shaders;
        };
    }
}

#endif  /* SHADERPROGRAM_HPP */
