// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_CAPS_HPP
#define SCENER_CONTENT_DDS_CAPS_HPP

#include <cstdint>

namespace scener { namespace content { namespace dds {

/// The caps structure defines the capabilities of a DirectDrawSurface object.
/// This structure is part of the DDCAPS and DDSURFACEDESC structures.
enum class caps : std::uint32_t
{
    complex = 0x8       ///< Optional; must be used on any file that contains more than one surface
                        ///< (a mipmap, a cubic environment map, or mipmapped volume texture)
  , mipmap  = 0x400000  ///< Optional; should be used for a mipmap.
  , texture = 0x1000    ///< Required
};

inline constexpr caps operator&(const caps& left, const caps& right)
{
    return static_cast<caps>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
}

inline constexpr caps operator|(const caps& left, const caps& right)
{
    return static_cast<caps>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
}

inline constexpr caps operator~(const caps& value)
{
    return static_cast<caps>(~static_cast<std::uint32_t>(value));
}

inline constexpr bool operator==(const caps& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) == right);
}

inline constexpr bool operator!=(const caps& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) != right);
}

inline caps& operator&=(caps& left, const caps& right)
{
    left = left & right;

    return left;
}

inline caps& operator|=(caps& left, const caps& right)
{
    left = left | right;

    return left;
}

}}}

#endif // SCENER_CONTENT_DDS_CAPS_HPP
