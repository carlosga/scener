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

#include <vector>
#include "Content/Readers/Texture2DReader.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/SurfaceFormat.hpp"
#include "Graphics/TextureMipMap.hpp"

namespace SceneR
{
    namespace Graphics
    {
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
                      const Int32&    width,
                      const Int32&    height);

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
                      const Int32&         width,
                      const Int32&         height,
                      const Boolean&       mipMap,
                      const SurfaceFormat& format);

        public:
            /**
             * Gets the format of the texture data.
             */
            virtual const SurfaceFormat& Format() const override;

            /**
             * Gets the texture height, in pixels
             */
            const Int32& Height() const;

            /**
             * Gets the number of texture levels in a multilevel texture.
             */
            virtual const Int32 LevelCount() const override;

            /**
             * Gets the texture width, in pixels
             */
            const Int32& Width() const;

        private:
            SurfaceFormat              format;
            Int32                      height;
            std::vector<TextureMipMap> mipmaps;
            Int32                      width;

            friend class SceneR::Content::Texture2DReader;
        };
    }
}

#endif  /* TEXTURE2D_HPP */
