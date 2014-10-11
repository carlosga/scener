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

#include <EncodingUTF8Test.hpp>

#include <System/Text/Encoding.hpp>

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
    auto bytes = std::vector<UByte> { };
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
    Char chars[]   = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto byteCount = Encoding::UTF8.GetByteCount(&chars[0], 5);
    auto bytes     = std::vector<UByte>(byteCount);
    auto count     = Encoding::UTF8.GetBytes(&chars[0], 5, &bytes[0], byteCount);

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
