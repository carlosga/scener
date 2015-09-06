// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECTPASSINSTANCEPROGRAM_HPP
#define EFFECTPASSINSTANCEPROGRAM_HPP

#include <map>
#include <memory>
#include <string>

#include <Graphics/ShaderType.hpp>

namespace SceneR
{
    namespace Content
    {
        class TechniquesReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class EffectParameter;

        class EffectPassInstanceProgram
        {
        public:
            EffectPassInstanceProgram();
            ~EffectPassInstanceProgram();

        private:
            /**
             * Compiles and links the shader program sources.
             */
            void build_program();

            /**
             * Activates the shader subroutine with the given index.
             */
            void activate_subroutine(const std::uint32_t& subroutineIndex) const;

            /**
             * Activates the shader subroutine with the given shader type and index.
             */
            void activate_subroutine(const SceneR::Graphics::ShaderType& type
                                   , const std::uint32_t&                subroutineIndex) const;

            /**
             * Verify if the shader program has been linked correctly.
             */
            void verify_linking_state();

        private:
            std::string                                             _name;
            std::map<std::string, std::shared_ptr<EffectParameter>> _attributes;
            std::map<std::string, std::shared_ptr<EffectParameter>> _uniforms;

            std::uint32_t                          _id;
//            std::vector<std::shared_ptr<Shader>>   _shaders;
//            std::shared_ptr<UniformBufferObject>   _uniform_buffer;

            friend class SceneR::Content::TechniquesReader;
        };
    }
}

#endif // EFFECTPASSINSTANCEPROGRAM_HPP
