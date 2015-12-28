// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SKELETAL_ANIMATION_EARTHSHAKER_HPP
#define SKELETAL_ANIMATION_EARTHSHAKER_HPP

#include <memory>

#include <SceneR/Graphics/DrawableComponent.hpp>
#include <SceneR/Math/Matrix.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Model;
        class StepTime;
    }
}

namespace SceneR
{
    namespace Sample
    {
        class SampleRenderer;

        class EarthShaker : public SceneR::Graphics::DrawableComponent
        {
        public:
            EarthShaker(SampleRenderer* renderer);
            ~EarthShaker() = default;

        public:
            void initialize() override;
            void update(const SceneR::Graphics::StepTime& renderTime) override;
            void draw(const SceneR::Graphics::StepTime& renderTime) override;

        protected:
            void load_content() override;
            void unload_content() override;

        private:
            std::shared_ptr<SceneR::Graphics::Model> _model;
            SceneR::Math::Matrix                     _world;
        };
    }
}

#endif // SKELETAL_ANIMATION_EARTHSHAKER_HPP
