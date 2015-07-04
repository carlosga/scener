// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef DRAWABLECOMPONENT_HPP
#define DRAWABLECOMPONENT_HPP

#include <System/Core.hpp>
#include <Framework/IDrawable.hpp>
#include <Framework/Component.hpp>
#include <Graphics/GraphicsDevice.hpp>

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
            DrawableComponent(SceneR::Framework::Renderer& renderer);

            /**
             * Releases all resources being used by this DrawableComponent.
             */
            virtual ~DrawableComponent()
            {
            }

        public:
            /**
             * The GraphicsDevice the DrawableComponent is associated with.
             */
            SceneR::Graphics::GraphicsDevice& CurrentGraphicsDevice();

            /**
             * Called when the component should be drawn.
             */
            virtual void Draw(const RenderTime& renderTime) override;

            /**
             * Gets a value indicating whether this object is enabled.
             */
            virtual bool Visible() const override;

            /**
             * Sets a value indicating whether this object is enabled.
             * @param visible a value indicating whether this object is enabled.
             */
            virtual void Visible(const bool& visible);

            /**
             * The order in which to draw this object relative to other objects.
             */
            virtual uint32_t DrawOrder() const override;

            /**
             * The order in which to draw this object relative to other objects.
             */
            void DrawOrder(const uint32_t& drawOrder);

            /**
             * Called when the component should be initialized.
             * This method can be used for tasks like querying for
             * services the component needs and setting up non-graphics resources.
             */
            virtual void Initialize() override;

        protected:
            virtual void LoadContent();
            virtual void UnloadContent();

        private:
            bool     visible;
            uint32_t drawOrder;
        };
    }
}

#endif /* DRAWABLECOMPONENT_HPP */
