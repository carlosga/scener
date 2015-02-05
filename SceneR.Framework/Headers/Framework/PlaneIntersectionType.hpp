// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PLANEINTERSECTIONTYPE_HPP
#define PLANEINTERSECTIONTYPE_HPP

#include <System/Core.hpp>

namespace SceneR
{
	namespace Framework
	{
	    /**
	     * Describes the intersection between a plane and a bounding volume.
	     */
		enum class PlaneIntersectionType : System::UInt32
		{
			/**
			 * There is no intersection, and the bounding volume is in the negative half-space of the Plane.
			 */
			Back = 0,
			/**
			 * There is no intersection, and the bounding volume is in the positive half-space of the Plane.
			 */
			Front = 1,
			/**
			 * The Plane is intersected.
			 */
			Intersecting = 2
		};
	}
}

#endif  // PLANEINTERSECTIONTYPE_HPP
