// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BUFFERVIEW_HPP
#define BUFFERVIEW_HPP

#include <cstddef>
#include <cstdint>
#include <memory>

#include <System/IDisposable.hpp>
#include <Graphics/BufferTarget.hpp>
#include <Graphics/BufferUsage.hpp>

namespace SceneR
{
    namespace Content
    {
        class AccessorsReader;
        class BufferViewsReader;
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
             * Gets the buffer object identifier.
             */
            std::uint32_t id() const;

            /**
             * Gets the buffer object target.
             */
            const BufferTarget& target() const;

            /**
             * Gets the buffer object usage.
             */
            const BufferUsage& usage() const;

            /**
             * Activates the buffer object.
             */
            void activate() const;

            /**
             * Creates the buffer object.
             */
            void create();

            /**
             * Deactivates the buffer object.
             */
            void deactivate() const;

            /**
             * Gets buffer data from object's data store.
             * @param data specifies a pointer to the new data that will be copied into the data store.
             */
            void get_data(void* data) const;

            /**
             * Gets a subset of data from a buffer object's data store.
             * @param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
             * @param count specifies the size in bytes of the data store region being replaced.
             * @param data specifies a pointer to the new data that will be copied into the data store.
             */
            void get_data(const std::size_t& offset, const std::size_t& count, void *data) const;

            /**
             * Creates and initializes the buffer object data store.
             * @param count specifies the size in bytes of the buffer object's new data store.
             * @param data specifies a pointer to data that will be copied into the data store for initialization,
             *             or NULL if no data is to be copied.
             */
            void set_data(const std::size_t& count, const void* data) const;

            /**
             * Updates a subset of a buffer object's data store
             * @param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
             * @param count specifies the size in bytes of the data store region being replaced.
             * @param data specifies a pointer to the new data that will be copied into the data store.
             */
            void set_data(const std::size_t& offset, const std::size_t& count, const void *data) const;

            /**
             * Invalidate the content_manager of a buffer object's data store
             */
            void invalidate() const;

            /**
             *  Invalidate a region of a buffer object's data store
             *  @param offset the offset within the buffer's data store of the start of the range to be invalidated.
             *  @param length the length of the range within the buffer's data store to be invalidated.
             */
            void invalidate(const std::size_t& offset, const std::size_t& length) const;

        private:
            std::uint32_t _id;
            BufferTarget  _target;
            BufferUsage   _usage;
            std::size_t   _byte_offset;
            std::size_t   _byte_length;

            friend class SceneR::Content::AccessorsReader;
            friend class SceneR::Content::BufferViewsReader;
        };
    }
}

#endif /* BUFFERVIEW_HPP */
