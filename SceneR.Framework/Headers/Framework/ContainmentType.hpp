// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#ifndef CONTAINMENTTYPE_HPP
#define CONTAINMENTTYPE_HPP

#include <System/Core.hpp>

namespace SceneR
{
	namespace Framework
	{
		/**
		 * Indicates the extent to which bounding volumes intersect or contain one another.
		 */ 
		enum class ContainmentType : System::UInt32
		{
			/**
			 * Indicates that one bounding volume completely contains the other.
			 */
			Contains = 0,
			/**
			 * Indicates there is no overlap between the bounding volumes.
			 */
			Disjoint = 1,
			/**
			 * Indicates that the bounding volumes partially overlap.			
			 */
			Intersects = 2
		};
	}
}

#endif // CONTAINMENTTYPE_HPP
