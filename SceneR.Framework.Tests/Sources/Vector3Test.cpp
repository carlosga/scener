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

#include <cppunit/SourceLine.h>
#include <cppunit/TestAssert.h>
#include <Framework/Matrix.hpp>
#include <Framework/Vector3.hpp>
#include <Vector3Test.hpp>

using namespace SceneR::Framework;

CPPUNIT_TEST_SUITE_REGISTRATION(Vector3Test);

Vector3Test::Vector3Test()
{
}

Vector3Test::~Vector3Test()
{
}

void Vector3Test::setUp()
{
}

void Vector3Test::tearDown()
{
}

void Vector3Test::testVector3()
{
    Vector3 vector3;

    // vector3 is equal to (0.0, 0.0, 0.0)
    CPPUNIT_ASSERT_EQUAL(0.0f, vector3.X());
    CPPUNIT_ASSERT_EQUAL(0.0f, vector3.Y());
    CPPUNIT_ASSERT_EQUAL(0.0f, vector3.Z());    
}

void Vector3Test::testVector32()
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;
    
    Vector3 vector3(x, y, z);
    
    // vector3 is equal to (20.0, 30.0, 40.0)
    CPPUNIT_ASSERT_EQUAL(x, vector3.X());
    CPPUNIT_ASSERT_EQUAL(y, vector3.Y());
    CPPUNIT_ASSERT_EQUAL(z, vector3.Z());    
}

void Vector3Test::testVector33()
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    Vector3 vector(x, y, z);
    Vector3 vector3(vector);
    
    // vector3 is equal to (20.0, 30.0, 40.0)
    CPPUNIT_ASSERT_EQUAL(x, vector3.X());
    CPPUNIT_ASSERT_EQUAL(y, vector3.Y());
    CPPUNIT_ASSERT_EQUAL(z, vector3.Z());    
}

void Vector3Test::testIndexer()
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    Vector3 vector(x, y, z);
    
    // vector3 is equal to (20.0, 30.0, 40.0)
    CPPUNIT_ASSERT_EQUAL(x, vector[0]);
    CPPUNIT_ASSERT_EQUAL(y, vector[1]);
    CPPUNIT_ASSERT_EQUAL(z, vector[2]);
}

void Vector3Test::testX()
{
    const float x = 20.0f;
    const float y = 30.0f;
    const float z = 40.0f;
    
    Vector3 vector3(x, y, z);
    
    // vector3 is equal to (20.0, 30.0, 40.0)
    CPPUNIT_ASSERT_EQUAL(x, vector3.X());
}

void Vector3Test::testY()
{
    const float x = 20.0f;
    const float y = 30.0f;
    const float z = 40.0f;
    
    Vector3 vector3(x, y, z);
        
    // vector3 is equal to (20.0, 30.0, 40.0)
    CPPUNIT_ASSERT_EQUAL(y, vector3.Y());
}

void Vector3Test::testZ()
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;
    
    Vector3 vector3(x, y, z);
        
    // vector3 is equal to (20.0, 30.0, 40.0)
    CPPUNIT_ASSERT_EQUAL(z, vector3.Z());
}

void Vector3Test::testLength()
{
    Vector3 vector3(20.0f, 30.0f, 40.0f);
    float length = vector3.Length();
            
    // length is approximately equal to 53.8516
    CPPUNIT_ASSERT_EQUAL(53.8516464f, length);
}

void Vector3Test::testLengthSquared()
{
    Vector3 vector3(20.0f, 30.0f, 40.0f);
    float length = vector3.LengthSquared();
            
    // length is approximately equal to 2900
    CPPUNIT_ASSERT_EQUAL(2900.0f, length);
}

void Vector3Test::testNegate()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    
    vector1.Negate();
	    
    // vector Result is equal to (-20, -30, -40)
    CPPUNIT_ASSERT_EQUAL(-20.0f, vector1.X());
    CPPUNIT_ASSERT_EQUAL(-30.0f, vector1.Y());
    CPPUNIT_ASSERT_EQUAL(-40.0f, vector1.Z());   
}

void Vector3Test::testNormalize()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    
    vector1.Normalize();
	    
    // vector Result is equal to (0.37139, 0.55709, 0.74278) 
    CPPUNIT_ASSERT_EQUAL(0.3713907f  , vector1.X());
    CPPUNIT_ASSERT_EQUAL(0.557086051f, vector1.Y());
    CPPUNIT_ASSERT_EQUAL(0.742781401f, vector1.Z());   
}

void Vector3Test::testCrossProduct()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    Vector3 vector2(45.0f, 70.0f, 80.0f);
    Vector3 crossProduct = vector1.CrossProduct(vector2);
    
    // crossProduct is equal to (-400, 200, 50)                        
    CPPUNIT_ASSERT_EQUAL(-400.0f, crossProduct.X());
    CPPUNIT_ASSERT_EQUAL(200.0f , crossProduct.Y());
    CPPUNIT_ASSERT_EQUAL(50.0f  , crossProduct.Z());   
}

void Vector3Test::testAngleBetween()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    Vector3 vector2(45.0f, 70.0f, 80.0f);
    float angle = vector1.AngleBetween(vector2);
    
    // angleBetween is approximately equal to 4.15128803
    CPPUNIT_ASSERT_EQUAL(4.15128803f, angle);
}

void Vector3Test::testSumOperator()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	Vector3 vector2(45.0f, 70.0f, 80.0f);
	Vector3 vectorResult = vector1 + vector2;
    
    // vectorResult is equal to (65, 100, 120)    
    CPPUNIT_ASSERT_EQUAL(65.0f , vectorResult.X());
    CPPUNIT_ASSERT_EQUAL(100.0f, vectorResult.Y());
    CPPUNIT_ASSERT_EQUAL(120.0f, vectorResult.Z());
}

void Vector3Test::testSubtractOperator()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	Vector3 vector2(45.0f, 70.0f, 80.0f);
	Vector3 vectorResult = vector1 - vector2;
    
    // vector Result is equal to (-25, -40, -40)
    CPPUNIT_ASSERT_EQUAL(-25.0f, vectorResult.X());
    CPPUNIT_ASSERT_EQUAL(-40.0f, vectorResult.Y());
    CPPUNIT_ASSERT_EQUAL(-40.0f, vectorResult.Z());
}

void Vector3Test::testVectorMultiplyOperator()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	Vector3 vector2(45.0f, 70.0f, 80.0f);
	Vector3 vectorResult = vector1 * vector2;
        
    // vector Result is equal to (800, 2100, 3200)
    CPPUNIT_ASSERT_EQUAL(900.0f , vectorResult.X());
    CPPUNIT_ASSERT_EQUAL(2100.0f, vectorResult.Y());
    CPPUNIT_ASSERT_EQUAL(3200.0f, vectorResult.Z());
}

void Vector3Test::testScalarMultiplyOperator()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    Vector3 vectorResult = vector1 * 75.0f; 
	    
    // vector Result is equal to (1500, 2250, 3000)
    CPPUNIT_ASSERT_EQUAL(1500.0f, vectorResult.X());
    CPPUNIT_ASSERT_EQUAL(2250.0f, vectorResult.Y());
    CPPUNIT_ASSERT_EQUAL(3000.0f, vectorResult.Z());   
}

void Vector3Test::testAdditionAssignmentOperator()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	Vector3 vector2(45.0f, 70.0f, 80.0f);	
    
    vector2 += vector1;
    
    // vector Result is equal to (65, 100, 120)    
    CPPUNIT_ASSERT_EQUAL(65.0f , vector2.X());
    CPPUNIT_ASSERT_EQUAL(100.0f, vector2.Y());
    CPPUNIT_ASSERT_EQUAL(120.0f, vector2.Z());    
}

void Vector3Test::testSubtractionAssignmentOperator()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	Vector3 vector2(45.0f, 70.0f, 80.0f);
	
    vector2 -= vector1;
    
    // vector Result is equal to (25, 40, 40)
    CPPUNIT_ASSERT_EQUAL(25.0f, vector2.X());
    CPPUNIT_ASSERT_EQUAL(40.0f, vector2.Y());
    CPPUNIT_ASSERT_EQUAL(40.0f, vector2.Z());    
}

void Vector3Test::testVectorMultplyAssignmentOperator()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    Vector3 vector2(45.0f, 70.0f, 80.0f);
	
    vector2 *= vector1;
    
    // vector Result is equal to (800, 2100, 3200)
    CPPUNIT_ASSERT_EQUAL(900.0f , vector2.X());
    CPPUNIT_ASSERT_EQUAL(2100.0f, vector2.Y());
    CPPUNIT_ASSERT_EQUAL(3200.0f, vector2.Z());
}

void Vector3Test::testScalarMultplyAssignmentOperator()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
	
    vector1 *= 75.0f;
    
    // vector Result is equal to (1500, 2250, 3000)
    CPPUNIT_ASSERT_EQUAL(1500.0f, vector1.X());
    CPPUNIT_ASSERT_EQUAL(2250.0f, vector1.Y());
    CPPUNIT_ASSERT_EQUAL(3000.0f, vector1.Z());   
}

void Vector3Test::testMatrixMultiply()
{
    Vector3 vector1(20.0f, 30.0f, 40.0f);
    Matrix  matrix1(10.0f, 10.0f, 10.0f, 0.0f, 
                     20.0f, 20.0f, 20.0f, 0.0f, 
                     30.0f, 30.0f, 30.0f, 0.0f, 
                     5.0f , 10.0f, 15.0f, 1.0f);
    
    Vector3 vectorResult = (vector1 * matrix1);

    // vector Result is equal to (2000, 2000, 2000)    
    CPPUNIT_ASSERT_EQUAL(2000.0f, vectorResult.X());
    CPPUNIT_ASSERT_EQUAL(2000.0f, vectorResult.Y());
    CPPUNIT_ASSERT_EQUAL(2000.0f, vectorResult.Z());   
}
