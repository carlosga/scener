/*
 * File:   QuaternionTest.hpp
 * Author: carlos
 *
 * Created on May 5, 2013, 4:51:58 PM
 */

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
