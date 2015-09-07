#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>

#include <Graphics/BufferType.hpp>

namespace SceneR
{
    namespace Content
    {
        class BuffersReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Buffer final
        {
        public:
            Buffer();
            ~Buffer();

        public:
            /**
             * Gets the buffer name.
             */
            const std::u16string& name() const;

            /**
             * Gets the buffer uri.
             */
            const std::u16string& uri() const;

            /**
             * Gets the buffer uri.
             */
            std::size_t byte_length() const;

            /**
             * Gets the buffer uri.
             */
            SceneR::Graphics::BufferType type() const;

            /**
             * Gets the buffer data
             */
            std::vector<std::uint8_t> get_data() const;

            /**
             * Gets the buffer data
             */
            void get_data(const std::size_t&                  offset
                        , const std::size_t&                  count
                        , std::vector<std::uint8_t>::iterator data) const;

            /**
             * Sets the buffer data
             */
            void set_data(const std::vector<std::uint8_t>& buffer);

        private:
            std::u16string            _name;
            std::u16string            _uri;
            std::size_t               _byte_length;
            BufferType                _type;
            std::vector<std::uint8_t> _data;

            friend class SceneR::Content::BuffersReader;
        };
    }
}

#endif // BUFFER_HPP
