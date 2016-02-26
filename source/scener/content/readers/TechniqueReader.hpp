// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_TECHNIQUEREADER_HPP
#define SCENER_CONTENT_READERS_TECHNIQUEREADER_HPP

#include "SceneR/Content/Readers/ContentTypeReader.hpp"

namespace scener { namespace graphics {

class EffectParameter;
class EffectPass;
class EffectTechnique;

}}

namespace scener { namespace content { namespace readers {

template <>
class ContentTypeReader<graphics::EffectTechnique>
{
public:
    ContentTypeReader() = default;

public:
    auto read(ContentReader* input, const std::string& key, const json11::Json& source) const noexcept;

private:
    void read_parameters(ContentReader* input, const json11::Json& source, graphics::EffectTechnique* effect) const noexcept;

    void set_parameter_values(ContentReader* input, const json11::Json& source, graphics::EffectTechnique* effect) const noexcept;

    void add_default_pass(ContentReader* input, const json11::Json& source, graphics::EffectTechnique* effect) const noexcept;

    void read_pass_program(ContentReader* input, const std::string& name, graphics::EffectPass* effectPass) const noexcept;

    void cache_parameters(graphics::EffectTechnique* effect) const noexcept;

    void describe_parameter(graphics::EffectParameter* parameter, std::int32_t type) const noexcept;
};

}}}

#endif // SCENER_TECHNIQUEREADER_HPP
