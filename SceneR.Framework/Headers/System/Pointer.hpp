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
        Pointer() = delete;
        Pointer(const Pointer& pointer);
        Pointer& operator=(const Pointer& pointer) = delete;
    };
}

#endif /* POINTER_HPP */
