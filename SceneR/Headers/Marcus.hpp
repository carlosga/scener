// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MARCUS_HPP
#define MARCUS_HPP

#include <memory>

#include <Framework/Matrix.hpp>
#include <Framework/DrawableComponent.hpp>
#include <Graphics/AnimatedModel.hpp>

namespace SceneR
{
    namespace Framework
    {
        class Renderer;
        class RenderTime;
    }
}

namespace SceneR
{
    namespace Sample
    {
        class Marcus : public SceneR::Framework::DrawableComponent
        {
        public:
            Marcus(SceneR::Framework::Renderer& renderer);

            virtual ~Marcus();

        public:
            virtual void Update(const SceneR::Framework::RenderTime& renderTime) override;
            virtual void Draw(const SceneR::Framework::RenderTime& renderTime) override;

        protected:
            virtual void LoadContent() override;
            virtual void UnloadContent() override;

        private:
            std::shared_ptr<SceneR::Graphics::Model>         model;
            std::shared_ptr<SceneR::Graphics::AnimatedModel> animatedModel;
            System::Single                                   rotation;
            SceneR::Framework::Matrix                        world;
            SceneR::Framework::Matrix                        view;
            SceneR::Framework::Matrix                        projection;
        };
    }
}

#endif /* ASTROBOY_HPP */
