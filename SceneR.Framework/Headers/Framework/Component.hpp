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

#include <Framework/Core.hpp>
#include <Framework/IComponent.hpp>
#include <Framework/IUpdateable.hpp>

namespace SceneR
{
    namespace Framework
    {
        class Renderer;

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
            Component(Renderer& renderer);

            /**
             * Releases all resources being used by this component instance.
             */
            virtual ~Component()
            {
            };

        public:
            /**
             * Called when the component should be updated.
             */
            virtual void Update(/* GameTime gameTime */) override;

            /**
             * Enables object updates.
             */
            void Enable();

            /**
             * Disables Object udaptes.
             */
            void Disable();

            /**
             * Gets a value indicating whether this object is enabled.
             */
            virtual const Boolean& IsEnabled()  const override;

            /**
             * Gets the order in which to update this object relative to other objects.
             * @returns the order in which to update this object relative to other objects.
             */
            virtual const UInt32& GetUpdateOrder()  const override;

            /**
             * Sets the order in which to update this object relative to other objects.
             * @param updateOrder the order in which to update this object relative to other objects.
             */
            virtual void SetUpdateOrder(const UInt32& updateOrder);

        protected:
            Renderer& renderer;

        private:
            Boolean enabled;
            UInt32  updateOrder;
        };
    }
}

#endif /* COMPONENT_HPP */
