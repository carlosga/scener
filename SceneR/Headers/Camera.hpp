// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Framework/DrawableComponent.hpp>
#include <Framework/Matrix.hpp>

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
            void Initialize() override;
            void Update(const SceneR::Framework::RenderTime& renderTime) override;

        public:
            SceneR::Framework::Matrix View;
            SceneR::Framework::Matrix Projection;

        private:
            float rotation;
        };
    }
}

#endif /* CAMERA_HPP */
