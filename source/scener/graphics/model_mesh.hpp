// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_MODEL_MESH_HPP
#define SCENER_GRAPHICS_MODEL_MESH_HPP

#include <memory>
#include <vector>
#include <string>

#include "scener/graphics/model_mesh_part.hpp"
#include "scener/graphics/skeleton.hpp"
#include "scener/graphics/steptime.hpp"
#include "scener/math/bounding_sphere.hpp"
#include "scener/math/basic_matrix.hpp"

namespace scener::content::readers { template <typename T> class content_type_reader; }

namespace scener::graphics
{
    /// Represents a mesh that is part of a Model.
    class model_mesh final
    {
    public:
        /// Gets the BoundingSphere that contains this mesh.
        /// \returns The BoundingSphere that contains this mesh.
        const math::bounding_sphere& bounding_sphere() const noexcept;

        /// Gets the name of this mesh.
        /// \returns The name of this mesh.
        const std::string& name() const noexcept;

        /// Gets the ModelMeshPart objects that make up this mesh. Each part of a mesh is composed of a set of primitives
        /// that share the same material.
        /// \returns the ModelMeshPart objects that make up this mesh.
        const std::vector<std::shared_ptr<model_mesh_part>>& mesh_parts() const noexcept;

        /// Gets the skeleton associated to this mesh.
        /// \returns the skeleton associated to this mesh.
        graphics::skeleton* skeleton() const noexcept;

        /// Updates the model animation and skin state.
        /// \param time snapshot of the rendering timing state.
        void update(const steptime& time) noexcept;

        /// Render a model after applying the given matrix transformations.
        /// \param world the world matrix
        /// \param view the view matrix
        /// \param projection the projection matrix
        void draw(const scener::math::matrix4& world
                , const scener::math::matrix4& view
                , const scener::math::matrix4& projection) noexcept;

        /// Draws all of the ModelMeshPart objects in this mesh.
        void draw() noexcept;

    private:
        std::vector<std::shared_ptr<model_mesh_part>> _mesh_parts      { };
        math::bounding_sphere                         _bounding_sphere { math::vector3::zero(), 0.0f };
        std::shared_ptr<graphics::skeleton>           _skeleton        { nullptr };
        std::string                                   _name            { };

        template <typename T> friend class scener::content::readers::content_type_reader;
    };
}

#endif // SCENER_GRAPHICS_MODEL_MESH_HPP
