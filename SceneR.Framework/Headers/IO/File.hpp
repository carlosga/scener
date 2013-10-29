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

#ifndef FILE_HPP
#define FILE_HPP

#include <Framework/Core.hpp>
#include <fstream>
#include <sstream>
#include <string>

namespace SceneR
{
    namespace IO
    {
        /**
         * Provides static methods for file access handling.
         */
        class File
        {
        public:
            /**
             * Opens a text file, reads all lines of the file, and then closes the file.
             */
            static std::wstring ReadAllText(const String& filePath)
            {
                std::wifstream stream(filePath, std::ios::in | std::ios::binary);

                if (!stream.is_open())
                {
                    throw std::runtime_error(String("Failed to open file: ") + filePath);
                }

                stream.seekg(0, std::ios_base::beg);
                std::wstringstream buffer;

                buffer << stream.rdbuf();

                stream.close();

                return buffer.str();
            };

        private:
            File() = default;
        };
    }
}

#endif  /* FILE_HPP */
