// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_TECHNIQUE_READER_HPP
#define SCENER_CONTENT_READERS_TECHNIQUE_READER_HPP

#include "scener/content/readers/content_type_reader.hpp"

namespace scener::graphics
{
    class effect_parameter;
    class effect_pass;
    class effect_technique;
}

namespace scener::content::readers
{
    template <>
    class content_type_reader<graphics::effect_technique>
    {
    public:
        content_type_reader() = default;

    public:
        auto read(content_reader* input, const std::string& key, const nlohmann::json& value) const noexcept;

    private:
        void read_parameters(content_reader* input, const nlohmann::json& value, graphics::effect_technique* effect) const noexcept;

        void set_parameter_values(content_reader* input, const nlohmann::json& value, graphics::effect_technique* effect) const noexcept;

        void add_default_pass(content_reader* input, const nlohmann::json& value, graphics::effect_technique* effect) const noexcept;

        void read_pass_program(content_reader* input, const std::string& name, graphics::effect_pass* pass) const noexcept;

        void cache_parameters(graphics::effect_technique* technique) const noexcept;

        void describe_parameter(graphics::effect_parameter* parameter, std::int32_t type) const noexcept;
    };
}

#endif // SCENER_CONTENT_READERS_TECHNIQUE_READER_HPP
