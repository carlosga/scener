// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SHADER_HPP
#define SHADER_HPP

#include <map>

#include <System/Core.hpp>
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
        class Shader final : System::IDisposable
        {
        public:
            /**
             * @brief Root path for shader includes.
             */
            static const std::string ShaderIncludeRoot;

        public:
            static void DeclareShaderInclude(const std::string& name, const std::string& shaderInclude);

        public:
            /**
             * Initializes a new instance of the Shader class.
             * @param shaderType the type of the shader
             * @param shaderCode the source code for the shader.
             */
            Shader(const ShaderType& shaderType, const System::String& shaderCode);

            /**
             * Initializes a new instance of the Shader class.
             * @param shaderType the type of the shader
             * @param shaderCode the source code for the shader.
             */
            Shader(const ShaderType&                               shaderType
                 , const System::String&                           shaderCode
                 , const std::map<System::String, System::String>& shaderIncludes);

            /**
             * Destructor
             */
            ~Shader() override;

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
            std::map<std::string, std::string> Convert();
            void VerifyCompilationState();

        private:
            System::UInt32                           object;
            ShaderType                               shaderType;
            System::String                           shaderCode;
            std::map<System::String, System::String> shaderIncludes;

            friend class ShaderProgram;
        };
    }
}

#endif  /* SHADER_HPP */
