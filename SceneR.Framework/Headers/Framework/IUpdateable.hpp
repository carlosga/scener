// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

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
            virtual ~IUpdateable() = default;

		public:
            /**
             * Gets a value indicating whether this object is enabled.
             */
			virtual const System::Boolean& Enabled() const = 0;

			/**
			 * Gets the order in which to update this object relative to other objects.
			 */
			virtual const System::UInt32& UpdateOrder() const = 0;

			/**
			 * Called when the component should be updated.
			 */
			virtual void Update(const RenderTime& renderTime) = 0;
		};
	}
}

#endif /* IUPDATEABLE_HPP */
