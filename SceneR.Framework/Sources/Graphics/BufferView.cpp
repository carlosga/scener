// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/BufferView.hpp>

#include <vector>

#include <Graphics/Buffer.hpp>

namespace SceneR
{
    namespace Graphics
    {
        BufferView::BufferView(const BufferTarget& target, const BufferUsage& usage)
            : _target      { target }
            , _usage       { usage }
            , _byte_offset { 0 }
            , _byte_length { 0 }
            , _name        { }
            , _buffer      { nullptr }
        {
        }

        BufferView::~BufferView()
        {
        }

        void BufferView::dispose()
        {
        }

        const BufferTarget& BufferView::target() const
        {
            return _target;
        }

        const BufferUsage& BufferView::usage() const
        {
            return _usage;
        }

        std::size_t BufferView::byte_offset() const
        {
            return _byte_offset;
        }

        std::size_t BufferView::byte_length() const
        {
            return _byte_length;
        }

        const std::u16string& BufferView::name() const
        {
            return _name;
        }

        std::vector<std::uint8_t> BufferView::get_data() const
        {
            std::vector<std::uint8_t> data(_byte_length, 0);

            get_data(0, _byte_length, data.begin());

            return data;
        }

        void BufferView::get_data(const std::size_t&                  offset
                                , const std::size_t&                  count
                                , std::vector<std::uint8_t>::iterator data) const
        {
            return _buffer->get_data(_byte_offset + offset, count, data);
        }
    }
}
