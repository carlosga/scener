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

using namespace System;
using namespace System::IO;

TEST_F(FileStreamTest, DefaultConstructor)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    stream.Close();
}

TEST_F(FileStreamTest, OpenFileStreamAsReadBinary)
{
    FileStream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    stream.Close();
}

TEST_F(FileStreamTest, BeginPosition)
{
    FileStream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    EXPECT_TRUE(0 == stream.Position());

    stream.Close();
}

TEST_F(FileStreamTest, EndPosition)
{
    FileStream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    stream.Seek(0, std::ios::end);

    EXPECT_TRUE(stream.Length() == stream.Position());

    stream.Close();
}

TEST_F(FileStreamTest, ReadByte)
{
    FileStream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    UByte value = stream.ReadByte();

    EXPECT_TRUE(sizeof(UByte) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadBytes)
{
}

TEST_F(FileStreamTest, ReadInt16)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    Int16 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Int16));

    EXPECT_TRUE(sizeof(Int16) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadUInt16)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    UInt16 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Int16));

    EXPECT_TRUE(sizeof(UInt16) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadInt32)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    Int32 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Int32));

    EXPECT_TRUE(sizeof(Int32) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadUInt32)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    UInt32 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Int32));

    EXPECT_TRUE(sizeof(UInt32) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadInt64)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    Int64 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Int64));

    EXPECT_TRUE(sizeof(Int64) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadUInt64)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    UInt64 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(UInt64));

    EXPECT_TRUE(sizeof(UInt64) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadSingle)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    Single value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Single));

    EXPECT_TRUE(sizeof(Single) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadDouble)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    Double value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(Double));

    EXPECT_TRUE(sizeof(Double) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadString)
{
}
