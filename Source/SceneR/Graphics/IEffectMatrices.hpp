// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IEFFECTMATRICES_HPP
#define SCENER_GRAPHICS_IEFFECTMATRICES_HPP

namespace SceneR { namespace Math { struct Matrix; } }

namespace SceneR { namespace Graphics {

/**
 * Defines the transformation matrices for the current effect.
 */
class IEffectMatrices
{
public:
    /**
     * Release all resource being used by the current IIEffectMatrices instance
     */
    virtual ~IEffectMatrices() = default;

public:
    /**
     * Gets the projection matrix in the current effect.
     */
    virtual const SceneR::Math::Matrix& projection() const = 0;

    /**
     * Sets the projection matrix in the current effect.
     */
    virtual void projection(const SceneR::Math::Matrix& projection) = 0;

    /**
     * Gets the view matrix in the current effect.
     */
    virtual const SceneR::Math::Matrix& view() const = 0;

    /**
     * Sets the view matrix in the current effect.
     */
    virtual void view(const SceneR::Math::Matrix& view) = 0;

    /**
     * Gets the world matrix in the current effect.
     */
    virtual const SceneR::Math::Matrix& world() const = 0;

    /**
     * Sets the world matrix in the current effect.
     */
    virtual void world(const SceneR::Math::Matrix& world) = 0;
};

}}

#endif // SCENER_GRAPHICS_IEFFECTMATRICES_HPP
