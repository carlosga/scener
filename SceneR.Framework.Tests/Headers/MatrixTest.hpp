/*
 * File:   Matrix3Test.hpp
 * Author: carlos
 *
 * Created on Apr 21, 2013, 8:32:02 PM
 */

#ifndef MATRIX3TEST_HPP
#define	MATRIX3TEST_HPP

#include <cppunit/extensions/HelperMacros.h>
class MatrixTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(MatrixTest);

    CPPUNIT_TEST(testMatrix3);
    CPPUNIT_TEST(testMatrix32);
    CPPUNIT_TEST(testMatrix33);
    CPPUNIT_TEST(testMatrixMultiply);
    CPPUNIT_TEST(testTranspose);

    CPPUNIT_TEST_SUITE_END();

public:
    MatrixTest();
    virtual ~MatrixTest();
    void setUp();
    void tearDown();

private:
    void testMatrix3();
    void testMatrix32();
    void testMatrix33();
    void testMatrixMultiply();
    void testTranspose();
};

#endif	/* MATRIX3TEST_HPP */