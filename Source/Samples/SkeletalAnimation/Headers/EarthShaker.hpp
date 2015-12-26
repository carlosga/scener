// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EARTHSHAKER_HPP
#define EARTHSHAKER_HPP

#include <memory>

#include <Framework/DrawableComponent.hpp>
#include <Framework/Matrix.hpp>

namespace SceneR
{
    namespace Framework
    {
        class RenderTime;
    }

    namespace Graphics
    {
        class Model;
    }
}

namespace SceneR
{
    namespace Sample
    {
        class SampleRenderer;

        class EarthShaker : public SceneR::Framework::DrawableComponent
        {
        public:
            EarthShaker(SampleRenderer* renderer);
            ~EarthShaker() = default;

        public:
            void initialize() override;
            void update(const SceneR::Framework::RenderTime& renderTime) override;
            void draw(const SceneR::Framework::RenderTime& renderTime) override;

        protected:
            void load_content() override;
            void unload_content() override;

        private:
            std::shared_ptr<SceneR::Graphics::Model> _model;
            SceneR::Framework::Matrix                _world;
        };
    }
}

#endif // EARTHSHAKER_HPP
