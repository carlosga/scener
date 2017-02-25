// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_SURFACE_MIPMAP_HPP
#define SCENER_CONTENT_DDS_SURFACE_MIPMAP_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include <gsl/gsl>

namespace scener::content::dds
{
    /// Represents a DirectDraw surface mipmap.
    class surface_mipmap final
    {
        typedef std::size_t index_type;
        typedef std::size_t size_type;

    public:
        /// Initializes a new instance of the SurfaceMipmap class.
        /// \param index  The mipmap index.
        /// \param width  The mipmap width (in pixels).
        /// \param height The mipmap height (in pixels).
        /// \param view   A view to the mipmap data.
        surface_mipmap(index_type index, size_type width, size_type height, const gsl::span<std::uint8_t>& view) noexcept;

    public:
        /// Gets the mipmap index.
        index_type index() const noexcept;

        /// Gets the mipmap width (in pixels).
        size_type  width() const noexcept;

        /// Gets the mipmap height (in pixels).
        size_type  height() const noexcept;

        /// Gets a view to the mipmap data.
        const gsl::span<std::uint8_t>& get_view() const noexcept;

    private:
        index_type              _index;
        size_type               _width;
        size_type               _height;
        gsl::span<std::uint8_t> _view;
    };
}

#endif // SCENER_CONTENT_DDS_SURFACE_MIPMAP_HPP
