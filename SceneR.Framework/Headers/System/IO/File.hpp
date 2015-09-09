// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SYSTEM_IO_FILE_HPP
#define SYSTEM_IO_FILE_HPP

#include <fstream>
#include <string>

#include <cassert>

#include <System/IO/BinaryReader.hpp>
#include <System/IO/FileStream.hpp>
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
            static std::u16string read_all_text(const std::u16string&         path
                                              , const System::Text::Encoding& encoding = System::Text::Encoding::utf8)
            {
                auto buffer = read_all_bytes(path);

                return encoding.get_string(buffer, 0, buffer.size());
            }

            /**
             * Opens a binary file, reads the contents of the file into a byte array, and then closes the file.
             */
            static std::vector<std::uint8_t> read_all_bytes(const std::u16string& path)
            {
                assert(exists(path));

                System::IO::FileStream   stream(path);
                System::IO::BinaryReader reader(stream);

                auto buffer = reader.read_bytes(stream.length());

                reader.close();
                stream.close();

                return buffer;
            }

        private:
            File() = delete;
            File(const File& file) = delete;
            File& operator=(const File& file) = delete;
        };
    }
}

#endif  // SYSTEM_IO_FILE_HPP
