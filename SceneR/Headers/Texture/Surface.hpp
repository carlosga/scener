// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTURE_SURFACE_HPP
#define TEXTURE_SURFACE_HPP

#include <cstddef>
#include <string>
#include <Graphics/SurfaceFormat.hpp>
#include <Texture/SurfaceMipmap.hpp>

namespace SceneR
{
    namespace Texture
    {
        class Surface final
        {
        public:
            typedef std::size_t size_type;

        public:
            Surface() = default;

            ~Surface() = default;

        public:
            void load(const std::string& filename);

        public:
            const SceneR::Graphics::SurfaceFormat& format() const noexcept;
            size_type width() const noexcept;
            size_type height() const noexcept;
            const std::vector<SurfaceMipmap>& mipmaps() const noexcept;

        private:
            std::vector<std::uint8_t> read_file(const std::string& filename) const noexcept;

        private:
            SceneR::Graphics::SurfaceFormat _format;
            size_type                       _width;
            size_type                       _height;
            std::vector<SurfaceMipmap>      _mipmaps;
        };
    }
}

#endif //SCENER_ROOT_SURFACE_HPP
