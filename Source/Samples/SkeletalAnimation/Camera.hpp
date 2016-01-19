// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SKELETAL_ANIMATION_CAMERA_HPP
#define SKELETAL_ANIMATION_CAMERA_HPP

#include <SceneR/Graphics/Component.hpp>
#include <SceneR/Math/Matrix.hpp>
#include <SceneR/Math/Vector3.hpp>

namespace SkeletalAnimation {

class SampleRenderer;

class Camera : public SceneR::Graphics::Component
{
public:
    Camera(SampleRenderer* renderer) noexcept;
    ~Camera() override = default;

public:
    void initialize() noexcept override;
    void update(const SceneR::Graphics::StepTime& renderTime) noexcept override;

public:
    SceneR::Math::Matrix view;
    SceneR::Math::Matrix projection;

private:
    SceneR::Math::Vector3 _position;
    SceneR::Math::Matrix  _rotationTransform;
    float                 _rotation;
};

}

#endif // SKELETAL_ANIMATION_CAMERA_HPP
