// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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

    uint8_t value = stream.ReadByte();

    EXPECT_TRUE(sizeof(uint8_t) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadBytes)
{
    FileStream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    Size length = stream.Length();
    std::vector<uint8_t> buffer(length);

    Size count = stream.Read(reinterpret_cast<char*>(&buffer[0]), 0, length);

    EXPECT_TRUE(length == stream.Position());
    EXPECT_TRUE(length == count);

    stream.Close();
}

TEST_F(FileStreamTest, ReadInt16)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    int16_t value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(int16_t));

    EXPECT_TRUE(sizeof(int16_t) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadUInt16)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    uint16_t value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(uint16_t));

    EXPECT_TRUE(sizeof(uint16_t) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadInt32)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    int32_t value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(int32_t));

    EXPECT_TRUE(sizeof(int32_t) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadUInt32)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    UInt32 value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(UInt32));

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
