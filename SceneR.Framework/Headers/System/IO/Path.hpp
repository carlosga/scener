// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PATH_HPP
#define PATH_HPP

#include <algorithm>

#include <System/Core.hpp>

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
            static const System::String ChangeExtension(const System::String& path
                                                      , const System::String& extension)
            {
                return GetFileNameWithoutExtension(path) + u"." + extension;
            }

            /**
             * Returns the directory information for the specified path string.
             * @param path the path of a file or directory.
             */
            static const System::String GetDirectoryName(const System::String& path)
            {
                auto result        = path.find_last_of(Path::DirectorySeparator());
                auto directoryName = path;

                // Does new_filename.erase(std::string::npos) working here in place of this following test?
                if (String::npos != result)
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
            static const System::String GetFileNameWithoutExtension(const System::String& path)
            {
                auto result               = path.find_last_of('.');
                auto pathWithoutExtension = path;

                // Does new_filename.erase(std::string::npos) working here in place of this following test?
                if (String::npos != result)
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
            static const String Combine(const String& path1, const String& path2)
            {
                String separator = u"";
                String cpath1    = path1;
                String cpath2    = path2;

#if __unix__
                if (!cpath1.empty())
                {
                    std::replace(cpath1.begin(), cpath1.end(), u'\\', Path::DirectorySeparator()[0]);
                }
                if (!cpath2.empty())
                {
                    std::replace(cpath2.begin(), cpath2.end(), u'\\', Path::DirectorySeparator()[0]);
                }
#endif

                if (!cpath1.empty() && cpath1.back() != DirectorySeparator()[0])
                {
                    separator = DirectorySeparator();
                }

                return String(cpath1 + separator + cpath2);
            }

            /**
             * Gets platform specific string with the directory separator.
             */
            static const String DirectorySeparator()
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

#endif // PATH_HPP
