// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Framework/DrawableComponent.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Sample
    {
        class SampleRenderer;

        class Camera : public SceneR::Framework::Component
        {
        public:
            Camera(SampleRenderer& renderer);
            ~Camera() = default;

        public:
            void initialize() override;
            void update(const SceneR::Framework::RenderTime& renderTime) override;

        public:
            SceneR::Framework::Matrix view;
            SceneR::Framework::Matrix projection;

        private:
            SceneR::Framework::Vector3 _position;
            SceneR::Framework::Matrix  _rotationTransform;
            float                      _rotation;
        };
    }
}

#endif  // CAMERA_HPP
