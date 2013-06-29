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

#ifndef TEXTUREMIPMAP_HPP
#define TEXTUREMIPMAP_HPP

#include <vector>
#include "Content/Readers/Texture2DReader.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Represents a texture mipmap
         */
        class TextureMipMap
        {
        public:
            /**
             * Initializes a new instance of the TextureMipMap class
             */
            TextureMipMap();

            /**
             * Gets the mip map data
             */
            const std::vector<Int16>& Data() const;

        private:
            std::vector<Int16> data;

            friend class SceneR::Content::Texture2DReader;
        };
    }
}


#endif /* TEXTUREMIPMAP_HPP */
