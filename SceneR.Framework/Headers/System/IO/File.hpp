// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <sstream>
#include <string>

#include <cassert>

#include <System/Text/Encoding.hpp>

namespace System
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
             * Checks whether the given file exists.
             */
            static bool exists(const std::u16string& path)
            {
                auto result = true;
                auto file   = std::fstream(System::Text::Encoding::convert(path), std::ios::in);

                if (!file || !file.good())
                {
                    result = false;
                }
                else
                {
                    file.close();
                }

                return result;
            }

            /**
             * Opens a text file, reads all lines of the file, and then closes the file.
             */
            static std::u16string read_all_text(const std::u16string& path)
            {
                auto stream = std::wifstream(System::Text::Encoding::convert(path), std::ios::in | std::ios::binary);

                assert(stream.is_open());

                stream.seekg(0, std::ios_base::beg);
                std::wstringstream buffer;

                buffer << stream.rdbuf();

                stream.close();

                auto text = buffer.str();

                return std::u16string(text.begin(), text.end());
            }

        private:
            File() = delete;
            File(const File& file) = delete;
            File& operator=(const File& file) = delete;
        };
    }
}

#endif  /* FILE_HPP */
