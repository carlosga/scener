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
            Surface();
            ~Surface();

        public:
            void load(const std::u16string& filename);

        public:
            const SceneR::Graphics::SurfaceFormat& format() const;
            size_type width() const;
            size_type height() const;
            const std::vector<SurfaceMipmap>& mipmaps() const;

        private:
            SceneR::Graphics::SurfaceFormat _format;
            size_type                       _width;
            size_type                       _height;
            std::vector<SurfaceMipmap>      _mipmaps;
        };
    }
}

#endif //SCENER_ROOT_SURFACE_HPP