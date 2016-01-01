// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_IO_PATH_HPP
#define SCENER_IO_PATH_HPP

#include <algorithm>
#include <string>

namespace SceneR { namespace IO {

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
    static std::string change_extension(const std::string& path, const std::string& extension)
    {
        return get_file_name_without_extension(path) + "." + extension;
    }

    /**
     * Returns the directory information for the specified path string.
     * @param path the path of a file or directory.
     */
    static std::string get_directory_name(const std::string& path)
    {
        auto position      = path.find_last_of(Path::directory_separator());
        auto directoryName = path;

        if (position != std::string::npos)
        {
            directoryName.erase(position);
        }

        return directoryName;
    }

    /**
     * Returns the file name of the specified path string without the extension.
     * @param path The path of the file.
     * @return the file name of the specified path string without the extension.
     */
    static std::string get_file_name_without_extension(const std::string& path)
    {
        auto position             = path.find_last_of('.');
        auto pathWithoutExtension = path;

        if (position != std::string::npos)
        {
            pathWithoutExtension.erase(position);
        }

        return pathWithoutExtension;
    }

    /**
     * Combines two strings into a path.
     *
     * @param path1 The first path to combine
     * @param path2 The second path to combine
     */
    static std::string combine(const std::string& path1, const std::string& path2)
    {
        std::string separator { };
        std::string cpath1    { path1 };
        std::string cpath2    { path2 };

#if __unix__
        if (!cpath1.empty())
        {
            std::replace(cpath1.begin(), cpath1.end(), '\\', Path::directory_separator());
        }
        if (!cpath2.empty())
        {
            std::replace(cpath2.begin(), cpath2.end(), '\\', Path::directory_separator());
        }
#endif

        if (!cpath1.empty() && cpath1.back() != Path::directory_separator())
        {
            separator = Path::directory_separator();
        }

        return std::string(cpath1 + separator + cpath2);
    }

    /**
     * Gets platform specific string with the directory separator.
     */
    static char directory_separator()
    {
#if __unix__
        return '/';
#else
        return '\\';
#endif
    }

private:
    Path() = delete;
    Path(const Path& path) = delete;
    Path& operator=(const Path& path) = delete;
};

}}

#endif // SCENER_IO_PATH_HPP