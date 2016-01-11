// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Math/Matrix.hpp"

#include <sstream>

#include <gsl.h>

#include "SceneR/Math/Math.hpp"
#include "SceneR/Math/Quaternion.hpp"
#include "SceneR/Math/Vector3.hpp"
#include "SceneR/Math/Vector4.hpp"
#include "SceneR/Math/Plane.hpp"

namespace SceneR { namespace Math {

const Matrix Matrix::identity { 1.0f, 0.0f, 0.0f, 0.0f
                              , 0.0f, 1.0f, 0.0f, 0.0f
                              , 0.0f, 0.0f, 1.0f, 0.0f
                              , 0.0f, 0.0f, 0.0f, 1.0f };

Matrix Matrix::create_from_axis_angle(const Vector3& axis, const Radians& angle) noexcept
{
    // http://mathworld.wolfram.com/RodriguesRotationFormula.html
    auto  naxis = Vector3::normalize(axis);
    float cos   = std::cos(angle.value());
    float sin   = std::sin(angle.value());
    float cos_1 = 1.0f - cos;
    float x     = naxis.x;
    float y     = naxis.y;
    float z     = naxis.z;
    float xx    = x * x;
    float yy    = y * y;
    float zz    = z * z;
    float xy    = x * y;
    float yz    = y * z;
    float xz    = x * z;

    return { cos + xx * cos_1     , z * sin + xy * cos_1 , -y * sin + xz * cos_1, 0.0f
           , xy * cos_1 - z * sin , cos + yy * cos_1     , x * sin + yz * cos_1 , 0.0f
           , y * sin + xz * cos_1 , -x * sin + yz * cos_1, cos + zz * cos_1     , 0.0f
           , 0.0f                 , 0.0f                 , 0.0f                 , 1.0f };
}

Matrix Matrix::create_from_quaternion(const Quaternion& quaternion) noexcept
{
    // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
    //            http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    //
    // 1 - 2yy - 2zz    2xy - 2zw       2xz + 2yw
    // 2xy + 2zw        1 - 2xx - 2zz   2yz - 2xw
    // 2xz - 2yw        2yz + 2xw       1 - 2xx - 2yy

    float xx = quaternion.x * quaternion.x;
    float yy = quaternion.y * quaternion.y;
    float zz = quaternion.z * quaternion.z;
    float xy = quaternion.x * quaternion.y;
    float zw = quaternion.z * quaternion.w;
    float xz = quaternion.x * quaternion.z;
    float yw = quaternion.y * quaternion.w;
    float yz = quaternion.y * quaternion.z;
    float xw = quaternion.x * quaternion.w;

    return { 1.0f - 2.0f * (yy + zz), 2.0f * (xy + zw)       , 2.0f * (xz - yw)       , 0.0f
           , 2.0f * (xy - zw)       , 1.0f - 2.0f * (xx + zz), 2.0f * (yz + xw)       , 0.0f
           , 2.0f * (xz + yw)       , 2.0f * (yz - xw)       , 1.0f - 2.0f * (xx + yy), 0.0f
           , 0.0f                   , 0.0f                   , 0.0f                   , 1.0f };
}

Matrix Matrix::create_from_yaw_pitch_roll(const Radians& yaw, const Radians& pitch, const Radians& roll) noexcept
{
    return Matrix::create_from_axis_angle(Vector3::unit_z, roll)
         * Matrix::create_from_axis_angle(Vector3::unit_x, pitch)
         * Matrix::create_from_axis_angle(Vector3::unit_y, yaw);
}

Matrix Matrix::create_frustum(float left, float right, float bottom, float top, float zNear, float zFar) noexcept
{
    Expects (zNear < 0 || zFar < 0);

    float rightSubLeft  = right - left;
    float rightPlusLeft = right + left;
    float topSubBottom  = top - bottom;
    float topPlusBottom = top + bottom;
    float farSubNear    = zFar - zNear;
    float farPlusNear   = zFar - zNear;

    return { (2 * zNear) / rightSubLeft, 0.0f                      , (rightPlusLeft / rightSubLeft), 0.0f
           , 0.0f                      , (2 * zNear) / topSubBottom, (topPlusBottom / topSubBottom), 0.0f
           , 0.0f                      , 0.0f                      , -(farPlusNear  / farSubNear)  , -(2 * zFar * zNear / farSubNear)
           , 0.0f                      , 0.0f                      , -1.0f                         , 0.0f };
}

Matrix Matrix::create_look_at(const Vector3& cameraPosition
                            , const Vector3& cameraTarget
                            , const Vector3& cameraUpVector) noexcept
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/bb281711(v=vs.85).aspx
    // zaxis = normal(cameraPosition - cameraTarget)
    // xaxis = normal(cross(cameraUpVector, zaxis))
    // yaxis = cross(zaxis, xaxis)

    //  xaxis.x                    yaxis.x                     zaxis.x                     0
    //  xaxis.y                    yaxis.y                     zaxis.y                     0
    //  xaxis.z                    yaxis.z                     zaxis.z                     0
    // -dot(xaxis, cameraPosition) -dot(yaxis, cameraPosition) -dot(zaxis, cameraPosition) 1

    auto zAxis = Vector3::normalize(cameraPosition - cameraTarget);
    auto xAxis = Vector3::normalize(Vector3::cross(cameraUpVector, zAxis));
    auto yAxis = Vector3::cross(zAxis, xAxis);
    auto dx    = Vector3::dot(xAxis, cameraPosition);
    auto dy    = Vector3::dot(yAxis, cameraPosition);
    auto dz    = Vector3::dot(zAxis, cameraPosition);

    return { xAxis.x, yAxis.x, zAxis.x, 0.0f
           , xAxis.y, yAxis.y, zAxis.y, 0.0f
           , xAxis.z, yAxis.z, zAxis.z, 0.0f
           , -dx    , -dy    , -dz    , 1.0f };
}

Matrix Matrix::create_orthographic(float width, float height, float zNear, float zFar) noexcept
{
    // Reference: http://msdn.microsoft.com/en-us/library/bb205349(v=vs.85).aspx
    // 2/w  0    0           0
    // 0    2/h  0           0
    // 0    0    1/(zn-zf)   0
    // 0    0    zn/(zn-zf)  1

    float nearSubFar = zNear - zFar;

    return { 2.0f / width, 0.0f         , 0.0f              , 0.0f
           , 0           , 2.0f / height, 0.0f              , 0.0f
           , 0.0f        , 0.0f         , 1 / nearSubFar    , 0.0f
           , 0.0f        , 0.0f         , zNear / nearSubFar, 1.0f };
}

Matrix Matrix::create_orthographic_off_center(float left  , float right
                                            , float bottom, float top
                                            , float zNear , float zFar) noexcept
{
    // Reference: http://msdn.microsoft.com/en-us/library/bb205348(v=vs.85).aspx
    // 2/(r-l)      0            0           0
    // 0            2/(t-b)      0           0
    // 0            0            1/(zn-zf)   0
    // (l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1

    float leftSubRight  = left - right;
    float leftPlusRight = left + right;
    float bottomSubTop  = bottom - top;
    float topPlusBottom = top + bottom;
    float nearSubFar    = zNear - zFar;

    return { 2.0f / (right - left)       , 0.0f                        , 0.0f              , 0.0f
           , 0.0f                        , 2.0f / (top - bottom)       , 0.0f              , 0.0f
           , 0.0f                        , 0.0f                        , 1.0f / nearSubFar , 0.0f
           , leftPlusRight / leftSubRight, topPlusBottom / bottomSubTop, zNear / nearSubFar, 1.0f };
}

Matrix Matrix::create_perspective(float width, float height, float zNear, float zFar) noexcept
{
    Expects(zNear >= 0.0f && zFar >= 0.0f && zNear < zFar);

    // Reference: http://msdn.microsoft.com/en-us/library/bb205355(v=vs.85).aspx
    // 2*zn/w  0       0              0
    // 0       2*zn/h  0              0
    // 0       0       zf/(zn-zf)    -1
    // 0       0       zn*zf/(zn-zf)  0

    float nearSubFar = zNear - zFar;

    return { 2 * zNear / width, 0.0f              , 0.0f                     , 0.0f
           , 0.0f             , 2 * zNear / height, 0.0f                     , 0.0f
           , 0.0f             , 0.0f              , zFar / nearSubFar        , -1.0f
           , 0.0f             , 0.0f              , zNear * zFar / nearSubFar, 0.0f };
}

Matrix Matrix::create_perspective_field_of_view(const Radians& fieldOfView, float aspectRatio
                                              , float          zNear      , float zFar) noexcept
{
    Expects(fieldOfView.value() >= 0.0f && fieldOfView.value() <= Math::pi);
    Expects(zNear >= 0.0f);
    Expects(zFar >= 0.0f);
    Expects(zNear < zFar);

    // Reference: http://msdn.microsoft.com/en-us/library/bb205351(v=vs.85).aspx
    // xScale     0          0              0
    // 0        yScale       0              0
    // 0        0        zf/(zn-zf)        -1
    // 0        0        zn*zf/(zn-zf)      0
    //
    // where:
    // yScale = cot(fovY/2)
    // xScale = yScale / aspect ratio

    float yScale     = 1.0f / std::tan(fieldOfView.value() / 2);
    float xScale     = yScale / aspectRatio;
    float nearSubFar = zNear - zFar;

    return { xScale, 0.0f  , 0.0f                     , 0.0f
           , 0.0f  , yScale, 0.0f                     , 0.0f
           , 0.0f  , 0.0f  , zFar / nearSubFar        , -1.0f
           , 0.0f  , 0.0f  , zNear * zFar / nearSubFar, 0.0f };
}

Matrix Matrix::create_perspective_off_center(float left  , float right
                                           , float bottom, float top
                                           , float zNear , float zFar) noexcept
{
    Expects(zNear >= 0.0f);
    Expects(zFar >= 0.0f);
    Expects(zNear < zFar);

    // Reference : https://msdn.microsoft.com/en-us/library/bb205354(v=vs.85).aspx

    // 2*zn/(r-l)   0            0                0
    // 0            2*zn/(t-b)   0                0
    // (l+r)/(r-l)  (t+b)/(t-b)  zf/(zn-zf)      -1
    // 0            0            zn*zf/(zn-zf)    0

    float rightSubLeft  = right - left;
    float leftPlusRight = left + right;
    float topSubBottom  = top - bottom;
    float topPlusBottom = top + bottom;
    float nearSubFar    = zNear - zFar;

    return { 2.0f * zNear / rightSubLeft , 0.0f                        , 0.0f                     , 0.0f
           , 0.0f                        , 2 * zNear / topSubBottom    , 0.0f                     , 0.0f
           , leftPlusRight / rightSubLeft, topPlusBottom / topSubBottom, zFar / nearSubFar        , -1.0f
           , 0.0f                        , 0.0f                        , zNear * zFar / nearSubFar, 0.0f};
}

Matrix Matrix::create_rotation_x(const Radians& angle) noexcept
{
    // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
    float cos = std::cos(angle.value());
    float sin = std::sin(angle.value());

    return { 1.0f, 0.0f, 0.0f, 0.0f
           , 0.0f,  cos,  sin, 0.0f
           , 0.0f, -sin,  cos, 0.0f
           , 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix Matrix::create_rotation_x(const Radians& angle, const Vector3& center) noexcept
{
    // Reference: http://www.euclideanspace.com/maths/geometry/affine/aroundPoint/matrix3d/index.htm
    //
    // r00	r01	r02	x - r00*x - r01*y - r02*z
    // r10	r11	r12	y - r10*x - r11*y - r12*z
    // r20	r21	r22	z - r20*x - r21*y - r22*z
    // 0	0	0	1

    float cos = std::cos(angle.value());
    float sin = std::sin(angle.value());
    float y   = center.y;
    float z   = center.z;

    return { 1.0f, 0.0f                 , 0.0f                 , 0.0f
           , 0.0f,  cos                 , sin                  , 0.0f
           , 0.0f, -sin                 , cos                  , 0.0f
           , 0.0f, y - cos * y + sin * z, z - sin * y - cos * z, 1.0f };
}

Matrix Matrix::create_rotation_y(const Radians& angle) noexcept
{
    // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
    float cos = std::cos(angle.value());
    float sin = std::sin(angle.value());

    return {  cos, 0.0f, -sin, 0.0f
           , 0.0f, 1.0f, 0.0f, 0.0f
           ,  sin, 0.0f,  cos, 0.0f
           , 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix Matrix::create_rotation_y(const Radians& angle, const Vector3& center) noexcept
{
    // Reference: http://www.euclideanspace.com/maths/geometry/affine/aroundPoint/matrix3d/index.htm
    //
    // r00	r01	r02 x - r00*x - r01*y - r02*z
    // r10	r11	r12	y - r10*x - r11*y - r12*z
    // r20	r21	r22	z - r20*x - r21*y - r22*z
    // 0	0	0	1

    float cos = std::cos(angle.value());
    float sin = std::sin(angle.value());
    float x   = center.x;
    float z   = center.z;

    return { cos                  , 0.0f, -sin                 , 0.0f
           , 0.0f                 , 1.0f, 0.0f                 , 0.0f
           , sin                  , 0.0f, cos                  , 0.0f
           , x - cos * x - sin * z, 0.0f, z + sin * x - cos * z, 1.0f };
}

Matrix Matrix::create_rotation_z(const Radians& angle) noexcept
{
    // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
    float cos = std::cos(angle.value());
    float sin = std::sin(angle.value());

    return {  cos,  sin, 0.0f, 0.0f
           , -sin,  cos, 0.0f, 0.0f
           , 0.0f, 0.0f, 1.0f, 0.0f
           , 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix Matrix::create_rotation_z(const Radians& angle, const Vector3& center) noexcept
{
    // Reference: http://www.euclideanspace.com/maths/geometry/affine/aroundPoint/matrix3d/index.htm
    //
    // r00	r01	r02 x - r00*x - r01*y - r02*z
    // r10	r11	r12	y - r10*x - r11*y - r12*z
    // r20	r21	r22	z - r20*x - r21*y - r22*z
    // 0	0	0	1

    float cos = std::cos(angle.value());
    float sin = std::sin(angle.value());
    float x   = center.x;
    float y   = center.y;

    return { cos                  , sin                  , 0.0f, 0.0f
           , -sin                 , cos                  , 0.0f, 0.0f
           , 0.0f                 , 0.0f                 , 1.0f, 0.0f
           , x - cos * x + sin * y, y - sin * x - cos * y, 0.0f, 1.0f };
}

Matrix Matrix::create_scale(float scale) noexcept
{
    return Matrix::create_scale(scale, scale, scale);
}

Matrix Matrix::create_scale(float scale, const Vector3& center) noexcept
{
    return Matrix::create_scale(scale, scale, scale, center);
}

Matrix Matrix::create_scale(const Vector3& scales) noexcept
{
    return Matrix::create_scale(scales.x, scales.y, scales.z);
}

Matrix Matrix::create_scale(float xScale, float yScale, float zScale) noexcept
{
    return { xScale, 0.0f  , 0.0f  , 0.0f
           , 0.0f  , yScale, 0.0f  , 0.0f
           , 0.0f  , 0.0f  , zScale, 0.0f
           , 0.0f  , 0.0f  , 0.0f  , 1.0f };
}

Matrix Matrix::create_scale(const Vector3& scales, const Vector3& center) noexcept
{
    return Matrix::create_scale(scales.x, scales.y, scales.z, center);
}

Matrix Matrix::create_scale(float xScale, float yScale, float zScale, const Vector3& center) noexcept
{
    // Reference: http://www.euclideanspace.com/maths/geometry/affine/aroundPoint/matrix3d/index.htm
    //
    // s00	s01	s02 x - s00*x - s01*y - s02*z
    // s10	s11	s12	y - s10*x - s11*y - s12*z
    // s20	s21	s22	z - s20*x - s21*y - s22*z
    // 0	0	0	1

    float x  = center.x;
    float y  = center.y;
    float z  = center.z;

    return { xScale        , 0.0f          , 0.0f          , 0.0f
           , 0.0f          , yScale        , 0.0f          , 0.0f
           , 0.0f          , 0.0f          , zScale        , 0.0f
           , x - xScale * x, y - yScale * y, z - zScale * z, 1.0f };
}

Matrix Matrix::create_translation(const Vector3& position) noexcept
{
    return Matrix::create_translation(position.x, position.y, position.z);
}

Matrix Matrix::create_translation(float x, float y, float z) noexcept
{
    return { 1.0f, 0.0f, 0.0f, 0.0f
           , 0.0f, 1.0f, 0.0f, 0.0f
           , 0.0f, 0.0f, 1.0f, 0.0f
           , x   , y   , z   , 1.0f };
}

Matrix Matrix::create_reflection(const Plane &plane) noexcept
{
    // Reference: https://msdn.microsoft.com/en-us/library/bb205356(v=vs.85).aspx
    // P = normalize(Plane);

    // -2 * P.a * P.a + 1  -2 * P.b * P.a      -2 * P.c * P.a        0
    // -2 * P.a * P.b      -2 * P.b * P.b + 1  -2 * P.c * P.b        0
    // -2 * P.a * P.c      -2 * P.b * P.c      -2 * P.c * P.c + 1    0
    // -2 * P.a * P.d      -2 * P.b * P.d      -2 * P.c * P.d        1

    auto P = Plane::normalize(plane);
    auto a = -P.normal.x;
    auto b = -P.normal.y;
    auto c = -P.normal.z;
    auto d = -P.d;

    return { -2 * a * a + 1, -2 * b * a    , -2 * c * a    , 0.0f
           , -2 * a * b    , -2 * b * b + 1, -2 * c * b    , 0.0f
           , -2 * a * c    , -2 * b * c    , -2 * c * c + 1, 0.0f
           , -2 * a * d    , -2 * b * d    , -2 * c * d    , 1.0f };
}

Matrix Matrix::create_shadow(const Vector3& lightDirection, const Plane& plane) noexcept
{
    // Reference: https://msdn.microsoft.com/en-us/library/bb205364(v=vs.85).aspx

    // P = normalize(Plane);
    // L = Light;
    // d = -dot(P, L)

    // P.a * L.x + d  P.a * L.y      P.a * L.z      P.a * L.w
    // P.b * L.x      P.b * L.y + d  P.b * L.z      P.b * L.w
    // P.c * L.x      P.c * L.y      P.c * L.z + d  P.c * L.w
    // P.d * L.x      P.d * L.y      P.d * L.z      P.d * L.w + d
    //
    // If the light's w-component is 0, the ray from the origin to the light represents a directional light.
    // If it is 1, the light is a point light.

    auto P = Plane::normalize(plane);
    auto L = Vector4 { lightDirection, 0.0f };
    auto a = -P.normal.x;
    auto b = -P.normal.y;
    auto c = -P.normal.z;
    auto d = -P.d;
    auto D = Plane::dot(P, L);

    return { a * L.x + D, a * L.y    , a * L.z    , a * L.w
           , b * L.x    , b * L.y + D, b * L.z    , b * L.w
           , c * L.x    , c * L.y    , c * L.z + D, c * L.w
           , d * L.x    , d * L.y    , d * L.z    , d * L.w + D };
}

Matrix Matrix::create_world(const Vector3& position, const Vector3& forward, const Vector3& up) noexcept
{
    auto nf    = Vector3::normalize(forward);
    auto right = Vector3::normalize(Vector3::cross(nf, Vector3::normalize(up)));
    auto upv   = Vector3::normalize(Vector3::cross(right, nf));

    return { right.x   , right.y   , right.z   , 0.0f
           , upv.x     , upv.y     , upv.z     , 0.0f
           , -nf.x     , -nf.y     , -nf.z     , 0.0f
           , position.x, position.y, position.z, 1.0f };
}

bool Matrix::decompose(const Matrix& matrix, Vector3& scale, Quaternion& rotation, Vector3& translation) noexcept
{
    // http://callumhay.blogspot.fr/2010/10/decomposing-affine-transforms.html

    // Copy the matrix first - we'll use this to break down each component
    Matrix mcopy = matrix;

    // Start by extracting the translation (and/or any projection) from the given matrix
    translation = mcopy.translation();

    mcopy.translation({ 0.0f });
    mcopy.m44 = 1.0;

    // Extract the rotation component - this is done using polar decompostion, where
    // we successively average the matrix with its inverse transpose until there is
    // no/a very small difference between successive averages
    float        norm  = 0.0f;
    std::int32_t count = 0;

    Matrix mrotation = mcopy;

    do {
        Matrix nextRotation;
        Matrix currInvTranspose = Matrix::invert(Matrix::transpose(mrotation));

        // find the next rotation matrix
        nextRotation = (mrotation + currInvTranspose) * 0.5f;

        norm = 0.0;

        for (std::uint32_t i = 0; i < 3; i++)
        {
            float n = std::abs(mrotation[i * 4 + 0] - nextRotation[i * 4 + 0])
                    + std::abs(mrotation[i * 4 + 1] - nextRotation[i * 4 + 1])
                    + std::abs(mrotation[i * 4 + 2] - nextRotation[i * 4 + 2]);

            norm = std::max(norm, n);
        }

        mrotation = nextRotation;
    } while (++count < 100 && norm > Math::epsilon);

    // Extract the scale
    auto v1 = Vector3 { mcopy.m11, mcopy.m12, mcopy.m13 };
    auto v2 = Vector3 { mcopy.m21, mcopy.m22, mcopy.m23 };
    auto v3 = Vector3 { mcopy.m31, mcopy.m32, mcopy.m33 };

    scale = { v1.length(), v2.length(), v3.length() };

    // Calculate the normalized rotation matrix and take its determinant to determine whether
    // it had a negative scale or not...
    auto row1 = Vector3::normalize(v1);
    auto row2 = Vector3::normalize(v2);
    auto row3 = Vector3::normalize(v3);

    Matrix nRotation(row1.x, row1.y, row1.z, 0.0f
                   , row2.x, row2.y, row2.z, 0.0f
                   , row3.x, row3.y, row3.z, 0.0f
                   ,   0.0f,   0.0f,   0.0f, 1.0f);

    rotation = Quaternion::create_from_rotation_matrix(nRotation);

    // Special consideration: if there's a single negative scale
    // (all other combinations of negative scales will
    // be part of the rotation matrix), the determinant of the
    // normalized rotation matrix will be < 0.
    // If this is the case we apply an arbitrary negative to one
    // of the component of the scale.
    auto determinant = nRotation.determinant();

    if (determinant < 0.0f)
    {
        scale.x *= -1;
    }

    return (determinant > Math::epsilon);
}

Matrix Matrix::invert(const Matrix& matrix) noexcept
{
    Matrix inverse = Matrix::identity;

    // Algorithm: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
    auto         mdet = matrix.determinant();
    Matrix       mtemp;
    std::int32_t sign;

    for (std::uint32_t i = 0; i < 4; i++)
    {
        for (std::uint32_t j = 0; j < 4; j++)
        {
            sign               = 1 - ((i + j) % 2) * 2;
            mtemp              = matrix.sub_matrix(i, j);
            inverse[i + j * 4] = (mtemp.sub_matrix_determinant() * sign) / mdet;
        }
    }

    return inverse;
}

Matrix Matrix::negate(const Matrix& matrix) noexcept
{
    return matrix * -1;
}

Matrix Matrix::transform(const Matrix& value, const Quaternion& rotation) noexcept
{
    return value * Matrix::create_from_quaternion(rotation);
}

Matrix Matrix::transpose(const Matrix& source) noexcept
{
    return { source.m11, source.m21, source.m31, source.m41
           , source.m12, source.m22, source.m32, source.m42
           , source.m13, source.m23, source.m33, source.m43
           , source.m14, source.m24, source.m34, source.m44 };
}

Matrix::Matrix() noexcept
    : Matrix { 0.0f, 0.0f, 0.0f, 0.0f
             , 0.0f, 0.0f, 0.0f, 0.0f
             , 0.0f, 0.0f, 0.0f, 0.0f
             , 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Matrix::Matrix(float m11, float m12, float m13, float m14
             , float m21, float m22, float m23, float m24
             , float m31, float m32, float m33, float m34
             , float m41, float m42, float m43, float m44) noexcept
    : m11 { m11 }, m12 { m12 }, m13 { m13 }, m14 { m14 }
    , m21 { m21 }, m22 { m22 }, m23 { m23 }, m24 { m24 }
    , m31 { m31 }, m32 { m32 }, m33 { m33 }, m34 { m34 }
    , m41 { m41 }, m42 { m42 }, m43 { m43 }, m44 { m44 }
{
}

Vector3 Matrix::translation() const noexcept
{
    return { m41, m42, m43 };
}

void Matrix::translation(const Vector3& translation) noexcept
{
    m41 = translation.x;
    m42 = translation.y;
    m43 = translation.z;
}

float Matrix::determinant() const noexcept
{
    // Algorithm: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
    std::int32_t i      = 1;
    float        result = 0;
    float        det    = 0;
    Matrix       msub;

    for (std::uint32_t n = 0; n < 4; n++, i *= -1)
    {
        msub    = sub_matrix(0, n);
        det     = msub.sub_matrix_determinant();
        result += data[n] * det * i;
    }

    return result;
}

bool Matrix::has_inverse() const noexcept
{
    return (std::abs(determinant()) > 0.0005f);
}

bool Matrix::is_identity() const noexcept
{
    return (*this == Matrix::identity);
}

std::string Matrix::to_string() const noexcept
{
    std::ostringstream stream;

    // loop through 3x3 submatrix
    for (std::uint32_t di = 0; di < 4; di++)
    {
        for (std::uint32_t dj = 0; dj < 4; dj++)
        {
            stream << data[di * 4 + dj] << '\t';
        }

        stream << '\n';
    }

    return stream.str();
}

float& Matrix::operator[](const std::size_t& index)
{
    Expects(index < 16);

    return data[index];
}

const float& Matrix::operator[](const std::size_t& index) const
{
    Expects(index < 16);

    return data[index];
}

bool Matrix::operator==(const Matrix& matrix) const
{
    return (Math::equal(m11, matrix.m11)
         && Math::equal(m12, matrix.m12)
         && Math::equal(m13, matrix.m13)
         && Math::equal(m14, matrix.m14)
         && Math::equal(m21, matrix.m21)
         && Math::equal(m22, matrix.m22)
         && Math::equal(m23, matrix.m23)
         && Math::equal(m24, matrix.m24)
         && Math::equal(m31, matrix.m31)
         && Math::equal(m32, matrix.m32)
         && Math::equal(m33, matrix.m33)
         && Math::equal(m34, matrix.m34)
         && Math::equal(m41, matrix.m41)
         && Math::equal(m42, matrix.m42)
         && Math::equal(m43, matrix.m43)
         && Math::equal(m44, matrix.m44));
}

bool Matrix::operator!=(const Matrix& matrix) const
{
    return !(*this == matrix);
}

Matrix& Matrix::operator*=(const Matrix& right)
{
    auto left = *this;

    m11 = ((left.m11 * right.m11) + (left.m12 * right.m21) + (left.m13 * right.m31) + (left.m14 * right.m41));
    m12 = ((left.m11 * right.m12) + (left.m12 * right.m22) + (left.m13 * right.m32) + (left.m14 * right.m42));
    m13 = ((left.m11 * right.m13) + (left.m12 * right.m23) + (left.m13 * right.m33) + (left.m14 * right.m43));
    m14 = ((left.m11 * right.m14) + (left.m12 * right.m24) + (left.m13 * right.m34) + (left.m14 * right.m44));

    m21 = ((left.m21 * right.m11) + (left.m22 * right.m21) + (left.m23 * right.m31) + (left.m24 * right.m41));
    m22 = ((left.m21 * right.m12) + (left.m22 * right.m22) + (left.m23 * right.m32) + (left.m24 * right.m42));
    m23 = ((left.m21 * right.m13) + (left.m22 * right.m23) + (left.m23 * right.m33) + (left.m24 * right.m43));
    m24 = ((left.m21 * right.m14) + (left.m22 * right.m24) + (left.m23 * right.m34) + (left.m24 * right.m44));

    m31 = ((left.m31 * right.m11) + (left.m32 * right.m21) + (left.m33 * right.m31) + (left.m34 * right.m41));
    m32 = ((left.m31 * right.m12) + (left.m32 * right.m22) + (left.m33 * right.m32) + (left.m34 * right.m42));
    m33 = ((left.m31 * right.m13) + (left.m32 * right.m23) + (left.m33 * right.m33) + (left.m34 * right.m43));
    m34 = ((left.m31 * right.m14) + (left.m32 * right.m24) + (left.m33 * right.m34) + (left.m34 * right.m44));

    m41 = ((left.m41 * right.m11) + (left.m42 * right.m21) + (left.m43 * right.m31) + (left.m44 * right.m41));
    m42 = ((left.m41 * right.m12) + (left.m42 * right.m22) + (left.m43 * right.m32) + (left.m44 * right.m42));
    m43 = ((left.m41 * right.m13) + (left.m42 * right.m23) + (left.m43 * right.m33) + (left.m44 * right.m43));
    m44 = ((left.m41 * right.m14) + (left.m42 * right.m24) + (left.m43 * right.m34) + (left.m44 * right.m44));

    return *this;
}

Matrix& Matrix::operator*=(const float& value)
{
    m11 *= value;
    m12 *= value;
    m13 *= value;
    m14 *= value;

    m21 *= value;
    m22 *= value;
    m23 *= value;
    m24 *= value;

    m31 *= value;
    m32 *= value;
    m33 *= value;
    m34 *= value;

    m41 *= value;
    m42 *= value;
    m43 *= value;
    m44 *= value;

    return *this;
}

Matrix& Matrix::operator+=(const Matrix& matrix)
{
    m11 += matrix.m11;
    m12 += matrix.m12;
    m13 += matrix.m13;
    m14 += matrix.m14;

    m21 += matrix.m21;
    m22 += matrix.m22;
    m23 += matrix.m23;
    m24 += matrix.m24;

    m31 += matrix.m31;
    m32 += matrix.m32;
    m33 += matrix.m33;
    m34 += matrix.m34;

    m41 += matrix.m41;
    m42 += matrix.m42;
    m43 += matrix.m43;
    m44 += matrix.m44;

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix)
{
    m11 -= matrix.m11;
    m12 -= matrix.m12;
    m13 -= matrix.m13;
    m14 -= matrix.m14;

    m21 -= matrix.m21;
    m22 -= matrix.m22;
    m23 -= matrix.m23;
    m24 -= matrix.m24;

    m31 -= matrix.m31;
    m32 -= matrix.m32;
    m33 -= matrix.m33;
    m34 -= matrix.m34;

    m41 -= matrix.m41;
    m42 -= matrix.m42;
    m43 -= matrix.m43;
    m44 -= matrix.m44;

    return *this;
}

const Matrix Matrix::operator*(const Matrix& matrix) const
{
    auto result = *this;

    result *= matrix;

    return result;
}

const Matrix Matrix::operator*(const float& value) const
{
    auto result = *this;

    result *= value;

    return result;
}

const Matrix Matrix::operator+(const Matrix& matrix) const
{
    auto result = *this;

    result += matrix;

    return result;
}

const Matrix Matrix::operator-(const Matrix& matrix) const
{
    auto result = *this;

    result -= matrix;

    return result;
}

const Matrix Matrix::operator-() const
{
    auto result = *this;

    result *= -1;

    return result;
}

float Matrix::sub_matrix_determinant()
{
    // Algorithm: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q23
    return m11 * (m22 * m33 - m32 * m23)
         - m12 * (m21 * m33 - m31 * m23)
         + m13 * (m21 * m32 - m31 * m22);
}

Matrix Matrix::sub_matrix(std::uint32_t row, std::uint32_t column) const
{
    // Algorithm: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
    std::uint32_t si;
    std::uint32_t sj;
    Matrix        result;

    // loop through 3x3 submatrix
    for (std::uint32_t di = 0; di < 3; di++)
    {
        for (std::uint32_t dj = 0; dj < 3; dj++)
        {
            // map 3x3 element (destination) to 4x4 element (source)
            si = di + ((di >= row) ? 1 : 0);
            sj = dj + ((dj >= column) ? 1 : 0);

            // copy element
            result[di * 4 + dj] = data[si * 4 + sj];
        }
    }

    return result;
}

}}
