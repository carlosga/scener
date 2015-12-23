// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_PROGRAM_HPP
#define GRAPHICS_PROGRAM_HPP

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <string>

#include <Graphics/ShaderType.hpp>
#include <Graphics/UniformBufferObject.hpp>
#include <System/IDisposable.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class EffectParameter;
        class Shader;

        class Program final : public System::IDisposable
        {
        public:
            Program() = default;

            ~Program() = default;

        public:
            void dispose() override;

        public:
            std::uint32_t id() const noexcept;

            UniformBufferObject* uniform_buffer() const noexcept;

            void create();

            void bind() const;

            void add_shader(std::shared_ptr<Shader> shader);

            void unbind() const;

            void link();

            std::map<std::string, std::size_t> get_uniform_offsets() const;

            void activate_subroutine(const ShaderType& type, const std::uint32_t& subroutineIndex) const;

        private:
            void verify_linking_state();

        public:
            std::string name { };

        private:
            std::uint32_t                        _id             { 0 };
            std::unique_ptr<UniformBufferObject> _uniform_buffer { nullptr };
        };
    }
}

#endif  // GRAPHICS
