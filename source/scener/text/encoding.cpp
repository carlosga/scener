// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/text/encoding.hpp"

#include <locale>

#include "scener/text/utf8_encoding.hpp"

namespace scener::text
{
    encoding::encoding()
    {
    }

    encoding::~encoding()
    {
    }

    std::vector<std::uint8_t> encoding::convert(const encoding&                  source_encoding
                                              , const encoding&                  target_encoding
                                              , const std::vector<std::uint8_t>& bytes)
    {
        return encoding::convert(source_encoding, target_encoding, bytes, 0, bytes.size());
    }

    std::vector<std::uint8_t> encoding::convert(const encoding&                  source_encoding
                                              , const encoding&                  target_encoding
                                              , const std::vector<std::uint8_t>& bytes
                                              , std::size_t                      index
                                              , std::size_t                      count)
    {
        auto chars = source_encoding.get_chars(bytes, index, count);

        return target_encoding.get_bytes(chars, 0, chars.size());
    }

    std::string encoding::convert(const std::u16string& source)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter; // UTF-8 <-> UTF-16 converter

        return converter.to_bytes(source);
    }

    std::u16string encoding::convert(const std::string& source)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter; // UTF-8 <-> UTF-16 converter

        return converter.from_bytes(source);
    }

    bool encoding::is_read_only() const
    {
        return true;
    }

    std::size_t encoding::get_byte_count(const std::vector<char16_t>& chars) const
    {
        return get_byte_count(chars, 0, chars.size());
    }

    std::size_t encoding::get_byte_count(const std::u16string& s) const
    {
        auto temp = std::vector<char16_t>(s.begin(), s.end());

        return get_byte_count(temp, 0, temp.size());
    }

    std::size_t encoding::get_byte_count(const char16_t* chars, std::size_t count) const
    {
        if (chars == nullptr)
        {
            throw std::runtime_error("chars cannot be null");
        }

        auto temp = std::vector<char16_t>(chars, chars + count);

        return get_byte_count(temp, 0, count);
    }

    std::vector<std::uint8_t> encoding::get_bytes(const std::vector<char16_t>& chars) const
    {
        return get_bytes(chars, 0, chars.size());
    }

    std::vector<std::uint8_t> encoding::get_bytes(const std::u16string& s) const
    {
        auto temp = std::vector<char16_t>(s.begin(), s.end());

        return get_bytes(temp, 0, temp.size());
    }

    std::vector<std::uint8_t> encoding::get_bytes(const std::vector<char16_t>& chars
                                                , std::size_t                  index
                                                , std::size_t                  count) const
    {
        auto byte_count = get_byte_count(chars, index, count);
        auto result     = std::vector<std::uint8_t>(byte_count, 0);

        get_bytes(chars, index, count, result, 0);

        return result;
    }

    std::size_t encoding::get_bytes(const char16_t* chars
                                  , std::size_t     char_count
                                  , std::uint8_t*   bytes
                                  , std::size_t     byte_count) const
    {
        return get_encoder().get_bytes(chars, char_count, bytes, byte_count, false);
    }

    std::size_t encoding::get_bytes(const std::u16string&      s
                                  , std::size_t                char_index
                                  , std::size_t                char_count
                                  , std::vector<std::uint8_t>& bytes
                                  , std::size_t                byte_index) const
    {
        auto temp = std::vector<char16_t>(s.begin(), s.end());

        return get_bytes(temp, char_index, char_count, bytes, byte_index);
    }

    std::size_t encoding::get_char_count(const std::vector<std::uint8_t>& bytes) const
    {
        return get_char_count(bytes, 0, bytes.size());
    }

    std::size_t encoding::get_char_count(const std::uint8_t* bytes, const std::size_t& count) const
    {
        auto temp = std::vector<std::uint8_t>(bytes, bytes + count);

        return get_char_count(temp, 0, count);
    }

    std::vector<char16_t> encoding::get_chars(const std::vector<std::uint8_t>& bytes) const
    {
        return get_chars(bytes, 0, bytes.size());
    }

    std::vector<char16_t> encoding::get_chars(const std::vector<std::uint8_t>& bytes
                                            , std::size_t                      index
                                            , std::size_t                      count) const
    {
        auto char_count = get_char_count(bytes, index, count);
        auto result     = std::vector<char16_t>(char_count, 0);

        get_chars(bytes, index, count, result, 0);

        return result;
    }

    std::size_t encoding::get_chars(const std::uint8_t* bytes
                                  , std::size_t         byte_count
                                  , char16_t*           chars
                                  , std::size_t         char_count) const
    {
        return get_decoder().get_chars(bytes, byte_count, chars, char_count, false);
    }

    std::u16string encoding::get_string(const std::vector<std::uint8_t>& bytes) const
    {
        return get_string(bytes, 0, bytes.size());
    }

    std::u16string encoding::get_string(const std::vector<std::uint8_t>& bytes, std::size_t index, std::size_t count) const
    {
        auto chars = get_chars(bytes, index, count);

        return std::u16string(chars.begin(), chars.end());
    }
}
