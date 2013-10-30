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

#ifndef UNICODE_HPP
#define UNICODE_HPP

#include <System/Core.hpp>
#include <iostream>
#include <locale>
#include <string>

namespace System
{
    namespace Text
    {
        /**
         * Unicode helper class
         */
        class Unicode
        {
        public:
            /**
             * Converts a wide string to a regular string.
             */
            static String Narrow(const std::wstring& source)
            {
                String narrowed(source.begin(), source.end());

                return narrowed;
            };

        private:
            Unicode() = default;
        };
    }
}


#endif /* UNICODE_HPP */
