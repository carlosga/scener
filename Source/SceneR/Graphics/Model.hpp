// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_MODEL_HPP
#define SCENER_GRAPHICS_MODEL_HPP

#include <memory>
#include <string>
#include <vector>

namespace SceneR { namespace Content { class ContentReader; } }

namespace SceneR { namespace Math { struct Matrix; } }

namespace SceneR { namespace Graphics {

class  ModelMesh;
struct StepTime;

/// Represents a 3D model composed of multiple ModelMesh objects which may be moved independently.
class Model final
{
public:
    /// Initializes a new instance of the Model class.
    Model() noexcept;

public:
    /// Gets the model name.
    /// \returns the model name.
    const std::string& name() const noexcept;

    /// Gets a collection of ModelMesh objects which compose the model.
    /// Each ModelMesh in a model may be moved independently and may be
    /// composed of multiple materials identified as ModelMeshPart objects.
    /// \returns the ModelMesh objects used by this model.
    const std::vector<std::shared_ptr<ModelMesh>>& meshes() const noexcept;

    /// Updates the model animation and skin state.
    /// \param elapsedtime snapshot of the rendering timing state.
    void update(const StepTime& elapsedtime) noexcept;

    /// Render a model after applying the given matrix transformations.
    /// \param world the world matrix
    /// \param view the view matrix
    /// \param projection the projection matrix
    void draw(const SceneR::Math::Matrix& world
            , const SceneR::Math::Matrix& view
            , const SceneR::Math::Matrix& projection) noexcept;

private:
    std::vector<std::shared_ptr<ModelMesh>> _meshes;
    std::string                             _name;

    friend class SceneR::Content::ContentReader;
};

}}

#endif // SCENER_GRAPHICS_MODEL_HPP
