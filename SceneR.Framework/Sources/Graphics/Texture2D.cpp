// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Texture2D.hpp>

#include <Graphics/GraphicsDevice.hpp>

namespace SceneR
{
    namespace Graphics
    {
        Texture2D::Texture2D(GraphicsDevice&    graphicsDevice
                           , const std::size_t& width
                           , const std::size_t& height)
            : Texture2D(graphicsDevice, width, height, false, SurfaceFormat::Color)
        {
        }

        Texture2D::Texture2D(GraphicsDevice&      graphicsDevice
                           , const std::size_t&   width
                           , const std::size_t&   height
                           , const bool&          mipmap
                           , const SurfaceFormat& format)
            : Texture      { graphicsDevice }
            , format       { format }
            , height       { height }
            , mipmap       { mipmap }
            , mipmapLevels { 0 }
            , mipmapHeight { height }
            , mipmapWidth  { width }
            , width        { width }
            , object       { TextureTarget::Texture2D }
        {
        }

        Texture2D::~Texture2D()
        {
        }

        void Texture2D::Dispose()
        {
            this->object.Dispose();
        }

        const SurfaceFormat& Texture2D::Format() const
        {
            return this->format;
        }

        std::size_t Texture2D::Height() const
        {
            return this->height;
        }

        std::size_t Texture2D::LevelCount() const
        {
            return this->mipmapLevels;
        }

        std::size_t Texture2D::Width() const
        {
            return this->width;
        }

        void Texture2D::SetData(const std::size_t& level, const std::size_t& size, const void* data)
        {
            // http://www.oldunreal.com/editing/s3tc/ARB_texture_compression.pdf
            if (this->mipmapWidth == 0)
            {
                this->mipmapWidth = 1;
            }
            if (this->mipmapHeight == 0)
            {
                this->mipmapHeight = 1;
            }

            this->object.TextureSubImage2D(this->format, level, this->mipmapWidth, this->mipmapHeight, size, data);

            this->mipmapWidth  >>= 1;
            this->mipmapHeight >>= 1;
        }

        void Texture2D::DeclareStorage(const std::size_t& mipMapLevels)
        {
            this->object.Declare2DStorage(this->format, mipMapLevels, this->width, this->height);
            this->mipmapLevels = mipMapLevels;
        }

        void Texture2D::Activate() const
        {
            this->object.Activate();
        }

        void Texture2D::Deactivate() const
        {
            this->object.Deactivate();
        }
    }
}
