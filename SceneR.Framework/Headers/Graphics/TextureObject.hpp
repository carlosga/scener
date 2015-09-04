// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTUREOBJECT_HPP
#define TEXTUREOBJECT_HPP

#include <cstddef>
#include <cstdint>

#include <System/IDisposable.hpp>
#include <Graphics/SurfaceFormat.hpp>
#include <Graphics/TextureTarget.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Represents an opengl texture object.
         */
        class TextureObject : System::IDisposable
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
            void dispose() override;

        public:
            /**
             * Gets the texture object identifier
             */
            std::uint32_t Id() const;

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

            /**
             * Declares the texture storage parameters.
             * @param levels texture mimap count
             * @param width texture width
             * @param height texture height
             */
            void Declare2DStorage(const SurfaceFormat& format
                                , const std::size_t&   levels
                                , const std::size_t&   width
                                , const std::size_t&   height) const;

            /**
             * Adds texture data to the texture object
             * @param format mipmap format
             * @param level mipmap level index
             * @param width mipmap width
             * @param height mipmap height
             * @param size mipmap data size
             * @param data mipmap data
             */
            void TextureSubImage2D(const SurfaceFormat& format
                                 , const std::size_t&   level
                                 , const std::size_t&   width
                                 , const std::size_t&   height
                                 , const std::size_t&   size
                                 , const void*          data) const;

        private:
            std::uint32_t id;
            TextureTarget target;
        };
    }
}

#endif /* TEXTUREOBJECT_HPP */
