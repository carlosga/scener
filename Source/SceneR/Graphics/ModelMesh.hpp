// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_MODELMESH_HPP
#define SCENER_GRAPHICS_MODELMESH_HPP

#include <memory>
#include <vector>
#include <string>

#include "SceneR/Graphics/Skeleton.hpp"
#include "SceneR/Math/BoundingSphere.hpp"

namespace SceneR { namespace Content { namespace Readers { template <typename T> class ContentTypeReader; } } }

namespace SceneR { namespace Graphics {

class EffectTechnique;
class ModelMeshPart;

/// Represents a mesh that is part of a Model.
class ModelMesh final
{
public:
    /// Initializes a new instance of the ModelMesh class.
    ModelMesh() = default;

public:
    /// Gets the BoundingSphere that contains this mesh.
    /// \returns The BoundingSphere that contains this mesh.
    const SceneR::Math::BoundingSphere& bounding_sphere() const noexcept;

    /// Gets the name of this mesh.
    /// \returns The name of this mesh.
    const std::string& name() const noexcept;

    /// Gets a collection of effects associated with this mesh.
    /// ModelMesh.Effects is a collection of all the Effect properties of the for the MeshParts of this ModelMesh.
    /// Each ModelMeshPart has a single Effect which is a reference to one of the Effects of the parent ModelMesh
    /// property. By updating all the effects of the ModelMesh all of the effects of each ModelMeshPart are updated
    /// as well.
    /// \returns a collection of effects associated with this mesh.
    std::vector<EffectTechnique*> effects() const noexcept;

    /// Gets the ModelMeshPart objects that make up this mesh. Each part of a mesh is composed of a set of primitives
    /// that share the same material.
    /// \returns the ModelMeshPart objects that make up this mesh.
    const std::vector<std::shared_ptr<ModelMeshPart>>& mesh_parts() const noexcept;

    /// Gets the skeleton associated to this mesh.
    /// \returns the skeleton associated to this mesh.
    Skeleton* skeleton() const noexcept;

public:
    /// Draws all of the ModelMeshPart objects in this mesh.
    void draw() noexcept;

private:
    std::vector<std::shared_ptr<ModelMeshPart>> _mesh_parts      { };
    SceneR::Math::BoundingSphere                _bounding_sphere { SceneR::Math::Vector3::zero, 0.0f };
    std::shared_ptr<Skeleton>                   _skeleton        { nullptr };
    std::string                                 _name            { };

    template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_MODELMESH_HPP
