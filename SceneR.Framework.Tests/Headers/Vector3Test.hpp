/*
 * File:   Vector3Test.hpp
 * Author: carlos
 *
 * Created on Apr 20, 2013, 12:16:36 AM
 */

#ifndef VECTOR3TEST_HPP
#define	VECTOR3TEST_HPP

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFixtureFactory.h>
#include <cppunit/extensions/TestNamer.h>
#include <cppunit/extensions/TestSuiteBuilderContext.h>
#include <cppunit/Portability.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class Vector3Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(Vector3Test);

    CPPUNIT_TEST(testVector3);
    CPPUNIT_TEST(testVector32);
    CPPUNIT_TEST(testVector33);
    CPPUNIT_TEST(testIndexer);
    CPPUNIT_TEST(testX);
    CPPUNIT_TEST(testY);
    CPPUNIT_TEST(testZ);
    CPPUNIT_TEST(testLength);
    CPPUNIT_TEST(testLengthSquared);
    CPPUNIT_TEST(testNegate);
    CPPUNIT_TEST(testNormalize);
    CPPUNIT_TEST(testCrossProduct);
    CPPUNIT_TEST(testAngleBetween);
    CPPUNIT_TEST(testSumOperator);
    CPPUNIT_TEST(testSubtractOperator);
    CPPUNIT_TEST(testVectorMultiplyOperator);
    CPPUNIT_TEST(testScalarMultiplyOperator);
    CPPUNIT_TEST(testMatrixMultiply);    
    CPPUNIT_TEST(testAdditionAssignmentOperator);
    CPPUNIT_TEST(testSubtractionAssignmentOperator);
    CPPUNIT_TEST(testVectorMultplyAssignmentOperator);
    CPPUNIT_TEST(testScalarMultplyAssignmentOperator);

    CPPUNIT_TEST_SUITE_END();

public:
    Vector3Test();
    virtual ~Vector3Test();
    void setUp();
    void tearDown();

private:
    void testVector3();
    void testVector32();
    void testVector33();
    void testIndexer();
    void testX();
    void testY();
    void testZ();
    void testLength();
    void testLengthSquared();
    void testNegate();
    void testNormalize();
    void testCrossProduct();
    void testAngleBetween();
    void testSumOperator();
    void testSubtractOperator();
    void testVectorMultiplyOperator();
    void testScalarMultiplyOperator();
    void testAdditionAssignmentOperator();
    void testSubtractionAssignmentOperator();
    void testVectorMultplyAssignmentOperator();
    void testScalarMultplyAssignmentOperator();
    void testMatrixMultiply();
};

#endif	/* VECTOR3TEST_HPP */
