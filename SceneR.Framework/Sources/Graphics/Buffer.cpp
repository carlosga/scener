#include <Graphics/Buffer.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Graphics::BufferType;

        Buffer::Buffer()
            : _name        { }
            , _uri         { }
            , _byte_length { 0 }
            , _type        { BufferType::ArrayBuffer }
        {
        }

        Buffer::~Buffer()
        {
        }

        const std::u16string Buffer::name() const
        {
            return _name;
        }

        const std::u16string& Buffer::uri() const
        {
            return _uri;
        }

        std::size_t Buffer::byte_length() const
        {
            return _byte_length;
        }

        const BufferType& Buffer::type() const
        {
            return _type;
        }

        std::vector<std::uint8_t> Buffer::get_data() const
        {
            return std::vector<uint8_t>();
        }

        std::vector<std::uint8_t> Buffer::get_data(const std::size_t& offset, const std::size_t& count) const
        {
            return std::vector<uint8_t>();
        }

        void Buffer::set_data(const std::vector<std::uint8_t>& buffer)
        {
        }

        void Buffer::set_data(const std::vector<std::uint8_t>& buffer
                            , const std::size_t&               offset
                            , const std::size_t&               count)
        {
        }

        void Buffer::set_data(const void* buffer)
        {
        }

        void Buffer::set_data(const void* buffer, const std::size_t& offset, const std::size_t& count)
        {
        }
    }
}
