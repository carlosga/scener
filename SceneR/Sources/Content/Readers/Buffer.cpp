// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers//Buffer.hpp>

namespace SceneR
{
    namespace Content
    {
        const std::string& Buffer::name() const noexcept
        {
            return _name;
        }

        const std::string& Buffer::uri() const noexcept
        {
            return _uri;
        }

        std::size_t Buffer::byte_length() const noexcept
        {
            return _byte_length;
        }

        const gsl::span<std::uint8_t> Buffer::get_data(const std::size_t& offset, const std::size_t& count)
        {
            Expects(offset < _data.size() && (offset + count) <= _data.size());

            return gsl::as_span(_data.data() + offset, count);
        }

        void Buffer::set_data(const std::vector<std::uint8_t>& buffer)
        {
            _data = std::move(buffer);
        }
    }
}
