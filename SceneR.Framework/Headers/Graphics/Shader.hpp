// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_SHADER_HPP
#define GRAPHICS_SHADER_HPP

#include <cstdint>
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
            Shader(const std::u16string& name, const ShaderType& type, const std::vector<std::uint8_t>& source);

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
            Shader(const std::u16string&            name
                 , const ShaderType&                type
                 , const std::vector<std::uint8_t>& source
                 , const std::vector<std::string>&  includes);

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
            void dispose() override;

        public:
            /**
             * @brief Gets the name of the shader.
             * @return the name of the shader.
             */
            const std::u16string& name() const;

            /**
             * @brief Gets the type of the shader.
             * @return the type of the shader.
             */
            const ShaderType& type() const;

            /**
             * Performs the compilation of the shader source code.
             */
            void compile();

            /**
             * Indicates wheter the shader has been compiled
             */
            bool is_compiled() const;

        private:
            void verify_compilation_state();

        private:
            std::u16string           _name;
            std::uint32_t            _id;
            ShaderType               _type;
            std::string              _source;
            std::vector<std::string> _includes;

            friend class Effect;
        };
    }
}

#endif  // GRAPHICS_SHADER_HPP
