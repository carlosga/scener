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

#include <FileStreamTest.hpp>
#include <System/IO/FileStream.hpp>
#include <cppunit/SourceLine.h>
#include <cppunit/TestAssert.h>

using namespace System;
using namespace System::IO;

CPPUNIT_TEST_SUITE_REGISTRATION(FileStreamTest);

FileStreamTest::FileStreamTest()
{
}

FileStreamTest::~FileStreamTest()
{
}

void FileStreamTest::setUp()
{
}

void FileStreamTest::tearDown()
{
}

void FileStreamTest::TestOpenFileStream()
{
    FileStream stream(FileStreamTest::TEST_FILE);

    stream.Close();
}

void FileStreamTest::TestOpenFileStreamReadBinary()
{
    FileStream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    stream.Close();
}

void FileStreamTest::TestBeginPosition()
{
    FileStream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    CPPUNIT_ASSERT(stream.Position() == 0);

    stream.Close();
}

void FileStreamTest::TestEndPosition()
{
    FileStream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    stream.Seek(0, std::ios::end);

    CPPUNIT_ASSERT(stream.Position() == stream.Length());

    stream.Close();
}

void FileStreamTest::TestReadByte()
{
    FileStream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    UByte value = stream.ReadByte();

    CPPUNIT_ASSERT(stream.Position() == sizeof(UByte));
    CPPUNIT_ASSERT(value != 0);

    stream.Close();
}

void FileStreamTest::TestReadBytes()
{
}

void FileStreamTest::TestReadInt16()
{
    FileStream stream(FileStreamTest::TEST_FILE);

    Int16 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Int16));

    CPPUNIT_ASSERT(stream.Position() == sizeof(Int16));
    CPPUNIT_ASSERT(value != 0);

    stream.Close();
}

void FileStreamTest::TestReadUInt16()
{
    FileStream stream(FileStreamTest::TEST_FILE);

    UInt16 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Int16));

    CPPUNIT_ASSERT(stream.Position() == sizeof(Int16));
    CPPUNIT_ASSERT(value != 0);

    stream.Close();
}

void FileStreamTest::TestReadInt32()
{
    FileStream stream(FileStreamTest::TEST_FILE);

    Int32 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Int32));

    CPPUNIT_ASSERT(stream.Position() == sizeof(Int32));
    CPPUNIT_ASSERT(value != 0);

    stream.Close();
}

void FileStreamTest::TestReadUInt32()
{
    FileStream stream(FileStreamTest::TEST_FILE);

    UInt32 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Int32));

    CPPUNIT_ASSERT(stream.Position() == sizeof(Int32));
    CPPUNIT_ASSERT(value != 0);

    stream.Close();
}

void FileStreamTest::TestReadInt64()
{
    FileStream stream(FileStreamTest::TEST_FILE);

    Int64 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Int64));

    CPPUNIT_ASSERT(stream.Position() == sizeof(Int64));
    CPPUNIT_ASSERT(value != 0);

    stream.Close();
}

void FileStreamTest::TestReadUInt64()
{
    FileStream stream(FileStreamTest::TEST_FILE);

    UInt64 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(UInt64));

    CPPUNIT_ASSERT(stream.Position() == sizeof(UInt64));
    CPPUNIT_ASSERT(value != 0);

    stream.Close();
}

void FileStreamTest::TestReadSingle()
{
    FileStream stream(FileStreamTest::TEST_FILE);

    Single value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Single));

    CPPUNIT_ASSERT(stream.Position() == sizeof(Single));
    CPPUNIT_ASSERT(value != 0);

    stream.Close();
}

void FileStreamTest::TestReadDouble()
{
    FileStream stream(FileStreamTest::TEST_FILE);

    Double value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Double));

    CPPUNIT_ASSERT(stream.Position() == sizeof(Double));
    CPPUNIT_ASSERT(value != 0);

    stream.Close();
}

void FileStreamTest::TestReadString()
{
}
