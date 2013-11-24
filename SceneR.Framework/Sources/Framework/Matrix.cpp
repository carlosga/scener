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

#include <Framework/MathHelper.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>
#include <cassert>
#include <cmath>
#include <stdexcept>

using namespace System;
using namespace SceneR::Framework;

const Matrix Matrix::Identity(1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f);

Matrix Matrix::CreateFromAxisAngle(const Vector3& axis, const Single&  angle)
{
    // Formula: http://en.wikipedia.org/wiki/Rotation_matrix
    Vector3 axisNormalized(Vector3::Normalize(axis));
    float theta = MathHelper::ToRadians(angle);
    float cos   = std::cos(theta) - 1 + 1;
    float sin   = std::sin(theta);
    float cos_1 = 1.0f - cos;
    float x     = axisNormalized.X();
    float y     = axisNormalized.Y();
    float z     = axisNormalized.Z();

    return Matrix(x * x * cos_1 + cos    , x * y * cos_1 - z * sin, x * z * cos_1 + y * sin, 0.0f,
                  y * x * cos_1 + z * sin, y * y * cos_1 + cos    , y * z * cos_1 - x * sin, 0.0f,
                  z * x * cos_1 - y * sin, z * y * cos_1 + x * sin, z * z * cos_1 + cos    , 0.0f,
                  0.0f                   , 0.0f                   , 0.0f                   , 1.0f);
}

Matrix Matrix::CreateFromQuaternion(const Quaternion& quaternion)
{
    // Formula: http://en.wikipedia.org/wiki/Rotation_matrix
    //          http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
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

    return Matrix(1.0f - 2.0f * yy - 2.0f * zz, 2.0f * xy - 2.0f * zw       , 2.0f * xz + 2.0f * yw       , 0.0f,
                  2.0f * xy + 2.0f * zw       , 1.0f - 2.0f * xx - 2.0f * zz, 2.0f * yz - 2.0f * xw       , 0.0f,
                  2.0f * xz - 2.0f * yw       , 2.0f * yz + 2.0f * xw       , 1.0f - 2.0f * xx - 2.0f * yy, 0.0f,
                  0.0f                        , 0.0f                        , 0.0f                        , 1.0f);
}

Matrix Matrix::CreateFromYawPitchRoll(const Single& yaw, const Single& pitch, const Single& roll)
{
    // Formula: http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToMatrix/index.htm
    Single ch = std::cos(MathHelper::ToRadians(yaw))   - 1 + 1;
    Single sh = std::sin(MathHelper::ToRadians(yaw))   - 1 + 1;
    Single ca = std::cos(MathHelper::ToRadians(pitch)) - 1 + 1;
    Single sa = std::sin(MathHelper::ToRadians(pitch)) - 1 + 1;
    Single sb = std::sin(MathHelper::ToRadians(roll))  - 1 + 1;
    Single cb = std::cos(MathHelper::ToRadians(roll))  - 1 + 1;

    return Matrix(ch * ca , - ch * sa * cb + sh * sb, ch * sa * sb + sh * cb , 0.0f,
                  sa      , ca * cb                 , -ca * sb               , 0.0f,
                  -sh * ca, sh * sa * cb + ch * sb  , -sh * sa * sb + ch * cb, 0.0f,
                  0.0f    , 0.0f                    , 0.0f                   , 1.0f);
}

Matrix Matrix::CreateFrustum(const Single& left  , const Single& right,
                             const Single& bottom, const Single& top,
                             const Single& zNear , const Single& zFar)
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

    return Matrix((2 * zNear) / rightSubLeft, 0.0f                      , (rightPlusLeft / rightSubLeft), 0.0f,
                  0.0f                      , (2 * zNear) / topSubBottom, (topPlusBottom / topSubBottom), 0.0f,
                  0.0f                      , 0.0f                      , -(farPlusNear  / farSubNear)  , -(2 * zFar * zNear / farSubNear),
                  0.0f                      , 0.0f                      , -1.0f                         , 0.0f);
}

Matrix Matrix::CreateLookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& cameraUpVector)
{
    // Formula: http://msdn.microsoft.com/en-us/library/bb205343(v=VS.85).aspx
    // zaxis = normal(Eye - At)
    // xaxis = normal(cross(Up, zaxis))
    // yaxis = cross(zaxis, xaxis)

    // xaxis.x           yaxis.x           zaxis.x          0
    // xaxis.y           yaxis.y           zaxis.y          0
    // xaxis.z           yaxis.z           zaxis.z          0
    // dot(xaxis, eye)   dot(yaxis, eye)   dot(zaxis, eye)  1

    Vector3 zAxis = Vector3::Normalize(cameraPosition - cameraTarget);
    Vector3 xAxis = Vector3::Normalize(cameraUpVector.CrossProduct(zAxis));
    Vector3 yAxis(zAxis.CrossProduct(xAxis));

    Single dx = xAxis.DotProduct(cameraPosition);
    Single dy = yAxis.DotProduct(cameraPosition);
    Single dz = zAxis.DotProduct(cameraPosition);

    return Matrix(xAxis.X(), yAxis.X(), zAxis.X(), 0.0f,
                  xAxis.Y(), yAxis.Y(), zAxis.Y(), 0.0f,
                  xAxis.Z(), yAxis.Z(), zAxis.Z(), 0.0f,
                  -dx      , -dy      , -dz      , 1.0f);
}

Matrix Matrix::CreateOrthographic(const Single& width, const Single& height, const Single& zNear, const Single& zFar)
{
    // Formula: http://msdn.microsoft.com/en-us/library/bb205349(v=vs.85).aspx
    // 2/w  0    0           0
    // 0    2/h  0           0
    // 0    0    1/(zn-zf)   0
    // 0    0    zn/(zn-zf)  1

    Single nearSubFar = zNear - zFar;

    return Matrix(2.0f / width, 0.0f         , 0.0f              , 0.0f,
                  0           , 2.0f / height, 0.0f              , 0.0f,
                  0.0f        , 0.0f         , 1 / nearSubFar    , 0.0f,
                  0.0f        , 0.0f         , zNear / nearSubFar, 1.0f);
}

Matrix Matrix::CreateOrthographicOffCenter(const Single& left,
                                           const Single& right,
                                           const Single& bottom,
                                           const Single& top,
                                           const Single& zNear,
                                           const Single& zFar)
{
    // Formula: http://msdn.microsoft.com/en-us/library/bb205348(v=vs.85).aspx
    // 2/(r-l)      0            0           0
    // 0            2/(t-b)      0           0
    // 0            0            1/(zn-zf)   0
    // (l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1

    Single leftSubRight  = left - right;
    Single leftPlusRight = left + right;
    Single bottomSubTop  = bottom - top;
    Single topPlusBottom = top + bottom;
    Single nearSubFar    = zNear - zFar;

    return Matrix(2.0f / (right - left)       , 0.0f                        , 0.0f              , 0.0f,
                  0.0f                        , 2.0f / (top - bottom)       , 0.0f              , 0.0f,
                  0.0f                        , 0.0f                        , 1.0f / nearSubFar , 0.0f,
                  leftPlusRight / leftSubRight, topPlusBottom / bottomSubTop, zNear / nearSubFar, 1.0f);
}

Matrix Matrix::CreatePerspective(const Single& width, const Single& height, const Single& zNear, const Single& zFar)
{
    // Formula http://msdn.microsoft.com/en-us/library/bb205355(v=vs.85).aspx
    // 2*zn/w  0       0              0
    // 0       2*zn/h  0              0
    // 0       0       zf/(zn-zf)    -1
    // 0       0       zn*zf/(zn-zf)  0

    if (zNear < 0 || zFar < 0)
    {
        throw std::invalid_argument("zNear and zFar should be positive values.");
    }

    Single nearSubFar = zNear - zFar;

    return Matrix(2 * zNear / width, 0.0f              , 0.0f                     , 0.0f,
                  0.0f             , 2 * zNear / height, 0.0f                     , 0.0f,
                  0.0f             , 0.0f              , zFar / nearSubFar        , -1.0f,
                  0.0f             , 0.0f              , zNear * zFar / nearSubFar, 0.0f);
}

Matrix Matrix::CreatePerspectiveFieldOfView(const Single& fieldOfView,
                                            const Single& aspectRatio,
                                            const Single& zNear,
                                            const Single& zFar)
{
    // Formula: http://msdn.microsoft.com/en-us/library/bb205351(v=vs.85).aspx
    // xScale     0          0              0
    // 0        yScale       0              0
    // 0        0        zf/(zn-zf)        -1
    // 0        0        zn*zf/(zn-zf)      0
    //
    // where:
    // yScale = cot(fovY/2)
    // xScale = yScale / aspect ratio

    if (zNear < 0 || zFar < 0)
    {
        throw std::invalid_argument("zNear and zFar should be positive values.");
    }

    Single yScale     = 1.0f / std::tan(MathHelper::ToRadians(fieldOfView / 2));
    Single xScale     = yScale / aspectRatio;
    Single nearSubFar = zNear - zFar;
    Single nearDotFar = zNear * zFar;

    return Matrix(xScale, 0.0f  , 0.0f                   , 0.0f,
                  0.0f  , yScale, 0.0f                   , 0.0f,
                  0.0f  , 0.0f  , zFar / nearSubFar      , -1.0f,
                  0.0f  , 0.0f  , nearDotFar / nearSubFar, 0.0f);
}

Matrix Matrix::CreateRotationX(const Single& angle)
{
    return Matrix::CreateFromAxisAngle(Vector3::UnitX, angle);
}

Matrix Matrix::CreateRotationY(const Single& angle)
{
    return Matrix::CreateFromAxisAngle(Vector3::UnitY, angle);
}

Matrix Matrix::CreateRotationZ(const Single& angle)
{
    return Matrix::CreateFromAxisAngle(Vector3::UnitZ, angle);
}

Matrix Matrix::CreateScale(const Single& scale)
{
    return Matrix::CreateScale(scale, scale, scale);
}

Matrix Matrix::CreateScale(const Single& xScale, const Single& yScale, const Single& zScale)
{
    return Matrix(xScale, 0.0f  , 0.0f  , 0.0f,
                  0.0f  , yScale, 0.0f  , 0.0f,
                  0.0f  , 0.0f  , zScale, 0.0f,
                  0.0f  , 0.0f  , 0.0f  , 1.0f);
}

Matrix Matrix::CreateScale(const Vector3& scales)
{
    return Matrix::CreateScale(scales.X(), scales.Y(), scales.Z());
}

Matrix Matrix::CreateTranslation(const Single& x, const Single& y, const Single& z)
{
    return Matrix(1.0f, 0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, 1.0f, 0.0f,
                  x   , y   , z   , 1.0f);
}

Matrix Matrix::CreateTranslation(const Vector3& position)
{
    return Matrix::CreateTranslation(position.X(), position.Y(), position.Z());
}

 Matrix Matrix::CreateWorld(const Vector3& position, const Vector3& forward, const Vector3& up)
{
     return Matrix::Identity;
}

Matrix Matrix::Transform(const Matrix& value, const Quaternion& rotation)
{
    return value * Matrix::CreateFromQuaternion(rotation);
}

Matrix Matrix::Transpose(const Matrix& source)
{
    Matrix result(source);

    result.Transpose();

    return result;
}

Matrix::Matrix()
    : m11(0.0f), m12(0.0f), m13(0.0f), m14(0.0f),
      m21(0.0f), m22(0.0f), m23(0.0f), m24(0.0f),
      m31(0.0f), m32(0.0f), m33(0.0f), m34(0.0f),
      m41(0.0f), m42(0.0f), m43(0.0f), m44(0.0f)
{
}

Matrix::Matrix(const Single& m11, const Single& m12, const Single& m13, const Single& m14,
               const Single& m21, const Single& m22, const Single& m23, const Single& m24,
               const Single& m31, const Single& m32, const Single& m33, const Single& m34,
               const Single& m41, const Single& m42, const Single& m43, const Single& m44)
    : m11(m11), m12(m12), m13(m13), m14(m14),
      m21(m21), m22(m22), m23(m23), m24(m24),
      m31(m31), m32(m32), m33(m33), m34(m34),
      m41(m41), m42(m42), m43(m43), m44(m44)
{
}

Matrix::Matrix(const Matrix& matrix)
    : m11(matrix.m11), m12(matrix.m12), m13(matrix.m13), m14(matrix.m14),
      m21(matrix.m21), m22(matrix.m22), m23(matrix.m23), m24(matrix.m24),
      m31(matrix.m31), m32(matrix.m32), m33(matrix.m33), m34(matrix.m34),
      m41(matrix.m41), m42(matrix.m42), m43(matrix.m43), m44(matrix.m44)
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

bool Matrix::Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation)
{
    return false;
}

const Single Matrix::Determinant() const
{
    // Algorithm: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24

	UInt32 n      = 0;
	Int32  i      = 1;
    Single result = 0;
    Single det    = 0;
    Matrix msub;

    for (; n < 4; n++, i *= -1)
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

        Single mdet = this->Determinant();
        Matrix mtemp;
        Int32  sign;

        for (UInt32 i = 0; i < 4; i++)
        {
            for (UInt32 j = 0; j < 4; j++)
            {
                sign                    = 1 - ((i + j) % 2) * 2;
                mtemp                   = this->SubMatrix(i, j);
                this->matrix[i + j * 4] = (mtemp.SubMatrixDeterminant() * sign) / mdet;
            }
        }
    }
}

bool Matrix::IsIdentity() const
{
    return (*this == Matrix::Identity);
}

void Matrix::Transpose()
{
    Matrix temp(*this);

    this->m11 = temp.m11;
    this->m12 = temp.m21;
    this->m13 = temp.m31;
    this->m14 = temp.m41;

    this->m21 = temp.m12;
    this->m22 = temp.m22;
    this->m23 = temp.m32;
    this->m24 = temp.m42;

    this->m31 = temp.m13;
    this->m32 = temp.m23;
    this->m33 = temp.m33;
    this->m34 = temp.m43;

    this->m41 = temp.m14;
    this->m42 = temp.m24;
    this->m43 = temp.m34;
    this->m44 = temp.m44;
}

Single& Matrix::operator[](const UInt32& index)
{
    assert(index >= 0 && index < 16);

    return this->matrix[index];
}

const Single& Matrix::operator[](const UInt32& index) const
{
    assert(index >= 0 && index < 16);

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
    Matrix left = *this;

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

const Matrix Matrix::operator*(const Matrix& matrix) const
{
    Matrix result = *this;

    result *= matrix;

    return result;
}

Single Matrix::SubMatrixDeterminant()
{
    return this->M11() * this->M22() * this->M33()
         + this->M12() * this->M23() * this->M31()
         + this->M13() * this->M21() * this->M32()
         - this->M13() * this->M22() * this->M31()
         - this->M12() * this->M21() * this->M33()
         - this->M11() * this->M23() * this->M32();
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
            result.matrix[di * 4 + dj] = this->matrix[si * 4 + sj];
        }
    }

    return result;
}
