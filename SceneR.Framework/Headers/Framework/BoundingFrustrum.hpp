// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BOUNDINGFRUSTRUM_HPP
#define BOUNDINGFRUSTRUM_HPP

#include <vector>

#include <System/Core.hpp>
#include <Framework/PlaneIntersectionType.hpp>
#include <Framework/ContainmentType.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Plane.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct BoundingBox;
        struct BoundingSphere;
        struct Ray;
        struct Vector3;

        /**
         * Defines a frustum and helps determine whether forms intersect with it.
         *
         */
        struct BoundingFrustrum
        {
        public:
            /**
             * Specifies the total number of corners (8) in the BoundingFrustrum.
             */
            static const uint32_t CornerCount;

        public:
            /**
             * Initializes a new instance of the BoundingFrustrum class.
             * @param value Combined matrix that usually takes view × projection matrix.
             */
            BoundingFrustrum(const SceneR::Framework::Matrix& value);

            /**
             * Initializes a new instance of the BoundingFrustrum class.
             */
            BoundingFrustrum(const BoundingFrustrum& frustrum);

            /**
             * Releases all resources being used by this BoundingFrustrum
             */
            ~BoundingFrustrum();

        public:
            /**
             * Gets the bottom plane of the BoundingFrustum.
             * @return the bottom plane of the BoundingFrustum.
             */
            const Plane& Bottom() const;

            /**
             * Gets the far plane of the BoundingFrustum.
             * @return the far plane of the BoundingFrustum.
             */
            const Plane& Far() const;

            /**
             * Gets the left plane of the BoundingFrustum.
             * @return the left plane of the BoundingFrustum.
             */
            const Plane& Left() const;

            /**
             * Gets the Matrix that describes this bounding frustum.
             * @return the Matrix that describes this bounding frustum.
             */
            const SceneR::Framework::Matrix& Matrix() const;

            /**
             * Sets the Matrix that describes this bounding frustum.
             * @param matrix the Matrix that describes this bounding frustum.
             */
            void Matrix(const SceneR::Framework::Matrix& matrix);

            /**
             * Gets the near plane of the BoundingFrustum.
             * @return the near plane of the BoundingFrustum.
             */
            const Plane& Near() const;

            /**
             * Gets the right plane of the BoundingFrustum.
             * @return the right plane of the BoundingFrustum.
             */
            const Plane& Right() const;

            /**
             * Gets the top plane of the BoundingFrustum.
             * @return the top plane of the BoundingFrustum.
             */
            const Plane& Top() const;

        public:
            /**
             * Checks whether the current BoundingFrustrum contains a BoundingBox.
             * @param box the BoundingBox to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType Contains(const BoundingBox& box) const;

            /**
             * Checks whether the current BoundingFrustrum contains another BoundingFrustrum.
             * @param box the BoundingFrustrum to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType Contains(const BoundingFrustrum& box) const;

            /**
             * Checks whether the current BoundingFrustrum contains a BoundingSphere.
             * @param sphere the BoundingSphere to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType Contains(const BoundingSphere& sphere) const;

            /**
             * Checks whether the current BoundingFrustrum contains a point.
             * @param point the point to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType Contains(const Vector3& point) const;

            /**
             * Gets the list of points that make up the corners of the BoundingFrustrum.
             */
            std::vector<Vector3> GetCorners();

            /**
             * Checks whether the current BoundingFrustrum intersects a specified BoundingBox.
             * @param box the BoundingBox to test for intersection with.
             * @returns true if the BoundingFrustrum and BoundingBox intersect; false otherwise.
             */
            bool Intersects(const BoundingBox& box) const;

            /**
             * Checks whether the current BoundingFrustrum intersects with another BoundingFrustum.
             * @param frustrum the BoundingFrustum to test for intersection with.
             * @returns true if both BoundingFrustrum's intersect; false otherwise.
             */
            bool Intersects(const BoundingFrustrum& frustrum) const;

            /**
             * Checks whether the current BoundingFrustrum intersects a specified BoundingSphere.
             * @param sphere the BoundingSphere to test for intersection with.
             * @returns true if the BoundingFrustrum and BoundingSphere intersect; false otherwise.
             */
            bool Intersects(const BoundingSphere& sphere) const;

            /**
             * Checks whether the current BoundingFrustrum intersects a specified Plane.
             * @param plane the Plane to test for intersection with.
             * @returns the relationship between the Plane and the BoundingFrustrum.
             */
            PlaneIntersectionType Intersects(const Plane& plane) const;

            /**
             * Checks whether the current BoundingFrustrum intersects a specified Ray.
             * @param ray the Ray to test for intersection with.
             * @returns distance at which the ray intersects the BoundingFrustrum, or 0 if there is no intersection.
             */
            System::Single Intersects(const Ray& ray) const;

        public:
            BoundingFrustrum& operator=(const BoundingFrustrum& frustrum);
            bool operator==(const BoundingFrustrum& frustrum) const;
            bool operator!=(const BoundingFrustrum& frustrum) const;

        private:
            void UpdatePlanes();

        private:
            Plane bottom;
            Plane far;
            Plane left;
            Plane near;
            Plane right;
            Plane top;
            SceneR::Framework::Matrix value;
        };
    }
}

#endif // BOUNDINGFRUSTRUM_HPP
