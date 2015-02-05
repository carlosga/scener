// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

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
        class Texture2D : public Texture
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
                      const System::UInt32&   width,
                      const System::UInt32&   height);

            /**
             * Creates a new instance of the Texture2D class.
             *
             * @param graphicsDevice the graphics device
             * @param width the texture width, in pixels
             * @param height the texture height, in pixels
             * @param mipMap true to generate a full mipmap chain; false otherwise.
             * @param format texture data format
             */
            Texture2D(GraphicsDevice&        graphicsDevice,
                      const System::UInt32&  width,
                      const System::UInt32&  height,
                      const System::Boolean& mipmap,
                      const SurfaceFormat&   format);

            /**
             * Releases all resources being used by this texture.
             */
            virtual ~Texture2D();

        public:
            /**
             * Gets the format of the texture data.
             */
            virtual const SurfaceFormat& Format() const override;

            /**
             * Gets the texture height, in pixels
             */
            const System::UInt32& Height() const;

            /**
             * Gets the number of texture levels in a multilevel texture.
             */
            virtual const System::UInt32& LevelCount() const override;

            /**
             * Gets the texture width, in pixels
             */
            const System::UInt32& Width() const;

            /**
             * Sets mipmap data to the texture.
             * @param level the mipmap level.
             * @param size the size of the mipmap data.
             * @param data pointer with the mipmap data.
             */
            void SetData(const System::UInt32& level, const System::Size& size, const void* data);

        public:
            /**
             * Activates the texture object
             */
            virtual void Activate() override;

            /**
             * Deactivates the texture object
             */
            virtual void Deactivate() override;

        private:
            void DeclareStorage(const System::UInt32& mipMapLevels);

        private:
            SurfaceFormat   format;
            System::UInt32  height;
            System::Boolean mipmap;
            System::UInt32  mipmapLevels;
            System::UInt32  mipmapHeight;
            System::UInt32  mipmapWidth;
            System::UInt32  width;
            TextureObject   object;

            friend class SceneR::Content::Texture2DReader;
        };
    }
}

#endif  /* TEXTURE2D_HPP */
