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
#define	SHADERPROGRAM_HPP

#include <memory>
#include <string>
#include <vector>
#include "Core/Core.hpp"
#include "Core/Matrix.hpp"
#include "Core/Vector3.hpp"
#include "Core/Vector4.hpp"
#include "Shaders/Shader.hpp"

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
             * Intializes a new instance of the Program Stage class
             */
            ShaderProgram(const std::wstring& name, std::vector<std::shared_ptr<Shader>> &shaders);

            /**
             * Releases all memory being used by the current ProgramStage instance
             */
            ~ShaderProgram();

        public:
            /**
             * Activates the shader program
             */
            void Activate() const;

            /**
             * Compiles and links the shader stage sources
             */
            void Build();

            /**
             * Deactivates the shader program
             */
            void Deactivate() const;

            /**
             * Gets the stage name
             */
            const std::wstring& Name() const;

            /**
             * Gets the location of the given parameter within the shader program.
             */
            const Int32 GetParameterLocation(const std::wstring& parameterName) const;

            void SetValue(const std::wstring& parameterName, const SceneR::Core::Matrix& matrix) const;
            void SetValue(const Int32& location, const SceneR::Core::Matrix& matrix) const;
            void SetValue(const std::wstring& parameterName, const SceneR::Core::Vector3& vector3) const;
            void SetValue(const Int32& location, const SceneR::Core::Vector3& vector3) const;
            void SetValue(const std::wstring& parameterName, const SceneR::Core::Vector4& vector4) const;
            void SetValue(const Int32& location, const SceneR::Core::Vector4& vector4) const;
            void SetValue(const std::wstring& parameterName, const Single& value) const;
            void SetValue(const Int32& location, const Single& value) const;

        private:
            void Release();

        private:
            std::wstring                         name;
            UInt32                               object;
            std::vector<std::shared_ptr<Shader>> shaders;
        };
    }
}

#endif	/* SHADERPROGRAM_HPP */
