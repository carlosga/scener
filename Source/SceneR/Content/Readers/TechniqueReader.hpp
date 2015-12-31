// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_TECHNIQUEREADER_HPP
#define SCENER_CONTENT_READERS_TECHNIQUEREADER_HPP

#include "SceneR/Content/Readers/ContentTypeReader.hpp"

namespace SceneR { namespace Graphics {

class EffectParameter;
class EffectPass;
class EffectTechnique;

}}

namespace SceneR { namespace Content { namespace Readers {

template <>
class ContentTypeReader<Graphics::EffectTechnique>
{
public:
    ContentTypeReader() = default;
    ~ContentTypeReader() = default;

public:
    auto read(ContentReader* input, const std::string& key, const json11::Json& source) const;

private:
    void read_parameters(ContentReader*             input
                       , const json11::Json&        source
                       , Graphics::EffectTechnique* effect) const;

    void set_parameter_values(ContentReader*             input
                            , const json11::Json&        source
                            , Graphics::EffectTechnique* effect) const;

    void add_default_pass(ContentReader*             input
                        , const json11::Json&        source
                        , Graphics::EffectTechnique* effect) const;

    void read_pass_program(ContentReader*        input
                         , const std::string&    name
                         , Graphics::EffectPass* effectPass) const;

    void cache_parameters(Graphics::EffectTechnique* effect) const;

    void describe_parameter(Graphics::EffectParameter* parameter, const std::int32_t& type) const;
};

}}}

#endif // SCENER_TECHNIQUEREADER_HPP
