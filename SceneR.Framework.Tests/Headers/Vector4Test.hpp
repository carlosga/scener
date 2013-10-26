/*
 * File:   Vector4Test.hpp
 * Author: carlos
 *
 * Created on May 5, 2013, 7:53:58 PM
 */

#ifndef POINT4DTEST_HPP
#define	POINT4DTEST_HPP

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFixtureFactory.h>
#include <cppunit/extensions/TestNamer.h>
#include <cppunit/extensions/TestSuiteBuilderContext.h>
#include <cppunit/Portability.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class Vector4Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(Vector4Test);

    CPPUNIT_TEST(testMatrixMultiply);

    CPPUNIT_TEST_SUITE_END();

public:
    Vector4Test();
    virtual ~Vector4Test();
    void setUp();
    void tearDown();

private:
    void testMatrixMultiply();
};

#endif	/* POINT4DTEST_HPP */
