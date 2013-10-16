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

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include "Core/Core.hpp"
#include "Shaders/ShaderType.hpp"

namespace SceneR
{
    namespace Shaders
    {
        class ShaderProgram;
        
        /**
         * Represents a shader
         */
        class Shader
        {
        public:
            /**
             * Initializes a new instance of the Shader class.
             *
             * @param shaderCode the source code for the shader.
             * @param shaderType the type of the shader
             */
            Shader(const std::wstring& shaderCode, const ShaderType& shaderType);

            /**
             * Releases all resources being used by this shader instance.
             */
            ~Shader();

        public:
            /**
             * Performs the compilation of the shader source code.
             */
            void Compile();

            /**
             * Indicates wheter the shader has been compiled
             */
            const bool IsCompiled() const;

        private:
            void Release();
            void VerifyCompilationState();

        private:
            GLuint       object;
            std::wstring shaderCode;
            ShaderType   shaderType;

            friend class ShaderProgram;
        };
    }
}

#endif  /* SHADER_HPP */
