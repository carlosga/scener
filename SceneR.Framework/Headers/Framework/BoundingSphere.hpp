// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_BOUNDINGSPHERE_HPP
#define FRAMEWORK_BOUNDINGSPHERE_HPP

#include <vector>

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
            static BoundingSphere create_from_bounding_box(const BoundingBox& box);

            /**
             * Creates the smallest BoundingSphere that can contain a specified BoundingFrustum.
             */
            static BoundingSphere create_from_frustum(const BoundingFrustum& frustum);

            /**
             * Creates a BoundingSphere that can contain a specified list of points.
             */
            static BoundingSphere create_from_points(const std::vector<Vector3>& points);

            /**
             * Creates a BoundingSphere that contains the two specified BoundingSphere instances.
             */
            static BoundingSphere create_merged(const BoundingSphere& original, const BoundingSphere& additional);

        public:
            /**
             * Initializes a new instance of the BoundingSphere class with
             * the given center an radius.
             */
            BoundingSphere(const Vector3& center, const float& radius);

            /**
             * Initializes a new instance of the BoundingSphere class.
             */
            BoundingSphere(const BoundingSphere& sphere);

            /**
             * Releases all resources being used by this BoundingSphere.
             */
            ~BoundingSphere() = default;

        public:
            /**
             * Gets the center of the sphere.
             */
            const Vector3& center() const;

            /**
             * * Gets the radius of the sphere.
             */
            float radius() const;

        public:
            /**
             * Checks whether the current BoundingSphere contains the specified BoundingBox.
             */
            ContainmentType contains(const BoundingBox& boundingBox) const;

            /**
             * Checks whether the current BoundingSphere contains the specified BoundingFrustum.
             */
            ContainmentType contains(const BoundingFrustum& frustrum) const;

            /**
             * Checks whether the current BoundingSphere contains the specified BoundingSphere.
             */
            ContainmentType contains(const BoundingSphere& sphere) const;

            /**
             * Checks whether the current BoundingSphere contains the specified point.
             */
            ContainmentType contains(const Vector3& point) const;

            /**
             * Checks whether the current BoundingSphere intersects with a specified BoundingBox.
             */
            bool intersects(const BoundingBox& boundingBox) const;

            /**
             * Checks whether the current BoundingSphere intersects with a specified BoundingFrustum.
             */
            bool intersects(const BoundingFrustum& frustrum) const;

            /**
             * Checks whether the current BoundingSphere intersects with a specified BoundingSphere.
             */
            bool intersects(const BoundingSphere& sphere) const;

            /**
             * Checks whether the current BoundingSphere intersects with a specified Plane.
             */
            PlaneIntersectionType intersects(const Plane& plane) const;

            /**
             * Checks whether the current BoundingSphere intersects with a specified Ray.
             */
            bool intersects(const Ray& ray) const;

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
            BoundingSphere transform(const Matrix& matrix) const;

        public:
            BoundingSphere& operator=(const BoundingSphere& sphere);
            bool operator==(const BoundingSphere& sphere) const;
            bool operator!=(const BoundingSphere& sphere) const;

        public:
            Vector3 _center;
            float   _radius;
        };
    }
}

#endif // FRAMEWORK_BOUNDINGSPHERE_HPP
