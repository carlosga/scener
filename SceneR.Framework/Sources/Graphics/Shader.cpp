// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Shader.hpp>

#include <cstddef>

#include <System/Text/Encoding.hpp>
#include <Graphics/ShaderManager.hpp>

namespace SceneR
{
    namespace Graphics
    {
        Shader::Shader(const std::u16string& name, const ShaderType& type, const std::vector<std::uint8_t>& source)
            : Shader { name, type, std::string(source.begin(), source.end()) }
        {
        }

        Shader::Shader(const std::u16string& name, const ShaderType& type, const std::string& source)
            : Shader { name, type, source, std::vector<std::string>() }
        {
        }

        Shader::Shader(const std::u16string&            name
                     , const ShaderType&                type
                     , const std::vector<std::uint8_t>& source
                     , const std::vector<std::string>&  includes)
            : Shader { name, type, std::string(source.begin(), source.end()), includes }
        {
        }

        Shader::Shader(const std::u16string&           name
                     , const ShaderType&               type
                     , const std::string&              source
                     , const std::vector<std::string>& includes)
            : _name     { name }
            , _id       { 0 }
            , _type     { type }
            , _source   { source }
            , _includes { includes }
        {

        }

        Shader::~Shader()
        {
        }

        void Shader::dispose()
        {
            if (_id != 0)
            {
                glDeleteShader(_id);
                _id = 0;
            }
        }

        const std::u16string& Shader::name() const
        {
            return _name;
        }

        const ShaderType& Shader::type() const
        {
            return _type;
        }

        void Shader::compile()
        {
            if (is_compiled())
            {
                return;
            }

            ShaderManager manager;

            std::vector<const char*> cpaths(0);

            // process includes
            for (const auto& path : _includes)
            {
                cpaths.push_back(manager.get_path_reference(path));
            }

            // create the shader object
            _id = glCreateShader(static_cast<GLenum>(_type));

            if (_id == 0)
            {
                throw std::runtime_error("glCreateShader failed");
            }

            // root shader
            const char* cstring = _source.c_str();

            glShaderSource(_id, 1, (const GLchar**)&cstring, NULL);

            // Compile the shader source
            glCompileShaderIncludeARB(_id, cpaths.size(), (const GLchar**)&cpaths[0], NULL);

            // Verify compilation state
            verify_compilation_state();
        }

        bool Shader::is_compiled() const
        {
            bool result = false;

            if (_id != 0)
            {
                GLint status;
                glGetShaderiv(_id, GL_COMPILE_STATUS, &status);

                result = (status == GL_TRUE);
            }

            return result;
        }

        void Shader::verify_compilation_state()
        {
            if (!is_compiled())
            {
                std::string msg("Compile failure in shader:\n");

                GLint infoLogLength;
                glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);

                if (infoLogLength)
                {
                    auto compileErrorMessage = std::string("", static_cast<std::size_t>(infoLogLength));

                    glGetShaderInfoLog(_id, infoLogLength, NULL, &compileErrorMessage[0]);

                    msg += compileErrorMessage;
                }

                dispose();

                throw std::runtime_error(msg);
            }
        }
    }
}