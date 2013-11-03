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

#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

#include <System/Core.hpp>

namespace SceneR
{
	namespace Framework
	{
	    /**
	     * Defines the interface for a drawable game component.
	     */
		class IDrawable
		{
		public:
		    /**
		     * Releases all the resources being used by this IDrawable instance.
		     */
		    virtual ~IDrawable()
		    {
		    };

		public:
		    /**
		     * Gets a value indicating whether this object is visible.
		     */
			virtual const System::Boolean& IsVisible() const = 0;

			/**
			 * The order in which to draw this object relative to other objects.
			 */
			virtual const System::UInt32& GetDrawOrder() const = 0;

			/**
			 * Called when the component should be drawn.
			 */
			virtual void Draw(/* GameTime gameTime */) = 0;
		};
	}
}

#endif /* IDRAWABLE_HPP */
