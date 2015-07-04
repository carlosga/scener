// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SHADER_HPP
#define SHADER_HPP

#include <stdint.h>
#include <string>
#include <vector>

#include <System/IDisposable.hpp>
#include <Graphics/ShaderType.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Effect;

        /**
         * Represents a shader
         */
        class Shader final : System::IDisposable
        {
        public:
            /**
             * Initializes a new instance of the Shader class.
             * @param name the name of the shader.
             * @param type the type of the shader.
             * @param source the source code for the shader.
             */
            Shader(const std::u16string& name, const ShaderType& type, const std::string& source);

            /**
             * Initializes a new instance of the Shader class.
             * @param name the name of the shader.
             * @param type the type of the shader
             * @param source the source code for the shader.
             * @param includes the shader includes references.
             */
            Shader(const std::u16string&           name
                 , const ShaderType&               type
                 , const std::string&              source
                 , const std::vector<std::string>& includes);

            /**
             * Destructor
             */
            ~Shader() override;

        public:
            void Dispose() override;

        public:
            /**
             * @brief Gets the name of the shader.
             * @return the name of the shader.
             */
            const std::u16string& Name() const;

            /**
             * @brief Gets the type of the shader.
             * @return the type of the shader.
             */
            const ShaderType& Type() const;

            /**
             * Performs the compilation of the shader source code.
             */
            void Compile();

            /**
             * Indicates wheter the shader has been compiled
             */
            bool IsCompiled() const;

        private:
            void VerifyCompilationState();

        private:
            std::u16string           name;
            uint32_t                 id;
            ShaderType               type;
            std::string              source;
            std::vector<std::string> includes;

            friend class Effect;
        };
    }
}

#endif  /* SHADER_HPP */
