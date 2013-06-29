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

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Core/Core.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Graphics/GraphicsResource.hpp"
#include "Graphics/SurfaceFormat.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Represents a texture reference.
         */
        class Texture : public GraphicsResource
        {
            public:
                /**
                 * Releases all resources being used by this texture.
                 */
                virtual ~Texture()
                {
                };

                /**
                 * Gets the format of the texture data.
                 */
                virtual const SurfaceFormat& Format() const = 0;

                /**
                 * Gets the number of texture levels in a multilevel texture.
                 */
                virtual const Int32 LevelCount() const = 0;

            protected:
                Texture(GraphicsDevice& graphicsDevice);
        };
    }
}


#endif  /* TEXTURE_HPP */
