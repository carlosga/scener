// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MARCUS_HPP
#define MARCUS_HPP

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

        class Marcus : public SceneR::Framework::DrawableComponent
        {
        public:
            Marcus(SampleRenderer& renderer);
            ~Marcus() = default;

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

#endif /* MARCUS_HPP */
