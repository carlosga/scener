// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "EncodingUTF8Test.hpp"

#include <cstddef>
#include <cstdint>

#include <scener/text/UTF8Encoding.hpp>

using namespace scener;
using namespace scener::text;

TEST_F(EncodingUTF8Test, GetByteCountFromCharArray)
{
    char16_t tmp[]    = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars    = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     encoding = UTF8Encoding { };
    auto     count    = encoding.get_byte_count(chars);

    EXPECT_TRUE(8 == count);
}

TEST_F(EncodingUTF8Test, GetByteCountFromCharArrayRange)
{
    char16_t tmp[]    = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars    = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     encoding = UTF8Encoding { };
    auto     count    = encoding.get_byte_count(chars, 2, 3);

    EXPECT_TRUE(6 == count);
}

TEST_F(EncodingUTF8Test, GetBytesFromCharArray)
{
    char16_t tmp[]    = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars    = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     encoding = UTF8Encoding { };
    auto     bytes    = encoding.get_bytes(chars);

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
    char16_t tmp[]    = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars    = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     encoding = UTF8Encoding { };
    auto     bcount   = encoding.get_byte_count(chars, 2, 3);
    auto     bytes    = std::vector<std::uint8_t>(bcount, 0);

    auto byteCount = encoding.get_bytes(chars, 2, 3, bytes, 0);

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
    auto s        = u"za\u0306\u01FD\u03B2";
    auto encoding = UTF8Encoding { };
    auto count    = encoding.get_byte_count(s);

    EXPECT_TRUE(8 == count);
}

TEST_F(EncodingUTF8Test, GetBytesFromString)
{
    auto s        = u"za\u0306\u01FD\u03B2";
    auto encoding = UTF8Encoding { };
    auto bytes    = encoding.get_bytes(s);

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
    std::u16string s = u"za\u0306\u01FD\u03B2";
    std::vector<char16_t> chars(s.begin(), s.end());

    auto encoding  = UTF8Encoding { };
    auto bcount    = encoding.get_byte_count(chars, 2, 3);
    auto bytes     = std::vector<std::uint8_t>(bcount, 0);
    auto byteCount = encoding.get_bytes(s, 2, 3, bytes, 0);

    EXPECT_TRUE(6 == bytes.size());
    EXPECT_TRUE(6 == byteCount);

    EXPECT_TRUE(0xCC == bytes[0]);
    EXPECT_TRUE(0x86 == bytes[1]);
    EXPECT_TRUE(0xC7 == bytes[2]);
    EXPECT_TRUE(0xBD == bytes[3]);
    EXPECT_TRUE(0xCE == bytes[4]);
    EXPECT_TRUE(0xB2 == bytes[5]);
}

TEST_F(EncodingUTF8Test, GetByteCountFromCharArrayPointer)
{
    char16_t chars[]  = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     encoding = UTF8Encoding { };
    auto     count    = encoding.get_byte_count(&chars[0], 5);

    EXPECT_TRUE(8 == count);
}

TEST_F(EncodingUTF8Test, GetBytesFromCharArrayPointer)
{
    char16_t chars[]   = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     encoding  = UTF8Encoding { };
    auto     bcount    = encoding.get_byte_count(&chars[0], 5);
    auto     bytes     = std::vector<std::uint8_t>(bcount, 0);
    auto     byteCount = encoding.get_bytes(&chars[0], 5, bytes.data(), bcount);

    EXPECT_TRUE(8 == bcount);
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
    std::u16string s        = u"za\u0306\u01FD\u03B2";
    auto           encoding = UTF8Encoding { };
    auto           bytes    = encoding.get_bytes(s);
    auto           count    = encoding.get_char_count(bytes);

    EXPECT_TRUE(5        == count);
    EXPECT_TRUE(s.size() == count);
}

TEST_F(EncodingUTF8Test, GetCharCountFromByteArrayPointer)
{
    std::u16string s        = u"za\u0306\u01FD\u03B2";
    auto           encoding = UTF8Encoding { };
    auto           bytes    = encoding.get_bytes(s);
    auto           count    = encoding.get_char_count(&bytes[0], bytes.size());

    EXPECT_TRUE(5        == count);
    EXPECT_TRUE(s.size() == count);
}
