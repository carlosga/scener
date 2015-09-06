// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft .NET corefx test suite ( https://github.com/dotnet/corefx )
//---------------------------------------------------------------------------------------------------

#include <UTF8EncodingTest.hpp>

#include <System/Text/UTF8Encoding.hpp>

using namespace System::Text;

TEST_F(UTF8EncodingTest, Constructor)
{
    UTF8Encoding utf8;
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// GetByteCount tests
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

// PosTest1: Verify method GetByteCount(std::vector<char16_t>,Int32,Int32) with non-null std::vector<char16_t>
TEST_F(UTF8EncodingTest, GetByteCountWithNonNullChar)
{
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03A0', u'\u03a3' };

    UTF8Encoding utf8;

    auto byteCount = utf8.get_byte_count(chars, 1, 2);

    EXPECT_TRUE(3 == byteCount);
}

// PosTest2: Verify method GetByteCount(std::vector<char16_t>,Int32,Int32) with null std::vector<char16_t>
TEST_F(UTF8EncodingTest, GetByteCountWithNullChar)
{
    std::vector<char16_t> chars = { };

    UTF8Encoding utf8;

    auto byteCount = utf8.get_byte_count(chars, 0, 0);

    EXPECT_TRUE(0 == byteCount);
}

// NegTest1: ArgumentNullException is not thrown when chars is a null reference
TEST_F(UTF8EncodingTest, GetByteCountWithNullReferenceChar)
{
    const char16_t* chars = nullptr;

    UTF8Encoding utf8;

    EXPECT_ANY_THROW({ utf8.get_byte_count(chars, 0); });
}

// NegTest2: ArgumentOutOfRangeException is not thrown when index is less than zero
TEST_F(UTF8EncodingTest, GetByteCountWhenIndexLessThanZero)
{
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03A0', u'\u03a3' };

    UTF8Encoding utf8;

    EXPECT_ANY_THROW({ utf8.get_byte_count(chars, -1, 2); });
}

// NegTest3: ArgumentOutOfRangeException is not thrown when count is less than zero
TEST_F(UTF8EncodingTest, GetByteCountWhenCountLessThanZero)
{
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03A0', u'\u03a3' };

    UTF8Encoding utf8;

    EXPECT_ANY_THROW({ utf8.get_byte_count(chars, 1, -2); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when index and count do not denote a valid range in chars
TEST_F(UTF8EncodingTest, GetByteCountWhenIndexWithInvalidRangeOfChars)
{
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03A0', u'\u03a3' };

    UTF8Encoding utf8;

    EXPECT_ANY_THROW({ utf8.get_byte_count(chars, 1, chars.size()); });
}

// PosTest1: Verify method GetByteCount(string) with non-null string
TEST_F(UTF8EncodingTest, GetByteCountWithNonNullString)
{
    std::u16string chars = u"UTF8 Encoding Example";

    UTF8Encoding utf8;

    auto byteCount = utf8.get_byte_count(chars);

    EXPECT_TRUE(chars.size() == byteCount);
}

// PosTest2: Verify method GetByteCount(string) with null string
TEST_F(UTF8EncodingTest, GetByteCountWithEmptyString)
{
    std::u16string chars = u"";

    UTF8Encoding utf8;
    Encoding* encoding = &utf8;

    auto byteCount = encoding->get_byte_count(chars);

    EXPECT_TRUE(0 == byteCount);
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// GetBytes tests
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

// PosTest1: Verify method GetBytes(std::vector<char16_t>,Int32,Int32,std::vector<std::uint8_t>,Int32) with non-null chars
TEST_F(UTF8EncodingTest, GetBytesWithNonNullChars)
{
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t>     chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    UTF8Encoding utf8;

    auto byteCount = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byteCount, 0);

    EXPECT_TRUE(3 == byteCount);

    auto bytesEncodedCount = utf8.get_bytes(chars, 1, 2, bytes, 0);

    EXPECT_TRUE(  3  == bytesEncodedCount);
    EXPECT_TRUE( 37 == bytes[0]);
    EXPECT_TRUE(206 == bytes[1]);
    EXPECT_TRUE(160 == bytes[2]);
}

// PosTest2: Verify method GetBytes(std::vector<char16_t>,Int32,Int32,std::vector<std::uint8_t>,Int32) with null chars
TEST_F(UTF8EncodingTest, GetBytesWithNullChars)
{
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t>    chars = { };

    UTF8Encoding utf8;

    auto byteCount = utf8.get_byte_count(chars, 0, 0);

    bytes.resize(byteCount, 0);

    auto bytesEncodedCount = utf8.get_bytes(chars, 0, 0, bytes, 0);

    EXPECT_TRUE(0 == bytesEncodedCount);
}

// NegTest1: ArgumentNullException is not thrown when chars is a null reference
TEST_F(UTF8EncodingTest, GetBytesWhenCharsIsNull)
{
    std::vector<std::uint8_t> bytes;
    char16_t* chars = nullptr;

    UTF8Encoding utf8;

    auto byteCount = 10;

    bytes.resize(byteCount, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, bytes.data(), 0); });
}

// NegTest2: ArgumentNullException is not thrown when bytes is a null reference
TEST_F(UTF8EncodingTest, GetBytesWhenBytesIsNull)
{
    std::uint8_t*         bytes = nullptr;
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    UTF8Encoding utf8;

    EXPECT_ANY_THROW({ utf8.get_bytes(chars.data(), 2, bytes, 0); });
}

// NegTest3: ArgumentOutOfRangeException is not thrown when charIndex is less than zero
TEST_F(UTF8EncodingTest, GetBytesWithCharIndexLessThanZero)
{
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    UTF8Encoding utf8;

    auto byteCount = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byteCount);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, -1, 2, bytes, 0); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when charCount is less than zero
TEST_F(UTF8EncodingTest, GetBytesWithCharCountLessThanZero)
{
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    UTF8Encoding utf8;

    auto byteCount = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byteCount, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, -2, bytes, 0); });
}

// PosTest1: Verify method GetBytes(Char[],Int32,Int32,Byte[],Int32) with non-null chars
TEST_F(UTF8EncodingTest, GetBytesWithNonNullString)
{
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    UTF8Encoding utf8;

    auto byteCount = chars.size();

    bytes.resize(byteCount, 0);

    auto bytesEncodedCount = utf8.get_bytes(chars, 1, 2, bytes, 0);

    EXPECT_TRUE(bytesEncodedCount == 2);
}

// PosTest2: Verify method GetBytes(String,Int32,Int32,Byte[],Int32) with null chars
TEST_F(UTF8EncodingTest, GetBytesWithEmptyString)
{
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"";

    UTF8Encoding utf8;

    auto byteCount = chars.size();

    bytes.resize(byteCount, 0);

    auto bytesEncodedCount = utf8.get_bytes(chars, 0, byteCount, bytes, 0);

    EXPECT_TRUE(0 == bytesEncodedCount);
}

// NegTest3: ArgumentOutOfRangeException is not thrown when charIndex is less than zero
TEST_F(UTF8EncodingTest, GetBytesFromStringWithCharIndexLessThanZero)
{
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    UTF8Encoding utf8;

    auto byteCount = chars.size();

    bytes.resize(byteCount, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, -1, 2, bytes, 0); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when charCount is less than zero
TEST_F(UTF8EncodingTest, GetBytesFromStringWithCharCountLessThanZero)
{
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    UTF8Encoding utf8;

    auto byteCount = chars.size();

    bytes.resize(byteCount, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, -2, bytes, 0); });
}

// NegTest5: ArgumentOutOfRangeException is not thrown when byteIndex is less than zero
TEST_F(UTF8EncodingTest, GetBytesFromStringWhenByteIndexIsLessThanZero)
{
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    UTF8Encoding utf8;

    auto byteCount = chars.size();

    bytes.resize(byteCount, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, 2, bytes, -1); });
}

// NegTest6: ArgumentOutOfRangeException is not thrown when charIndex and charCount do not denote a valid range in chars
TEST_F(UTF8EncodingTest, GetBytesFromStringWithInvalidCharRange)
{
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    UTF8Encoding utf8;

    auto byteCount = chars.size();

    bytes.resize(byteCount, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, chars.size(), bytes, 0); });
}

// NegTest7: ArgumentException is not thrown when bytes does not have enough capacity
// from byteIndex to the end of the array to accommodate the resulting bytes
TEST_F(UTF8EncodingTest, GetBytesFromStringWithInvalidBufferSize)
{
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    UTF8Encoding utf8;

    auto byteCount = chars.size();

    bytes.resize(byteCount, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, 2, bytes, bytes.size()); });
}

// NegTest5: ArgumentOutOfRangeException is not thrown when byteIndex is less than zero
TEST_F(UTF8EncodingTest, GetByteCountWhenByteIndexIsLessThanZero)
{
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    UTF8Encoding utf8;

    auto byteCount = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byteCount, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, 2, bytes, -1); });
}

// NegTest6: ArgumentOutOfRangeException is not thrown when charIndex and charCount do not denote a valid range in chars
TEST_F(UTF8EncodingTest, GetByteCountInvalidRange)
{
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    UTF8Encoding utf8;

    auto byteCount = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byteCount, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, chars.size(), bytes, 1); });
}

// NegTest7: ArgumentException is not thrown when bytes does not have enough capacity from
// byteIndex to the end of the array to accommodate the resulting bytes
TEST_F(UTF8EncodingTest, GetByteCountInvalidBufferSize)
{
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    UTF8Encoding utf8;

    auto byteCount = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byteCount, 0);

    EXPECT_ANY_THROW({  utf8.get_bytes(chars, 1, 2, bytes, bytes.size()); });
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// GetCharCount tests
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

// PosTest1: Verify method GetCharCount with a non-null buffer
TEST_F(UTF8EncodingTest, GetCharCountWithNonNullBuffer)
{
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    UTF8Encoding utf8;

    auto charCount = utf8.get_char_count(bytes, 2, 8);

    ASSERT_TRUE(8 == charCount);
}

// PosTest2: Verify method GetCharCount with a empty buffer
TEST_F(UTF8EncodingTest, GetCharCountWithEmptyBuffer)
{
    std::vector<std::uint8_t> bytes = { };

    UTF8Encoding utf8;

    int charCount = utf8.get_char_count(bytes, 0, 0);

    ASSERT_TRUE(0 == charCount);
}

// NegTest2: ArgumentOutOfRangeException is not thrown when index is less than zero
TEST_F(UTF8EncodingTest, GetCharCountWhenIndexLessThanZero)
{
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    UTF8Encoding utf8;

    EXPECT_ANY_THROW({ utf8.get_char_count(bytes, -1, 8); });
}

// NegTest3: ArgumentOutOfRangeException is not thrown when count is less than zero
TEST_F(UTF8EncodingTest, GetCharCountWhenCountLessThanZero)
{
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    UTF8Encoding utf8;

    EXPECT_ANY_THROW({ utf8.get_char_count(bytes, 2, -1); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when index and count do not denote a valid range in bytes
TEST_F(UTF8EncodingTest, GetCharCountWithInvalidRange)
{
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    UTF8Encoding utf8;

    EXPECT_ANY_THROW({ utf8.get_char_count(bytes, 2, bytes.size()); });
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// GetChars tests
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

// PosTest1: Verify method GetChars with non-null chars
TEST_F(UTF8EncodingTest, GetCharsWithNonNullChars)
{
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };

    std::vector<char16_t> chars;

    UTF8Encoding utf8;

    int charCount = utf8.get_char_count(bytes, 2, 2);

    EXPECT_TRUE(1 == charCount);

    chars.resize(charCount);

    int charsEncodedCount = utf8.get_chars(bytes, 2, 2, chars, 0);

    EXPECT_TRUE(1 == charsEncodedCount);
    EXPECT_TRUE(u'\u03a0' == chars[0]);
}

// PosTest2: Verify method GetChars with null chars
TEST_F(UTF8EncodingTest, GetCharsWithEmptyChars)
{
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };

    std::vector<char16_t> chars;

    UTF8Encoding utf8;

    int charCount = utf8.get_char_count(bytes, 2, 2);

    EXPECT_TRUE(1 == charCount);

    int charsEncodedCount = utf8.get_chars(bytes, 0, 0, chars, 0);

    EXPECT_TRUE(0 == charsEncodedCount);
}

// NegTest3: ArgumentOutOfRangeException is not thrown when byteIndex is less than zero
TEST_F(UTF8EncodingTest, GetCharsWhenByteIndexIsLessThanZero)
{
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };

    std::vector<char16_t> chars;

    UTF8Encoding utf8;

    int charCount = utf8.get_char_count(bytes, 2, 2);

    EXPECT_TRUE(1 == charCount);

    EXPECT_ANY_THROW({ utf8.get_chars(bytes, -1, 2, chars, 0); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when byteCount is less than zero
TEST_F(UTF8EncodingTest, GetCharsWhenByteCountIsLessThanZero)
{
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };

    std::vector<char16_t> chars;

    UTF8Encoding utf8;

    int charCount = utf8.get_char_count(bytes, 2, 2);

    EXPECT_TRUE(1 == charCount);

    EXPECT_ANY_THROW({ utf8.get_chars(bytes, 1, -2, chars, 0); });
}

// NegTest5: ArgumentOutOfRangeException is not thrown when charIndex is less than zero
TEST_F(UTF8EncodingTest, GetCharsWhenCharIndexIsLessThanZero)
{
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };

    std::vector<char16_t> chars;

    UTF8Encoding utf8;

    int charCount = utf8.get_char_count(bytes, 2, 2);

    EXPECT_TRUE(1 == charCount);

    EXPECT_ANY_THROW({ utf8.get_chars(bytes, 2, 2, chars, -1); });
}

// NegTest6: ArgumentOutOfRangeException is not thrown when byteIndex and byteCount do not denote a valid range in chars
TEST_F(UTF8EncodingTest, GetCharsWithInvalidRangeInChars)
{
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };

    std::vector<char16_t> chars;

    UTF8Encoding utf8;

    int charCount = utf8.get_char_count(bytes, 2, 2);

    EXPECT_TRUE(1 == charCount);

    EXPECT_ANY_THROW({ utf8.get_chars(bytes, 2, 2, chars, 1); });
}

// NegTest7: ArgumentException is not thrown when chars does not have enough capacity from charIndex to the end of the
// array to accommodate the resulting characters
TEST_F(UTF8EncodingTest, GetCharsWithNotEnoughSpaceInChars)
{
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };

    std::vector<char16_t> chars;

    UTF8Encoding utf8;

    int charCount = utf8.get_char_count(bytes, 2, 2);

    EXPECT_TRUE(1 == charCount);

    EXPECT_ANY_THROW({ utf8.get_chars(bytes, 2, 2, chars, chars.size()); });
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// GetString tests
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

TEST_F(UTF8EncodingTest, GetString)
{
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    UTF8Encoding utf8;

    auto str = utf8.get_string(bytes, 0, bytes.size());

    EXPECT_TRUE(u"UTF8 Encoding Example" == str);
}

// NegTest2: ArgumentOutOfRangeException is not thrown when index is less than zero
TEST_F(UTF8EncodingTest, GetStringWhenIndexIsLessThanZero)
{
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    UTF8Encoding utf8;

    EXPECT_ANY_THROW({ utf8.get_string(bytes, -1, bytes.size()); });
}

// NegTest3: ArgumentOutOfRangeException is not thrown when count is less than zero
TEST_F(UTF8EncodingTest, GetStringWhenCountIsLessThanZero)
{
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    UTF8Encoding utf8;

    EXPECT_ANY_THROW({ utf8.get_string(bytes, 0, -1); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when index and count do not denote a valid range in bytes
TEST_F(UTF8EncodingTest, GetStringWhenByteRangeIsInvalid)
{
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    UTF8Encoding utf8;

    EXPECT_ANY_THROW({  utf8.get_string(bytes, 1, bytes.size()); });
}
