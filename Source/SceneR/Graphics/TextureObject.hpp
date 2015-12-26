// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_TEXTUREOBJECT_HPP
#define SCENER_GRAPHICS_TEXTUREOBJECT_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include <Core/IDisposable.hpp>
#include <Graphics/SurfaceFormat.hpp>
#include <Graphics/TextureTarget.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Represents an opengl texture object.
         */
        class TextureObject : SceneR::IDisposable
        {
        public:
            /**
             * Initializes a new instance of the TextureObject class.
             * @param target the texturer target.
             */
            TextureObject(const TextureTarget& target) noexcept;

            /**
             * Releases all resources being used by this TextureObject.
             */
            ~TextureObject() = default;

        public:
            virtual void dispose() override;

        public:
            /**
             * Gets the texture object identifier
             */
            std::uint32_t id() const noexcept;

            /**
             * Binds the texture object.
             */
            void bind() const;

            /**
             * Creates the texture object.
             */
            void create();

            /**
             * Unbinds the texture object.
             */
            void unbind() const;

            /**
             * Declares the texture storage parameters.
             * @param levels texture mimap count
             * @param width texture width
             * @param height texture height
             */
            void declare_2D_storage(const SurfaceFormat& format
                                  , const std::size_t&   levels
                                  , const std::size_t&   width
                                  , const std::size_t&   height) const;

            /**
             * Adds texture data to the texture object
             * @param format mipmap format
             * @param level mipmap level index
             * @param width mipmap width
             * @param height mipmap height
             * @param data mipmap data
             */
            void texture_sub_image_2D(const SurfaceFormat&             format
                                    , const std::size_t&               level
                                    , const std::size_t&               width
                                    , const std::size_t&               height
                                    , const std::vector<std::uint8_t>& data) const;

        private:
            std::uint32_t _id;
            TextureTarget _target;
        };
    }
}

#endif // SCENER_GRAPHICS_TEXTUREOBJECT_HPP
