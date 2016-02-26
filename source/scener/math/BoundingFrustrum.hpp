// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BOUNDINGFRUSTRUM_HPP
#define SCENER_MATH_BOUNDINGFRUSTRUM_HPP

#include <cstdint>
#include <vector>

#include "scener/math/plane_intersection_type.hpp"
#include "scener/math/ContainmentType.hpp"
#include "scener/math/basic_matrix.hpp"
#include "scener/math/basic_plane.hpp"
#include "scener/math/basic_vector.hpp"

namespace scener { namespace math {

struct BoundingBox;
struct BoundingSphere;
struct Ray;

/// Defines a frustum and helps determine whether forms intersect with it.
struct BoundingFrustrum
{
public:
    /// Specifies the total number of corners (8) in the BoundingFrustrum.
    constexpr static const std::uint32_t CornerCount = 8;

public:
    /// Initializes a new instance of the BoundingFrustrum class.
    /// \param value Combined matrix that usually takes view × projection matrix.
    BoundingFrustrum(const matrix4& value) noexcept;

public:
    /// Gets the bottom plane of the BoundingFrustum.
    /// \returns the bottom plane of the BoundingFrustum.
    const plane_t& bottom() const noexcept;

    /// Gets the far plane of the BoundingFrustum.
    /// \returns the far plane of the BoundingFrustum.
    const plane_t& far() const noexcept;

    /// Gets the left plane of the BoundingFrustum.
    /// \returns the left plane of the BoundingFrustum.
    const plane_t& left() const noexcept;

    /// Gets the matrix4 that describes this bounding frustum.
    /// \returns the matrix4 that describes this bounding frustum.
    const matrix4& matrix() const noexcept;

    /// Sets the matrix4 that describes this bounding frustum.
    /// \param matrix the matrix4 that describes this bounding frustum.
    void matrix(const matrix4& matrix) noexcept;

    /// Gets the near plane of the BoundingFrustum.
    /// \returns the near plane of the BoundingFrustum.
    const plane_t& near() const noexcept;

    /// Gets the right plane of the BoundingFrustum.
    /// \returns the right plane of the BoundingFrustum.
    const plane_t& right() const noexcept;

    /// Gets the top plane of the BoundingFrustum.
    /// \returns the top plane of the BoundingFrustum.
    const plane_t& top() const noexcept;

public:
    /// Checks whether the current BoundingFrustrum contains a BoundingBox.
    /// \param box the BoundingBox to test for overlap.
    /// \returns the extent of overlap
    ContainmentType contains(const BoundingBox& box) const noexcept;

    /// Checks whether the current BoundingFrustrum contains another BoundingFrustrum.
    /// \param box the BoundingFrustrum to test for overlap.
    /// \returns the extent of overlap
    ContainmentType contains(const BoundingFrustrum& box) const noexcept;

    /// Checks whether the current BoundingFrustrum contains a BoundingSphere.
    /// \param sphere the BoundingSphere to test for overlap.
    /// \returns the extent of overlap
    ContainmentType contains(const BoundingSphere& sphere) const noexcept;

    /// Checks whether the current BoundingFrustrum contains a point.
    /// \param point the point to test for overlap.
    /// \returns the extent of overlap
    ContainmentType contains(const vector3& point) const noexcept;

    /// Gets the list of points that make up the corners of the BoundingFrustrum.
    /// \returns the list of points that make up the corners of the BoundingFrustrum.
    std::vector<vector3> get_corners() noexcept;

    /// Checks whether the current BoundingFrustrum intersects a specified BoundingBox.
    /// \param box the BoundingBox to test for intersection with.
    /// \returns true if the BoundingFrustrum and BoundingBox intersect; false otherwise.
    bool intersects(const BoundingBox& box) const noexcept;

    /// Checks whether the current BoundingFrustrum intersects with another BoundingFrustum.
    /// \param frustrum the BoundingFrustum to test for intersection with.
    /// \returns true if both BoundingFrustrum's intersect; false otherwise.
    bool intersects(const BoundingFrustrum& frustrum) const noexcept;

    /// Checks whether the current BoundingFrustrum intersects a specified BoundingSphere.
    /// \param sphere the BoundingSphere to test for intersection with.
    /// \returns true if the BoundingFrustrum and BoundingSphere intersect; false otherwise.
    bool intersects(const BoundingSphere& sphere) const noexcept;

    /// Checks whether the current BoundingFrustrum intersects a specified Plane.
    /// \param plane the Plane to test for intersection with.
    /// \returns the relationship between the Plane and the BoundingFrustrum.
    plane_intersection_type intersects(const plane_t& plane) const noexcept;

    /// Checks whether the current BoundingFrustrum intersects a specified Ray.
    /// \param ray the Ray to test for intersection with.
    /// \returns distance at which the ray intersects the BoundingFrustrum, or 0 if there is no intersection.
    float intersects(const Ray& ray) const noexcept;

public:
    /// Equality operator for comparing BoundingFrustrum instances.
    bool operator==(const BoundingFrustrum& frustrum) const noexcept;

    /// Inequality operator for comparing BoundingFrustrum instances.
    bool operator!=(const BoundingFrustrum& frustrum) const noexcept;

private:
    void update_planes() noexcept;

private:
    plane_t _bottom;
    plane_t _far;
    plane_t _left;
    plane_t _near;
    plane_t _right;
    plane_t _top;
    matrix4 _value;
};

}}

#endif // SCENER_NATH_BOUNDINGFRUSTRUM_HPP
