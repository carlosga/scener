// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/EffectPassInstanceProgram.hpp>

namespace SceneR
{
    namespace Graphics
    {
        EffectPassInstanceProgram::EffectPassInstanceProgram()
        {
        }

        EffectPassInstanceProgram::~EffectPassInstanceProgram()
        {
            if (_id != 0)
            {
                // Dipose all the shader instances
//                if (_shaders.size() > 0)
//                {
//                    for (auto& shader : _shaders)
//                    {
//                        shader->dispose();
//                    }
//
//                    _shaders.clear();
//                }

                // dispose the uniform buffer object
//                _uniform_buffer->dispose();
//                _uniform_buffer = nullptr;
//
//                // Delete the shader program
//                glDeleteProgram(_id);

                // Reset the shader program name
                _id = 0;
            }
        }

        void EffectPassInstanceProgram::build_program()
        {
//            // Compile the shaders ...
//            for (auto& s : _shaders)
//            {
//                s->Compile();
//            }
//
//            // ... Create the program object
//            _id = glCreateProgram();
//
//            if (_id == 0)
//            {
//                throw std::runtime_error("glCreateProgram failed");
//            }
//
//            // ... attach the shaders to the new shader program
//            for (const auto& s : _shaders)
//            {
//                // Attach the shader
//                glAttachShader(_id, s->id);
//            }
//
//            // ... link the shader program
//            glLinkProgram(_id);
//
//            // ... verify program linking
//            _VerifyLinkingState();
//
//            // ... fill uniform buffer info
//            _uniformBuffer = std::make_shared<UniformBufferObject>(u"ConstantBuffer", _id);
//            _uniformBuffer->Describe();
//
//            // ... describe efffect parameters
//            _DescribeParameters();
        }

        void EffectPassInstanceProgram::activate_subroutine(const std::uint32_t& subroutineIndex) const
        {
//            for (const auto& shader : _shaders)
//            {
//                activate_subroutine(shader->type(), subroutineIndex);
//            }
        }

        void EffectPassInstanceProgram::activate_subroutine(const ShaderType& type, const std::uint32_t& subroutineIndex) const
        {
            glUniformSubroutinesuiv(static_cast<GLenum>(type), 1, &subroutineIndex);
        }

        void EffectPassInstanceProgram::verify_linking_state()
        {
            // ... verify program linking
            GLint status;
            glGetProgramiv(_id, GL_LINK_STATUS, &status);

            if (status == GL_FALSE)
            {
                auto msg = std::string("Program linking failure: ");

                GLint infoLogLength;
                glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);

                if (infoLogLength)
                {
                    std::string linkErrorMessage("", static_cast<std::size_t>(infoLogLength));

                    glGetProgramInfoLog(_id, infoLogLength, NULL, &linkErrorMessage[0]);

                    msg += linkErrorMessage;
                }

                //_dispose();

                throw std::runtime_error(msg);
            }
        }
    }
}
