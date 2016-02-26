// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_MODEL_HPP
#define SCENER_GRAPHICS_MODEL_HPP

#include <memory>
#include <string>
#include <vector>

#include "scener/math/basic_matrix.hpp"

namespace scener { namespace content { class content_reader; } }

namespace scener { namespace graphics {

class  model_mesh;
struct steptime;

/// Represents a 3D model composed of multiple ModelMesh objects which may be moved independently.
class model final
{
public:
    /// Initializes a new instance of the Model class.
    model() noexcept;

public:
    /// Gets the model name.
    /// \returns the model name.
    const std::string& name() const noexcept;

    /// Gets a collection of ModelMesh objects which compose the model.
    /// Each ModelMesh in a model may be moved independently and may be
    /// composed of multiple materials identified as ModelMeshPart objects.
    /// \returns the ModelMesh objects used by this model.
    const std::vector<std::shared_ptr<model_mesh>>& meshes() const noexcept;

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

private:
    std::vector<std::shared_ptr<model_mesh>> _meshes;
    std::string                             _name;

    friend class scener::content::content_reader;
};

}}

#endif // SCENER_GRAPHICS_MODEL_HPP
