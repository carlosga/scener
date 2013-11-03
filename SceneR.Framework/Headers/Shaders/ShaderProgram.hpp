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

#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <System/Core.hpp>
#include <Shaders/Shader.hpp>
#include <memory>
#include <string>
#include <vector>

namespace SceneR
{
    namespace Framework
    {
        class Matrix;
        class Vector3;
        class Vector4;
    }
}

namespace SceneR
{
    namespace Shaders
    {
        /**
         * Represents a shader program.
         */
        class ShaderProgram
        {
        public:
            /**
             * Intializes a new instance of the ShaderProgram class.
             */
            ShaderProgram(const std::wstring& name, std::vector<std::shared_ptr<Shader>> &shaders);

            /**
             * Releases all memory being used by the current ShaderProgram instance.
             */
            ~ShaderProgram();

        public:
            /**
             * Activates the shader program.
             */
            void Activate() const;

            /**
             * Compiles and links the shader program sources.
             */
            void Build();

            /**
             * Deactivates the shader program.
             */
            void Deactivate() const;

            /**
             * Gets the shader program name.
             * @return the shader program name.
             */
            const std::wstring& Name() const;

            /**
             * Gets the location of the shader parameter with the given name within the shader program.
             * @return the location of the shader parameter with the given name within the shader program.
             */
            const System::Int32 GetParameterLocation(const std::wstring& parameterName) const;

            /**
             * Sets the value of the shader parameter with the given name as a Matrix.
             * @param parameterName the shader parameter name.
             * @param matrix the value to assign to the shader parameter.
             */
            void SetValue(const std::wstring& parameterName, const SceneR::Framework::Matrix& matrix) const;

            /**
             * Sets the value of the shader parameter with the given location as a Matrix.
             * @param location the location of the shader parameter.
             * @param matrix the value to assign to the shader parameter.
             */
            void SetValue(const System::Int32& location, const SceneR::Framework::Matrix& matrix) const;

            /**
             * Sets the value of the shader parameter with the given name as a Vector3.
             * @param parameterName the shader parameter name.
             * @param vector3 the value to assign to the shader parameter.
             */
            void SetValue(const std::wstring& parameterName, const SceneR::Framework::Vector3& vector3) const;

            /**
             * Sets the value of the shader parameter with the given location as a Vector3.
             * @param location the location of the shader parameter.
             * @param vector3 the value to assign to the shader parameter.
             */
            void SetValue(const System::Int32& location, const SceneR::Framework::Vector3& vector3) const;

            /**
             * Sets the value of the shader parameter with the given name as a Vector4.
             * @param parameterName the shader parameter name.
             * @param vector4 the value to assign to the shader parameter.
             */
            void SetValue(const std::wstring& parameterName, const SceneR::Framework::Vector4& vector4) const;

            /**
             * Sets the value of the shader parameter with the given location as a Vector4.
             * @param location the location of the shader parameter.
             * @param vector4 the value to assign to the shader parameter.
             */
            void SetValue(const System::Int32& location, const SceneR::Framework::Vector4& vector4) const;

            /**
             * Sets the value of the shader parameter with the given name as a scalar value of type System::Single.
             * @param parameterName the shader parameter name.
             * @param value the value to assign to the shader parameter.
             */
            void SetValue(const std::wstring& parameterName, const System::Single& value) const;

            /**
             * Sets the value of the shader parameter with the given location as a scalar value of type System::Single.
             * @param location the location of the shader parameter.
             * @param value the value to assign to the shader parameter.
             */
            void SetValue(const System::Int32& location, const System::Single& value) const;

        private:
            void Release();
            void VerifyLinkingState();

        private:
            std::wstring                         name;
            System::UInt32                       object;
            std::vector<std::shared_ptr<Shader>> shaders;
        };
    }
}

#endif  /* SHADERPROGRAM_HPP */
