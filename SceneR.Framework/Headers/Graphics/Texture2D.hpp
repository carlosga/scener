//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <Framework/Core.hpp>
#include <Graphics/SurfaceFormat.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/TextureMipMap.hpp>
#include <memory>
#include <vector>

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
                      const UInt32&   width,
                      const UInt32&   height);

            /**
             * Creates a new instance of the Texture2D class.
             *
             * @param graphicsDevice the graphics device
             * @param width the texture width, in pixels
             * @param height the texture height, in pixels
             * @param mipMap true to generate a full mipmap chain; false otherwise.
             * @param format texture data format
             */
            Texture2D(GraphicsDevice&      graphicsDevice,
                      const UInt32&        width,
                      const UInt32&        height,
                      const Boolean&       mipMap,
                      const SurfaceFormat& format);

            /**
             * Releases all resources being used by this texture.
             */
            ~Texture2D();

        public:
            /**
             * Gets the format of the texture data.
             */
            virtual const SurfaceFormat& Format() const override;

            /**
             * Gets the texture height, in pixels
             */
            const UInt32& Height() const;

            /**
             * Gets the number of texture levels in a multilevel texture.
             */
            virtual const Int32 LevelCount() const override;

            /**
             * Gets the texture width, in pixels
             */
            const UInt32& Width() const;

        private:
            SurfaceFormat              format;
            UInt32                     height;
            std::vector<TextureMipMap> mipmaps;
            UInt32                     width;

            friend class SceneR::Content::Texture2DReader;
        };
    }
}

#endif  /* TEXTURE2D_HPP */
