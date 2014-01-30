/*
 * EncodingTest.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: carlos
 */

#include <System/Core.hpp>
#include <System/Text/Encoding.hpp>
#include <EncodingUTF8Test.hpp>

using namespace System;
using namespace System::Text;

TEST_F(EncodingUTF8Test, GetByteCountFromCharArray)
{
    Char tmp[] = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto chars = std::vector<Char>(std::begin(tmp), std::end(tmp));
    auto count = Encoding::UTF8.GetByteCount(chars);

    EXPECT_TRUE(8 == count);
}

TEST_F(EncodingUTF8Test, GetByteCountFromCharArrayRange)
{
    Char tmp[] = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto chars = std::vector<Char>(std::begin(tmp), std::end(tmp));
    auto count = Encoding::UTF8.GetByteCount(chars, 2, 3);

    EXPECT_TRUE(6 == count);
}

TEST_F(EncodingUTF8Test, GetBytesFromCharArray)
{
    Char tmp[] = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto chars = std::vector<Char>(std::begin(tmp), std::end(tmp));
    auto bytes = Encoding::UTF8.GetBytes(chars);

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
    Char tmp[] = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto chars = std::vector<Char>(std::begin(tmp), std::end(tmp));
    std::vector<UByte> bytes;
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
    String s     = u"za\u0306\u01FD\u03B2";
    UInt32 count = Encoding::UTF8.GetByteCount(s);

    EXPECT_TRUE(8 == count);
}

TEST_F(EncodingUTF8Test, GetBytesFromString)
{
    String s     = u"za\u0306\u01FD\u03B2";
    auto   bytes = Encoding::UTF8.GetBytes(s);

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

TEST_F(EncodingUTF8Test, GetByteCountFromCharArrayPointer)
{
    Char   chars[] = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    UInt32 count   = Encoding::UTF8.GetByteCount(&chars[0], 5);

    EXPECT_TRUE(8 == count);
}

TEST_F(EncodingUTF8Test, GetBytesFromCharArrayPointer)
{
    Char chars[] = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto byteCount = Encoding::UTF8.GetByteCount(&chars[0], 5);
    std::vector<UByte> bytes(byteCount);
    auto count = Encoding::UTF8.GetBytes(&chars[0], 5, &bytes[0], byteCount);

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
    String s     = u"za\u0306\u01FD\u03B2";
    auto   bytes = Encoding::UTF8.GetBytes(s);
    auto   count = Encoding::UTF8.GetCharCount(bytes);

    EXPECT_TRUE(5        == count);
    EXPECT_TRUE(s.size() == count);
}

TEST_F(EncodingUTF8Test, GetCharCountFromByteArrayPointer)
{
    String s     = u"za\u0306\u01FD\u03B2";
    auto   bytes = Encoding::UTF8.GetBytes(s);
    auto   count = Encoding::UTF8.GetCharCount(&bytes[0], bytes.size());

    EXPECT_TRUE(5        == count);
    EXPECT_TRUE(s.size() == count);
}
