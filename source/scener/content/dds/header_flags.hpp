// Copyrhs (c) Carlos Guzmán Álvarez. All rhss reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_HEADER_FLAGS_HPP
#define SCENER_CONTENT_DDS_HEADER_FLAGS_HPP

#include <cstdint>

namespace scener::content::dds
{
    /// DDS file header flags, indicates which members contain valid data.
    enum class header_flags : std::uint32_t
    {
        caps        = 0x1      ///< Required in every .dds file.
      , height      = 0x2      ///< Required in every .dds file
      , width       = 0x4      ///< Required in every .dds file.
      , pitch       = 0x8      ///< Required when pitch is provided for an uncompressed texture.
      , pixelformat = 0x1000   ///< Required in every .dds file.
      , mipmapcount = 0x20000  ///< Required in a mipmapped texture.
      , linearsize  = 0x80000  ///< Required when pitch is provided for a compressed texture.
      , depth       = 0x800000 ///< Required in a depth texture.
    };

    /// Bitwise AND operator for header_flags.
    inline constexpr header_flags operator&(const header_flags& lhs, const header_flags& rhs)
    {
        return static_cast<header_flags>(static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs));
    }

    /// Bitwise OR operator for header_flags.
    inline constexpr header_flags operator|(const header_flags& lhs, const header_flags& rhs)
    {
        return static_cast<header_flags>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
    }

    /// Unary complement operator for header_flags.
    inline constexpr header_flags operator~(const header_flags& value)
    {
        return static_cast<header_flags>(~static_cast<std::uint32_t>(value));
    }

    /// Equality operator for comparing a header_flags value against an unsigned int32.
    inline constexpr bool operator==(const header_flags& lhs, const std::uint32_t& rhs)
    {
        return (static_cast<std::uint32_t>(lhs) == rhs);
    }

    /// Inequality operator for comparing a header_flags value against an unsigned int32.
    inline constexpr bool operator!=(const header_flags& lhs, const std::uint32_t& rhs)
    {
        return (static_cast<std::uint32_t>(lhs) != rhs);
    }

    /// Equality operator for comparing header_flags values.
    inline header_flags& operator&=(header_flags& lhs, const header_flags& rhs)
    {
        lhs = lhs & rhs;

        return lhs;
    }

    /// Equality operator for comparing header_flags values.
    inline header_flags& operator|=(header_flags& lhs, const header_flags& rhs)
    {
        lhs = lhs | rhs;

        return lhs;
    }
}

#endif // SCENER_CONTENT_DDS_HEADER_FLAGS_HPP
