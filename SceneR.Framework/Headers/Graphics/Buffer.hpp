// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include <Graphics/BufferType.hpp>

namespace SceneR
{
    namespace Content
    {
        class BuffersReader;
        class BufferViewsReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Buffer
        {
        public:
            Buffer();
            ~Buffer();

        public:
            const std::string& uri() const;

            std::size_t byte_length() const;

            const BufferType& type() const;

        public:
            /**
             * Gets the buffer data
             */
            std::vector<std::uint8_t> get_data() const;

            /**
             * Gets the buffer data
             */
            std::vector<std::uint8_t> get_data(const std::size_t& offset, const std::size_t& count) const;

            /**
             * Sets the buffer data
             */
            void set_data(const std::vector<std::uint8_t>& buffer);

            /**
             * Sets the buffer data
             */
            void set_data(const std::vector<std::uint8_t>& buffer, const std::size_t& offset, const std::size_t& count);

            /**
             * Sets the buffer data
             */
            void set_data(const void* buffer);

            /**
             * Sets the buffer data
             */
            void set_data(const void* buffer, const std::size_t& offset, const std::size_t& count);

        private:
            std::string _uri;
            std::size_t _byte_length;
            BufferType  _type;

            friend class SceneR::Content::BuffersReader;
            friend class SceneR::Content::BufferViewsReader;
        };
    }
}

#endif // BUFFER_HPP
