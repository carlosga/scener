// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

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
             * @param m
             */
            ContentLoadException(const std::string m = "Content Load Exception")
                : msg(m)
            {
            };

            /**
             * ContentLoadException destructor
             */
            ~ContentLoadException() throw ()
            {
            };

        public:
            /**
             * Gets the message that describes the error.
             * @return  the message describing the error.
             */
            const char* what() const throw ()
            {
                return this->msg.c_str();
            };

        private:
            std::string msg;
        };
    }
}

#endif  /* CONTENTLOADEXCEPTION_HPP */
