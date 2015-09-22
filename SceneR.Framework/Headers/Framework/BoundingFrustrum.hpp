// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_BOUNDINGFRUSTRUM_HPP
#define FRAMEWORK_BOUNDINGFRUSTRUM_HPP

#include <cstdint>
#include <vector>

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
            static const std::uint32_t CornerCount;

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
            ~BoundingFrustrum() = default;

        public:
            /**
             * Gets the bottom plane of the BoundingFrustum.
             * @return the bottom plane of the BoundingFrustum.
             */
            const Plane& bottom() const;

            /**
             * Gets the far plane of the BoundingFrustum.
             * @return the far plane of the BoundingFrustum.
             */
            const Plane& far() const;

            /**
             * Gets the left plane of the BoundingFrustum.
             * @return the left plane of the BoundingFrustum.
             */
            const Plane& left() const;

            /**
             * Gets the Matrix that describes this bounding frustum.
             * @return the Matrix that describes this bounding frustum.
             */
            const SceneR::Framework::Matrix& matrix() const;

            /**
             * Sets the Matrix that describes this bounding frustum.
             * @param matrix the Matrix that describes this bounding frustum.
             */
            void matrix(const SceneR::Framework::Matrix& matrix);

            /**
             * Gets the near plane of the BoundingFrustum.
             * @return the near plane of the BoundingFrustum.
             */
            const Plane& near() const;

            /**
             * Gets the right plane of the BoundingFrustum.
             * @return the right plane of the BoundingFrustum.
             */
            const Plane& right() const;

            /**
             * Gets the top plane of the BoundingFrustum.
             * @return the top plane of the BoundingFrustum.
             */
            const Plane& top() const;

        public:
            /**
             * Checks whether the current BoundingFrustrum contains a BoundingBox.
             * @param box the BoundingBox to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType contains(const BoundingBox& box) const;

            /**
             * Checks whether the current BoundingFrustrum contains another BoundingFrustrum.
             * @param box the BoundingFrustrum to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType contains(const BoundingFrustrum& box) const;

            /**
             * Checks whether the current BoundingFrustrum contains a BoundingSphere.
             * @param sphere the BoundingSphere to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType contains(const BoundingSphere& sphere) const;

            /**
             * Checks whether the current BoundingFrustrum contains a point.
             * @param point the point to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType contains(const Vector3& point) const;

            /**
             * Gets the list of points that make up the corners of the BoundingFrustrum.
             */
            std::vector<Vector3> get_corners();

            /**
             * Checks whether the current BoundingFrustrum intersects a specified BoundingBox.
             * @param box the BoundingBox to test for intersection with.
             * @returns true if the BoundingFrustrum and BoundingBox intersect; false otherwise.
             */
            bool intersects(const BoundingBox& box) const;

            /**
             * Checks whether the current BoundingFrustrum intersects with another BoundingFrustum.
             * @param frustrum the BoundingFrustum to test for intersection with.
             * @returns true if both BoundingFrustrum's intersect; false otherwise.
             */
            bool intersects(const BoundingFrustrum& frustrum) const;

            /**
             * Checks whether the current BoundingFrustrum intersects a specified BoundingSphere.
             * @param sphere the BoundingSphere to test for intersection with.
             * @returns true if the BoundingFrustrum and BoundingSphere intersect; false otherwise.
             */
            bool intersects(const BoundingSphere& sphere) const;

            /**
             * Checks whether the current BoundingFrustrum intersects a specified Plane.
             * @param plane the Plane to test for intersection with.
             * @returns the relationship between the Plane and the BoundingFrustrum.
             */
            PlaneIntersectionType intersects(const Plane& plane) const;

            /**
             * Checks whether the current BoundingFrustrum intersects a specified Ray.
             * @param ray the Ray to test for intersection with.
             * @returns distance at which the ray intersects the BoundingFrustrum, or 0 if there is no intersection.
             */
            float intersects(const Ray& ray) const;

        public:
            BoundingFrustrum& operator=(const BoundingFrustrum& frustrum);
            bool operator==(const BoundingFrustrum& frustrum) const;
            bool operator!=(const BoundingFrustrum& frustrum) const;

        private:
            void update_planes();

        private:
            Plane _bottom;
            Plane _far;
            Plane _left;
            Plane _near;
            Plane _right;
            Plane _top;
            SceneR::Framework::Matrix _value;
        };
    }
}

#endif // FRAMEWORK_BOUNDINGFRUSTRUM_HPP
