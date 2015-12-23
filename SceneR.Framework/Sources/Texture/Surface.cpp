// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Texture/Surface.hpp>

#include <gsl.h>

#include <System/Math.hpp>
#include <System/IO/BinaryReader.hpp>
#include <System/IO/File.hpp>
#include <System/IO/FileStream.hpp>
#include <System/IO/MemoryStream.hpp>
#include <Texture/Dds.hpp>

namespace SceneR
{
    namespace Texture
    {
        using namespace SceneR::DDS;
        using SceneR::Graphics::SurfaceFormat;
        using System::Math;
        using System::IO::BinaryReader;
        using System::IO::FileStream;
        using System::IO::MemoryStream;

        void Surface::load(const std::string& filename)
        {
            Expects(System::IO::File::exists(filename));

            auto         buffer = read_file(filename);
            MemoryStream stream(gsl::as_span(buffer));
            BinaryReader reader(stream);
            DDS_HEADER   ddsheader;
            std::size_t  blockSize = 16;

            Ensures(stream.length() >= 128);

            auto rawHeader = reader.read_bytes(128);

            std::copy_n(rawHeader.begin(), 128, ddsheader.data);

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
                _format   = SurfaceFormat::Dxt1;
                blockSize = 8;
            }
            else if (ddsheader.ddspf.dwFourCC == DDS_FOURCC::DDSFOURCC_DXT3)
            {
                _format = SurfaceFormat::Dxt3;
            }
            else if (ddsheader.ddspf.dwFourCC == DDS_FOURCC::DDSFOURCC_DXT5)
            {
                _format = SurfaceFormat::Dxt5;
            }

            auto mipmapWidth  = _width;
            auto mipmapHeight = _height;

            for (std::size_t level = 0; level < ddsheader.dwMipMapCount; level++)
            {
                SurfaceMipmap mipmap;
                std::size_t   size = Math::max(4, mipmapWidth) / 4 * Math::max(4, mipmapHeight) / 4 * blockSize;

                mipmap._index  = level;
                mipmap._width  = mipmapWidth;
                mipmap._height = mipmapHeight;
                mipmap._data   = reader.read_bytes(size);

                _mipmaps.push_back(mipmap);

                mipmapWidth  = Math::max(1, mipmapWidth  >>= 1);
                mipmapHeight = Math::max(1, mipmapHeight >>= 1);
            }
        }

        const SceneR::Graphics::SurfaceFormat& Surface::format() const noexcept
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

        std::vector<uint8_t> Surface::read_file(const std::string& filename) const noexcept
        {
            FileStream   stream(filename);
            BinaryReader reader(stream);

            return reader.read_bytes(stream.length());
        }
    }
}
