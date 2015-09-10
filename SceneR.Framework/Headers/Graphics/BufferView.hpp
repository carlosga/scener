// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_UFFERVIEW_HPP
#define GRAPHICS_UFFERVIEW_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <System/IDisposable.hpp>
#include <Graphics/BufferTarget.hpp>
#include <Graphics/BufferUsage.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Buffer;

        /**
         * Represents an OpenGL buffer object.
         */
        class BufferView : System::IDisposable
        {
        public:
            /**
             * Initializes a new instance of the BufferView class.
             * @param target the buffer target.
             * @param usage the buffer usage.
             */
            BufferView(const BufferTarget& target, const BufferUsage& usage);

            /**
             * Releases all resources being used by this BufferView.
             */
            ~BufferView();

        public:
            void dispose();

        public:
            /**
             * Gets the buffer object target.
             */
            const BufferTarget& target() const;

            /**
             * Gets the buffer object usage.
             */
            const BufferUsage& usage() const;

            std::size_t byte_offset() const;
            std::size_t byte_length() const;

            /**
             * Gets the buffer name.
             * @return the buffer name.
             */
            const std::u16string& name() const;

            /**
             * Gets buffer data from object's data store.
             */
            std::vector<std::uint8_t> get_data() const;

            /**
             * Gets buffer data from object's data store.
             */
            void get_data(const std::size_t&                  offset
                        , const std::size_t&                  count
                        , std::vector<std::uint8_t>::iterator data) const;

        private:
            BufferTarget            _target;
            BufferUsage             _usage;
            std::size_t             _byte_offset;
            std::size_t             _byte_length;
            std::u16string          _name;
            std::shared_ptr<Buffer> _buffer;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif // GRAPHICS_BUFFERVIEW_HPP
