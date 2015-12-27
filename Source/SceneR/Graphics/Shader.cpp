// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Shader.hpp"

#include <cstddef>

#include <gsl_assert.h>

#include "SceneR/Graphics/ShaderInclude.hpp"

namespace SceneR
{
    namespace Graphics
    {
        Shader::Shader(const std::string& name, const ShaderType& type, const std::vector<std::uint8_t>& source) noexcept
            : Shader { name, type, std::string(source.begin(), source.end()) }
        {
        }

        Shader::Shader(const std::string& name, const ShaderType& type, const std::string& source) noexcept
            : _name   { name }
            , _id     { 0 }
            , _type   { type }
            , _source { source }
        {
        }

        void Shader::dispose()
        {
            if (_id != 0)
            {
                for (auto include : _includes)
                {
                    include->remove();
                }

                _includes.clear();
                glDeleteShader(_id);
                _id = 0;
            }
        }

        std::uint32_t Shader::id() const noexcept
        {
            return _id;
        }

        const std::string& Shader::name() const noexcept
        {
            return _name;
        }

        const ShaderType& Shader::type() const noexcept
        {
            return _type;
        }

        void Shader::add_include(std::shared_ptr<ShaderInclude> include)
        {
            Expects(!is_compiled());
            Expects(include->is_declared());

            _includes.push_back(include);
        }

        void Shader::compile()
        {
            if (is_compiled())
            {
                return;
            }

            // create the shader object
            _id = glCreateShader(static_cast<GLenum>(_type));

            Ensures(_id > 0);

            // root shader
            const char* cstring = _source.c_str();

            glShaderSource(_id, 1, (const GLchar**)&cstring, NULL);

            if (_includes.size() == 0)
            {
                // Compile the shader source
                glCompileShader(_id);
            }
            else
            {
                std::vector<const char*> cpaths(0);

                // process include paths
                for (const auto& include : _includes)
                {
                    cpaths.push_back(include->path.c_str());
                }

                // Compile the shader source
                glCompileShaderIncludeARB(_id, cpaths.size(), (const GLchar**)&cpaths[0], NULL);
            }

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
            if (is_compiled())
            {
                return;
            }

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
