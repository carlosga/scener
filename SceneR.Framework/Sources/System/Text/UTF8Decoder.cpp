// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#include <System/Text/UTF8Decoder.hpp>

using namespace System;
using namespace System::Text;

UTF8Decoder::UTF8Decoder()
    : Decoder { }
{
}

UTF8Decoder::~UTF8Decoder()
{
}

Size UTF8Decoder::GetCharCount(const std::vector<UByte>& bytes
                             , const Size&               index
                             , const Size&               count) const
{
    Size result = 0;

    for (Size i = index; i < (index + count);)
    {
        auto buffer    = bytes[i];
        Size byteCount = 1;

        // http://xbox.create.msdn.com/en-US/sample/xnb_format
        // Decode UTF-8.
        if (buffer & 0x80)
        {
            while (buffer & (0x80 >> byteCount))
            {
                byteCount++;
            }
        }

        i += byteCount;
        result++;
    }

    return result;
}

Size UTF8Decoder::GetChars(const std::vector<UByte>& bytes
                         , const Size&               byteIndex
                         , const Size&               byteCount
                         , std::vector<Char>&        chars
                         , const Size&               charIndex) const
{
    auto        from     = (char*)&bytes[0] + byteIndex;
    auto        fromEnd  = from + byteCount;
    const char* fromNext = nullptr;
    auto        to       = std::vector<Char>(byteCount);
    auto        toStart  = &to[0];
    auto        toEnd    = toStart + byteCount;
    Char*       toNext   = nullptr;
    auto        iterator = chars.begin() + charIndex;
    auto        state    = std::mbstate_t();
    auto        status   = this->converter.in(state, from, fromEnd, fromNext, toStart, toEnd, toNext);

    if (status == std::codecvt_base::error)
    {
        throw std::runtime_error("decoder error");
    }
    else if (status == std::codecvt_base::partial)
    {
    }
    else if (status == std::codecvt_base::ok)
    {
        for (auto position = toStart; position < toNext; position++)
        {
            chars.emplace(iterator++, *position);
        }
    }

    return static_cast<Size>(toNext - toStart);
}

void UTF8Decoder::Reset()
{
}
