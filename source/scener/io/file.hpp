// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_IO_FILE_HPP
#define SCENER_IO_FILE_HPP

#include <gsl/assert>

#include "scener/io/binary_reader.hpp"
#include "scener/io/file_stream.hpp"

namespace scener::io
{
    /// Provides static methods for file access handling.
    class file final
    {
    public:
        /// Checks whether the given file exists.
        /// \param path the file to check.
        /// \returns true of the given file exists; false otherwise.
        static bool exists(const std::string& path) noexcept
        {
            auto result = true;
            auto file   = std::fstream(path, std::ios::in);

            if (!file || !file.good())
            {
                result = false;
            }

            return result;
        }

        /// Opens a text file, reads all lines of the file, and then closes the file.
        /// \param path the file to open for reading.
        /// \returns a string containing all lines of the file.
        static std::string read_all_text(const std::string& path) noexcept
        {
            auto buffer = read_all_bytes(path);

            return std::string(buffer.begin(), buffer.end());
        }

        /// Opens a binary file, reads the contents of the file into a byte array, and then closes the file.
        /// \param path the file to open for reading.
        /// \returns the contents of the file.
        static std::vector<std::uint8_t> read_all_bytes(const std::string& path) noexcept
        {
            Expects(exists(path));

            file_stream   stream(path);
            binary_reader reader(stream);

            return reader.read_bytes(stream.length());
        }

    private:
        file() = delete;
        file(const file& file) = delete;
        file& operator=(const file& file) = delete;
    };
}

#endif // SCENER_IO_FILE_HPP
