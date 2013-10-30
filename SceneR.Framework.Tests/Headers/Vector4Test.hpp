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
