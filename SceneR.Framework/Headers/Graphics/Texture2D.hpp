// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <cstddef>
#include <cstdint>

#include <Graphics/SurfaceFormat.hpp>
#include <Graphics/TextureObject.hpp>
#include <Graphics/Texture.hpp>

namespace SceneR
{
    namespace Content
    {
        class Texture2DReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;

        /**
         * Represents a 2D texture.
         */
        class Texture2D final : public Texture
        {
        public:
            /**
             * Creates a new instance of the Texture2D class.
             *
             * @param graphicsDevice the graphics device
             * @param width the texture width, in pixels
             * @param height the texture height, in pixels
             */
            Texture2D(GraphicsDevice&    graphicsDevice
                    , const std::size_t& width
                    , const std::size_t& height);

            /**
             * Creates a new instance of the Texture2D class.
             *
             * @param graphicsDevice the graphics device
             * @param width the texture width, in pixels
             * @param height the texture height, in pixels
             * @param mipmap true to generate a full mipmap chain; false otherwise.
             * @param format texture data format
             */
            Texture2D(GraphicsDevice&      graphicsDevice
                    , const std::size_t&   width
                    , const std::size_t&   height
                    , const bool&          mipmap
                    , const SurfaceFormat& format);

            /**
             * Releases all resources being used by this texture.
             */
            ~Texture2D() override;

        public:
            void Dispose() override;

        public:
            std::uint32_t Id() const override;

            /**
             * Gets the format of the texture data.
             */
            const SurfaceFormat& Format() const override;

            /**
             * Gets the texture height, in pixels
             */
            std::size_t Height() const;

            /**
             * Gets the number of texture levels in a multilevel texture.
             */
            std::size_t LevelCount() const override;

            /**
             * Gets the texture width, in pixels
             */
            std::size_t Width() const;

            /**
             * Sets mipmap data to the texture.
             * @param level the mipmap level.
             * @param size the size of the mipmap data.
             * @param data pointer with the mipmap data.
             */
            void SetData(const std::size_t& level, const std::size_t& size, const void* data);

            /**
             * Activates the texture object
             */
            void Activate() const override;

            /**
             * Deactivates the texture object
             */
            void Deactivate() const override;

        private:
            void DeclareStorage(const std::size_t& mipMapLevels);

        private:
            SurfaceFormat format;
            std::size_t   height;
            bool          mipmap;
            std::size_t   mipmapLevels;
            std::size_t   mipmapHeight;
            std::size_t   mipmapWidth;
            std::size_t   width;
            TextureObject object;

            friend class SceneR::Content::Texture2DReader;
        };
    }
}

#endif  /* TEXTURE2D_HPP */
