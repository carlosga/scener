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

#ifndef IUPDATEABLE_HPP
#define IUPDATEABLE_HPP

#include <System/Core.hpp>

namespace SceneR
{
	namespace Framework
	{
	    class RenderTime;

	    /**
	     * Defines an interface for a component that should be updated in Renderer.Update.
	     */
		class IUpdateable
		{
        public:
		    /**
		     * Releases all resources being used by this IUpdateable instance.
		     */
            virtual ~IUpdateable()
            {
            };

		public:
            /**
             * Gets a value indicating whether this object is enabled.
             */
			virtual const System::Boolean& IsEnabled() const = 0;

			/**
			 * Gets the order in which to update this object relative to other objects.
			 */
			virtual const System::UInt32& GetUpdateOrder() const = 0;

			/**
			 * Called when the component should be updated.
			 */
			virtual void Update(const RenderTime& renderTime) = 0;
		};
	}
}

#endif /* IUPDATEABLE_HPP */