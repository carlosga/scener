// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_BUFFEROBJECT_HPP
#define SCENER_GRAPHICS_BUFFEROBJECT_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include "SceneR/Core/IDisposable.hpp"
#include "SceneR/Graphics/BufferTarget.hpp"
#include "SceneR/Graphics/BufferUsage.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Represents an OpenGL buffer object.
         */
        class BufferObject : SceneR::IDisposable
        {
        public:
            /**
             * Initializes a new instance of the BufferObject class.
             * @param target the buffer target.
             * @param usage the buffer usage.
             */
            BufferObject(const BufferTarget& target, const BufferUsage& usage) noexcept;

            /**
             * Releases all resources being used by this BufferObject.
             */
            virtual ~BufferObject() override = default;

        public:
            virtual void dispose() override;

        public:
            /**
             * Gets the buffer object identifier.
             */
            std::uint32_t id() const noexcept;

            /**
             * Gets the buffer object target.
             */
            const BufferTarget& target() const noexcept;

            /**
             * Gets the buffer object usage.
             */
            const BufferUsage& usage() const noexcept;

            /**
             * Activates the buffer object.
             */
            void bind() const;

            /**
             * Creates the buffer object.
             */
            void create();

            /**
             * Deactivates the buffer object.
             */
            void unbind() const;

            /**
             * Gets a subset of data from a buffer object's data store.
             * @param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
             * @param size specifies the size in bytes of the data store region being replaced.
             * @param data specifies a pointer to the new data that will be copied into the data store.
             */
            std::vector<std::uint8_t> get_data(const std::size_t& offset, const std::size_t& size) const;

            /**
             * Creates and initializes the buffer object data store.
             * @param size specifies the size in bytes of the buffer object's new data store.
             * @param data specifies a pointer to data that will be copied into the data store for initialization,
             *             or NULL if no data is to be copied.
             */
            void set_data(const std::size_t& size, const void* data) const;

            /**
             * Updates a subset of a buffer object's data store
             * @param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
             * @param size specifies the size in bytes of the data store region being replaced.
             * @param data specifies a pointer to the new data that will be copied into the data store.
             */
            void set_data(const std::size_t& offset, const std::size_t& size, const void* data) const;

            /**
             * Invalidate the content of a buffer object's data store
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
        };
    }
}

#endif // SCENER_GRAPHICS_BUFFEROBJECT_HPP
