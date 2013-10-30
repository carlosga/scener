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

#ifndef QUATERNIONTEST_HPP
#define	QUATERNIONTEST_HPP

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFixtureFactory.h>
#include <cppunit/extensions/TestNamer.h>
#include <cppunit/extensions/TestSuiteBuilderContext.h>
#include <cppunit/Portability.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class QuaternionTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(QuaternionTest);

    CPPUNIT_TEST(testConjugate);
    CPPUNIT_TEST(testLength);
    CPPUNIT_TEST(testLengthSquared);
    CPPUNIT_TEST(testNormalize);
    CPPUNIT_TEST(testW);
    CPPUNIT_TEST(testX);
    CPPUNIT_TEST(testY);
    CPPUNIT_TEST(testZ);
    CPPUNIT_TEST(testMultiplyOperator);
    CPPUNIT_TEST(testFromAxisAngle);

    CPPUNIT_TEST_SUITE_END();

public:
    QuaternionTest();
    virtual ~QuaternionTest();
    void setUp();
    void tearDown();

private:
    void testConjugate();
    void testLength();
    void testLengthSquared();
    void testNormalize();
    void testW();
    void testX();
    void testY();
    void testZ();
    void testMultiplyOperator();
    void testFromAxisAngle();
};

#endif	/* QUATERNIONTEST_HPP */
