// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <EncodingUTF8Test.hpp>

#include <cstddef>
#include <cstdint>

#include <System/Text/Encoding.hpp>

using namespace System;
using namespace System::Text;

TEST_F(EncodingUTF8Test, GetByteCountFromCharArray)
{
    char16_t tmp[] = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     count = Encoding::UTF8.GetByteCount(chars);

    EXPECT_TRUE(8 == count);
}

TEST_F(EncodingUTF8Test, GetByteCountFromCharArrayRange)
{
    char16_t tmp[] = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     count = Encoding::UTF8.GetByteCount(chars, 2, 3);

    EXPECT_TRUE(6 == count);
}

TEST_F(EncodingUTF8Test, GetBytesFromCharArray)
{
    char16_t tmp[] = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     bytes = Encoding::UTF8.GetBytes(chars);

    EXPECT_TRUE(8 == bytes.size());

    EXPECT_TRUE(0x7A == bytes[0]);
    EXPECT_TRUE(0x61 == bytes[1]);
    EXPECT_TRUE(0xCC == bytes[2]);
    EXPECT_TRUE(0x86 == bytes[3]);
    EXPECT_TRUE(0xC7 == bytes[4]);
    EXPECT_TRUE(0xBD == bytes[5]);
    EXPECT_TRUE(0xCE == bytes[6]);
    EXPECT_TRUE(0xB2 == bytes[7]);
}

TEST_F(EncodingUTF8Test, GetBytesFromCharArrayRange)
{
    char16_t tmp[] = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     bytes = std::vector<std::uint8_t> { };

    bytes.reserve(Encoding::UTF8.GetByteCount(chars, 2, 3));

    auto byteCount = Encoding::UTF8.GetBytes(chars, 2, 3, bytes, 0);

    EXPECT_TRUE(6 == byteCount);
    EXPECT_TRUE(6 == bytes.size());

    EXPECT_TRUE(0xCC == bytes[0]);
    EXPECT_TRUE(0x86 == bytes[1]);
    EXPECT_TRUE(0xC7 == bytes[2]);
    EXPECT_TRUE(0xBD == bytes[3]);
    EXPECT_TRUE(0xCE == bytes[4]);
    EXPECT_TRUE(0xB2 == bytes[5]);
}

TEST_F(EncodingUTF8Test, GetByteCountFromString)
{
    auto s     = u"za\u0306\u01FD\u03B2";
    auto count = Encoding::UTF8.GetByteCount(s);

    EXPECT_TRUE(8 == count);
}

TEST_F(EncodingUTF8Test, GetBytesFromString)
{
    auto s     = u"za\u0306\u01FD\u03B2";
    auto bytes = Encoding::UTF8.GetBytes(s);

    EXPECT_TRUE(8 == bytes.size());

    EXPECT_TRUE(0x7A == bytes[0]);
    EXPECT_TRUE(0x61 == bytes[1]);
    EXPECT_TRUE(0xCC == bytes[2]);
    EXPECT_TRUE(0x86 == bytes[3]);
    EXPECT_TRUE(0xC7 == bytes[4]);
    EXPECT_TRUE(0xBD == bytes[5]);
    EXPECT_TRUE(0xCE == bytes[6]);
    EXPECT_TRUE(0xB2 == bytes[7]);
}

TEST_F(EncodingUTF8Test, GetBytesFromStringRange)
{
    auto s     = u"za\u0306\u01FD\u03B2";
    auto bytes = std::vector<std::uint8_t>();

    bytes.reserve(Encoding::UTF8.GetByteCount(s));

    auto count = Encoding::UTF8.GetBytes(s, 2, 3, bytes, 0);

    EXPECT_TRUE(6 == bytes.size());
    EXPECT_TRUE(6 == count);

    EXPECT_TRUE(0xCC == bytes[0]);
    EXPECT_TRUE(0x86 == bytes[1]);
    EXPECT_TRUE(0xC7 == bytes[2]);
    EXPECT_TRUE(0xBD == bytes[3]);
    EXPECT_TRUE(0xCE == bytes[4]);
    EXPECT_TRUE(0xB2 == bytes[5]);
}

TEST_F(EncodingUTF8Test, GetByteCountFromCharArrayPointer)
{
    char16_t chars[] = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     count   = Encoding::UTF8.GetByteCount(&chars[0], 5);

    EXPECT_TRUE(8 == count);
}

TEST_F(EncodingUTF8Test, GetBytesFromCharArrayPointer)
{
    char16_t chars[]   = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     byteCount = Encoding::UTF8.GetByteCount(&chars[0], 5);
    auto     bytes     = std::vector<std::uint8_t>(byteCount);
    auto     count     = Encoding::UTF8.GetBytes(&chars[0], 5, &bytes[0], byteCount);

    EXPECT_TRUE(8 == count);
    EXPECT_TRUE(8 == byteCount);
    EXPECT_TRUE(8 == bytes.size());

    EXPECT_TRUE(0x7A == bytes[0]);
    EXPECT_TRUE(0x61 == bytes[1]);
    EXPECT_TRUE(0xCC == bytes[2]);
    EXPECT_TRUE(0x86 == bytes[3]);
    EXPECT_TRUE(0xC7 == bytes[4]);
    EXPECT_TRUE(0xBD == bytes[5]);
    EXPECT_TRUE(0xCE == bytes[6]);
    EXPECT_TRUE(0xB2 == bytes[7]);
}

TEST_F(EncodingUTF8Test, GetCharCountFromByteArray)
{
    std::u16string s     = u"za\u0306\u01FD\u03B2";
    auto           bytes = Encoding::UTF8.GetBytes(s);
    auto           count = Encoding::UTF8.GetCharCount(bytes);

    EXPECT_TRUE(5        == count);
    EXPECT_TRUE(s.size() == count);
}

TEST_F(EncodingUTF8Test, GetCharCountFromByteArrayPointer)
{
    std::u16string s     = u"za\u0306\u01FD\u03B2";
    auto           bytes = Encoding::UTF8.GetBytes(s);
    auto           count = Encoding::UTF8.GetCharCount(&bytes[0], bytes.size());

    EXPECT_TRUE(5        == count);
    EXPECT_TRUE(s.size() == count);
}
