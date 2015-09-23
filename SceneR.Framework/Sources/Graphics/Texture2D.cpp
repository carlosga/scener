// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Texture2D.hpp>

#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/SamplerState.hpp>

namespace SceneR
{
    namespace Graphics
    {
        Texture2D::Texture2D(Guide::not_null<GraphicsDevice*> graphicsDevice
                           , const std::size_t&               width
                           , const std::size_t&               height)
            : Texture2D(graphicsDevice, width, height, false, SurfaceFormat::Color)
        {
        }

        Texture2D::Texture2D(Guide::not_null<GraphicsDevice*> graphicsDevice
                           , const std::size_t&               width
                           , const std::size_t&               height
                           , const bool&                      mipmap
                           , const SurfaceFormat&             format)
            : Texture        { graphicsDevice }
            , _format        { format }
            , _height        { height }
            , _mipmap        { mipmap }
            , _mipmap_levels { 0 }
            , _mipmap_height { height }
            , _mipmap_width  { width }
            , _width         { width }
            , _object        { TextureTarget::Texture2D }
        {
        }

        void Texture2D::dispose()
        {
            _object.dispose();
        }

        std::uint32_t Texture2D::id() const
        {
            return _object.id();
        }

        const SurfaceFormat& Texture2D::format() const
        {
            return _format;
        }

        std::size_t Texture2D::height() const
        {
            return _height;
        }

        std::size_t Texture2D::level_count() const
        {
            return _mipmap_levels;
        }

        std::size_t Texture2D::width() const
        {
            return _width;
        }

        std::shared_ptr<SamplerState> Texture2D::sampler_state() const
        {
            return _sampler_state;
        }

        void Texture2D::set_data(const std::size_t& level, const std::size_t& size, const void* data)
        {
            // http://www.oldunreal.com/editing/s3tc/ARB_texture_compression.pdf
            if (_mipmap_width == 0)
            {
                _mipmap_width = 1;
            }
            if (_mipmap_height == 0)
            {
                _mipmap_height = 1;
            }

            _object.texture_sub_image_2D(_format, level, _mipmap_width, _mipmap_height, size, data);

            _mipmap_width  >>= 1;
            _mipmap_height >>= 1;
        }

        void Texture2D::declare_storage(const std::size_t& mipMapLevels)
        {
            _object.declare_2D_storage(_format, mipMapLevels, _width, _height);
            _mipmap_levels = mipMapLevels;
        }

        void Texture2D::bind() const
        {
            _object.activate();
        }

        void Texture2D::unbind() const
        {
            _object.deactivate();
        }
    }
}
