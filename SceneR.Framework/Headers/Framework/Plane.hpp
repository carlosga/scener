// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PLANE_HPP
#define PLANE_HPP

#include <Framework/PlaneIntersectionType.hpp>
#include <Framework/Vector3.hpp>

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
             * @brief Creates a Plane object that contains three specified points.
             * @param point1 The first point defining the plane.
             * @param point2 The second point defining the plane.
             * @param point3 The third point defining the plane.
             * @return The plane containing the three points.
             */
            static Plane CreateFromVertices(const Vector3& point1, const Vector3& point2, const Vector3& point3);

            /**
             * Calculates the dot product of a specified Vector4 and this Plane.
             *
             * @param plane The plane.
             * @param value The four-dimensional vector.
             */
            static float Dot(const Plane& plane, const Vector4& value);

            /**
             * Returns the dot product of a specified three-dimensional vector and the Normal vector of this plane.
             * @param p The plane.
             * @param v The three-dimensional vector.
             * @returns The dot product.
             */
            static float DotNormal(const Plane& p, const Vector3& v);

            /**
             * Returns the dot product of a specified three-dimensional vector and the normal vector of this plane plus the distance (D) value of the plane.
             * @param p The plane
             * @param value The three-dimensional vector.
             * @returns The dot product
             */
            static float DotCoordinate(const Plane& p, const Vector3& value);

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
            Plane();

            /**
             * Initializes a new instance of the Plane structure.
             */
            Plane(const float& a, const float& b, const float& c, const float& d);

            /**
             * Initializes a new instance of the Plane structure.
             */
            Plane(const Vector3& normal, const float& d);

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
             * Gets The normal vector of the Plane.
             */
            const Vector3& Normal() const;

            /**
             * 	Gets the distance of the Plane along its normal from the origin.
             */
            float D() const;

        public:
            /**
             * Sets The normal vector of the Plane.
             */
            void Normal(const Vector3& normal);

            /**
             * 	Gets the distance of the Plane along its normal from the origin.
             */
            void D(const float& d);

        public:
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

        public:
            Plane& operator=(const Plane& plane);
            bool operator==(const Plane& plane) const;
            bool operator!=(const Plane& plane) const;

        private:
            Vector3 normal;
            float   d;
        };
    }
}

#endif // PLANE_HPP
