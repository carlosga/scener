// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_MODELMESHREADER_HPP
#define SCENER_CONTENT_READERS_MODELMESHREADER_HPP

#include "SceneR/Content/Readers/ContentTypeReader.hpp"

namespace SceneR { namespace Graphics {

enum class VertexElementFormat : std::uint32_t;
enum class VertexElementUsage  : std::uint32_t;

class EffectTechnique;
class ModelMesh;

}}

namespace SceneR { namespace Content { namespace GLTF {

enum class AttributeType : std::uint32_t;

}}}

namespace SceneR { namespace Content { namespace Readers {

template<>
class ContentTypeReader<Graphics::ModelMesh>
{
public:
    ContentTypeReader() = default;
    ~ContentTypeReader() = default;

public:
    /**
     * Reads the meshes contents.
     */
    auto read(ContentReader* input, const std::string& key, const json11::Json& source) const noexcept;

private:
    void read_mesh_part(ContentReader* input, const json11::Json& source, Graphics::ModelMesh* mesh) const noexcept;

    std::shared_ptr<Graphics::EffectTechnique> read_material(ContentReader* input, const std::string& key) const noexcept;

    Graphics::VertexElementFormat get_vertex_element_format(GLTF::AttributeType type) const noexcept;

    Graphics::VertexElementUsage get_vertex_element_usage(const std::string& semantic) const noexcept;
};

}}}

#endif  // SCENER_CONTENT_READERS_MODELMESHREADER_HPP
