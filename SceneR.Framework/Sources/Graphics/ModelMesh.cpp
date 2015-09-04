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
            : name             { }
            , tag              { }
            , _mesh_parts      ( 0 )
            , _parent_bone     { nullptr }
            , _bounding_sphere { Vector3::Zero, 0.0f }
        {
        }

        ModelMesh::~ModelMesh()
        {
        }

        const BoundingSphere& ModelMesh::bounding_sphere() const
        {
            return _bounding_sphere;
        }

        std::vector<std::shared_ptr<Effect>> ModelMesh::effects() const
        {
            auto effects = std::vector<std::shared_ptr<Effect>>(0);

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

                graphicsDevice.vertex_buffer = meshPart->vertex_buffer();
                graphicsDevice.index_buffer  = meshPart->index_buffer();

                graphicsDevice.draw_indexed_primitives(PrimitiveType::TriangleList
                                                     , meshPart->vertex_offset()
                                                     , 0
                                                     , meshPart->vertex_count()
                                                     , meshPart->start_index()
                                                     , meshPart->primitive_count());
            }
        }
    }
}
