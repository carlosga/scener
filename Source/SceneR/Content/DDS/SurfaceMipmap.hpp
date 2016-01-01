// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_SURFACEMIPMAP_HPP
#define SCENER_CONTENT_DDS_SURFACEMIPMAP_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

namespace SceneR { namespace Content { namespace DDS {

class Surface;

class SurfaceMipmap final
{
public:
    typedef std::size_t size_type;
    typedef std::size_t index_type;

public:
    SurfaceMipmap() = default;
    ~SurfaceMipmap() = default;

public:
    index_type index() const noexcept;
    size_type  width() const noexcept;
    size_type  height() const noexcept;
    const std::vector<std::uint8_t>& get_data() const noexcept;

private:
    index_type                _index;
    size_type                 _width;
    size_type                 _height;
    std::vector<std::uint8_t> _data;

    friend class SceneR::Content::DDS::Surface;
};

}}}

#endif // SCENER_CONTENT_DDS_SURFACEMIPMAP_HPP