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

#ifndef BINARYREADERTEST_HPP
#define	BINARYREADERTEST_HPP

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFixtureFactory.h>
#include <cppunit/extensions/TestNamer.h>
#include <cppunit/extensions/TestSuiteBuilderContext.h>
#include <cppunit/Portability.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <System/Core.hpp>

class BinaryReaderTest : public CPPUNIT_NS::TestFixture
{
    const System::String TEST_FILE = "/home/carlos/development/projects/cpp/opengl/workspace/SceneR/Content/BasicEffect_VS.glsl";

    CPPUNIT_TEST_SUITE(BinaryReaderTest);

    CPPUNIT_TEST(TestOpenBinaryReader);
    CPPUNIT_TEST(TestReadByte);
    CPPUNIT_TEST(TestReadBytes);
    CPPUNIT_TEST(TestReadInt16);
    CPPUNIT_TEST(TestReadUInt16);
    CPPUNIT_TEST(TestReadInt32);
    CPPUNIT_TEST(TestReadUInt32);
    CPPUNIT_TEST(TestReadInt64);
    CPPUNIT_TEST(TestReadUInt64);
    CPPUNIT_TEST(TestReadSingle);
    CPPUNIT_TEST(TestReadDouble);
    CPPUNIT_TEST(TestReadString);

    CPPUNIT_TEST_SUITE_END();

public:
    BinaryReaderTest();
    virtual ~BinaryReaderTest();
    void setUp();
    void tearDown();

private:
    void TestOpenBinaryReader();
    void TestReadByte();
    void TestReadBytes();
    void TestReadInt16();
    void TestReadUInt16();
    void TestReadInt32();
    void TestReadUInt32();
    void TestReadInt64();
    void TestReadUInt64();
    void TestReadSingle();
    void TestReadDouble();
    void TestReadString();
};

#endif	/* BINARYREADERTEST_HPP */
