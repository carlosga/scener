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
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class TextureObject
        {
        public:
            TextureObject(const System::UInt32&  width,
                          const System::UInt32&  height,
                          const SurfaceFormat&   format,
                          const TextureTarget&   target);

            virtual ~TextureObject();

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
             * Defines the texture storage parameters.
             */
            void DeclareStorage(const SurfaceFormat& format,
                               const System::UInt32& mipMapLevels,
                               const System::UInt32& width,
                               const System::UInt32& height) const;

            void TextureSubImage2D(const SurfaceFormat&  format,
                                   const System::UInt32& mipMapLevel,
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
