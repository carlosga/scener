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

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <System/Core.hpp>
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
            virtual ~Component() = default;

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
            const System::Boolean& Enabled() const override;

            /**
             * Sets a value indicating whether the component is enabled.
             */
            void Enabled(const System::Boolean& enabled);

            /**
             * Gets the order in which to update this object relative to other objects.
             * @returns the order in which to update this object relative to other objects.
             */
            virtual const System::UInt32& UpdateOrder() const override;

            /**
             * Sets the order in which to update this object relative to other objects.
             * @param updateOrder the order in which to update this object relative to other objects.
             */
            void UpdateOrder(const System::UInt32& updateOrder);

        protected:
            SceneR::Framework::Renderer& renderer;

        private:
            System::Boolean enabled;
            System::UInt32  updateOrder;
        };
    }
}

#endif /* COMPONENT_HPP */
