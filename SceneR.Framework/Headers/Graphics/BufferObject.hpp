//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef BUFFEROBJECT_HPP
#define BUFFEROBJECT_HPP

#include <Graphics/BufferTarget.hpp>
#include <Graphics/BufferUsage.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
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

            /**
             * Deletes the buffer object.
             */
            void Delete();

            /**
             * Gets a subset of data from a buffer object's data store.
             * @param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
             * @param size specifies the size in bytes of the data store region being replaced.
             * @param data specifies a pointer to the new data that will be copied into the data store.
             */
            void GetData(const System::Size& offset, const System::Size& size, void *data) const;

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
