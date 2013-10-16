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

#include <cassert>
#include <cmath>
#include "Core/MathHelper.hpp"
#include "Core/Vector4.hpp"

using namespace SceneR::Core;

Vector4::Vector4()
    : Vector4(0.0f, 0.0f, 0.0f, 1.0f)
{
}

Vector4::Vector4(const Single& x, const Single& y, const Single& z)
    : Vector4(x, y, z, 1.0f)
{
}

Vector4::Vector4(const Single& x, const Single& y, const Single& z, const Single& w)
    : xCoordinate(x), yCoordinate(y), zCoordinate(z), wCoordinate(w)
{
}

Vector4::Vector4(const Vector4& vector)
    : xCoordinate(vector.X()), yCoordinate(vector.Y()), zCoordinate(vector.Z()), wCoordinate(vector.W())
{
}

const Single& Vector4::X() const
{
    return this->xCoordinate;
}

const Single& Vector4::Y() const
{
    return this->yCoordinate;
}

const Single& Vector4::Z() const
{
    return this->zCoordinate;
}

const Single& Vector4::W() const
{
    return this->wCoordinate;
}

const Single Vector4::LengthSquared() const
{
    return   (this->xCoordinate * this->xCoordinate) 
           + (this->yCoordinate * this->yCoordinate) 
           + (this->zCoordinate * this->zCoordinate)
           + (this->wCoordinate * this->wCoordinate);
}

const Single Vector4::Length() const
{
    // The modulus or magnitude of a vector is simply its length. 
    // This can easily be found using Pythagorean Theorem with the vector components. 
    //
    // The modulus is written like:
    // a = |a|
    //
    // Given:
    // a = xi + yj + zk
    //
    // Then:
    //
    // |a| = sqrt(x^2 + y^2 + z^2 + w^2)
    
    return std::sqrt(this->LengthSquared());
}

void Vector4::Negate()
{
   (*this *= -1.0f);
}

const Single Vector4::DotProduct(const Vector4& vectorb) const
{
    Vector4 dotProduct = *this * vectorb;
    
    return (dotProduct.X() + dotProduct.Y() + dotProduct.Z() + dotProduct.W());
}

void Vector4::Normalize()
{
    // To find the unit vector of another vector, we use the modulus operator 
    // and scalar multiplication like so:
    // b = a / |a|
    //
    // Where |a| is the modulus of a

    (*this /= this->Length());
}       
    
Single& Vector4::operator[](const Int32& index)
{
    assert(index >= 0 && index < 4);
    
    return (this->vector[index]);
}

const Single& Vector4::operator[](const Int32& index) const
{
    assert(index >= 0 && index < 4);
    
    return (this->vector[index]);
}
        
Vector4& Vector4::operator=(const Vector4 &vector)
{
    if (this != &vector)
    {
        this->xCoordinate = vector.X();
        this->yCoordinate = vector.Y();
        this->zCoordinate = vector.Z();
        this->wCoordinate = vector.W();
    }

    return *this;
}

bool Vector4::operator==(const Vector4 &vector) const
{
    return (this->xCoordinate    == vector.xCoordinate
            && this->yCoordinate == vector.yCoordinate
            && this->zCoordinate == vector.zCoordinate
            && this->wCoordinate == vector.wCoordinate);
}

bool Vector4::operator!=(const Vector4 &vector) const
{
    return !(*this == vector);
}

Vector4& Vector4::operator*=(const Vector4 &vector)
{
    this->xCoordinate *= vector.xCoordinate;
    this->yCoordinate *= vector.yCoordinate;
    this->zCoordinate *= vector.zCoordinate;
    this->wCoordinate *= vector.wCoordinate;

    return *this;
}

Vector4& Vector4::operator*=(const Single &value)
{
    this->xCoordinate *= value;
    this->yCoordinate *= value;
    this->zCoordinate *= value;
    this->wCoordinate *= value;

    return *this;
}
            
Vector4& Vector4::operator/=(const Vector4 &vector)
{
    this->xCoordinate /= vector.xCoordinate;
    this->yCoordinate /= vector.yCoordinate;
    this->zCoordinate /= vector.zCoordinate;
    this->wCoordinate /= vector.wCoordinate;

    return *this;
}

Vector4& Vector4::operator/=(const Single &value)
{
    this->xCoordinate /= value;
    this->yCoordinate /= value;
    this->zCoordinate /= value;
    this->wCoordinate /= value;

    return *this;
}

Vector4& Vector4::operator-=(const Vector4 &vector)
{
    this->xCoordinate -= vector.xCoordinate;
    this->yCoordinate -= vector.yCoordinate;
    this->zCoordinate -= vector.zCoordinate;
    this->wCoordinate -= vector.wCoordinate;

    return *this;
}

Vector4& Vector4::operator+=(const Vector4 &vector)
{
    this->xCoordinate += vector.xCoordinate;
    this->yCoordinate += vector.yCoordinate;
    this->zCoordinate += vector.zCoordinate;
    this->wCoordinate += vector.wCoordinate;
    
    return *this;
}

const Vector4 Vector4::operator*(const Vector4 &vector) const
{
    Vector4 result = *this;

    result *= vector;
    
    return result;
}

const Vector4 Vector4::operator*(const Single &value) const
{
    Vector4 result = *this;

    result *= value;
    
    return result;
}

const Vector4 Vector4::operator*(const Matrix &matrix) const
{
    Single x = (this->xCoordinate * matrix.M11())
             + (this->yCoordinate * matrix.M21())
             + (this->zCoordinate * matrix.M31())
             + (this->wCoordinate * matrix.M41());

    Single y = (this->xCoordinate * matrix.M12())
             + (this->yCoordinate * matrix.M22())
             + (this->zCoordinate * matrix.M32())
             + (this->wCoordinate * matrix.M42());

    Single z = (this->xCoordinate * matrix.M13())
             + (this->yCoordinate * matrix.M23())
             + (this->zCoordinate * matrix.M33())
             + (this->wCoordinate * matrix.M43());

    Single w = (this->xCoordinate * matrix.M14())
             + (this->yCoordinate * matrix.M24())
             + (this->zCoordinate * matrix.M34())
             + (this->wCoordinate * matrix.M44());

    return Vector4(x, y, z, w);
}

const Vector4 Vector4::operator/(const Vector4 &vector) const
{
    Vector4 result = *this;

    result /= vector;
    
    return result;
}

const Vector4 Vector4::operator/(const Single &value) const
{
    Vector4 result = *this;

    result /= value;
    
    return result;
}

const Vector4 Vector4::operator-(const Vector4 &vector) const
{
    Vector4 result = *this;

    result -= vector;
    
    return result;
}           

const Vector4 Vector4::operator+(const Vector4 &vector) const
{
    Vector4 result = *this;

    result += vector;
    
    return result;
}
