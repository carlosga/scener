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
            void Dispose();

        public:
            /**
             * Gets the buffer object identifier.
             */
            std::uint32_t Id() const;

            /**
             * Gets the buffer object target.
             */
            const BufferTarget& Target() const;

            /**
             * Gets the buffer object usage.
             */
            const BufferUsage& Usage() const;

            /**
             * Activates the buffer object.
             */
            void Activate() const;

            /**
             * Deactivates the buffer object.
             */
            void Deactivate() const;

            /**
             * Gets a subset of data from a buffer object's data store.
             * @param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
             * @param size specifies the size in bytes of the data store region being replaced.
             * @param data specifies a pointer to the new data that will be copied into the data store.
             */
            void GetData(const std::size_t& offset, const std::size_t& size, void *data) const;

            /**
             * Creates and initializes the buffer object data store.
             * @param size specifies the size in bytes of the buffer object's new data store.
             * @param data specifies a pointer to data that will be copied into the data store for initialization,
             *             or NULL if no data is to be copied.
             */
            void BufferData(const std::size_t& size, const void* data) const;

            /**
             * Updates a subset of a buffer object's data store
             * @param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
             * @param size specifies the size in bytes of the data store region being replaced.
             * @param data specifies a pointer to the new data that will be copied into the data store.
             */
            void BufferData(const std::size_t& offset, const std::size_t& size, const void *data) const;

            /**
             * Invalidate the content of a buffer object's data store
             */
            void Invalidate() const;

            /**
             *  Invalidate a region of a buffer object's data store
             *  @param offset the offset within the buffer's data store of the start of the range to be invalidated.
             *  @param length the length of the range within the buffer's data store to be invalidated.
             */
            void Invalidate(const std::size_t& offset, const std::size_t& length) const;

        private:
            /**
             * Creates the buffer object.
             */
            void Create();

        private:
            std::uint32_t           id;
            BufferTarget            target;
            BufferUsage             usage;
            std::shared_ptr<Buffer> buffer;
            std::uint64_t           byteOffset;
            std::uint64_t           byteLength;

            friend class SceneR::Content::AccessorsReader;
            friend class SceneR::Content::BufferViewsReader;
        };
    }
}

#endif /* BUFFERVIEW_HPP */
