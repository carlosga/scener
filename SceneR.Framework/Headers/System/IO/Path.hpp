// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SYSTEM_IO_PATH_HPP
#define SYSTEM_IO_PATH_HPP

#include <algorithm>

#include <string>

namespace System
{
    namespace IO
    {
        /**
         * Utility class for path operations.
         */
        class Path
        {
        public:
            /**
             * Changes the extension of a path string.
             * @param path The path of the file.
             * @param extension The new file extension
             * @return The file path with the new extension
             */
            static const std::u16string change_extension(const std::u16string& path
                                                       , const std::u16string& extension)
            {
                return get_file_name_without_extension(path) + u"." + extension;
            }

            /**
             * Returns the directory information for the specified path string.
             * @param path the path of a file or directory.
             */
            static const std::u16string get_directory_name(const std::u16string& path)
            {
                auto result        = path.find_last_of(Path::directory_separator());
                auto directoryName = path;

                // Does new_filename.erase(std::string::npos) working here in place of this following test?
                if (std::u16string::npos != result)
                {
                    directoryName.erase(result);
                }

                return directoryName;
            }

            /**
             * Returns the file name of the specified path string without the extension.
             * @param path The path of the file.
             * @return the file name of the specified path string without the extension.
             */
            static const std::u16string get_file_name_without_extension(const std::u16string& path)
            {
                auto result               = path.find_last_of('.');
                auto pathWithoutExtension = path;

                // Does new_filename.erase(std::string::npos) working here in place of this following test?
                if (std::u16string::npos != result)
                {
                    pathWithoutExtension.erase(result);
                }

                return pathWithoutExtension;
            }

            /**
             * Combines two strings into a path.
             *
             * @param path1 The first path to combine
             * @param path2 The second path to combine
             */
            static const std::u16string combine(const std::u16string& path1, const std::u16string& path2)
            {
                std::u16string separator = u"";
                std::u16string cpath1    = path1;
                std::u16string cpath2    = path2;

#if __unix__
                if (!cpath1.empty())
                {
                    std::replace(cpath1.begin(), cpath1.end(), u'\\', Path::directory_separator()[0]);
                }
                if (!cpath2.empty())
                {
                    std::replace(cpath2.begin(), cpath2.end(), u'\\', Path::directory_separator()[0]);
                }
#endif

                if (!cpath1.empty() && cpath1.back() != Path::directory_separator()[0])
                {
                    separator = Path::directory_separator();
                }

                return std::u16string(cpath1 + separator + cpath2);
            }

            /**
             * Gets platform specific string with the directory separator.
             */
            static const std::u16string directory_separator()
            {
#if __unix__
                return u"/";
#else
                return u"\\";
#endif
            }

        private:
            Path() = delete;
            Path(const Path& path) = delete;
            Path& operator=(const Path& path) = delete;
        };
    }
}

#endif  // SYSTEM_IO_PATH_HPP
