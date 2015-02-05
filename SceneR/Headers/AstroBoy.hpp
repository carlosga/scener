// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef ASTROBOY_HPP
#define ASTROBOY_HPP

#include <memory>

#include <Framework/Matrix.hpp>
#include <Framework/DrawableComponent.hpp>

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
    namespace Graphics
    {
        class Model;
    }
}

namespace SceneR
{
    namespace Sample
    {
        class AstroBoy : public SceneR::Framework::DrawableComponent
        {
        public:
            AstroBoy(SceneR::Framework::Renderer& renderer);
            virtual ~AstroBoy();

        public:
            virtual void Update(const SceneR::Framework::RenderTime& renderTime) override;
            virtual void Draw(const SceneR::Framework::RenderTime& renderTime) override;

        protected:
            virtual void LoadContent() override;
            virtual void UnloadContent() override;

        private:
            std::shared_ptr<SceneR::Graphics::Model> model;
            System::Single                           rotation;
            SceneR::Framework::Matrix                world;
            SceneR::Framework::Matrix                view;
            SceneR::Framework::Matrix                projection;
        };
    }
}

#endif /* ASTROBOY_HPP */
