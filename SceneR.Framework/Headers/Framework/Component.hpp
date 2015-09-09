// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_COMPONENT_HPP
#define FRAMEWORK_COMPONENT_HPP

#include <cstdint>

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
            virtual ~Component();

        public:
            /**
             * Gets the Renderer associated with this Component.
             */
            SceneR::Framework::Renderer& renderer();

            /**
             * Called when the component should be updated.
             */
            virtual void update(const RenderTime& renderTime) override;

            /**
             * Gets a value indicating whether the component is enabled.
             */
            bool enabled() const override;

            /**
             * Sets a value indicating whether the component is enabled.
             */
            void enabled(const bool& enabled);

            /**
             * Gets the order in which to update this object relative to other objects.
             * @returns the order in which to update this object relative to other objects.
             */
            virtual std::uint32_t update_order() const override;

            /**
             * Sets the order in which to update this object relative to other objects.
             * @param updateOrder the order in which to update this object relative to other objects.
             */
            void update_order(const std::uint32_t& updateOrder);

        protected:
            SceneR::Framework::Renderer& _renderer;

        private:
            bool          _enabled;
            std::uint32_t _update_order;
        };
    }
}

#endif // FRAMEWORK_COMPONENT_HPP
