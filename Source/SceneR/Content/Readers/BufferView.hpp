// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_BUFFERVIEW_HPP
#define SCENER_CONTENT_READERS_BUFFERVIEW_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <gsl.h>

#include "Buffer.hpp"

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;

        /**
         * GLTF. A view into a buffer.
         */
        class BufferView final
        {
        public:
            /**
             * Initializes a new instance of the BufferView class.
             */
            BufferView() noexcept = default;

            /**
             * Releases all resources being used by this BufferView.
             */
            ~BufferView() = default;

        public:
            /**
             * Gets the offset into the buffer in bytes.
             */
            std::size_t byte_offset() const noexcept;

            /**
             * Gets the length of the buffer-view in bytes.
             */
            std::size_t byte_length() const noexcept;

            /**
             * Gets the buffer name.
             * @return the buffer name.
             */
            const std::string& name() const noexcept;

            /**
             * Gets buffer data from object's data store.
             */
            const gsl::span<std::uint8_t> get_data() const;

            /**
             * Gets buffer data from object's data store.
             */
            const gsl::span<std::uint8_t> get_data(const std::size_t& offset, const std::size_t& count) const;

        private:
            std::shared_ptr<Buffer> _buffer      { nullptr };
            std::size_t             _byte_offset { 0 };
            std::size_t             _byte_length { 0 };
            std::string             _name        { };

            template <typename T> friend class ContentTypeReader;
        };
    }
}

#endif // SCENER_CONTENT_READERS_BUFFERVIEW_HPP
