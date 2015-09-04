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
            void Initialize() override;
            void Update(const SceneR::Framework::RenderTime& renderTime) override;
            void Draw(const SceneR::Framework::RenderTime& renderTime) override;

        protected:
            void LoadContent() override;
            void UnloadContent() override;

        private:
            std::shared_ptr<SceneR::Graphics::Model> model;
            SceneR::Framework::Matrix                world;
        };
    }
}

#endif /* MARCUS_HPP */
