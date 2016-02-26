// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/dds/surface.hpp"

#include "scener/content/dds/header.hpp"
#include "scener/io/file.hpp"

namespace scener { namespace content { namespace dds {

using scener::graphics::SurfaceFormat;
using scener::io::file_stream;

void surface::load(const std::string& filename) noexcept
{
    Expects(scener::io::file::exists(filename));

    file_stream  stream(filename);
    header      ddsheader;
    std::size_t blockSize = 16;

    Ensures(stream.length() >= sizeof ddsheader);

    stream.read(reinterpret_cast<char*>(&ddsheader), 0, sizeof ddsheader);

    // ensure contents are in DDS format
    Ensures(ddsheader.magic == 0x20534444);

    // ensure required flags are meet
    Ensures((ddsheader.flags & header_flags::pixelformat) == header_flags::pixelformat);
    Ensures((ddsheader.flags & header_flags::caps)        == header_flags::caps);
    Ensures((ddsheader.flags & header_flags::height)      == header_flags::height);
    Ensures((ddsheader.flags & header_flags::width)       == header_flags::width);

    if (ddsheader.mipmap_count > 0)
    {
        Ensures((ddsheader.flags & header_flags::mipmapcount) == header_flags::mipmapcount);
        Ensures((ddsheader.flags & header_flags::linearsize)  == header_flags::linearsize);
    }

    // ensure pixel format size is correct
    Ensures(ddsheader.pixel_format.size == 32);

    // ensure the texture is in compressed format
    Ensures((ddsheader.pixel_format.flags & pixel_format_flags::fourcc) == pixel_format_flags::fourcc);

    // check DXTn format
    Ensures(ddsheader.pixel_format.fourcc == fourcc::dxt1
         || ddsheader.pixel_format.fourcc == fourcc::dxt3
         || ddsheader.pixel_format.fourcc == fourcc::dxt5);

    // process dds contents
    _height = ddsheader.height;
    _width  = ddsheader.width;

    if (ddsheader.pixel_format.fourcc == fourcc::dxt1)
    {
        _format   = SurfaceFormat::dxt1;
        blockSize = 8;
    }
    else if (ddsheader.pixel_format.fourcc == fourcc::dxt3)
    {
        _format = SurfaceFormat::dxt3;
    }
    else if (ddsheader.pixel_format.fourcc == fourcc::dxt5)
    {
        _format = SurfaceFormat::dxt5;
    }

    auto mipmapWidth  = _width;
    auto mipmapHeight = _height;
    auto position     = size_type { 0 };
    auto length       = stream.length() - sizeof ddsheader;

    _mipmaps.clear();
    _buffer.clear();
    _view = { };

    _mipmaps.reserve(ddsheader.mipmap_count);
    _buffer.reserve(length);

    auto readed = stream.read(reinterpret_cast<char*>(_buffer.data()), 0, length);

    Ensures(readed == length);

    _view = gsl::span<std::uint8_t>(_buffer.data(), static_cast<std::ptrdiff_t>(length));

    for (size_type level = 0; level < ddsheader.mipmap_count; ++level)
    {
        auto size = std::max<size_type>(4, mipmapWidth) / 4 * std::max<size_type>(4, mipmapHeight) / 4 * blockSize;
        auto view = _view.subspan(static_cast<std::ptrdiff_t>(position), static_cast<std::ptrdiff_t>(size));

        _mipmaps.push_back({ level, mipmapWidth, mipmapHeight, view });

        mipmapWidth  = std::max<std::size_t>(1, mipmapWidth  >>= 1);
        mipmapHeight = std::max<std::size_t>(1, mipmapHeight >>= 1);

        position += size;
    }
}

SurfaceFormat surface::format() const noexcept
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
