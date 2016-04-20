// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/dds/surface.hpp"

#include "scener/content/dds/header.hpp"
#include "scener/io/file.hpp"

namespace scener { namespace content { namespace dds {

using scener::graphics::surface_format;
using scener::io::file_stream;

void surface::load(const std::string& filename) noexcept
{
    Expects(scener::io::file::exists(filename));

    file_stream stream(filename);
    header      dds_header;
    std::size_t block_size = 16;

    Ensures(stream.length() >= sizeof dds_header);

    stream.read(reinterpret_cast<char*>(&dds_header), 0, sizeof dds_header);

    // ensure contents are in DDS format
    Ensures(dds_header.magic == 0x20534444);

    // ensure required flags are meet
    Ensures((dds_header.flags & header_flags::pixelformat) == header_flags::pixelformat);
    Ensures((dds_header.flags & header_flags::caps)        == header_flags::caps);
    Ensures((dds_header.flags & header_flags::height)      == header_flags::height);
    Ensures((dds_header.flags & header_flags::width)       == header_flags::width);

    if (dds_header.mipmap_count > 0)
    {
        Ensures((dds_header.flags & header_flags::mipmapcount) == header_flags::mipmapcount);
        Ensures((dds_header.flags & header_flags::linearsize)  == header_flags::linearsize);
    }

    // ensure pixel format size is correct
    Ensures(dds_header.pixel_format.size == 32);

    // ensure the texture is in compressed format
    Ensures((dds_header.pixel_format.flags & pixel_format_flags::fourcc) == pixel_format_flags::fourcc);

    // check DXTn format
    Ensures(dds_header.pixel_format.fourcc == fourcc::dxt1
         || dds_header.pixel_format.fourcc == fourcc::dxt3
         || dds_header.pixel_format.fourcc == fourcc::dxt5);

    // process dds contents
    _height = dds_header.height;
    _width  = dds_header.width;

    if (dds_header.pixel_format.fourcc == fourcc::dxt1)
    {
        _format   = surface_format::dxt1;
        block_size = 8;
    }
    else if (dds_header.pixel_format.fourcc == fourcc::dxt3)
    {
        _format = surface_format::dxt3;
    }
    else if (dds_header.pixel_format.fourcc == fourcc::dxt5)
    {
        _format = surface_format::dxt5;
    }

    auto mipmap_width  = _width;
    auto mipmap_height = _height;
    auto position      = size_type { 0 };
    auto length        = stream.length() - sizeof dds_header;

    _mipmaps.clear();
    _buffer.clear();
    _view = { };

    _mipmaps.reserve(dds_header.mipmap_count);
    _buffer.reserve(length);

    auto readed = stream.read(reinterpret_cast<char*>(_buffer.data()), 0, length);

    Ensures(readed == length);

    _view = gsl::span<std::uint8_t>(_buffer.data(), static_cast<std::ptrdiff_t>(length));

    for (size_type level = 0; level < dds_header.mipmap_count; ++level)
    {
        auto size = std::max<size_type>(4, mipmap_width) / 4 * std::max<size_type>(4, mipmap_height) / 4 * block_size;
        auto view = _view.subspan(static_cast<std::ptrdiff_t>(position), static_cast<std::ptrdiff_t>(size));

        _mipmaps.push_back({ level, mipmap_width, mipmap_height, view });

        mipmap_width  = std::max<std::size_t>(1, mipmap_width  >>= 1);
        mipmap_height = std::max<std::size_t>(1, mipmap_height >>= 1);

        position += size;
    }
}

surface_format surface::format() const noexcept
{
    return _format;
}

surface::size_type surface::width() const noexcept
{
    return _width;
}

surface::size_type surface::height() const noexcept
{
    return _height;
}

const std::vector<surface_mipmap>& surface::mipmaps() const noexcept
{
    return _mipmaps;
}

}}}
