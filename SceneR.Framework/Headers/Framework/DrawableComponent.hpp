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

#ifndef DRAWABLECOMPONENT_HPP
#define DRAWABLECOMPONENT_HPP

#include <Framework/Component.hpp>
#include <Framework/IDrawable.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;
    }
}

namespace SceneR
{
    namespace Framework
    {
        class Renderer;
        class RenderTime;

        /**
         * A component that is notified when it needs to draw itself.
         */
        class DrawableComponent : public Component, public IDrawable
        {
        public:
            /**
             * Initializes a new instance of the DrawableComponent class.
             */
            DrawableComponent(Renderer& renderer);

        public:
            /**
             * The GraphicsDevice the DrawableComponent is associated with.
             */
            SceneR::Graphics::GraphicsDevice& GetGraphicsDevice();

            /**
             * Called when the component should be drawn.
             */
            virtual void Draw(const RenderTime& renderTime) override;

            /**
             * Enables object updates.
             */
            void Show();

            /**
             * Disables Object udaptes.
             */
            void Hide();

            /**
             * Gets a value indicating whether this object is enabled.
             */
            virtual const System::Boolean& IsVisible() const override;

            /**
             * The order in which to draw this object relative to other objects.
             */
            virtual const System::UInt32& DrawOrder() const override;

            /**
             * The order in which to draw this object relative to other objects.
             */
            virtual void DrawOrder(const System::UInt32& drawOrder);

            /**
             * Called when the component should be initialized.
             * This method can be used for tasks like querying for services the component needs and setting up non-graphics resources.
             */
            virtual void Initialize() override;

        protected:
            virtual void LoadContent() ;
            virtual void UnloadContent();

        private:
            System::Boolean visible;
            System::UInt32  drawOrder;
        };
    }
}

#endif /* DRAWABLECOMPONENT_HPP */
