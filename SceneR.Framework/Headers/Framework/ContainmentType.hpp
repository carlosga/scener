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
