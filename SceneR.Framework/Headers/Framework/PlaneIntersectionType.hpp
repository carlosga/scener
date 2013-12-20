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
