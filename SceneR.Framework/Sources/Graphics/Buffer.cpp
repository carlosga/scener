#include <Graphics/Buffer.hpp>

#include <algorithm>
#include <cassert>

namespace SceneR
{
    namespace Graphics
    {
        Buffer::Buffer()
            : _name        { }
            , _uri         { }
            , _byte_length { 0 }
            , _data        (0)
        {
        }

        Buffer::~Buffer()
        {
        }

        const std::string& Buffer::name() const
        {
            return _name;
        }

        const std::string& Buffer::uri() const
        {
            return _uri;
        }

        std::size_t Buffer::byte_length() const
        {
            return _byte_length;
        }

        std::vector<std::uint8_t> Buffer::get_data() const
        {
            return _data;
        }

        void Buffer::get_data(const std::size_t&                  offset
                            , const std::size_t&                  count
                            , std::vector<std::uint8_t>::iterator data) const
        {
            assert(offset < _data.size() && (offset + count) <= _data.size());

            std::copy_n(_data.begin() + offset, count, data);
        }

        void Buffer::set_data(const std::vector<std::uint8_t>& buffer)
        {
            _data.clear();
            _data.resize(buffer.size(), 0);

            _data.assign(buffer.begin(), buffer.end());
        }
    }
}
