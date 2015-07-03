// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef RAY_HPP
#define RAY_HPP

#include <System/Core.hpp>
#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct BoundingBox;
        struct BoundingFrustum;
        struct BoundingSphere;
        struct Plane;

        /**
         * Defines a ray.
         */
        struct Ray
        {
        public:
            /**
             * Initializes a new instance of the Ray structure with the given position an direction.
             * @param position the ray starting.
             * @param direction unit vector describing he ray direction.
             */
            Ray(const Vector3& position, const Vector3& direction);

            /**
             * Initializes a new instance of the Ray structure with the given position an direction.
             */
            Ray(const Ray& ray);

            /**
             * Releases all resources being used by this Ray.
             */
            ~Ray();

        public:
            /**
             * Unit vector specifying the direction the Ray is pointing.
             */
            const Vector3& Direction() const;

            /**
             * Specifies the starting point of the Ray.
             */
            const Vector3& Position() const;

        public:
            /**
             * Checks whether the Ray intersects a specified BoundingBox.
             */
            bool Intersects(const BoundingBox& boundingBox);

            /**
             * Checks whether the Ray intersects a specified BoundingFrustum.
             */
            bool Intersects(const BoundingFrustum& frustum);

            /**
             * Checks whether the Ray intersects a specified BoundingSphere.
             */
            bool Intersects(const BoundingSphere& sphere);

            /**
             * Determines whether this Ray intersects a specified Plane.
             */
            bool Intersects(const Plane& plane);

        public:
            Ray& operator=(const Ray& ray);
            bool operator==(const Ray& ray) const;
            bool operator!=(const Ray& ray) const;

        private:
            Vector3 direction;
            Vector3 position;
        };
    }
}

#endif // RAY_HPP
