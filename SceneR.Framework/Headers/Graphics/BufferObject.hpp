/*
 * BufferObject.hpp
 *
 *  Created on: Dec 16, 2013
 *      Author: carlos
 */

#ifndef BUFFEROBJECT_HPP
#define BUFFEROBJECT_HPP

#include <GL/glew.h>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        enum class BufferTarget : System::UInt32;
        enum class BufferUsage : System::UInt32;

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
             */
            void BufferData(const System::Size& size, const GLvoid* data);

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
