// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "FileStreamTest.hpp"

#include <cstddef>
#include <cstdint>

#include <scener/io/file_stream.hpp>

using namespace scener;
using namespace scener::io;

TEST_F(FileStreamTest, DefaultConstructor)
{
    file_stream stream(FileStreamTest::TEST_FILE);

    stream.close();
}

TEST_F(FileStreamTest, OpenFileStreamAsReadBinary)
{
    file_stream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    stream.close();
}

TEST_F(FileStreamTest, BeginPosition)
{
    file_stream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    EXPECT_TRUE(0 == stream.position());

    stream.close();
}

TEST_F(FileStreamTest, EndPosition)
{
    file_stream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    stream.seek(0, std::ios::end);

    EXPECT_TRUE(stream.length() == stream.position());

    stream.close();
}

TEST_F(FileStreamTest, ReadByte)
{
    file_stream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    auto value = stream.read_byte();

    EXPECT_TRUE(sizeof(std::uint8_t) == stream.position());
    EXPECT_TRUE(value != 0);

    stream.close();
}

TEST_F(FileStreamTest, ReadBytes)
{
    file_stream stream(FileStreamTest::TEST_FILE, std::ios::in | std::ios::binary);

    std::size_t               length = stream.length();
    std::vector<std::uint8_t> buffer(length);

    std::size_t count = stream.read(reinterpret_cast<char*>(&buffer[0]), 0, length);

    EXPECT_TRUE(length == stream.position());
    EXPECT_TRUE(length == count);

    stream.close();
}

TEST_F(FileStreamTest, ReadInt16)
{
    file_stream stream(FileStreamTest::TEST_FILE);

    std::int16_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::int16_t));

    EXPECT_TRUE(sizeof(std::int16_t) == stream.position());
    EXPECT_TRUE(value != 0);

    stream.close();
}

TEST_F(FileStreamTest, ReadUInt16)
{
    file_stream stream(FileStreamTest::TEST_FILE);

    std::uint16_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::uint16_t));

    EXPECT_TRUE(sizeof(std::uint16_t) == stream.position());
    EXPECT_TRUE(value != 0);

    stream.close();
}

TEST_F(FileStreamTest, ReadInt32)
{
    file_stream stream(FileStreamTest::TEST_FILE);

    std::int32_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::int32_t));

    EXPECT_TRUE(sizeof(std::int32_t) == stream.position());
    EXPECT_TRUE(value != 0);

    stream.close();
}

TEST_F(FileStreamTest, ReadUInt32)
{
    file_stream stream(FileStreamTest::TEST_FILE);

    std::uint32_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::uint32_t));

    EXPECT_TRUE(sizeof(std::uint32_t) == stream.position());
    EXPECT_TRUE(value != 0);

    stream.close();
}

TEST_F(FileStreamTest, ReadInt64)
{
    file_stream stream(FileStreamTest::TEST_FILE);

    std::int64_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::int64_t));

    EXPECT_TRUE(sizeof(std::int64_t) == stream.position());
    EXPECT_TRUE(value != 0);

    stream.close();
}

TEST_F(FileStreamTest, ReadUInt64)
{
    file_stream stream(FileStreamTest::TEST_FILE);

    std::uint64_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::uint64_t));

    EXPECT_TRUE(sizeof(std::uint64_t) == stream.position());
    EXPECT_TRUE(value != 0);

    stream.close();
}

TEST_F(FileStreamTest, ReadSingle)
{
    file_stream stream(FileStreamTest::TEST_FILE);

    float value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(float));

    EXPECT_TRUE(sizeof(float) == stream.position());
    EXPECT_TRUE(value != 0);

    stream.close();
}

TEST_F(FileStreamTest, ReadDouble)
{
    file_stream stream(FileStreamTest::TEST_FILE);

    double value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(double));

    EXPECT_TRUE(sizeof(double) == stream.position());
    EXPECT_TRUE(value != 0);

    stream.close();
}
