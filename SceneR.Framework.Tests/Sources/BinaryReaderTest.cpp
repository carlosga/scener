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

#include <BinaryReaderTest.hpp>
#include <System/IO/BinaryReader.hpp>
#include <System/IO/FileStream.hpp>
#include <cppunit/SourceLine.h>
#include <cppunit/TestAssert.h>
#include <memory>

using namespace System;
using namespace System::IO;

CPPUNIT_TEST_SUITE_REGISTRATION(BinaryReaderTest);

BinaryReaderTest::BinaryReaderTest()
{
}

BinaryReaderTest::~BinaryReaderTest()
{
}

void BinaryReaderTest::setUp()
{
}

void BinaryReaderTest::tearDown()
{
}

void BinaryReaderTest::TestOpenBinaryReader()
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    reader.Close();
}

void BinaryReaderTest::TestReadByte()
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    UByte value = reader.ReadByte();

    CPPUNIT_ASSERT(value != 0);

    reader.Close();
}

void BinaryReaderTest::TestReadBytes()
{
}

void BinaryReaderTest::TestReadInt16()
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    Int16 value = reader.ReadInt16();

    CPPUNIT_ASSERT(value != 0);

    reader.Close();
}

void BinaryReaderTest::TestReadUInt16()
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    UInt16 value = reader.ReadUInt16();

    CPPUNIT_ASSERT(value != 0);

    reader.Close();
}

void BinaryReaderTest::TestReadInt32()
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    Int32 value = reader.ReadInt32();

    CPPUNIT_ASSERT(value != 0);

    reader.Close();
}

void BinaryReaderTest::TestReadUInt32()
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    UInt32 value = reader.ReadUInt32();

    CPPUNIT_ASSERT(value != 0);

    reader.Close();
}

void BinaryReaderTest::TestReadInt64()
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    Int64 value = reader.ReadInt64();

    CPPUNIT_ASSERT(value != 0);

    reader.Close();
}

void BinaryReaderTest::TestReadUInt64()
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    UInt64 value = reader.ReadUInt64();

    CPPUNIT_ASSERT(value != 0);

    reader.Close();
}

void BinaryReaderTest::TestReadSingle()
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    Single value = reader.ReadSingle();

    CPPUNIT_ASSERT(value != 0);

    reader.Close();
}

void BinaryReaderTest::TestReadDouble()
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    Double value = reader.ReadDouble();

    CPPUNIT_ASSERT(value != 0);

    reader.Close();
}

void BinaryReaderTest::TestReadString()
{
}
