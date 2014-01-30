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

#ifndef BOUNDINGFRUSTRUM_HPP
#define BOUNDINGFRUSTRUM_HPP

#include <Framework/ContainmentType.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Plane.hpp>
#include <Framework/PlaneIntersectionType.hpp>
#include <System/Core.hpp>
#include <vector>

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
            static const System::Int32& CornerCount;

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
             * @param sphere the point to test for overlap.
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
             * @param sphere the BoundingFrustrum to test for intersection with.
             * @returns the relationship between the Plane and the BoundingFrustrum.
             */
            PlaneIntersectionType Intersects(const Plane& plane) const;

            /**
             * Checks whether the current BoundingFrustrum intersects a specified Ray.
             * @param sphere the BoundingSphere to test for intersection with.
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
