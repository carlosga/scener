// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BOUNDINGSPHERE_HPP
#define BOUNDINGSPHERE_HPP

#include <vector>

#include <System/Core.hpp>
#include <Framework/PlaneIntersectionType.hpp>
#include <Framework/ContainmentType.hpp>
#include <Framework/Vector3.hpp>

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
            bool Intersects(const BoundingBox& boundingBox) const;

            /**
             * Checks whether the current BoundingSphere intersects with a specified BoundingFrustum.
             */
            bool Intersects(const BoundingFrustum& frustrum) const;

            /**
             * Checks whether the current BoundingSphere intersects with a specified BoundingSphere.
             */
            bool Intersects(const BoundingSphere& sphere) const;

            /**
             * Checks whether the current BoundingSphere intersects with a specified Plane.
             */
            PlaneIntersectionType Intersects(const Plane& plane) const;

            /**
             * Checks whether the current BoundingSphere intersects with a specified Ray.
             */
            bool Intersects(const Ray& ray) const;

            /**
             * 	 Checks whether the current BoundingSphere intersects a Ray.
             */
            // bool Intersects(const Ray& ray, Nullable<Single>);

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
