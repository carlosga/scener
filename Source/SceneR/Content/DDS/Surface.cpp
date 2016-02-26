// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/DDS/Surface.hpp"

#include "SceneR/Content/DDS/Dds.hpp"
#include "SceneR/IO/File.hpp"

namespace scener { namespace content { namespace dds {

using scener::graphics::SurfaceFormat;
using scener::io::FileStream;

void Surface::load(const std::string& filename) noexcept
{
    Expects(scener::io::File::exists(filename));

    FileStream  stream(filename);
    DDS_HEADER  ddsheader;
    std::size_t blockSize = 16;

    Ensures(stream.length() >= sizeof ddsheader);

    stream.read(reinterpret_cast<char*>(&ddsheader), 0, sizeof ddsheader);

    // ensure contents are in DDS format
    Ensures(ddsheader.dwMagic == 0x20534444);

    // ensure required flags are meet
    Ensures((ddsheader.dwFlags & DDS_HEADER_FLAGS::DDSD_PIXELFORMAT) == DDS_HEADER_FLAGS::DDSD_PIXELFORMAT);
    Ensures((ddsheader.dwFlags & DDS_HEADER_FLAGS::DDSD_CAPS)        == DDS_HEADER_FLAGS::DDSD_CAPS);
    Ensures((ddsheader.dwFlags & DDS_HEADER_FLAGS::DDSD_HEIGHT)      == DDS_HEADER_FLAGS::DDSD_HEIGHT);
    Ensures((ddsheader.dwFlags & DDS_HEADER_FLAGS::DDSD_WIDTH)       == DDS_HEADER_FLAGS::DDSD_WIDTH);

    if (ddsheader.dwMipMapCount > 0)
    {
        Ensures((ddsheader.dwFlags & DDS_HEADER_FLAGS::DDSD_MIPMAPCOUNT) == DDS_HEADER_FLAGS::DDSD_MIPMAPCOUNT);
        Ensures((ddsheader.dwFlags & DDS_HEADER_FLAGS::DDSD_LINEARSIZE)  == DDS_HEADER_FLAGS::DDSD_LINEARSIZE);
    }

    // ensure pixel format size is correct
    Ensures(ddsheader.ddspf.dwSize == 32);

    // ensure the texture is in compressed format
    Ensures((ddsheader.ddspf.dwFlags & DDS_PIXELFORMAT_FLAGS::DDPF_FOURCC) == DDS_PIXELFORMAT_FLAGS::DDPF_FOURCC);

    // check DXTn format
    Ensures(ddsheader.ddspf.dwFourCC == DDS_FOURCC::DDSFOURCC_DXT1
         || ddsheader.ddspf.dwFourCC == DDS_FOURCC::DDSFOURCC_DXT3
         || ddsheader.ddspf.dwFourCC == DDS_FOURCC::DDSFOURCC_DXT5);

    // process dds contents
    _height = ddsheader.dwHeight;
    _width  = ddsheader.dwWidth;

    if (ddsheader.ddspf.dwFourCC == DDS_FOURCC::DDSFOURCC_DXT1)
    {
        _format   = SurfaceFormat::dxt1;
        blockSize = 8;
    }
    else if (ddsheader.ddspf.dwFourCC == DDS_FOURCC::DDSFOURCC_DXT3)
    {
        _format = SurfaceFormat::dxt3;
    }
    else if (ddsheader.ddspf.dwFourCC == DDS_FOURCC::DDSFOURCC_DXT5)
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

    _mipmaps.reserve(ddsheader.dwMipMapCount);
    _buffer.reserve(length);

    auto readed = stream.read(reinterpret_cast<char*>(_buffer.data()), 0, length);

    Ensures(readed == length);

    _view = gsl::span<std::uint8_t>(_buffer.data(), static_cast<std::ptrdiff_t>(length));

    for (size_type level = 0; level < ddsheader.dwMipMapCount; ++level)
    {
        auto size = std::max<size_type>(4, mipmapWidth) / 4 * std::max<size_type>(4, mipmapHeight) / 4 * blockSize;
        auto view = _view.subspan(static_cast<std::ptrdiff_t>(position), static_cast<std::ptrdiff_t>(size));

        _mipmaps.push_back({ level, mipmapWidth, mipmapHeight, view });

        mipmapWidth  = std::max<std::size_t>(1, mipmapWidth  >>= 1);
        mipmapHeight = std::max<std::size_t>(1, mipmapHeight >>= 1);

        position += size;
    }
}

SurfaceFormat Surface::format() const noexcept
{
    return _format;
}

Surface::size_type Surface::width() const noexcept
{
    return _width;
}

Surface::size_type Surface::height() const noexcept
{
    return _height;
}

const std::vector<SurfaceMipmap>& Surface::mipmaps() const noexcept
{
    return _mipmaps;
}

}}}
