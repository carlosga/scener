// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_PROGRAM_HPP
#define GRAPHICS_PROGRAM_HPP

#include <memory>
#include <vector>
#include <string>
#include <System/IDisposable.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Shader;

        class Program final : public System::IDisposable
        {
        public:
            Program();
            ~Program();

        public:
            void dispose() override;

        public:
            std::uint32_t id() const;

            void create();

            void add_shader(std::shared_ptr<Shader> shader);

            void link();

        private:
            void verify_linking_state();

        public:
            std::u16string name;

        private:
            std::uint32_t _id;
        };
    }
}

#endif  // GRAPHICS
