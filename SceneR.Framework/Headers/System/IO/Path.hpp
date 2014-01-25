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

#ifndef PATH_HPP
#define PATH_HPP

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
            };

            /**
             * Returns the directory information for the specified path string.
             * @param path the path of a file or directory.
             */
            static const System::String GetDirectoryName(const System::String& path)
            {
                String::size_type result        = path.find_last_of(Path::DirectorySeparator());
                String            directoryName = path;

                // Does new_filename.erase(std::string::npos) working here in place of this following test?
                if (String::npos != result)
                {
                    directoryName.erase(result);
                }

                return directoryName;
            };

            /**
             * Returns the file name of the specified path string without the extension.
             * @param path The path of the file.
             * @return the file name of the specified path string without the extension.
             */
            static const System::String GetFileNameWithoutExtension(const System::String& path)
            {
                String::size_type result               = path.find_last_of('.');
                String            pathWithoutExtension = path;

                // Does new_filename.erase(std::string::npos) working here in place of this following test?
                if (String::npos != result)
                {
                    pathWithoutExtension.erase(result);
                }

                return pathWithoutExtension;
            };

            /**
             * Combines two strings into a path.
             *
             * @param path1 The first path to combine
             * @param path2 The second path to combine
             */
            static const String Combine(const String& path1, const String& path2)
            {
                return String(path1 + DirectorySeparator() + path2);
            };

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
            };

        private:
            Path() = delete;
			Path(const Path& path) = delete;
			Path& operator=(const Path& path) = delete;
        };
    }
}

#endif // PATH_HPP
