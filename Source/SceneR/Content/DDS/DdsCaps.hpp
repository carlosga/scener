// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_DDSCAPS_HPP
#define SCENER_CONTENT_DDS_DDSCAPS_HPP

#include <cstdint>

namespace SceneR { namespace Content { namespace DDS {

/// The DDSCAPS structure defines the capabilities of a DirectDrawSurface object.
/// This structure is part of the DDCAPS and DDSURFACEDESC structures.
enum class DDS_CAPS : std::uint32_t
{
    DDSCAPS_COMPLEX = 0x8       ///< Optional; must be used on any file that contains more than one surface
                                ///< (a mipmap, a cubic environment map, or mipmapped volume texture)
  , DDSCAPS_MIPMAP  = 0x400000  ///< Optional; should be used for a mipmap.
  , DDSCAPS_TEXTURE = 0x1000    ///< Required
};

inline constexpr DDS_CAPS operator&(const DDS_CAPS& left, const DDS_CAPS& right)
{
    return static_cast<DDS_CAPS>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
}

inline constexpr DDS_CAPS operator|(const DDS_CAPS& left, const DDS_CAPS& right)
{
    return static_cast<DDS_CAPS>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
}

inline constexpr DDS_CAPS operator~(const DDS_CAPS& value)
{
    return static_cast<DDS_CAPS>(~static_cast<std::uint32_t>(value));
}

inline constexpr bool operator==(const DDS_CAPS& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) == right);
}

inline constexpr bool operator!=(const DDS_CAPS& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) != right);
}

inline DDS_CAPS& operator&=(DDS_CAPS& left, const DDS_CAPS& right)
{
    left = left & right;

    return left;
}

inline DDS_CAPS& operator|=(DDS_CAPS& left, const DDS_CAPS& right)
{
    left = left | right;

    return left;
}

}}}

#endif // SCENER_CONTENT_DDS_DDSCAPS_HPP
