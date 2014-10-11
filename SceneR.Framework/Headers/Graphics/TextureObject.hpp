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

#ifndef TEXTUREOBJECT_HPP
#define TEXTUREOBJECT_HPP

#include <Graphics/SurfaceFormat.hpp>
#include <Graphics/TextureTarget.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Represents an opengl texture object.
         */
        class TextureObject
        {
        public:
            /**
             * Initializes a new instance of the TextureObject class.
             * @param target the texturer target.
             */
            TextureObject(const TextureTarget& target);

            /**
             * Releases all resources being used by this TextureObject.
             */
            ~TextureObject();

        public:
            /**
             * Activates the texture object.
             */
            void Activate() const;

            /**
             * Creates the texture object.
             */
            void Create();

            /**
             * Deactivates the texture object.
             */
            void Deactivate() const;

            /*
             * Deletes the texture objects.
             */
            void Delete();

            /**
             * Declares the texture storage parameters.
             * @param levels texture mimap count
             * @param width texture width
             * @param height texture height
             */
            void Declare2DStorage(const SurfaceFormat&  format
                                , const System::UInt32& levels
                                , const System::UInt32& width
                                , const System::UInt32& height) const;

            /**
             * Adds texture data to the texture object
             * @param format mipmap format
             * @param level mipmap level index
             * @param width mipmap width
             * @param height mipmap height
             * @param size mipmap data size
             * @param data mipmap data
             */
            void TextureSubImage2D(const SurfaceFormat&  format,
                                   const System::UInt32& level,
                                   const System::UInt32& width,
                                   const System::UInt32& height,
                                   const System::Size&   size,
                                   const void*           data) const;

        private:
            System::UInt32 texId;
            TextureTarget  target;
        };
    }
}

#endif /* TEXTUREOBJECT_HPP */
