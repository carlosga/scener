// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_TECHNIQUEREADER_HPP
#define SCENER_CONTENT_READERS_TECHNIQUEREADER_HPP

#include "scener/content/readers/content_type_reader.hpp"

namespace scener { namespace graphics {

class effect_parameter;
class effect_pass;
class effect_technique;

}}

namespace scener { namespace content { namespace readers {

template <>
class content_type_reader<graphics::effect_technique>
{
public:
    content_type_reader() = default;

public:
    auto read(content_reader* input, const std::string& key, const json11::Json& source) const noexcept;

private:
    void read_parameters(content_reader* input, const json11::Json& source, graphics::effect_technique* effect) const noexcept;

    void set_parameter_values(content_reader* input, const json11::Json& source, graphics::effect_technique* effect) const noexcept;

    void add_default_pass(content_reader* input, const json11::Json& source, graphics::effect_technique* effect) const noexcept;

    void read_pass_program(content_reader* input, const std::string& name, graphics::effect_pass* effectPass) const noexcept;

    void cache_parameters(graphics::effect_technique* effect) const noexcept;

    void describe_parameter(graphics::effect_parameter* parameter, std::int32_t type) const noexcept;
};

}}}

#endif // SCENER_TECHNIQUEREADER_HPP
