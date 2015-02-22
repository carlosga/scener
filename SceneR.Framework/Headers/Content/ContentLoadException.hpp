// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTLOADEXCEPTION_HPP
#define CONTENTLOADEXCEPTION_HPP

#include <string>

namespace SceneR
{
    namespace Content
    {
        /**
         * Exception used to report errors from the ContentManager.Load method.
         */
        class ContentLoadException : std::exception
        {
        public:
            /**
             * Initializes a new instance of the ContentLoadException class with the given message
             * @param m the exception message
             */
            ContentLoadException(const std::string m = "Content Load Exception")
                : msg(m)
            {
            }

        public:
            /**
             * Gets the message that describes the error.
             * @return  the message describing the error.
             */
            const char* what() const noexcept
            {
                return this->msg.c_str();
            }

        private:
            std::string msg;
        };
    }
}

#endif  /* CONTENTLOADEXCEPTION_HPP */
