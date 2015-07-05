// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <FileStreamTest.hpp>

#include <cstddef>
#include <cstdint>

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

    auto value = stream.ReadByte();

    EXPECT_TRUE(sizeof(std::uint8_t) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadBytes)
{
    FileStream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    std::size_t               length = stream.Length();
    std::vector<std::uint8_t> buffer(length);

    std::size_t count = stream.Read(reinterpret_cast<char*>(&buffer[0]), 0, length);

    EXPECT_TRUE(length == stream.Position());
    EXPECT_TRUE(length == count);

    stream.Close();
}

TEST_F(FileStreamTest, ReadInt16)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    std::int16_t value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(std::int16_t));

    EXPECT_TRUE(sizeof(std::int16_t) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadUInt16)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    std::uint16_t value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(std::uint16_t));

    EXPECT_TRUE(sizeof(std::uint16_t) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadInt32)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    std::int32_t value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(std::int32_t));

    EXPECT_TRUE(sizeof(std::int32_t) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadUInt32)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    std::uint32_t value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(std::uint32_t));

    EXPECT_TRUE(sizeof(std::uint32_t) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadInt64)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    std::int64_t value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(std::int64_t));

    EXPECT_TRUE(sizeof(std::int64_t) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadUInt64)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    std::uint64_t value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(std::uint64_t));

    EXPECT_TRUE(sizeof(std::uint64_t) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadSingle)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    float value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(float));

    EXPECT_TRUE(sizeof(float) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}

TEST_F(FileStreamTest, ReadDouble)
{
    FileStream stream(FileStreamTest::TEST_FILE);

    double value;

    stream.Read(reinterpret_cast<char*>(&value), 0, sizeof(double));

    EXPECT_TRUE(sizeof(double) == stream.Position());
    EXPECT_TRUE(value != 0);

    stream.Close();
}
