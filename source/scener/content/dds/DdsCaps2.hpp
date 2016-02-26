// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_DDSCAPS2_HPP
#define SCENER_CONTENT_DDS_DDSCAPS2_HPP

namespace scener { namespace content {  namespace dds {

/// The DDSCAPS2 structure defines the capabilities of a DirectDrawSurface object
enum class DDS_CAPS2
{
    DDSCAPS2_CUBEMAP           = 0x200    ///< Required for a cube map.
  , DDSCAPS2_CUBEMAP_POSITIVEX = 0x400    ///< Required when these surfaces are stored in a cube map.
  , DDSCAPS2_CUBEMAP_NEGATIVEX = 0x800    ///< Required when these surfaces are stored in a cube map.
  , DDSCAPS2_CUBEMAP_POSITIVEY = 0x1000   ///< Required when these surfaces are stored in a cube map.
  , DDSCAPS2_CUBEMAP_NEGATIVEY = 0x2000   ///< Required when these surfaces are stored in a cube map.
  , DDSCAPS2_CUBEMAP_POSITIVEZ = 0x4000   ///< Required when these surfaces are stored in a cube map.
  , DDSCAPS2_CUBEMAP_NEGATIVEZ = 0x8000   ///< Required when these surfaces are stored in a cube map.
  , DDSCAPS2_VOLUME	           = 0x200000 ///< Required for a volume texture.
};

inline constexpr DDS_CAPS2 operator&(const DDS_CAPS2& left, const DDS_CAPS2& right)
{
    return static_cast<DDS_CAPS2>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
}

inline constexpr DDS_CAPS2 operator|(const DDS_CAPS2& left, const DDS_CAPS2& right)
{
    return static_cast<DDS_CAPS2>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
}

inline constexpr DDS_CAPS2 operator~(const DDS_CAPS2& value)
{
    return static_cast<DDS_CAPS2>(~static_cast<std::uint32_t>(value));
}

inline constexpr bool operator==(const DDS_CAPS2& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) == right);
}

inline constexpr bool operator!=(const DDS_CAPS2& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) != right);
}

inline DDS_CAPS2& operator&=(DDS_CAPS2& left, const DDS_CAPS2& right)
{
    left = left & right;

    return left;
}

inline DDS_CAPS2& operator|=(DDS_CAPS2& left, const DDS_CAPS2& right)
{
    left = left | right;

    return left;
}

}}}

#endif // SCENER_CONTENT_DDS_DDSCAPS2_HPP
