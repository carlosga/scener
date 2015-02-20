// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <vector>

#include <Framework/PlaneIntersectionType.hpp>
#include <Framework/ContainmentType.hpp>
#include <Framework/Vector3.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct BoundingFrustrum;
        struct BoundingSphere;
        struct Plane;
        struct Ray;

        /**
         * Defines an axis-aligned box-shaped 3D volume.
         */
        struct BoundingBox
        {
        public:
            /**
             * Specifies the total number of corners (8) in the BoundingBox.
             */
            static const System::Int32& CornerCount;

        public:
            //Public Method Static    CreateFromPoints    Creates the smallest BoundingBox that will contain a group of points.
            //Public Method Static    CreateFromSphere    Overloaded. Creates the smallest BoundingBox that will contain the specified BoundingSphere.
            //Public Method Static    CreateMerged    Overloaded. Creates the smallest BoundingBox that contains the two specified BoundingBox instances.

        public:
            /**
             * Initializes a new instance of the BoundingBox class.
             * @param min the minimum point the BoundingBox includes.
             * @param max the maximum point the BoundingBox includes.
             */
            BoundingBox(const Vector3& min, const Vector3& max);

            /**
             * Initializes a new instance of the BoundingBox class.
             */
            BoundingBox(const BoundingBox& boundingBox);

            /**
             * Releases all resources being used by this BoundingBox.
             */
            ~BoundingBox() = default;

        public:
            /**
             * Gets the maximum point the BoundingBox contains.
             */
            const Vector3& Max() const;

            /**
             * Sets the maximum point the BoundingBox contains.
             */
            void Max(const Vector3& max);

            /**
             * Gets the minimum point the BoundingBox contains.
             */
            const Vector3& Min() const;

            /**
             * Sets the minimum point the BoundingBox contains.
             */
            void Min(const Vector3& min);

        public:
            /**
             * Checks whether the current BoundingBox contains another BoundingBox.
             * @param box the BoundingBox to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType Contains(const BoundingBox& box) const;

            /**
             * Checks whether the current BoundingBox contains a BoundingFrustrum.
             * @param frustrum the BoundingFrustrum to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType Contains(const BoundingFrustrum& frustrum) const;

            /**
             * Checks whether the current BoundingBox contains a BoundingSphere.
             * @param sphere the BoundingSphere to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType Contains(const BoundingSphere& sphere) const;

            /**
             * Checks whether the current BoundingBox contains a point.
             * @param point the point to test for overlap.
             * @returns the extent of overlap
             */
            ContainmentType Contains(const Vector3& point) const;

            /**
             * Gets the list of points that make up the corners of the BoundingBox.
             */
            std::vector<Vector3> GetCorners() const;

            /**
             * Checks whether the current BoundingBox intersects with another BoundingBox.
             * @param box the BoundingBox to test for intersection with.
             * @returns true if both BoundingBoxes intersect; false otherwise.
             */
            bool Intersects(const BoundingBox& box) const;

            /**
             * Checks whether the current BoundingBox intersects a specified BoundingFrustum.
             * @param frustrum the BoundingFrustum to test for intersection with.
             * @returns true if the BoundingBox and BoundingFrustrum intersect; false otherwise.
             */
            bool Intersects(const BoundingFrustrum& frustrum) const;

            /**
             * Checks whether the current BoundingBox intersects a specified BoundingSphere.
             * @param sphere the BoundingSphere to test for intersection with.
             * @returns true if the BoundingBox and BoundingSphere intersect; false otherwise.
             */
            bool Intersects(const BoundingSphere& sphere) const;

            /**
             * Checks whether the current BoundingBox intersects a specified Plane.
             * @param plane the Plane to test for intersection with.
             * @returns the relationship between the Plane and the BoundingBox.
             */
            PlaneIntersectionType Intersects(const Plane& plane) const;

            /**
             * Checks whether the current BoundingBox intersects a specified Ray.
             * @param ray the Ray to test for intersection with.
             * @returns distance at which the ray intersects the BoundingBox, or 0 if there is no intersection.
             */
            System::Single Intersects(const Ray& ray) const;

        public:
            BoundingBox& operator=(const BoundingBox& box);
            bool operator==(const BoundingBox& box) const;
            bool operator!=(const BoundingBox& box) const;

        private:
            Vector3 min;
            Vector3 max;
        };
    }
}

#endif // BOUNDINGBOX_HPP
