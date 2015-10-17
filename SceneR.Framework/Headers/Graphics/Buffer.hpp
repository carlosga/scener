// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_BUFFER_HPP
#define GRAPHICS_BUFFER_HPP

#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>

#include <gsl.h>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
        /**
         * GLTF. Buffers contain geometry, animation, or skins.
         */
        class Buffer final
        {
        public:
            /**
             * Initializes a new instance of the Buffer class.
             */
            Buffer() = default;

            /**
             * Destructor.
             */
            ~Buffer() = default;

        public:
            /**
             * Gets the buffer name.
             */
            const std::string& name() const noexcept;

            /**
             * Gets the buffer uri.
             */
            const std::string& uri() const noexcept;

            /**
             * Gets the buffer uri.
             */
            std::size_t byte_length() const noexcept;

            /**
             * Gets the buffer data.
             */
            const gsl::array_view<std::uint8_t> get_data(const std::size_t& offset, const std::size_t& count);

            /**
             * Sets the buffer data.
             */
            void set_data(const std::vector<std::uint8_t>& buffer);

        private:
            std::string               _name        { };
            std::string               _uri         { };
            std::size_t               _byte_length { 0 };
            std::vector<std::uint8_t> _data;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif // GRAPHICS_BUFFER_HPP
