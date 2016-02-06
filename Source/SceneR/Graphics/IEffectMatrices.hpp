// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IEFFECTMATRICES_HPP
#define SCENER_GRAPHICS_IEFFECTMATRICES_HPP

namespace SceneR { namespace Math { struct Matrix; } }

namespace SceneR { namespace Graphics {

/// Gets or sets transformation matrix parameters for the current effect.
class IEffectMatrices
{
public:
    /// Release all resource being used by the current IIEffectMatrices instance
    virtual ~IEffectMatrices() = default;

public:
    /// Gets the projection matrix in the current effect.
    /// \returns the projection transformation matrix.
    virtual const SceneR::Math::Matrix& projection() const noexcept = 0;

    /// Sets the projection matrix in the current effect.
    /// \param projection the projection transformation matrix.
    virtual void projection(const SceneR::Math::Matrix& projection) noexcept = 0;

    /// Gets the view matrix in the current effect.
    /// \returns the view transformation matrix.
    virtual const SceneR::Math::Matrix& view() const noexcept = 0;

    /// Sets the view matrix in the current effect.
    /// \param view the view transformation matrix.
    virtual void view(const SceneR::Math::Matrix& view) noexcept = 0;

    /// Gets the world matrix in the current effect.
    /// \returns the world transformation matrix.
    virtual const SceneR::Math::Matrix& world() const noexcept = 0;

    /// Sets the world matrix in the current effect.
    /// \param world the world transformation matrix.
    virtual void world(const SceneR::Math::Matrix& world) noexcept = 0;
};

}}

#endif // SCENER_GRAPHICS_IEFFECTMATRICES_HPP
