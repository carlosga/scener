// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BOUNDINGSPHERE_HPP
#define SCENER_MATH_BOUNDINGSPHERE_HPP

#include <vector>

#include "scener/math/basic_matrix.hpp"
#include "scener/math/basic_plane.hpp"
#include "scener/math/basic_vector.hpp"

namespace scener { namespace math {

enum class plane_intersection_type : std::uint32_t;
enum class ContainmentType       : std::uint32_t;

struct BoundingBox;
struct BoundingFrustum;
struct Ray;

/// Defines a sphere.
struct BoundingSphere
{
public:
    /// Creates the smallest BoundingSphere that can contain a specified BoundingBox.
    static BoundingSphere create_from_bounding_box(const BoundingBox& box) noexcept;

    /// Creates the smallest BoundingSphere that can contain a specified BoundingFrustum.
    static BoundingSphere create_from_frustum(const BoundingFrustum& frustum) noexcept;

    /// Creates a BoundingSphere that can contain a specified list of points.
    static BoundingSphere create_from_points(const std::vector<vector3>& points) noexcept;

    /// Creates a BoundingSphere that contains the two specified BoundingSphere instances.
    static BoundingSphere create_merged(const BoundingSphere& original, const BoundingSphere& additional) noexcept;

public:
    /// Initializes a new instance of the BoundingSphere class with the given center an radius.
    /// \param center center point of the sphere.
    /// \param radius radius of the sphere.
    BoundingSphere(const vector3& center, float radius) noexcept;

public:
    /// Gets the center of the sphere.
    /// \returns the center of the sphere.
    const vector3& center() const noexcept;

    /// Gets the radius of the sphere.
    /// \returns the radius of the sphere.
    float radius() const noexcept;

public:
    /// Checks whether the current BoundingSphere contains the specified BoundingBox.
    ContainmentType contains(const BoundingBox& boundingBox) const noexcept;

    /// Checks whether the current BoundingSphere contains the specified BoundingFrustum.
    ContainmentType contains(const BoundingFrustum& frustrum) const noexcept;

    /// Checks whether the current BoundingSphere contains the specified BoundingSphere.
    ContainmentType contains(const BoundingSphere& sphere) const noexcept;

    /// Checks whether the current BoundingSphere contains the specified point.
    ContainmentType contains(const vector3& point) const noexcept;

    /// Checks whether the current BoundingSphere intersects with a specified BoundingBox.
    bool intersects(const BoundingBox& boundingBox) const noexcept;

    /// Checks whether the current BoundingSphere intersects with a specified BoundingFrustum.
    bool intersects(const BoundingFrustum& frustrum) const noexcept;

    /// Checks whether the current BoundingSphere intersects with a specified BoundingSphere.
    bool intersects(const BoundingSphere& sphere) const noexcept;

    /// Checks whether the current BoundingSphere intersects with a specified Plane.
    plane_intersection_type intersects(const plane_t& plane) const noexcept;

    /// Checks whether the current BoundingSphere intersects with a specified Ray.
    bool intersects(const Ray& ray) const noexcept;

    // Checks whether the current BoundingSphere intersects a Ray.
    // bool Intersects(const Ray& ray, Nullable<Single>);

    /// Translates and scales the BoundingSphere using a given matrix4.
    /// \param matrix transformation matrix that might include translation, rotation, or uniform scaling.
    ///               Note that BoundingSphere.Transform will not return correct results if there are non-uniform scaling,
    ///               shears, or other unusual transforms in this transformation matrix.
    ///               This is because there is no way to shear or non-uniformly scale a sphere.
    ///               Such an operation would cause the sphere to lose its shape as a sphere.
    BoundingSphere transform(const matrix4& matrix) const noexcept;

public:
    /// Equality operator for comparing BoundingSphere instances.
    bool operator==(const BoundingSphere& sphere) const noexcept;

    /// Inequality operator for comparing BoundingSphere instances.
    bool operator!=(const BoundingSphere& sphere) const noexcept;

public:
    vector3 _center;
    float   _radius;
};

}}

#endif // SCENER_MATH_BOUNDINGSPHERE_HPP
