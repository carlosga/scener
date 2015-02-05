// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef POINTER_HPP
#define POINTER_HPP

#include <memory>

namespace System
{
    /**
     * Helper class for pointer handling .
     */
    class Pointer
    {
    public:
        /**
         * Creates a new unique pointer with the given arguments
         * http://clean-cpp.org/underprivileged-unique-pointers-make_unique/
         * http://herbsutter.com/gotw/_102/
         */
        template <typename Value, typename ... Arguments>
        static std::unique_ptr<Value> CreateUnique(Arguments && ... arguments_for_constructor)
        {
            return std::unique_ptr<Value>(new Value(std::forward<Arguments>(arguments_for_constructor)...));
        };

    private:
        Pointer() = delete;
        Pointer(const Pointer& pointer);
        Pointer& operator=(const Pointer& pointer) = delete;
    };
}

#endif /* POINTER_HPP */
