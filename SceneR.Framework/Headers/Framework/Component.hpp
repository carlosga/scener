// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <Framework/IComponent.hpp>
#include <Framework/IUpdateable.hpp>

namespace SceneR
{
    namespace Framework
    {
        class Renderer;
        class RenderTime;

        /**
         * Base class for all components.
         */
        class Component : public IComponent, public IUpdateable
        {
        public:
            /**
             * Initializes a new instance of the Component class.
             * @param renderer the renderer that owns the component.
             */
            Component(SceneR::Framework::Renderer& renderer);

            /**
             * Releases all resources being used by this component instance.
             */
            virtual ~Component()
            {
            }

        public:
            /**
             * Gets the Renderer associated with this Component.
             */
            SceneR::Framework::Renderer& Renderer();

            /**
             * Called when the component should be updated.
             */
            virtual void Update(const RenderTime& renderTime) override;

            /**
             * Gets a value indicating whether the component is enabled.
             */
            bool Enabled() const override;

            /**
             * Sets a value indicating whether the component is enabled.
             */
            void Enabled(const bool& enabled);

            /**
             * Gets the order in which to update this object relative to other objects.
             * @returns the order in which to update this object relative to other objects.
             */
            virtual System::UInt32 UpdateOrder() const override;

            /**
             * Sets the order in which to update this object relative to other objects.
             * @param updateOrder the order in which to update this object relative to other objects.
             */
            void UpdateOrder(const System::UInt32& updateOrder);

        protected:
            SceneR::Framework::Renderer& renderer;

        private:
            bool           enabled;
            System::UInt32 updateOrder;
        };
    }
}

#endif /* COMPONENT_HPP */
