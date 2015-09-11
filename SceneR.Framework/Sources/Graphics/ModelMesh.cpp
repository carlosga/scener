// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/ModelMesh.hpp>

#include <Framework/Vector3.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/VertexBuffer.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::BoundingSphere;
        using SceneR::Framework::Vector3;

        ModelMesh::ModelMesh()
            : _name            { }
            , _mesh_parts      ( 0 )
            , _parent_bone     { nullptr }
            , _bounding_sphere { Vector3::zero, 0.0f }
        {
        }

        ModelMesh::~ModelMesh()
        {
        }

        const BoundingSphere& ModelMesh::bounding_sphere() const
        {
            return _bounding_sphere;
        }

        const std::u16string& ModelMesh::name() const
        {
            return _name;
        }

        std::vector<std::shared_ptr<EffectMaterial>> ModelMesh::effects() const
        {
            auto effects = std::vector<std::shared_ptr<EffectMaterial>>(0);

            for (const auto& meshPart : _mesh_parts)
            {
                if (meshPart->effect.get() != nullptr)
                {
                    effects.push_back(meshPart->effect);
                }
            }

            return effects;
        }

        const std::vector<std::shared_ptr<ModelMeshPart>>& ModelMesh::mesh_parts() const
        {
            return _mesh_parts;
        }

        const std::shared_ptr<ModelBone>& ModelMesh::parent_bone() const
        {
            return _parent_bone;
        }

        void ModelMesh::draw()
        {
            for (const auto& meshPart : _mesh_parts)
            {
                auto& graphicsDevice = meshPart->vertex_buffer()->graphics_device();

                if (meshPart->effect.get() != nullptr)
                {
                    graphicsDevice.effect = meshPart->effect;
                }

                graphicsDevice.index_buffer  = meshPart->index_buffer();
                graphicsDevice.vertex_buffer = meshPart->vertex_buffer();

                graphicsDevice.draw_indexed_primitives(meshPart->primitive_type()
                                                     , meshPart->vertex_offset()
                                                     , 0
                                                     , meshPart->vertex_count()
                                                     , meshPart->start_index()
                                                     , meshPart->primitive_count());
            }
        }
    }
}
