// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SHADER_HPP
#define SHADER_HPP

#include <System/IDisposable.hpp>
#include <Graphics/ShaderType.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class ShaderProgram;

        /**
         * Represents a shader
         */
        class Shader : System::IDisposable
        {
        public:
            /**
             * Initializes a new instance of the Shader class.
             *
             * @param shaderCode the source code for the shader.
             * @param shaderType the type of the shader
             */
            Shader(const System::String& shaderCode, const ShaderType& shaderType);

            /**
             * Destructor
             */
            ~Shader();

        public:
            void Dispose() override;

        public:
            /**
             * Performs the compilation of the shader source code.
             */
            void Compile();

            /**
             * Indicates wheter the shader has been compiled
             */
            System::Boolean IsCompiled() const;

        private:
            void VerifyCompilationState();

        private:
            System::UInt32 object;
            System::String shaderCode;
            ShaderType     shaderType;

            friend class ShaderProgram;
        };
    }
}

#endif  /* SHADER_HPP */
