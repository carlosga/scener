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

#ifndef CONTENTLOADEXCEPTION_HPP
#define CONTENTLOADEXCEPTION_HPP

#include <stdexcept>
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
                return msg.c_str();
            };

        private:
            std::string msg;
        };
    }
}

#endif  /* CONTENTLOADEXCEPTION_HPP */
