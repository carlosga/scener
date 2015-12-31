// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_DDSFOURCC_HPP
#define SCENER_CONTENT_DDS_DDSFOURCC_HPP

#include <cstdint>

namespace SceneR { namespace Content { namespace DDS {

enum class DDS_FOURCC : std::uint32_t
{
    DDSFOURCC_DXT1 = 0x31545844
  , DDSFOURCC_DXT2 = 0x32545844
  , DDSFOURCC_DXT3 = 0x33545844
  , DDSFOURCC_DXT4 = 0x34545844
  , DDSFOURCC_DXT5 = 0x35545844
};

}}}

#endif // SCENER_CONTENT_DDS_DDSFOURCC_HPP
