// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Matrix.hpp>

#include <cmath>
#include <cassert>
#include <stdexcept>

#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/MathHelper.hpp>

using namespace System;
using namespace SceneR::Framework;

const Matrix& Matrix::Identity { 1.0f, 0.0f, 0.0f, 0.0f
                               , 0.0f, 1.0f, 0.0f, 0.0f
                               , 0.0f, 0.0f, 1.0f, 0.0f
                               , 0.0f, 0.0f, 0.0f, 1.0f };

Matrix Matrix::CreateFromAxisAngle(const Vector3& axis, const Single&  angle)
{
    // http://mathworld.wolfram.com/RodriguesRotationFormula.html
    auto   naxis = Vector3::Normalize(axis);
    Single cos   = std::cos(angle);
    Single sin   = std::sin(angle);
    Single cos_1 = 1.0f - cos;
    Single x     = naxis.X();
    Single y     = naxis.Y();
    Single z     = naxis.Z();
    Single xx    = x * x;
    Single yy    = y * y;
    Single zz    = z * z;
    Single xy    = x * y;
    Single yz    = y * z;
    Single xz    = x * z;

    return { cos + xx * cos_1     , z * sin + xy * cos_1 , -y * sin + xz * cos_1, 0.0f
           , xy * cos_1 - z * sin , cos + yy * cos_1     , x * sin + yz * cos_1 , 0.0f
           , y * sin + xz * cos_1 , -x * sin + yz * cos_1, cos + zz * cos_1     , 0.0f
           , 0.0f                 , 0.0f                 , 0.0f                 , 1.0f };
}

Matrix Matrix::CreateFromQuaternion(const Quaternion& quaternion)
{
    // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
    //            http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    //
    // 1 - 2yy - 2zz    2xy - 2zw       2xz + 2yw
    // 2xy + 2zw        1 - 2xx - 2zz   2yz - 2xw
    // 2xz - 2yw        2yz + 2xw       1 - 2xx - 2yy

    Single xx = quaternion.X() * quaternion.X();
    Single yy = quaternion.Y() * quaternion.Y();
    Single zz = quaternion.Z() * quaternion.Z();
    Single xy = quaternion.X() * quaternion.Y();
    Single zw = quaternion.Z() * quaternion.W();
    Single xz = quaternion.X() * quaternion.Z();
    Single yw = quaternion.Y() * quaternion.W();
    Single yz = quaternion.Y() * quaternion.Z();
    Single xw = quaternion.X() * quaternion.W();

    return { 1.0f - 2.0f * (yy + zz), 2.0f * (xy + zw)       , 2.0f * (xz - yw)       , 0.0f
           , 2.0f * (xy - zw)       , 1.0f - 2.0f * (xx + zz), 2.0f * (yz + xw)       , 0.0f
           , 2.0f * (xz + yw)       , 2.0f * (yz - xw)       , 1.0f - 2.0f * (xx + yy), 0.0f
           , 0.0f                   , 0.0f                   , 0.0f                   , 1.0f };
}

Matrix Matrix::CreateFromYawPitchRoll(const Single& yaw, const Single& pitch, const Single& roll)
{
    return Matrix::CreateFromAxisAngle(Vector3::UnitZ, roll)
         * Matrix::CreateFromAxisAngle(Vector3::UnitX, pitch)
         * Matrix::CreateFromAxisAngle(Vector3::UnitY, yaw);
}

Matrix Matrix::CreateFrustum(const Single& left  , const Single& right
                           , const Single& bottom, const Single& top
                           , const Single& zNear , const Single& zFar)
{
    if (zNear < 0 || zFar < 0)
    {
        throw std::invalid_argument("zNear and zFar should be positive values.");
    }

    Single rightSubLeft  = right - left;
    Single rightPlusLeft = right + left;
    Single topSubBottom  = top - bottom;
    Single topPlusBottom = top + bottom;
    Single farSubNear    = zFar - zNear;
    Single farPlusNear   = zFar - zNear;

    return { (2 * zNear) / rightSubLeft, 0.0f                      , (rightPlusLeft / rightSubLeft), 0.0f
           , 0.0f                      , (2 * zNear) / topSubBottom, (topPlusBottom / topSubBottom), 0.0f
           , 0.0f                      , 0.0f                      , -(farPlusNear  / farSubNear)  , -(2 * zFar * zNear / farSubNear)
           , 0.0f                      , 0.0f                      , -1.0f                         , 0.0f };
}

Matrix Matrix::CreateLookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& cameraUpVector)
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/bb281711(v=vs.85).aspx
    // zaxis = normal(cameraPosition - cameraTarget)
    // xaxis = normal(cross(cameraUpVector, zaxis))
    // yaxis = cross(zaxis, xaxis)

    //  xaxis.x                    yaxis.x                     zaxis.x                     0
    //  xaxis.y                    yaxis.y                     zaxis.y                     0
    //  xaxis.z                    yaxis.z                     zaxis.z                     0
    // -dot(xaxis, cameraPosition) -dot(yaxis, cameraPosition) -dot(zaxis, cameraPosition) 1

    auto zAxis = Vector3::Normalize(cameraPosition - cameraTarget);
    auto xAxis = Vector3::Normalize(Vector3::Cross(cameraUpVector, zAxis));
    auto yAxis = Vector3::Cross(zAxis, xAxis);
    auto dx    = Vector3::DotProduct(xAxis, cameraPosition);
    auto dy    = Vector3::DotProduct(yAxis, cameraPosition);
    auto dz    = Vector3::DotProduct(zAxis, cameraPosition);

    return { xAxis.X(), yAxis.X(), zAxis.X(), 0.0f
           , xAxis.Y(), yAxis.Y(), zAxis.Y(), 0.0f
           , xAxis.Z(), yAxis.Z(), zAxis.Z(), 0.0f
           , -dx      , -dy      , -dz      , 1.0f };
}

Matrix Matrix::CreateOrthographic(const Single& width, const Single& height, const Single& zNear, const Single& zFar)
{
    // Reference: http://msdn.microsoft.com/en-us/library/bb205349(v=vs.85).aspx
    // 2/w  0    0           0
    // 0    2/h  0           0
    // 0    0    1/(zn-zf)   0
    // 0    0    zn/(zn-zf)  1

    Single nearSubFar = zNear - zFar;

    return { 2.0f / width, 0.0f         , 0.0f              , 0.0f
           , 0           , 2.0f / height, 0.0f              , 0.0f
           , 0.0f        , 0.0f         , 1 / nearSubFar    , 0.0f
           , 0.0f        , 0.0f         , zNear / nearSubFar, 1.0f };
}

Matrix Matrix::CreateOrthographicOffCenter(const Single& left  , const Single& right
                                         , const Single& bottom, const Single& top
                                         , const Single& zNear , const Single& zFar)
{
    // Reference: http://msdn.microsoft.com/en-us/library/bb205348(v=vs.85).aspx
    // 2/(r-l)      0            0           0
    // 0            2/(t-b)      0           0
    // 0            0            1/(zn-zf)   0
    // (l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1

    Single leftSubRight  = left - right;
    Single leftPlusRight = left + right;
    Single bottomSubTop  = bottom - top;
    Single topPlusBottom = top + bottom;
    Single nearSubFar    = zNear - zFar;

    return { 2.0f / (right - left)       , 0.0f                        , 0.0f              , 0.0f
           , 0.0f                        , 2.0f / (top - bottom)       , 0.0f              , 0.0f
           , 0.0f                        , 0.0f                        , 1.0f / nearSubFar , 0.0f
           , leftPlusRight / leftSubRight, topPlusBottom / bottomSubTop, zNear / nearSubFar, 1.0f };
}

Matrix Matrix::CreatePerspective(const Single& width, const Single& height
                               , const Single& zNear, const Single& zFar)
{
    // Reference: http://msdn.microsoft.com/en-us/library/bb205355(v=vs.85).aspx
    // 2*zn/w  0       0              0
    // 0       2*zn/h  0              0
    // 0       0       zf/(zn-zf)    -1
    // 0       0       zn*zf/(zn-zf)  0

    if (zNear <= 0.0f)
    {
        throw std::out_of_range("zNear should be a positive value.");
    }

    if (zFar <= 0.0f)
    {
        throw std::out_of_range("zNear should be a positive value.");
    }

    if (zNear >= zFar)
    {
        throw std::out_of_range("zNear should be greather than zFar.");
    }

    Single nearSubFar = zNear - zFar;

    return { 2 * zNear / width, 0.0f              , 0.0f                     , 0.0f
           , 0.0f             , 2 * zNear / height, 0.0f                     , 0.0f
           , 0.0f             , 0.0f              , zFar / nearSubFar        , -1.0f
           , 0.0f             , 0.0f              , zNear * zFar / nearSubFar, 0.0f };
}

Matrix Matrix::CreatePerspectiveFieldOfView(const Single& fieldOfView, const Single& aspectRatio,
                                            const Single& zNear      , const Single& zFar)
{
    // Reference: http://msdn.microsoft.com/en-us/library/bb205351(v=vs.85).aspx
    // xScale     0          0              0
    // 0        yScale       0              0
    // 0        0        zf/(zn-zf)        -1
    // 0        0        zn*zf/(zn-zf)      0
    //
    // where:
    // yScale = cot(fovY/2)
    // xScale = yScale / aspect ratio

    if (fieldOfView <= 0.0f || fieldOfView >= MathHelper::Pi)
    {
        throw std::out_of_range("fieldOfView should be a positive value less than MathHelper::Pi");
    }

    if (zNear <= 0.0f)
    {
        throw std::out_of_range("zNear should be a positive value.");
    }

    if (zFar <= 0.0f)
    {
        throw std::out_of_range("zNear should be a positive value.");
    }

    if (zNear >= zFar)
    {
        throw std::out_of_range("zNear should be greather than zFar.");
    }

    Single yScale     = 1.0f / std::tan(fieldOfView / 2);
    Single xScale     = yScale / aspectRatio;
    Single nearSubFar = zNear - zFar;

    return { xScale, 0.0f  , 0.0f                     , 0.0f
           , 0.0f  , yScale, 0.0f                     , 0.0f
           , 0.0f  , 0.0f  , zFar / nearSubFar        , -1.0f
           , 0.0f  , 0.0f  , zNear * zFar / nearSubFar, 0.0f };
}

Matrix Matrix::CreatePerspectiveOffCenter(const Single& left
                                        , const Single& right
                                        , const Single& bottom
                                        , const Single& top
                                        , const Single& zNear
                                        , const Single& zFar)
{
    if (zNear <= 0.0f)
    {
        throw std::out_of_range("zNear should be a positive value.");
    }

    if (zFar <= 0.0f)
    {
        throw std::out_of_range("zNear should be a positive value.");
    }

    if (zNear >= zFar)
    {
        throw std::out_of_range("zNear should be greather than zFar.");
    }

    // Reference : https://msdn.microsoft.com/en-us/library/bb205354(v=vs.85).aspx

    // 2*zn/(r-l)   0            0                0
    // 0            2*zn/(t-b)   0                0
    // (l+r)/(r-l)  (t+b)/(t-b)  zf/(zn-zf)      -1
    // 0            0            zn*zf/(zn-zf)    0

    Single rightSubLeft  = right - left;
    Single leftPlusRight = left + right;
    Single topSubBottom  = top - bottom;
    Single topPlusBottom = top + bottom;
    Single nearSubFar    = zNear - zFar;

    return { 2.0f * zNear / rightSubLeft , 0.0f                        , 0.0f                     , 0.0f
           , 0.0f                        , 2 * zNear / topSubBottom    , 0.0f                     , 0.0f
           , leftPlusRight / rightSubLeft, topPlusBottom / topSubBottom, zFar / nearSubFar        , -1.0f
           , 0.0f                        , 0.0f                        , zNear * zFar / nearSubFar, 0.0f};
}


Matrix Matrix::CreateRotationX(const Single& angle)
{
    // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
    Single cos = std::cos(angle);
    Single sin = std::sin(angle);

    return { 1.0f, 0.0f, 0.0f, 0.0f
           , 0.0f,  cos,  sin, 0.0f
           , 0.0f, -sin,  cos, 0.0f
           , 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix Matrix::CreateRotationY(const Single& angle)
{
    // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
    Single cos = std::cos(angle);
    Single sin = std::sin(angle);

    return {  cos, 0.0f, -sin, 0.0f
           , 0.0f, 1.0f, 0.0f, 0.0f
           ,  sin, 0.0f,  cos, 0.0f
           , 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix Matrix::CreateRotationZ(const Single& angle)
{
    // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
    Single cos = std::cos(angle);
    Single sin = std::sin(angle);

    return {  cos,  sin, 0.0f, 0.0f
           , -sin,  cos, 0.0f, 0.0f
           , 0.0f, 0.0f, 1.0f, 0.0f
           , 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix Matrix::CreateScale(const Single& scale)
{
    return Matrix::CreateScale(scale, scale, scale);
}

Matrix Matrix::CreateScale(const Vector3& scales)
{
    return Matrix::CreateScale(scales.X(), scales.Y(), scales.Z());
}

Matrix Matrix::CreateScale(const Single& xScale, const Single& yScale, const Single& zScale)
{
    return { xScale, 0.0f  , 0.0f  , 0.0f
           , 0.0f  , yScale, 0.0f  , 0.0f
           , 0.0f  , 0.0f  , zScale, 0.0f
           , 0.0f  , 0.0f  , 0.0f  , 1.0f };
}

Matrix Matrix::CreateTranslation(const Vector3& position)
{
    return Matrix::CreateTranslation(position.X(), position.Y(), position.Z());
}

Matrix Matrix::CreateTranslation(const Single& x, const Single& y, const Single& z)
{
    return { 1.0f, 0.0f, 0.0f, 0.0f
           , 0.0f, 1.0f, 0.0f, 0.0f
           , 0.0f, 0.0f, 1.0f, 0.0f
           , x   , y   , z   , 1.0f };
}

Matrix Matrix::CreateWorld(const Vector3& position, const Vector3& forward, const Vector3& up)
{
    auto nf    = Vector3::Normalize(forward);
    auto right = Vector3::Normalize(Vector3::Cross(nf, up));
    auto upv   = Vector3::Normalize(Vector3::Cross(right, nf));

    return { right.X()   , right.Y()   , right.Z()   , 0.0f
           , upv.X()     , upv.Y()     , upv.Z()     , 0.0f
           , -forward.X(), -forward.Y(), -forward.Z(), 0.0f
           , position.X(), position.Y(), position.Z(), 1.0f };
}

bool Matrix::Decompose(const Matrix& matrix, Vector3& scale, Quaternion& rotation, Vector3& translation)
{
    auto result = Matrix { matrix };

    return result.Decompose(scale, rotation, translation);
}

Matrix Matrix::Invert(const Matrix& matrix)
{
    auto result = Matrix(matrix);

    result.Invert();

    return result;
}

Matrix Matrix::Negate(const Matrix& matrix)
{
    return matrix * -1;
}

Matrix Matrix::Transform(const Matrix& value, const Quaternion& rotation)
{
    return value * Matrix::CreateFromQuaternion(rotation);
}

Matrix Matrix::Transpose(const Matrix& source)
{
    return { source.m11, source.m21, source.m31, source.m41
           , source.m12, source.m22, source.m32, source.m42
           , source.m13, source.m23, source.m33, source.m43
           , source.m14, source.m24, source.m34, source.m44 };
}

Matrix::Matrix()
    : Matrix { 0.0f, 0.0f, 0.0f, 0.0f
             , 0.0f, 0.0f, 0.0f, 0.0f
             , 0.0f, 0.0f, 0.0f, 0.0f
             , 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Matrix::Matrix(const Single& m11, const Single& m12, const Single& m13, const Single& m14
             , const Single& m21, const Single& m22, const Single& m23, const Single& m24
             , const Single& m31, const Single& m32, const Single& m33, const Single& m34
             , const Single& m41, const Single& m42, const Single& m43, const Single& m44)
    : m11 { m11 }, m12 { m12 }, m13 { m13 }, m14 { m14 }
    , m21 { m21 }, m22 { m22 }, m23 { m23 }, m24 { m24 }
    , m31 { m31 }, m32 { m32 }, m33 { m33 }, m34 { m34 }
    , m41 { m41 }, m42 { m42 }, m43 { m43 }, m44 { m44 }
{
}

Matrix::Matrix(const Matrix& matrix)
    : m11 { matrix.m11 }, m12 { matrix.m12 }, m13 { matrix.m13 }, m14 { matrix.m14 }
    , m21 { matrix.m21 }, m22 { matrix.m22 }, m23 { matrix.m23 }, m24 { matrix.m24 }
    , m31 { matrix.m31 }, m32 { matrix.m32 }, m33 { matrix.m33 }, m34 { matrix.m34 }
    , m41 { matrix.m41 }, m42 { matrix.m42 }, m43 { matrix.m43 }, m44 { matrix.m44 }
{
}

const Single& Matrix::M11() const
{
    return this->m11;
}

const Single& Matrix::M12() const
{
    return this->m12;
}

const Single& Matrix::M13() const
{
    return this->m13;
}

const Single& Matrix::M14() const
{
    return this->m14;
}

const Single& Matrix::M21() const
{
    return this->m21;
}

const Single& Matrix::M22() const
{
    return this->m22;
}

const Single& Matrix::M23() const
{
    return this->m23;
}

const Single& Matrix::M24() const
{
    return this->m24;
}

const Single& Matrix::M31() const
{
    return this->m31;
}

const Single& Matrix::M32() const
{
    return this->m32;
}

const Single& Matrix::M33() const
{
    return this->m33;
}

const Single& Matrix::M34() const
{
    return this->m34;
}

const Single& Matrix::M41() const
{
    return this->m41;
}

const Single& Matrix::M42() const
{
    return this->m42;
}

const Single& Matrix::M43() const
{
    return this->m43;
}

const Single& Matrix::M44() const
{
    return this->m44;
}

void Matrix::M11(const System::Single& value)
{
    this->m11 = value;
}

void Matrix::M12(const System::Single& value)
{
    this->m12 = value;
}

void Matrix::M13(const System::Single& value)
{
    this->m13 = value;
}

void Matrix::M14(const System::Single& value)
{
    this->m14 = value;
}

void Matrix::M21(const System::Single& value)
{
    this->m21 = value;
}

void Matrix::M22(const System::Single& value)
{
    this->m22 = value;
}

void Matrix::M23(const System::Single& value)
{
    this->m23 = value;
}

void Matrix::M24(const System::Single& value)
{
    this->m24 = value;
}

void Matrix::M31(const System::Single& value)
{
    this->m31 = value;
}

void Matrix::M32(const System::Single& value)
{
    this->m32 = value;
}

void Matrix::M33(const System::Single& value)
{
    this->m33 = value;
}

void Matrix::M34(const System::Single& value)
{
    this->m34 = value;
}

void Matrix::M41(const Single& value)
{
    this->m41 = value;
}

void Matrix::M42(const Single& value)
{
    this->m42 = value;
}

void Matrix::M43(const Single& value)
{
    this->m43 = value;
}

void Matrix::M44(const Single& value)
{
    this->m44 = value;
}

bool Matrix::Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation)
{
    translation = { this->m41, this->m42, this->m43 };

    auto v1 = Vector3 { this->m11, this->m12, this->m13 };
    auto v2 = Vector3 { this->m21, this->m22, this->m23 };
    auto v3 = Vector3 { this->m31, this->m32, this->m33 };

    scale = { v1.Length(), v2.Length(), v3.Length() };

    if (this->Determinant() < 0.0f)
    {
        scale.Negate();
    }

    rotation = Quaternion::CreateFromRotationMatrix(*this);

    return (scale != Vector3::Zero && rotation != Quaternion::Identity && translation != Vector3::Zero);
}

Single Matrix::Determinant() const
{
    // Algorithm: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
	Int32  i      = 1;
    Single result = 0;
    Single det    = 0;
    Matrix msub;

    for (UInt32 n = 0; n < 4; n++, i *= -1)
    {
        msub    = this->SubMatrix(0, n);
        det     = msub.SubMatrixDeterminant();
        result += this->matrix[n] * det * i;
    }

    return result;
}

bool Matrix::HasInverse() const
{
    return (std::fabs(this->Determinant()) > 0.0005f);
}

void Matrix::Invert()
{
    if (this->HasInverse())
    {
        // Algorithm: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
        auto   mdet = this->Determinant();
        auto   copy = *this;
        Matrix mtemp;
        Int32  sign;

        for (UInt32 i = 0; i < 4; i++)
        {
            for (UInt32 j = 0; j < 4; j++)
            {
                sign                    = 1 - ((i + j) % 2) * 2;
                mtemp                   = copy.SubMatrix(i, j);
                this->matrix[i + j * 4] = (mtemp.SubMatrixDeterminant() * sign) / mdet;
            }
        }
    }
}

bool Matrix::IsIdentity() const
{
    return (*this == Matrix::Identity);
}

Single& Matrix::operator[](const Size& index)
{
    assert(index < 16);

    return this->matrix[index];
}

const Single& Matrix::operator[](const Size& index) const
{
    assert(index < 16);

    return this->matrix[index];
}

bool Matrix::operator==(const Matrix& matrix) const
{
    return (this->m11 == matrix.m11
         && this->m12 == matrix.m12
         && this->m13 == matrix.m13
         && this->m14 == matrix.m14
         && this->m21 == matrix.m21
         && this->m22 == matrix.m22
         && this->m23 == matrix.m23
         && this->m24 == matrix.m24
         && this->m31 == matrix.m31
         && this->m32 == matrix.m32
         && this->m33 == matrix.m33
         && this->m34 == matrix.m34
         && this->m41 == matrix.m41
         && this->m42 == matrix.m42
         && this->m43 == matrix.m43
         && this->m44 == matrix.m44);
}

bool Matrix::operator!=(const Matrix& matrix) const
{
    return !(*this == matrix);
}

Matrix& Matrix::operator*=(const Matrix& right)
{
    auto left = *this;

    this->m11 = ((left.m11 * right.m11) + (left.m12 * right.m21) + (left.m13 * right.m31) + (left.m14 * right.m41));
    this->m12 = ((left.m11 * right.m12) + (left.m12 * right.m22) + (left.m13 * right.m32) + (left.m14 * right.m42));
    this->m13 = ((left.m11 * right.m13) + (left.m12 * right.m23) + (left.m13 * right.m33) + (left.m14 * right.m43));
    this->m14 = ((left.m11 * right.m14) + (left.m12 * right.m24) + (left.m13 * right.m34) + (left.m14 * right.m44));

    this->m21 = ((left.m21 * right.m11) + (left.m22 * right.m21) + (left.m23 * right.m31) + (left.m24 * right.m41));
    this->m22 = ((left.m21 * right.m12) + (left.m22 * right.m22) + (left.m23 * right.m32) + (left.m24 * right.m42));
    this->m23 = ((left.m21 * right.m13) + (left.m22 * right.m23) + (left.m23 * right.m33) + (left.m24 * right.m43));
    this->m24 = ((left.m21 * right.m14) + (left.m22 * right.m24) + (left.m23 * right.m34) + (left.m24 * right.m44));

    this->m31 = ((left.m31 * right.m11) + (left.m32 * right.m21) + (left.m33 * right.m31) + (left.m34 * right.m41));
    this->m32 = ((left.m31 * right.m12) + (left.m32 * right.m22) + (left.m33 * right.m32) + (left.m34 * right.m42));
    this->m33 = ((left.m31 * right.m13) + (left.m32 * right.m23) + (left.m33 * right.m33) + (left.m34 * right.m43));
    this->m34 = ((left.m31 * right.m14) + (left.m32 * right.m24) + (left.m33 * right.m34) + (left.m34 * right.m44));

    this->m41 = ((left.m41 * right.m11) + (left.m42 * right.m21) + (left.m43 * right.m31) + (left.m44 * right.m41));
    this->m42 = ((left.m41 * right.m12) + (left.m42 * right.m22) + (left.m43 * right.m32) + (left.m44 * right.m42));
    this->m43 = ((left.m41 * right.m13) + (left.m42 * right.m23) + (left.m43 * right.m33) + (left.m44 * right.m43));
    this->m44 = ((left.m41 * right.m14) + (left.m42 * right.m24) + (left.m43 * right.m34) + (left.m44 * right.m44));

    return *this;
}

Matrix& Matrix::operator*=(const Single& value)
{
    this->m11 *= value;
    this->m12 *= value;
    this->m13 *= value;
    this->m14 *= value;

    this->m21 *= value;
    this->m22 *= value;
    this->m23 *= value;
    this->m24 *= value;

    this->m31 *= value;
    this->m32 *= value;
    this->m33 *= value;
    this->m34 *= value;

    this->m41 *= value;
    this->m42 *= value;
    this->m43 *= value;
    this->m44 *= value;

    return *this;
}

Matrix& Matrix::operator+=(const Matrix& matrix)
{
    this->m11 += matrix.m11;
    this->m12 += matrix.m12;
    this->m13 += matrix.m13;
    this->m14 += matrix.m14;

    this->m21 += matrix.m21;
    this->m22 += matrix.m22;
    this->m23 += matrix.m23;
    this->m24 += matrix.m24;

    this->m31 += matrix.m31;
    this->m32 += matrix.m32;
    this->m33 += matrix.m33;
    this->m34 += matrix.m34;

    this->m41 += matrix.m41;
    this->m42 += matrix.m42;
    this->m43 += matrix.m43;
    this->m44 += matrix.m44;

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix)
{
    this->m11 -= matrix.m11;
    this->m12 -= matrix.m12;
    this->m13 -= matrix.m13;
    this->m14 -= matrix.m14;

    this->m21 -= matrix.m21;
    this->m22 -= matrix.m22;
    this->m23 -= matrix.m23;
    this->m24 -= matrix.m24;

    this->m31 -= matrix.m31;
    this->m32 -= matrix.m32;
    this->m33 -= matrix.m33;
    this->m34 -= matrix.m34;

    this->m41 -= matrix.m41;
    this->m42 -= matrix.m42;
    this->m43 -= matrix.m43;
    this->m44 -= matrix.m44;

    return *this;
}

const Matrix Matrix::operator*(const Matrix& matrix) const
{
    auto result = *this;

    result *= matrix;

    return result;
}

const Matrix Matrix::operator*(const Single& value) const
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

Single Matrix::SubMatrixDeterminant()
{
    // Algorithm: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q23
    return this->m11 * (this->m22 * this->m33 - this->m32 * this->m23)
         - this->m12 * (this->m21 * this->m33 - this->m31 * this->m23)
         + this->m13 * (this->m21 * this->m32 - this->m31 * this->m22);
}

Matrix Matrix::SubMatrix(const UInt32& row, const UInt32& column) const
{
    // Algorithm: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
    UInt32 si;
    UInt32 sj;
    Matrix result;

    // loop through 3x3 submatrix
    for (UInt32 di = 0; di < 3; di++)
    {
        for (UInt32 dj = 0; dj < 3; dj++)
        {
            // map 3x3 element (destination) to 4x4 element (source)
            si = di + ((di >= row) ? 1 : 0);
            sj = dj + ((dj >= column) ? 1 : 0);

            // copy element
            result[di * 4 + dj] = this->matrix[si * 4 + sj];
        }
    }

    return result;
}
