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

#ifndef CORE_HPP
#define CORE_HPP

#include <string>

namespace System
{
    using Char    = char16_t;
    using Boolean = bool;
    using Byte    = int8_t;
    using UByte   = uint8_t;
    using Int16   = int16_t;
    using UInt16  = uint16_t;
    using Int32   = int32_t;
    using UInt32  = uint32_t;
    using Int64   = int64_t;
    using UInt64  = uint64_t;
    using Single  = float;
    using Double  = double;
    using Size    = uint32_t;
    using String  = std::u16string;
}

#endif  /* CORE_HPP */
