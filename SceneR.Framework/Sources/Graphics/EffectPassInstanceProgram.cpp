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
        }

        void EffectPassInstanceProgram::build_program()
        {
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


    }
}
