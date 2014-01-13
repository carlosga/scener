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

#include <Framework/Matrix.hpp>
#include <Framework/Vector3.hpp>
#include <Vector3Test.hpp>

using namespace System;
using namespace SceneR::Framework;

TEST_F(Vector3Test, DefaultConstructor) 
{
    Vector3 vector3;

    // vector3 is equal to (0.0, 0.0, 0.0)
    EXPECT_TRUE(0.0f == vector3.X());
    EXPECT_TRUE(0.0f == vector3.Y());
    EXPECT_TRUE(0.0f == vector3.Z());
}

TEST_F(Vector3Test, IndividualCoordinatesConstructor) 
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;
    
    Vector3 vector3(x, y, z);
    
    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(x == vector3.X());
    EXPECT_TRUE(y == vector3.Y());
    EXPECT_TRUE(z == vector3.Z());
}

TEST_F(Vector3Test, CopyConstructor)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    Vector3 vector(x, y, z);
    Vector3 vector3(vector);
    
    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(x == vector3.X());
    EXPECT_TRUE(y == vector3.Y());
    EXPECT_TRUE(z == vector3.Z());
}

TEST_F(Vector3Test, Indexer)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    Vector3 vector(x, y, z);
    
    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(x == vector[0]);
    EXPECT_TRUE(y == vector[1]);
    EXPECT_TRUE(z == vector[2]);
}

TEST_F(Vector3Test, XCoordinateValue)
{
    const float x = 20.0f;
    const float y = 30.0f;
    const float z = 40.0f;
    
    Vector3 vector3(x, y, z);
    
    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(x == vector3.X());
}

TEST_F(Vector3Test, YCoordinateValue)
{
    const float x = 20.0f;
    const float y = 30.0f;
    const float z = 40.0f;
    
    Vector3 vector3(x, y, z);
        
    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(y == vector3.Y());
}

TEST_F(Vector3Test, ZCoordinateValue)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;
    
    Vector3 vector3(x, y, z);
        
    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(z == vector3.Z());
}

TEST_F(Vector3Test, Length)
{
    Vector3 vector3(20.0f, 30.0f, 40.0f);
    float length = vector3.Length();
            
    // length is approximately equal to 53.8516
    EXPECT_TRUE(53.8516464f == length);
}

TEST_F(Vector3Test, LengthSquared)
{
    Vector3 vector3(20.0f, 30.0f, 40.0f);
    float length = vector3.LengthSquared();
            
    // length is approximately equal to 2900
    EXPECT_TRUE(2900.0f == length);
}

TEST_F(Vector3Test, Negation)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    
    vector1.Negate();
	    
    // vector Result is equal to (-20, -30, -40)
    EXPECT_TRUE(-20.0f == vector1.X());
    EXPECT_TRUE(-30.0f == vector1.Y());
    EXPECT_TRUE(-40.0f == vector1.Z());
}

TEST_F(Vector3Test, Normalization)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    
    vector1.Normalize();
	    
    // vector Result is equal to (0.37139, 0.55709, 0.74278) 
    EXPECT_TRUE(0.3713907f   == vector1.X());
    EXPECT_TRUE(0.557086051f == vector1.Y());
    EXPECT_TRUE(0.742781401f == vector1.Z());
}

TEST_F(Vector3Test, Cross)
{
    Vector3 left(20.0f, 30.0f, 40.0f);
    Vector3 right(45.0f, 70.0f, 80.0f);
    Vector3 crossProduct = Vector3::Cross(left, right);
    
    // crossProduct is equal to (-400, 200, 50)                        
    EXPECT_TRUE(-400.0f == crossProduct.X());
    EXPECT_TRUE(200.0f  == crossProduct.Y());
    EXPECT_TRUE(50.0f   == crossProduct.Z());
}

TEST_F(Vector3Test, DotProduct)
{
    Vector3 left(20.0f, 30.0f, 40.0f);
    Vector3 right(45.0f, 70.0f, 80.0f);
    Single  dotProduct = Vector3::DotProduct(left, right);

    EXPECT_TRUE(6200.0f == dotProduct);
}

TEST_F(Vector3Test, AngleBetween)
{
    Vector3 left(20.0f, 30.0f, 40.0f);
    Vector3 right(45.0f, 70.0f, 80.0f);
    
    Single angle = Vector3::AngleBetween(left, right);

    // angleBetween is approximately equal to 4.15128803
    EXPECT_TRUE(0.0724536479f == angle);
}

TEST_F(Vector3Test, Addition)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	Vector3 vector2(45.0f, 70.0f, 80.0f);
	Vector3 vectorResult = vector1 + vector2;
    
    // vectorResult is equal to (65, 100, 120)    
    EXPECT_TRUE(65.0f  == vectorResult.X());
    EXPECT_TRUE(100.0f == vectorResult.Y());
    EXPECT_TRUE(120.0f == vectorResult.Z());
}

TEST_F(Vector3Test, Subtraction)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	Vector3 vector2(45.0f, 70.0f, 80.0f);
	Vector3 vectorResult = vector1 - vector2;
    
    // vector Result is equal to (-25, -40, -40)
    EXPECT_TRUE(-25.0f == vectorResult.X());
    EXPECT_TRUE(-40.0f == vectorResult.Y());
    EXPECT_TRUE(-40.0f == vectorResult.Z());
}

TEST_F(Vector3Test, Multiplication)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	Vector3 vector2(45.0f, 70.0f, 80.0f);
	Vector3 vectorResult = vector1 * vector2;
        
    // vector Result is equal to (800, 2100, 3200)
    EXPECT_TRUE(900.0f  == vectorResult.X());
    EXPECT_TRUE(2100.0f == vectorResult.Y());
    EXPECT_TRUE(3200.0f == vectorResult.Z());
}

TEST_F(Vector3Test, ScalarMultiplication)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    Vector3 vectorResult = vector1 * 75.0f; 
	    
    // vector Result is equal to (1500, 2250, 3000)
    EXPECT_TRUE(1500.0f == vectorResult.X());
    EXPECT_TRUE(2250.0f == vectorResult.Y());
    EXPECT_TRUE(3000.0f == vectorResult.Z());
}

TEST_F(Vector3Test, AdditionAssignment)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	Vector3 vector2(45.0f, 70.0f, 80.0f);	
    
    vector2 += vector1;
    
    // vector Result is equal to (65, 100, 120)    
    EXPECT_TRUE(65.0f  == vector2.X());
    EXPECT_TRUE(100.0f == vector2.Y());
    EXPECT_TRUE(120.0f == vector2.Z());
}

TEST_F(Vector3Test, SubtractionAssignment)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	Vector3 vector2(45.0f, 70.0f, 80.0f);
	
    vector2 -= vector1;
    
    // vector Result is equal to (25, 40, 40)
    EXPECT_TRUE(25.0f == vector2.X());
    EXPECT_TRUE(40.0f == vector2.Y());
    EXPECT_TRUE(40.0f == vector2.Z());
}

TEST_F(Vector3Test, MultplicationAssignment)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    Vector3 vector2(45.0f, 70.0f, 80.0f);
	
    vector2 *= vector1;
    
    // vector Result is equal to (800, 2100, 3200)
    EXPECT_TRUE(900.0f  == vector2.X());
    EXPECT_TRUE(2100.0f == vector2.Y());
    EXPECT_TRUE(3200.0f == vector2.Z());
}

TEST_F(Vector3Test, ScalarMultplicationAssignment)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	
    vector1 *= 75.0f;
    
    // vector Result is equal to (1500, 2250, 3000)
    EXPECT_TRUE(1500.0f == vector1.X());
    EXPECT_TRUE(2250.0f == vector1.Y());
    EXPECT_TRUE(3000.0f == vector1.Z());
}

TEST_F(Vector3Test, MatrixMultiplication)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    Matrix  matrix1(10.0f, 10.0f, 10.0f, 0.0f,
                    20.0f, 20.0f, 20.0f, 0.0f,
                    30.0f, 30.0f, 30.0f, 0.0f,
                    5.0f , 10.0f, 15.0f, 1.0f);
    
    Vector3 vectorResult = (vector1 * matrix1);

    // vector Result is equal to (2005, 2010, 2015)
    EXPECT_TRUE(2005.0f == vectorResult.X());
    EXPECT_TRUE(2010.0f == vectorResult.Y());
    EXPECT_TRUE(2015.0f == vectorResult.Z());
}

TEST_F(Vector3Test, Transform)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    Matrix  matrix1(10.0f, 10.0f, 10.0f, 0.0f,
                    20.0f, 20.0f, 20.0f, 0.0f,
                    30.0f, 30.0f, 30.0f, 0.0f,
                    5.0f , 10.0f, 15.0f, 1.0f);

    Vector3 vectorResult = Vector3::Transform(vector1, matrix1);

    // vector Result is equal to (2005, 2010, 2015)
    EXPECT_TRUE(2005.0f == vectorResult.X());
    EXPECT_TRUE(2010.0f == vectorResult.Y());
    EXPECT_TRUE(2015.0f == vectorResult.Z());
}

TEST_F(Vector3Test, TransformNormal)
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    Matrix  matrix1(10.0f, 10.0f, 10.0f, 0.0f,
                    20.0f, 20.0f, 20.0f, 0.0f,
                    30.0f, 30.0f, 30.0f, 0.0f,
                    5.0f , 10.0f, 15.0f, 1.0f);

    Vector3 vectorResult = Vector3::TransformNormal(vector1, matrix1);

    // vector Result is equal to (2000, 2000, 2000)
    EXPECT_TRUE(2000.0f == vectorResult.X());
    EXPECT_TRUE(2000.0f == vectorResult.Y());
    EXPECT_TRUE(2000.0f == vectorResult.Z());
}

TEST_F(Vector3Test, Lerp)
{
    Vector3 value1(5.0f, 10.0f, 50.0f);
    Vector3 value2(0.0f, -20.0f, 100.0f);
    Vector3 vector = Vector3::Lerp(value1, value2, 0.4f);

    EXPECT_TRUE(3.0f  == vector.X());
    EXPECT_TRUE(-2.0f == vector.Y());
    EXPECT_TRUE(70.0f == vector.Z());
}
