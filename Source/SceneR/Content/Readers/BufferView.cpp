// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "BufferView.hpp"

namespace SceneR
{
    namespace Content
    {
        std::size_t BufferView::byte_offset() const noexcept
        {
            return _byte_offset;
        }

        std::size_t BufferView::byte_length() const noexcept
        {
            return _byte_length;
        }

        const std::string& BufferView::name() const noexcept
        {
            return _name;
        }

        const gsl::span<std::uint8_t> BufferView::get_data() const
        {
            return get_data(0, _byte_length);
        }

        const gsl::span<std::uint8_t> BufferView::get_data(const std::size_t& offset
                                                         , const std::size_t& count) const
        {
            return _buffer->get_data(_byte_offset + offset, count);
        }
    }
}
