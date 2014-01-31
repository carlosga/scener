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

#ifndef BOUNDINGSPHERE_HPP
#define BOUNDINGSPHERE_HPP

#include <Framework/ContainmentType.hpp>
#include <Framework/PlaneIntersectionType.hpp>
#include <Framework/Vector3.hpp>
#include <System/Core.hpp>
#include <vector>

namespace SceneR
{
	namespace Framework
	{
		struct BoundingBox;
		struct BoundingFrustum;
		struct Matrix;
		struct Plane;
		struct Ray;

		/**
		 * Defines a sphere.
		 */
		struct BoundingSphere
		{
		public:
			/**
			 * Creates the smallest BoundingSphere that can contain a specified BoundingBox.
			 */
			static BoundingSphere CreateFromBoundingBox(const BoundingBox& box);

			/**
			 * Creates the smallest BoundingSphere that can contain a specified BoundingFrustum.
			 */
			static BoundingSphere CreateFromFrustum(const BoundingFrustum& frustum);

			/**
			 * Creates a BoundingSphere that can contain a specified list of points.
			 */ 
			static BoundingSphere CreateFromPoints(const std::vector<Vector3>& points);

			/**
			 * Creates a BoundingSphere that contains the two specified BoundingSphere instances.
			 */
			static BoundingSphere CreateMerged(const BoundingSphere& original, const BoundingSphere& additional);

		public:
			/**
			 * Initializes a new instance of the BoundingSphere class with
			 * the given center an radius.
			 */
			BoundingSphere(const Vector3& center, const System::Single& radius);

            /**
             * Initializes a new instance of the BoundingSphere class.
             */
            BoundingSphere(const BoundingSphere& sphere);

			/**
			 * Releases all resources being used by this BoundingSphere.
			 */
			~BoundingSphere();

		public:
			/**
			 * Gets the center of the sphere.
			 */
			const Vector3& Center() const;

			/**
			 * * Gets the radius of the sphere.
			 */ 
			const System::Single& Radius() const;

		public:
			/**
			 * Checks whether the current BoundingSphere contains the specified BoundingBox.
			 */
			ContainmentType Contains(const BoundingBox& boundingBox) const;

			/**
			 * Checks whether the current BoundingSphere contains the specified BoundingFrustum.
			 */
			ContainmentType Contains(const BoundingFrustum& frustrum) const;

			/**
			 * Checks whether the current BoundingSphere contains the specified BoundingSphere.
			 */
			ContainmentType Contains(const BoundingSphere& sphere) const;

			/**
			 * Checks whether the current BoundingSphere contains the specified point.
			 */
			ContainmentType Contains(const Vector3& point) const;

			/**
			 * Checks whether the current BoundingSphere intersects with a specified BoundingBox.
			 */
			System::Boolean Intersects(const BoundingBox& boundingBox) const;

			/**
			 * Checks whether the current BoundingSphere intersects with a specified BoundingFrustum.
			 */
			System::Boolean Intersects(const BoundingFrustum& frustrum) const;

			/**
			 * Checks whether the current BoundingSphere intersects with a specified BoundingSphere.
			 */
			System::Boolean Intersects(const BoundingSphere& sphere) const;

			/**
			 * Checks whether the current BoundingSphere intersects with a specified Plane.
			 */
			PlaneIntersectionType Intersects(const Plane& plane) const;

			/**
			 * Checks whether the current BoundingSphere intersects with a specified Ray.
			 */
			System::Boolean Intersects(const Ray& ray) const;

			/**
			 * 	 Checks whether the current BoundingSphere intersects a Ray.
			 */
			// System::Boolean Intersects(const Ray& ray, Nullable<Single>);

			/**
			 * Translates and scales the BoundingSphere using a given Matrix.
			 * @param matrix transformation matrix that might include translation, 
			 * rotation, or uniform scaling. Note that BoundingSphere.Transform 
			 * will not return correct results if there are non-uniform scaling, 
			 * shears, or other unusual transforms in this transformation matrix. 
			 * This is because there is no way to shear or non-uniformly scale a sphere. 
			 * Such an operation would cause the sphere to lose its shape as a sphere.
			 */
 			BoundingSphere Transform(const Matrix& matrix) const;

		public:
 			BoundingSphere& operator=(const BoundingSphere& sphere);
            bool operator==(const BoundingSphere& sphere) const;
            bool operator!=(const BoundingSphere& sphere) const;

		public:
			Vector3 	   center;
			System::Single radius;
		};
	}
}

#endif // BOUNDINGSPHERE_HPP
