// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SAMPLEMODEL_HPP
#define SAMPLEMODEL_HPP

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

        class SampleModel : public SceneR::Framework::DrawableComponent
        {
        public:
            SampleModel(SampleRenderer& renderer);
            ~SampleModel() = default;

        public:
            void Draw(const SceneR::Framework::RenderTime& renderTime) override;

        protected:
            void Initialize() override;
            void LoadContent() override;
            void UnloadContent() override;

        private:
            std::shared_ptr<SceneR::Graphics::Model> model;
            SceneR::Framework::Matrix                world;
        };
    }
}

#endif /* SAMPLEMODEL_HPP */
