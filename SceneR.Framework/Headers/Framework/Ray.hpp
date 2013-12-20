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

#ifndef RAY_HPP
#define RAY_HPP

namespace SceneR
{
	namespace Framework
	{		
		struct BoundingBox;
		struct BoundingFrustum;
		struct BoundingSphere;
		struct Plane;
		struct Vector3;

		/**
		 * Defines a ray.
		 */ 
		struct Ray
		{
		public:
			/**
			 * Initializes a new instance of the Ray structure with the given position an direction.
			 */
			Ray(const Vector3& position, const Vector3& direction);

			/**
			 * Releases all resources being used by this Ray.
			 */
			virtual ~Ray();

		public:
			/**
			 * Unit vector specifying the direction the Ray is pointing.
			 */
			const Vector3& Direction();

			/**
			 * Specifies the starting point of the Ray.
			 */
			const Vector3& Position();

		public:
			/**
			 * Checks whether the Ray intersects a specified BoundingBox.
			 */
			System::Boolean Intersects(const BoundingBox& boundingBox);

			/**
			 * Checks whether the Ray intersects a specified BoundingFrustum.
			 */
			System::Boolean Intersects(const BoundingFrustum& frustum);

			/**
			 * Checks whether the Ray intersects a specified BoundingSphere.
			 */
			System::Boolean Intersects(const BoundingSphere& sphere);

			/**
			 * Determines whether this Ray intersects a specified Plane.
			 */
			System::Boolean Intersects(const Plane& plane);

		public:			
            bool operator==(const Ray& ray) const;
            bool operator!=(const Ray& ray) const;

		private:
			Vector3 position;
			Vector3 direction;
		};
	}
}

#endif // RAY_HPP
