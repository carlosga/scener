/*
 * BufferObject.hpp
 *
 *  Created on: Dec 16, 2013
 *      Author: carlos
 */

#ifndef BUFFEROBJECT_HPP
#define BUFFEROBJECT_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        enum class BufferTarget : System::UInt32;
        enum class BufferUsage  : System::UInt32;

        /**
         * Represents an OpenGL buffer object.
         */
        class BufferObject
        {
        public:
            /**
             * Initializes a new instance of the BufferObject class.
             * @param target the buffer target.
             * @param usage the buffer usage.
             */
            BufferObject(const BufferTarget& target, const BufferUsage& usage);

            /**
             * Releases all resources being used by this BufferObject.
             */
            virtual ~BufferObject();

        public:
            /**
             * Gets the buffer object identifier.
             */
            const System::UInt32& Id() const;

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

            /*
             * Deletes the buffer objects.
             */
            void Delete();

            /**
             * Creates and initializes the buffer object data store.
             * @param size specifies the size in bytes of the buffer object's new data store.
             * @param data specifies a pointer to data that will be copied into the data store for initialization,
             *             or NULL if no data is to be copied.
             */
            void BufferData(const System::Size& size, const void* data) const;

            /**
             * Updates a subset of a buffer object's data store
             * @param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
             * @param size specifies the size in bytes of the data store region being replaced.
             * @param data specifies a pointer to the new data that will be copied into the data store.
             */
            void BufferData(const System::Size& offset, const System::Size& size, const void *data) const;

            /**
             * Invalidate the content of a buffer object's data store
             */
            void Invalidate() const;

            /**
             *  Invalidate a region of a buffer object's data store
             *  @param offset the offset within the buffer's data store of the start of the range to be invalidated.
             *  @param length the length of the range within the buffer's data store to be invalidated.
             */
            void Invalidate(const System::Size& offset, const System::Size& length) const;

        private:
            /**
             * Creates the buffer object.
             */
            void Create();

        private:
            System::UInt32 id;
            BufferTarget   target;
            BufferUsage    usage;
        };
    }
}

#endif /* BUFFEROBJECT_HPP */
