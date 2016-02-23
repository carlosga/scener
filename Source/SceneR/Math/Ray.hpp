// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_RAY_HPP
#define SCENER_MATH_RAY_HPP

#include "SceneR/Math/Vector3.hpp"

namespace SceneR { namespace Math {

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
     * @param rposition the ray starting.
     * @param rdirection unit vector describing he ray direction.
     */
    Ray(const Vector3& rposition, const Vector3& rdirection) noexcept;

    /**
     * Initializes a new instance of the Ray structure with the given position an direction.
     */
    Ray(const Ray& ray) = default;

    /**
     * Releases all resources being used by this Ray.
     */
    ~Ray() = default;

public:
    /**
     * Checks whether the Ray intersects a specified BoundingBox.
     */
    bool intersects(const BoundingBox& boundingBox) noexcept;

    /**
     * Checks whether the Ray intersects a specified BoundingFrustum.
     */
    bool intersects(const BoundingFrustum& frustum) noexcept;

    /**
     * Checks whether the Ray intersects a specified BoundingSphere.
     */
    bool intersects(const BoundingSphere& sphere) noexcept;

    /**
     * Determines whether this Ray intersects a specified Plane.
     */
    bool intersects(const Plane& plane) noexcept;

public:
    Ray& operator=(const Ray& ray) = default;

    bool operator==(const Ray& ray) const noexcept;
    bool operator!=(const Ray& ray) const noexcept;

public:
    /**
     * Unit vector specifying the direction the Ray is pointing.
     */
    Vector3 direction;

    /**
     * Specifies the starting point of the Ray.
     */
    Vector3 position;
};

}}

#endif // SCENER_MATH_RAY_HPP
