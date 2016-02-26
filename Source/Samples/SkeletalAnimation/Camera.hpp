// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SKELETAL_ANIMATION_CAMERA_HPP
#define SKELETAL_ANIMATION_CAMERA_HPP

#include <nod/nod.hpp>

#include <SceneR/Graphics/Component.hpp>
#include <scener/math/angle.hpp>
#include <scener/math/matrix.hpp>
#include <scener/math/vector.hpp>

namespace SkeletalAnimation {

class SampleRenderer;

class Camera : public scener::graphics::Component
{
public:
    Camera(SampleRenderer* renderer) noexcept;
    ~Camera() override = default;

public:
    void initialize() noexcept override;
    void update(const scener::graphics::StepTime& renderTime) noexcept override;

private:
    void update_projection() noexcept;

public:
    scener::math::matrix4   view;
    scener::math::matrix4   projection;

private:
    scener::math::vector3  _position;
    scener::math::matrix4  _rotationTransform;
    scener::math::degrees  _rotation;
    nod::scoped_connection _resize_connection;
};

}

#endif // SKELETAL_ANIMATION_CAMERA_HPP
