// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_MODELMESHREADER_HPP
#define SCENER_CONTENT_READERS_MODELMESHREADER_HPP

#include "SceneR/Content/Readers/ContentTypeReader.hpp"

namespace scener { namespace graphics {

enum class VertexElementFormat : std::uint32_t;
enum class VertexElementUsage  : std::uint32_t;

class EffectTechnique;
class ModelMesh;
class ModelMeshPart;

}}

namespace scener { namespace content { namespace gltf { enum class AttributeType : std::uint32_t; } } }

namespace scener { namespace content { namespace readers {

template<>
class ContentTypeReader<graphics::ModelMesh>
{
public:
    ContentTypeReader() = default;

public:
    auto read(ContentReader* input, const std::string& key, const json11::Json& source) const noexcept;

private:
    std::shared_ptr<graphics::ModelMeshPart> read_mesh_part(ContentReader* input, const json11::Json& source) const noexcept;

    std::shared_ptr<graphics::EffectTechnique> read_material(ContentReader* input, const std::string& key) const noexcept;

    graphics::VertexElementFormat get_vertex_element_format(gltf::AttributeType type) const noexcept;

    graphics::VertexElementUsage get_vertex_element_usage(const std::string& semantic) const noexcept;
};

}}}

#endif  // SCENER_CONTENT_READERS_MODELMESHREADER_HPP
