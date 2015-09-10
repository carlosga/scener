// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_PROGRAM_HPP
#define GRAPHICS_PROGRAM_HPP

#include <cstddef>
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <System/IDisposable.hpp>

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
        class Shader;
        class UniformBufferObject;

        class Program final : public System::IDisposable
        {
        public:
            Program();
            ~Program();

        public:
            void dispose() override;

        public:
            std::uint32_t id() const;

            std::shared_ptr<UniformBufferObject> uniform_buffer() const;

            void create();

            void activate() const;

            void add_shader(std::shared_ptr<Shader> shader);

            void deactivate() const;

            void link();

            std::map<std::string, std::size_t> get_uniform_offsets() const;

            void activate_subroutine(const ShaderType& type, const std::uint32_t& subroutineIndex) const;

        private:
            void verify_linking_state();

        public:
            std::u16string name;

        private:
            std::uint32_t                        _id;
            std::shared_ptr<UniformBufferObject> _uniform_buffer;

            friend class SceneR::Content::TechniquesReader;
        };
    }
}

#endif  // GRAPHICS
