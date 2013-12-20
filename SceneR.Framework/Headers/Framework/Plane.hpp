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

#ifndef PLANE_HPP
#define PLANE_HPP

#include <System/Core.hpp>
#include <Framework/Vector3.hpp>

namespace SceneR
{
	namespace Framework
	{
		struct Vector4;

		/**
		 * Defines a plane.
		 */
		struct Plane
		{
		public:
			/**
			 * Initializes a new instance of the Plane structure.
			 */
			Plane (const System::Single& a, const System::Single& b, const System::Single& c, const System::Single& d);

			/**
			 * Initializes a new instance of the Plane structure.
			 */			
			Plane (const Vector3& normal, const System::Single& d);

			/**
			 * Initializes a new instance of the Plane structure.
			 */			
			Plane (const Vector3& point1, const Vector3& point2, const Vector3& point3);

			/**
			 * Initializes a new instance of the Plane structure.
			 */			
			Plane (const Vector4& value);


			/**
			 * Releases all resources being used by this Plane.
			 */
			virtual ~Plane();

		public:
			/**
			 * 	The distance of the Plane along its normal from the origin.
			 */
			const System::Single& D();

			/**
			 * The normal vector of the Plane.
			 */ 
			const Vector3& Normal();

		public:

		private:
			System::Single d;
			Vector3 	   normal;
		};
	}
}

#endif // PLANE_HPP
