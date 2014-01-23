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

#include <Framework/PlaneIntersectionType.hpp>
#include <Framework/Vector3.hpp>
#include <System/Core.hpp>

namespace SceneR
{
	namespace Framework
	{
	    struct BoundingBox;
	    struct BoundingFrustrum;
	    struct BoundingSphere;
	    struct Matrix;
	    struct Quaternion;
		struct Vector4;

		/**
		 * Defines a plane.
		 */
		struct Plane
		{
		public:
		    /**
		     * Calculates the dot product between the normal vector of a plane and a 3D vector.
		     * @param p Vector3 describing the plane coefficients (A, B, C, D) for the plane equation
		     * @param v 3D vector to use in the dot product.
		     */
		    static Vector4 DotNormal(const Vector3& p, const Vector3& v);

		    /**
		     * Changes the coefficients of the Normal vector of a Plane to make it of unit length.
		     * @param value the Plane to normalize.
		     */
		    static Plane Normalize(const Plane& value);

		    /**
		     *  Transforms a normalized Plane by a Matrix.
		     *  @param plane the normalized Plane to transform. This Plane must already be normalized.
		     *  @param matrix the transform Matrix to apply to the Plane.
		     *  @returns a new Plane that results from applying the transform.
		     */
            static Plane Transform(const Plane& plane, const Matrix& matrix);

            /**
             * Transforms a normalized Plane by a Quaternion rotation.
             * @param plane the normalized Plane to transform. This Plane must already be normalized.
             * @param rotation the Quaternion rotation to apply to the Plane.
             * @returns a new Plane that results from applying the rotation.
             */
            static Plane Transform(const Plane& plane, const Quaternion& rotation);

		public:
			/**
			 * Initializes a new instance of the Plane structure.
			 */
			Plane(const System::Single& a, const System::Single& b, const System::Single& c, const System::Single& d);

			/**
			 * Initializes a new instance of the Plane structure.
			 */			
			Plane(const Vector3& normal, const System::Single& d);

			/**
			 * Initializes a new instance of the Plane structure.
			 */			
			Plane(const Vector3& point1, const Vector3& point2, const Vector3& point3);

			/**
			 * Initializes a new instance of the Plane structure.
			 */			
			Plane(const Vector4& value);

            /**
             * Initializes a new instance of the Plane structure. Copy constructor
             */
            Plane(const Plane& value);

			/**
			 * Releases all resources being used by this Plane.
			 */
			~Plane();

		public:
			/**
			 * 	The distance of the Plane along its normal from the origin.
			 */
			const System::Single& D() const;

			/**
			 * The normal vector of the Plane.
			 */ 
			const Vector3& Normal() const;

		public:
			/**
			 * Calculates the dot product of a specified Vector4 and this Plane.
			 *
			 * @param the Vector4 to multiply this Plane by.
			 */
			System::Single Dot(const Vector4& value) const;

			/**
			 * Returns the dot product of a specified Vector3 and the Normal vector of this Plane plus the D constant value of the Plane.
			 * @param value the Vector3 to multiply by.
			 */
			System::Single DotCoordinate(const Vector3& value) const;

			/**
			 * Returns the dot product of a specified Vector3 and the Normal vector of this Plane.
			 * @param the Vector3 to multiply by.
			 */
			System::Single DotNormal(const Vector3& value) const;

			/**
			 * Checks whether the current Plane intersects a specified BoundingBox.
			 * @param box the BoundingBox to test for intersection with.
			 * @returns the relationship between the Plane and the BoundingBox.
			 */
			PlaneIntersectionType Intersects(const BoundingBox& box) const;

			/**
			 * Checks whether the current Plane intersects a specified BoundingFrustum.
			 * @param frustrum the BoundingFrustum to test for intersection with.
			 * @returns the relationship between the Plane and the BoundingFrustum.
			 */
			PlaneIntersectionType Intersects(const BoundingFrustrum& frustrum) const;

			/**
			 * Checks whether the current Plane intersects a specified BoundingSphere.
             * @param sphere the BoundingSphere to test for intersection with.
             * @returns the relationship between the Plane and the BoundingSphere.
			 */
			PlaneIntersectionType Intersects(const BoundingSphere& sphere) const;

			/**
			 * Changes the coefficients of the Normal vector of this Plane to make it of unit length.
			 */
			void Normalize();

		public:
			Plane& operator=(const Plane& plane);
			bool operator==(const Plane& plane) const;
			bool operator!=(const Plane& plane) const;

		private:
			System::Single d;
			Vector3 	   normal;
		};
	}
}

#endif // PLANE_HPP
