// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_TEXTURE2D_HPP
#define GRAPHICS_TEXTURE2D_HPP

#include <cstddef>
#include <cstdint>
#include <memory>

#include <Graphics/SurfaceFormat.hpp>
#include <Graphics/TextureObject.hpp>
#include <Graphics/Texture.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
        class GraphicsDevice;
        class SamplerState;

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
            Texture2D(Guide::not_null<GraphicsDevice*> graphicsDevice
                    , const std::size_t&               width
                    , const std::size_t&               height);

            /**
             * Creates a new instance of the Texture2D class.
             *
             * @param graphicsDevice the graphics device
             * @param width the texture width, in pixels
             * @param height the texture height, in pixels
             * @param mipmap true to generate a full mipmap chain; false otherwise.
             * @param format texture data format
             */
            Texture2D(Guide::not_null<GraphicsDevice*> graphicsDevice
                    , const std::size_t&               width
                    , const std::size_t&               height
                    , const bool&                      mipmap
                    , const SurfaceFormat&             format);

            /**
             * Releases all resources being used by this texture.
             */
            ~Texture2D() = default;

        public:
            void dispose() override;

        public:
            std::uint32_t id() const override;

            /**
             * Gets the format of the texture data.
             */
            const SurfaceFormat& format() const override;

            /**
             * Gets the texture height, in pixels
             */
            std::size_t height() const;

            /**
             * Gets the number of texture levels in a multilevel texture.
             */
            std::size_t level_count() const override;

            /**
             * Gets the texture width, in pixels
             */
            std::size_t width() const;

            /**
             * Gets the texure sampler state.
             * @return the texure sampler state.
             */
            std::shared_ptr<SamplerState> sampler_state() const;

            /**
             * Sets mipmap data to the texture.
             * @param level the mipmap level.
             * @param size the size of the mipmap data.
             * @param data pointer with the mipmap data.
             */
            void set_data(const std::size_t& level, const std::size_t& size, const void* data);

            /**
             * Activates the texture object
             */
            void bind() const override;

            /**
             * Deactivates the texture object
             */
            void unbind() const override;

        private:
            void declare_storage(const std::size_t& mipMapLevels);

        private:
            SurfaceFormat                 _format;
            std::size_t                   _height;
            bool                          _mipmap;
            std::size_t                   _mipmap_levels;
            std::size_t                   _mipmap_height;
            std::size_t                   _mipmap_width;
            std::size_t                   _width;
            TextureObject                 _object;
            std::shared_ptr<SamplerState> _sampler_state;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_TEXTURE2D_HPP