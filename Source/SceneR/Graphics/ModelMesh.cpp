// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/ModelMesh.hpp>

#include <gsl.h>

#include <Math/Vector3.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/VertexBuffer.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Math::BoundingSphere;
        using SceneR::Math::Vector3;

        const BoundingSphere& ModelMesh::bounding_sphere() const noexcept
        {
            return _bounding_sphere;
        }

        const std::string& ModelMesh::name() const noexcept
        {
            return _name;
        }

        std::vector<EffectTechnique*> ModelMesh::effects() const noexcept
        {
            auto effects = std::vector<EffectTechnique*>(0);

            for (const auto meshPart : _mesh_parts)
            {
                auto effect = meshPart->effect.get();

                Ensures(effect != nullptr);

                effects.push_back(effect);
            }

            return effects;
        }

        const std::vector<std::shared_ptr<ModelMeshPart>>& ModelMesh::mesh_parts() const noexcept
        {
            return _mesh_parts;
        }

        Skeleton* ModelMesh::skeleton() const noexcept
        {
            return _skeleton.get();
        }

        void ModelMesh::draw() noexcept
        {
            for (const auto& meshPart : _mesh_parts)
            {
                auto graphicsDevice = meshPart->vertex_buffer()->graphics_device();

                if (meshPart->effect.get() != nullptr)
                {
                    graphicsDevice->effect = meshPart->effect.get();
                }

                graphicsDevice->index_buffer  = meshPart->index_buffer();
                graphicsDevice->vertex_buffer = meshPart->vertex_buffer();

                graphicsDevice->draw_indexed_primitives(meshPart->primitive_type()
                                                      , meshPart->vertex_offset()
                                                      , 0
                                                      , meshPart->vertex_count()
                                                      , meshPart->start_index()
                                                      , meshPart->primitive_count());
            }
        }
    }
}
