//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef MARCUS_HPP
#define MARCUS_HPP

#include <Framework/DrawableComponent.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Renderer.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/AnimatedModel.hpp>
#include <System/Core.hpp>
#include <memory>

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
            SceneR::Framework::Matrix                        world;
            SceneR::Framework::Matrix                        view;
            SceneR::Framework::Matrix                        projection;
        };
    }
}

#endif /* ASTROBOY_HPP */
