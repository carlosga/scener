// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <System/Core.hpp>
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
            Texture2D(GraphicsDevice& graphicsDevice,
                      const uint32_t& width,
                      const uint32_t& height);

            /**
             * Creates a new instance of the Texture2D class.
             *
             * @param graphicsDevice the graphics device
             * @param width the texture width, in pixels
             * @param height the texture height, in pixels
             * @param mipmap true to generate a full mipmap chain; false otherwise.
             * @param format texture data format
             */
            Texture2D(GraphicsDevice&      graphicsDevice,
                      const uint32_t&      width,
                      const uint32_t&      height,
                      const bool&          mipmap,
                      const SurfaceFormat& format);

            /**
             * Releases all resources being used by this texture.
             */
            ~Texture2D() override;

        public:
            void Dispose() override;

        public:
            /**
             * Gets the format of the texture data.
             */
            const SurfaceFormat& Format() const override;

            /**
             * Gets the texture height, in pixels
             */
            uint32_t Height() const;

            /**
             * Gets the number of texture levels in a multilevel texture.
             */
            uint32_t LevelCount() const override;

            /**
             * Gets the texture width, in pixels
             */
            uint32_t Width() const;

            /**
             * Sets mipmap data to the texture.
             * @param level the mipmap level.
             * @param size the size of the mipmap data.
             * @param data pointer with the mipmap data.
             */
            void SetData(const uint32_t& level, const System::Size& size, const void* data);

            /**
             * Activates the texture object
             */
            void Activate() const override;

            /**
             * Deactivates the texture object
             */
            void Deactivate() const override;

        private:
            void DeclareStorage(const uint32_t& mipMapLevels);

        private:
            SurfaceFormat format;
            uint32_t      height;
            bool          mipmap;
            uint32_t      mipmapLevels;
            uint32_t      mipmapHeight;
            uint32_t      mipmapWidth;
            uint32_t      width;
            TextureObject object;

            friend class SceneR::Content::Texture2DReader;
        };
    }
}

#endif  /* TEXTURE2D_HPP */
