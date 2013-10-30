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
#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>
#include <QuaternionTest.hpp>

using namespace SceneR::Framework;

CPPUNIT_TEST_SUITE_REGISTRATION(QuaternionTest);

QuaternionTest::QuaternionTest()
{
}

QuaternionTest::~QuaternionTest()
{
}

void QuaternionTest::setUp()
{
}

void QuaternionTest::tearDown()
{
}

void QuaternionTest::testConjugate()
{
}

void QuaternionTest::testLength()
{
}

void QuaternionTest::testLengthSquared()
{
}

void QuaternionTest::testNormalize()
{
}

void QuaternionTest::testW()
{
}

void QuaternionTest::testX()
{
}

void QuaternionTest::testY()
{
}

void QuaternionTest::testZ()
{
}

void QuaternionTest::testMultiplyOperator()
{
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);
    Quaternion qResult = q1 * q2;
    
    // quaternion Result is equal to (24, 48, 48, -6)
    CPPUNIT_ASSERT_EQUAL(24.0f, qResult.X());
    CPPUNIT_ASSERT_EQUAL(48.0f, qResult.Y());
    CPPUNIT_ASSERT_EQUAL(48.0f, qResult.Z());       
    CPPUNIT_ASSERT_EQUAL(-6.0f, qResult.W());
}

void QuaternionTest::testFromAxisAngle()
{
    Vector3    axis(1, 0, 0);
    Quaternion qResult = Quaternion::CreateFromAxisAngle(axis, 90);

    // quaternion Result is equal to (0.707106769, 0, 0, 0.707106769)
    CPPUNIT_ASSERT_EQUAL(0.707106769f, qResult.X());
    CPPUNIT_ASSERT_EQUAL(0.0f        , qResult.Y());
    CPPUNIT_ASSERT_EQUAL(0.0f        , qResult.Z());       
    CPPUNIT_ASSERT_EQUAL(0.707106769f, qResult.W());
}
