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

#include <Graphics/Shader.hpp>
#include <System/Core.hpp>
#include <memory>
#include <vector>

namespace SceneR
{
    namespace Graphics
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
            ShaderProgram(std::vector<std::shared_ptr<Shader>> &shaders);

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
            const System::String& Name() const;

            /**
             * Gets the location of the shader parameter with the given name within the shader program.
             * @return the location of the shader parameter with the given name within the shader program.
             */
            System::Int32 GetParameterLocation(const System::String& parameterName) const;

        private:
            void Release();
            void VerifyLinkingState();

        private:
            System::UInt32                       id;
            std::vector<std::shared_ptr<Shader>> shaders;
        };
    }
}

#endif  /* SHADERPROGRAM_HPP */
