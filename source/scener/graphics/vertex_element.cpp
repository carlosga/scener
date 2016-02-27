// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vertex_element.hpp"

namespace scener { namespace graphics {

vertex_element::vertex_element(std::size_t           offset
                             , vertex_element_format format
                             , vertex_element_usage  usage
                             , std::uint32_t         usageIndex) noexcept
    : _offset      { offset }
    , _format      { format }
    , _usage       { usage }
    , _usage_index { usageIndex }
{
}

std::size_t vertex_element::offset() const noexcept
{
    return _offset;
}

std::uint32_t vertex_element::usage_index() const noexcept
{
    return _usage_index;
}

vertex_element_format vertex_element::format() const noexcept
{
    return _format;
}

vertex_element_usage vertex_element::usage() const noexcept
{
    return _usage;
}

}}
