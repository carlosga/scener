// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_CAPS2_HPP
#define SCENER_CONTENT_DDS_CAPS2_HPP

namespace scener { namespace content {  namespace dds {

/// The caps2 structure defines the capabilities of a DirectDrawSurface object
enum class caps2
{
    cubemap           = 0x200    ///< Required for a cube map.
  , cubemap_positivex = 0x400    ///< Required when these surfaces are stored in a cube map.
  , cubemap_negativex = 0x800    ///< Required when these surfaces are stored in a cube map.
  , cubemap_positivey = 0x1000   ///< Required when these surfaces are stored in a cube map.
  , cubemap_negativey = 0x2000   ///< Required when these surfaces are stored in a cube map.
  , cubemap_positivez = 0x4000   ///< Required when these surfaces are stored in a cube map.
  , cubemap_negativez = 0x8000   ///< Required when these surfaces are stored in a cube map.
  , volume            = 0x200000 ///< Required for a volume texture.
};

inline constexpr caps2 operator&(const caps2& left, const caps2& right)
{
    return static_cast<caps2>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
}

inline constexpr caps2 operator|(const caps2& left, const caps2& right)
{
    return static_cast<caps2>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
}

inline constexpr caps2 operator~(const caps2& value)
{
    return static_cast<caps2>(~static_cast<std::uint32_t>(value));
}

inline constexpr bool operator==(const caps2& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) == right);
}

inline constexpr bool operator!=(const caps2& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) != right);
}

inline caps2& operator&=(caps2& left, const caps2& right)
{
    left = left & right;

    return left;
}

inline caps2& operator|=(caps2& left, const caps2& right)
{
    left = left | right;

    return left;
}

}}}

#endif // SCENER_CONTENT_DDS_CAPS2_HPP
