/*
 * Pointer.hpp
 *
 *  Created on: Oct 30, 2013
 *      Author: carlos
 */

#ifndef POINTER_HPP
#define POINTER_HPP

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
        Pointer() = default;
    };
}

#endif /* POINTER_HPP */
