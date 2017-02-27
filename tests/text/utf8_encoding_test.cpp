// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Partially ported from Microsoft .NET corefx test suite ( https://github.com/dotnet/corefx )
//---------------------------------------------------------------------------------------------------

#include "utf8_encoding_test.hpp"

#include "scener/text/utf8_encoding.hpp"

using namespace scener::text;

TEST_F(utf8_encoding_test, constructor)
{
    utf8_encoding utf8;
}

TEST_F(utf8_encoding_test, get_byte_count_from_char_array)
{
    auto     encoding = utf8_encoding { };
    char16_t tmp[]    = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars    = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     count    = encoding.get_byte_count(chars);

    EXPECT_EQ(8, count);
}

TEST_F(utf8_encoding_test, get_byte_count_from_char_array_range)
{
    auto     encoding = utf8_encoding { };
    char16_t tmp[]    = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars    = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     count    = encoding.get_byte_count(chars, 2, 3);

    EXPECT_EQ(6, count);
}

TEST_F(utf8_encoding_test, get_bytes_from_char_array)
{
    auto     encoding = utf8_encoding { };
    char16_t tmp[]    = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars    = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     bytes    = encoding.get_bytes(chars);

    EXPECT_EQ(   8, bytes.size());
    EXPECT_EQ(0x7A, bytes[0]);
    EXPECT_EQ(0x61, bytes[1]);
    EXPECT_EQ(0xCC, bytes[2]);
    EXPECT_EQ(0x86, bytes[3]);
    EXPECT_EQ(0xC7, bytes[4]);
    EXPECT_EQ(0xBD, bytes[5]);
    EXPECT_EQ(0xCE, bytes[6]);
    EXPECT_EQ(0xB2, bytes[7]);
}

TEST_F(utf8_encoding_test, get_bytes_from_char_array_range)
{
    auto     encoding = utf8_encoding { };
    char16_t tmp[]    = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     chars    = std::vector<char16_t>(std::begin(tmp), std::end(tmp));
    auto     bcount   = encoding.get_byte_count(chars, 2, 3);
    auto     bytes    = std::vector<std::uint8_t>(bcount, 0);

    auto byte_count = encoding.get_bytes(chars, 2, 3, bytes, 0);

    EXPECT_EQ(   6, byte_count);
    EXPECT_EQ(   6, bytes.size());
    EXPECT_EQ(0xCC, bytes[0]);
    EXPECT_EQ(0x86, bytes[1]);
    EXPECT_EQ(0xC7, bytes[2]);
    EXPECT_EQ(0xBD, bytes[3]);
    EXPECT_EQ(0xCE, bytes[4]);
    EXPECT_EQ(0xB2, bytes[5]);
}

TEST_F(utf8_encoding_test, get_byte_count_from_string)
{
    auto encoding = utf8_encoding { };
    auto s        = u"za\u0306\u01FD\u03B2";
    auto count    = encoding.get_byte_count(s);

    EXPECT_EQ(8, count);
}

TEST_F(utf8_encoding_test, get_bytes_from_string)
{
    auto encoding = utf8_encoding { };
    auto s        = u"za\u0306\u01FD\u03B2";
    auto bytes    = encoding.get_bytes(s);

    EXPECT_EQ(   8, bytes.size());
    EXPECT_EQ(0x7A, bytes[0]);
    EXPECT_EQ(0x61, bytes[1]);
    EXPECT_EQ(0xCC, bytes[2]);
    EXPECT_EQ(0x86, bytes[3]);
    EXPECT_EQ(0xC7, bytes[4]);
    EXPECT_EQ(0xBD, bytes[5]);
    EXPECT_EQ(0xCE, bytes[6]);
    EXPECT_EQ(0xB2, bytes[7]);
}

TEST_F(utf8_encoding_test, get_bytes_from_string_range)
{
    auto encoding    = utf8_encoding { };
    std::u16string s = u"za\u0306\u01FD\u03B2";
    auto chars       = std::vector<char16_t>(s.begin(), s.end());
    auto bcount      = encoding.get_byte_count(chars, 2, 3);
    auto bytes       = std::vector<std::uint8_t>(bcount, 0);
    auto byte_count  = encoding.get_bytes(s, 2, 3, bytes, 0);

    EXPECT_EQ(   6, bytes.size());
    EXPECT_EQ(   6, byte_count);
    EXPECT_EQ(0xCC, bytes[0]);
    EXPECT_EQ(0x86, bytes[1]);
    EXPECT_EQ(0xC7, bytes[2]);
    EXPECT_EQ(0xBD, bytes[3]);
    EXPECT_EQ(0xCE, bytes[4]);
    EXPECT_EQ(0xB2, bytes[5]);
}

TEST_F(utf8_encoding_test, get_byte_count_from_char_array_pointer)
{
    auto     encoding = utf8_encoding { };
    char16_t chars[]  = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     count    = encoding.get_byte_count(&chars[0], 5);

    EXPECT_EQ(8, count);
}

TEST_F(utf8_encoding_test, get_bytes_from_char_array_pointer)
{
    auto     encoding   = utf8_encoding { };
    char16_t chars[]    = { u'z', u'a', u'\u0306', u'\u01FD', u'\u03B2'};
    auto     bcount     = encoding.get_byte_count(&chars[0], 5);
    auto     bytes      = std::vector<std::uint8_t>(bcount, 0);
    auto     byte_count = encoding.get_bytes(&chars[0], 5, bytes.data(), bcount);

    EXPECT_EQ(   8, bcount);
    EXPECT_EQ(   8, byte_count);
    EXPECT_EQ(   8, bytes.size());
    EXPECT_EQ(0x7A, bytes[0]);
    EXPECT_EQ(0x61, bytes[1]);
    EXPECT_EQ(0xCC, bytes[2]);
    EXPECT_EQ(0x86, bytes[3]);
    EXPECT_EQ(0xC7, bytes[4]);
    EXPECT_EQ(0xBD, bytes[5]);
    EXPECT_EQ(0xCE, bytes[6]);
    EXPECT_EQ(0xB2, bytes[7]);
}

TEST_F(utf8_encoding_test, get_char_count_from_byte_array)
{
    auto           encoding = utf8_encoding { };
    std::u16string s        = u"za\u0306\u01FD\u03B2";
    auto           bytes    = encoding.get_bytes(s);
    auto           count    = encoding.get_char_count(bytes);

    EXPECT_EQ(5       , count);
    EXPECT_EQ(s.size(), count);
}

TEST_F(utf8_encoding_test, get_char_count_from_byte_array_pointer)
{
    auto           encoding = utf8_encoding { };
    std::u16string s        = u"za\u0306\u01FD\u03B2";
    auto           bytes    = encoding.get_bytes(s);
    auto           count    = encoding.get_char_count(&bytes[0], bytes.size());

    EXPECT_EQ(5       , count);
    EXPECT_EQ(s.size(), count);
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// get_byte_count tests
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

// PosTest1: Verify method get_byte_count(std::vector<char16_t>,Int32,Int32) with non-null std::vector<char16_t>
TEST_F(utf8_encoding_test, get_byte_count_with_non_null_char)
{
    utf8_encoding         utf8;
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03A0', u'\u03a3' };

    auto byte_count = utf8.get_byte_count(chars, 1, 2);

    EXPECT_EQ(3, byte_count);
}

// PosTest2: Verify method get_byte_count(std::vector<char16_t>,Int32,Int32) with null std::vector<char16_t>
TEST_F(utf8_encoding_test, get_byte_count_with_null_char)
{
    utf8_encoding         utf8;
    std::vector<char16_t> chars = { };

    auto byte_count = utf8.get_byte_count(chars, 0, 0);

    EXPECT_EQ(0, byte_count);
}

// NegTest1: ArgumentNullException is not thrown when chars is a null reference
TEST_F(utf8_encoding_test, get_byte_count_with_null_reference_char)
{
    utf8_encoding   utf8;
    const char16_t* chars = nullptr;

    EXPECT_ANY_THROW({ utf8.get_byte_count(chars, 0); });
}

// NegTest2: ArgumentOutOfRangeException is not thrown when index is less than zero
TEST_F(utf8_encoding_test, get_byte_count_when_index_less_than_zero)
{
    utf8_encoding         utf8;
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03A0', u'\u03a3' };

    EXPECT_ANY_THROW({ utf8.get_byte_count(chars, -1, 2); });
}

// NegTest3: ArgumentOutOfRangeException is not thrown when count is less than zero
TEST_F(utf8_encoding_test, get_byte_count_when_count_less_than_zero)
{
    utf8_encoding         utf8;
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03A0', u'\u03a3' };

    EXPECT_ANY_THROW({ utf8.get_byte_count(chars, 1, -2); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when index and count do not denote a valid range in chars
TEST_F(utf8_encoding_test, get_byte_count_when_index_with_invalid_range_of_chars)
{
    utf8_encoding         utf8;
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03A0', u'\u03a3' };

    EXPECT_ANY_THROW({ utf8.get_byte_count(chars, 1, chars.size()); });
}

// PosTest1: Verify method get_byte_count(string) with non-null string
TEST_F(utf8_encoding_test, get_byte_count_with_non_null_string)
{
    utf8_encoding  utf8;
    std::u16string chars = u"UTF8 Encoding Example";

    auto byte_count = utf8.get_byte_count(chars);

    EXPECT_EQ(chars.size(), byte_count);
}

// PosTest2: Verify method get_byte_count(string) with null string
TEST_F(utf8_encoding_test, get_byte_count_with_empty_string)
{
    utf8_encoding  utf8;
    std::u16string chars = u"";

    auto byte_count = utf8.get_byte_count(chars);

    EXPECT_EQ(0, byte_count);
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// GetBytes tests
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

// PosTest1: Verify method GetBytes(std::vector<char16_t>,Int32,Int32,std::vector<std::uint8_t>,Int32) with non-null chars
TEST_F(utf8_encoding_test, get_bytes_withnon_null_chars)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t>     chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    auto byte_count = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byte_count, 0);

    EXPECT_EQ(3, byte_count);

    auto bytes_encoded_count = utf8.get_bytes(chars, 1, 2, bytes, 0);

    EXPECT_EQ(  3, bytes_encoded_count);
    EXPECT_EQ( 37, bytes[0]);
    EXPECT_EQ(206, bytes[1]);
    EXPECT_EQ(160, bytes[2]);
}

// PosTest2: Verify method GetBytes(std::vector<char16_t>,Int32,Int32,std::vector<std::uint8_t>,Int32) with null chars
TEST_F(utf8_encoding_test, get_bytes_with_null_chars)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t>     chars = { };

    auto byte_count = utf8.get_byte_count(chars, 0, 0);

    bytes.resize(byte_count, 0);

    auto bytes_encoded_count = utf8.get_bytes(chars, 0, 0, bytes, 0);

    EXPECT_EQ(0, bytes_encoded_count);
}

// NegTest1: ArgumentNullException is not thrown when chars is a null reference
TEST_F(utf8_encoding_test, get_bytes_when_chars_isNull)
{
    utf8_encoding             utf8;
    char16_t*                 chars = nullptr;
    std::vector<std::uint8_t> bytes;

    auto byte_count = 10;

    bytes.resize(byte_count, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, bytes.data(), 0); });
}

// NegTest2: ArgumentNullException is not thrown when bytes is a null reference
TEST_F(utf8_encoding_test, get_bytes_when_bytes_is_nNull)
{
    utf8_encoding         utf8;
    std::uint8_t*         bytes = nullptr;
    std::vector<char16_t> chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    EXPECT_ANY_THROW({ utf8.get_bytes(chars.data(), 2, bytes, 0); });
}

// NegTest3: ArgumentOutOfRangeException is not thrown when charIndex is less than zero
TEST_F(utf8_encoding_test, get_bytes_with_char_index_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t>     chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    auto byte_count = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byte_count);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, -1, 2, bytes, 0); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when char_count is less than zero
TEST_F(utf8_encoding_test, get_bytes_with_char_count_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t>     chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    auto byte_count = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byte_count, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, -2, bytes, 0); });
}

// PosTest1: Verify method GetBytes(Char[],Int32,Int32,Byte[],Int32) with non-null chars
TEST_F(utf8_encoding_test, get_bytes_with_non_null_string)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    auto byte_count = chars.size();

    bytes.resize(byte_count, 0);

    auto bytes_encoded_count = utf8.get_bytes(chars, 1, 2, bytes, 0);

    EXPECT_EQ(2, bytes_encoded_count);
}

// PosTest2: Verify method GetBytes(String,Int32,Int32,Byte[],Int32) with null chars
TEST_F(utf8_encoding_test, get_bytes_with_empty_string)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"";

    auto byte_count = chars.size();

    bytes.resize(byte_count, 0);

    auto bytes_encoded_count = utf8.get_bytes(chars, 0, byte_count, bytes, 0);

    EXPECT_EQ(0, bytes_encoded_count);
}

// NegTest3: ArgumentOutOfRangeException is not thrown when charIndex is less than zero
TEST_F(utf8_encoding_test, get_bytes_from_string_with_char_index_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    auto byte_count = chars.size();

    bytes.resize(byte_count, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, -1, 2, bytes, 0); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when char_count is less than zero
TEST_F(utf8_encoding_test, get_bytes_from_string_with_char_count_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    auto byte_count = chars.size();

    bytes.resize(byte_count, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, -2, bytes, 0); });
}

// NegTest5: ArgumentOutOfRangeException is not thrown when byteIndex is less than zero
TEST_F(utf8_encoding_test, get_bytes_from_string_when_byte_index_is_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    auto byte_count = chars.size();

    bytes.resize(byte_count, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, 2, bytes, -1); });
}

// NegTest6: ArgumentOutOfRangeException is not thrown when charIndex and char_count do not denote a valid range in chars
TEST_F(utf8_encoding_test, get_bytes_from_string_with_invalid_char_range)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    auto byte_count = chars.size();

    bytes.resize(byte_count, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, chars.size(), bytes, 0); });
}

// NegTest7: ArgumentException is not thrown when bytes does not have enough capacity
// from byteIndex to the end of the array to accommodate the resulting bytes
TEST_F(utf8_encoding_test, get_bytes_from_string_with_invalid_buffer_size)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::u16string            chars = u"UTF8 Encoding Example";

    auto byte_count = chars.size();

    bytes.resize(byte_count, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, 2, bytes, bytes.size()); });
}

// NegTest5: ArgumentOutOfRangeException is not thrown when byteIndex is less than zero
TEST_F(utf8_encoding_test, get_byte_count_when_byte_index_is_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t>     chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    auto byte_count = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byte_count, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, 2, bytes, -1); });
}

// NegTest6: ArgumentOutOfRangeException is not thrown when charIndex and char_count do not denote a valid range in chars
TEST_F(utf8_encoding_test, get_byte_count_invalid_range)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t>     chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    auto byte_count = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byte_count, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, chars.size(), bytes, 1); });
}

// NegTest7: ArgumentException is not thrown when bytes does not have enough capacity from
// byteIndex to the end of the array to accommodate the resulting bytes
TEST_F(utf8_encoding_test, get_byte_count_invalid_buffer_size)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes;
    std::vector<char16_t>     chars = { u'\u0023', u'\u0025', u'\u03a0', u'\u03a3' };

    auto byte_count = utf8.get_byte_count(chars, 1, 2);

    bytes.resize(byte_count, 0);

    EXPECT_ANY_THROW({ utf8.get_bytes(chars, 1, 2, bytes, bytes.size()); });
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// get_char_count tests
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

// PosTest1: Verify method get_char_count with a non-null buffer
TEST_F(utf8_encoding_test, get_char_count_with_non_null_buffer)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    auto char_count = utf8.get_char_count(bytes, 2, 8);

    ASSERT_TRUE(8 == char_count);
}

// PosTest2: Verify method get_char_count with a empty buffer
TEST_F(utf8_encoding_test, get_char_count_with_empty_buffer)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { };

    int char_count = utf8.get_char_count(bytes, 0, 0);

    EXPECT_EQ(0, char_count);
}

// NegTest2: ArgumentOutOfRangeException is not thrown when index is less than zero
TEST_F(utf8_encoding_test, get_char_count_when_index_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    EXPECT_ANY_THROW({ utf8.get_char_count(bytes, -1, 8); });
}

// NegTest3: ArgumentOutOfRangeException is not thrown when count is less than zero
TEST_F(utf8_encoding_test, get_char_count_when_count_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    EXPECT_ANY_THROW({ utf8.get_char_count(bytes, 2, -1); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when index and count do not denote a valid range in bytes
TEST_F(utf8_encoding_test, get_char_count_with_invalid_range)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    EXPECT_ANY_THROW({ utf8.get_char_count(bytes, 2, bytes.size()); });
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// GetChars tests
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

// PosTest1: Verify method GetChars with non-null chars
TEST_F(utf8_encoding_test, get_chars_with_non_null_chars)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };
    std::vector<char16_t>     chars;

    int char_count = utf8.get_char_count(bytes, 2, 2);

    EXPECT_TRUE(1 == char_count);

    chars.resize(char_count);

    int charsEncodedCount = utf8.get_chars(bytes, 2, 2, chars, 0);

    EXPECT_EQ(1        , charsEncodedCount);
    EXPECT_EQ(u'\u03a0', chars[0]);
}

// PosTest2: Verify method GetChars with null chars
TEST_F(utf8_encoding_test, get_chars_with_empty_chars)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };
    std::vector<char16_t>     chars;

    int char_count = utf8.get_char_count(bytes, 2, 2);

    EXPECT_EQ(1, char_count);

    int charsEncodedCount = utf8.get_chars(bytes, 0, 0, chars, 0);

    EXPECT_EQ(0, charsEncodedCount);
}

// NegTest3: ArgumentOutOfRangeException is not thrown when byteIndex is less than zero
TEST_F(utf8_encoding_test, get_chars_when_byte_index_is_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };
    std::vector<char16_t>     chars;
    auto                      char_count = utf8.get_char_count(bytes, 2, 2);

    EXPECT_EQ(1, char_count);
    EXPECT_ANY_THROW({ utf8.get_chars(bytes, -1, 2, chars, 0); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when byte_count is less than zero
TEST_F(utf8_encoding_test, get_chars_when_byte_count_is_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };
    std::vector<char16_t>     chars;
    auto                      char_count = utf8.get_char_count(bytes, 2, 2);

    EXPECT_EQ(1, char_count);
    EXPECT_ANY_THROW({ utf8.get_chars(bytes, 1, -2, chars, 0); });
}

// NegTest5: ArgumentOutOfRangeException is not thrown when charIndex is less than zero
TEST_F(utf8_encoding_test, get_chars_when_char_index_is_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };
    std::vector<char16_t>     chars;
    auto                      char_count = utf8.get_char_count(bytes, 2, 2);

    EXPECT_EQ(1, char_count);
    EXPECT_ANY_THROW({ utf8.get_chars(bytes, 2, 2, chars, -1); });
}

// NegTest6: ArgumentOutOfRangeException is not thrown when byteIndex and byte_count do not denote a valid range in chars
TEST_F(utf8_encoding_test, get_chars_with_invalid_range_in_chars)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };
    std::vector<char16_t>     chars;
    auto                      char_count = utf8.get_char_count(bytes, 2, 2);

    EXPECT_EQ(1, char_count);
    EXPECT_ANY_THROW({ utf8.get_chars(bytes, 2, 2, chars, 1); });
}

// NegTest7: ArgumentException is not thrown when chars does not have enough capacity from charIndex to the end of the
// array to accommodate the resulting characters
TEST_F(utf8_encoding_test, get_chars_with_not_enough_space_in_chars)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 35, 37, 206, 160, 206, 163 };
    std::vector<char16_t>     chars;
    auto                      char_count = utf8.get_char_count(bytes, 2, 2);

    EXPECT_EQ(1, char_count);
    EXPECT_ANY_THROW({ utf8.get_chars(bytes, 2, 2, chars, chars.size()); });
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// get_string tests
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

TEST_F(utf8_encoding_test, get_string)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    auto str = utf8.get_string(bytes, 0, bytes.size());

    EXPECT_EQ(u"UTF8 Encoding Example", str);
}

// NegTest2: ArgumentOutOfRangeException is not thrown when index is less than zero
TEST_F(utf8_encoding_test, get_string_when_index_is_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    EXPECT_ANY_THROW({ utf8.get_string(bytes, -1, bytes.size()); });
}

// NegTest3: ArgumentOutOfRangeException is not thrown when count is less than zero
TEST_F(utf8_encoding_test, get_string_when_count_is_less_than_zero)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    EXPECT_ANY_THROW({ utf8.get_string(bytes, 0, -1); });
}

// NegTest4: ArgumentOutOfRangeException is not thrown when index and count do not denote a valid range in bytes
TEST_F(utf8_encoding_test, get_string_when_byte_range_is_invalid)
{
    utf8_encoding             utf8;
    std::vector<std::uint8_t> bytes = { 85,  84,  70,  56,  32,  69, 110,
                                        99, 111, 100, 105, 110, 103,  32,
                                        69, 120,  97, 109, 112, 108, 101 };

    EXPECT_ANY_THROW({  utf8.get_string(bytes, 1, bytes.size()); });
}
