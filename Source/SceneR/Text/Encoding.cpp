// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Encoding.hpp"

#include <locale>

#include "UTF8Encoding.hpp"

namespace SceneR
{
    namespace Text
    {
        const Encoding& Encoding::utf8 = UTF8Encoding { };

        Encoding::Encoding()
        {
        }

        Encoding::~Encoding()
        {
        }

        std::vector<std::uint8_t> Encoding::convert(const Encoding&                  srcEncoding
                                                  , const Encoding&                  dstEncoding
                                                  , const std::vector<std::uint8_t>& bytes)
        {
            return Encoding::convert(srcEncoding, dstEncoding, bytes, 0, bytes.size());
        }

        std::vector<std::uint8_t> Encoding::convert(const Encoding&                  srcEncoding
                                                  , const Encoding&                  dstEncoding
                                                  , const std::vector<std::uint8_t>& bytes
                                                  , const std::size_t&               index
                                                  , const std::size_t&               count)
        {
            auto srcChars = srcEncoding.get_chars(bytes, index, count);

            return dstEncoding.get_bytes(srcChars, 0, srcChars.size());
        }

        std::string Encoding::convert(const std::u16string& source)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter; // UTF-8 <-> UTF-16 converter

            return converter.to_bytes(source);
        }

        std::u16string Encoding::convert(const std::string& source)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter; // UTF-8 <-> UTF-16 converter

            return converter.from_bytes(source);
        }

        bool Encoding::is_read_only() const
        {
            return true;
        }

        std::size_t Encoding::get_byte_count(const std::vector<char16_t>& chars) const
        {
            return get_byte_count(chars, 0, chars.size());
        }

        std::size_t Encoding::get_byte_count(const std::u16string& s) const
        {
            auto temp = std::vector<char16_t>(s.begin(), s.end());

            return get_byte_count(temp, 0, temp.size());
        }

        std::size_t Encoding::get_byte_count(const char16_t* chars, const std::size_t& count) const
        {
            if (chars == nullptr)
            {
                throw std::runtime_error("chars cannot be null");
            }

            auto temp = std::vector<char16_t>(chars, chars + count);

            return get_byte_count(temp, 0, count);
        }

        std::vector<std::uint8_t> Encoding::get_bytes(const std::vector<char16_t>& chars) const
        {
            return get_bytes(chars, 0, chars.size());
        }

        std::vector<std::uint8_t> Encoding::get_bytes(const std::u16string& s) const
        {
            auto temp = std::vector<char16_t>(s.begin(), s.end());

            return get_bytes(temp, 0, temp.size());
        }

        std::vector<std::uint8_t> Encoding::get_bytes(const std::vector<char16_t>& chars
                                                    , const std::size_t&           index
                                                    , const std::size_t&           count) const
        {
            auto byteCount = get_byte_count(chars, index, count);
            auto result    = std::vector<std::uint8_t>(byteCount, 0);

            get_bytes(chars, index, count, result, 0);

            return result;
        }

        std::size_t Encoding::get_bytes(const char16_t*    chars
                                      , const std::size_t& charCount
                                      , std::uint8_t*      bytes
                                      , const std::size_t& byteCount) const
        {
            return get_encoder().get_bytes(chars, charCount, bytes, byteCount, false);
        }

        std::size_t Encoding::get_bytes(const std::u16string&      s
                                      , const std::size_t&         charIndex
                                      , const std::size_t&         charCount
                                      , std::vector<std::uint8_t>& bytes
                                      , const std::size_t&         byteIndex) const
        {
            auto temp = std::vector<char16_t>(s.begin(), s.end());

            return get_bytes(temp, charIndex, charCount, bytes, byteIndex);
        }

        std::size_t Encoding::get_char_count(const std::vector<std::uint8_t>& bytes) const
        {
            return get_char_count(bytes, 0, bytes.size());
        }

        std::size_t Encoding::get_char_count(const std::uint8_t* bytes, const std::size_t& count) const
        {
            auto temp = std::vector<std::uint8_t>(bytes, bytes + count);

            return get_char_count(temp, 0, count);
        }

        std::vector<char16_t> Encoding::get_chars(const std::vector<std::uint8_t>& bytes) const
        {
            return get_chars(bytes, 0, bytes.size());
        }

        std::vector<char16_t> Encoding::get_chars(const std::vector<std::uint8_t>& bytes
                                                , const std::size_t&               index
                                                , const std::size_t&               count) const
        {
            auto charCount = get_char_count(bytes, index, count);
            auto result    = std::vector<char16_t>(charCount, 0);

            get_chars(bytes, index, count, result, 0);

            return result;
        }

        std::size_t Encoding::get_chars(const std::uint8_t* bytes
                                      , const std::size_t&  byteCount
                                      , char16_t*           chars
                                      , const std::size_t&  charCount) const
        {
            return get_decoder().get_chars(bytes, byteCount, chars, charCount, false);
        }

        std::u16string Encoding::get_string(const std::vector<std::uint8_t>& bytes) const
        {
            return get_string(bytes, 0, bytes.size());
        }

        std::u16string Encoding::get_string(const std::vector<std::uint8_t>& bytes
                                          , const std::size_t&               index
                                          , const std::size_t&               count) const
        {
            auto chars = get_chars(bytes, index, count);

            return std::u16string(chars.begin(), chars.end());
        }
    }
}
