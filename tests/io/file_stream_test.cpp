// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "file_stream_test.hpp"

#include <cstddef>
#include <cstdint>

#include <scener/io/file_stream.hpp>

using namespace scener;
using namespace scener::io;

TEST_F(file_stream_test, constructor)
{
    file_stream stream(file_stream_test::TEST_FILE);

    stream.close();
}

TEST_F(file_stream_test, open_file_stream_for_binary_read)
{
    file_stream stream(file_stream_test::TEST_FILE, std::ios::in | std::ios::binary);

    stream.close();
}

TEST_F(file_stream_test, begin_position)
{
    file_stream stream(file_stream_test::TEST_FILE, std::ios::in | std::ios::binary);

    EXPECT_EQ(static_cast<std::size_t>(0), stream.position());

    stream.close();
}

TEST_F(file_stream_test, end_position)
{
    file_stream stream(file_stream_test::TEST_FILE, std::ios::in | std::ios::binary);

    stream.seek(0, std::ios::end);

    EXPECT_EQ(stream.length(), stream.position());

    stream.close();
}

TEST_F(file_stream_test, read_byte)
{
    file_stream stream(file_stream_test::TEST_FILE, std::ios::in | std::ios::binary);

    auto value = stream.read_byte();

    EXPECT_EQ(sizeof(std::uint8_t), stream.position());
    EXPECT_NE(value, 0);

    stream.close();
}

TEST_F(file_stream_test, read_bytes)
{
    file_stream stream(file_stream_test::TEST_FILE, std::ios::in | std::ios::binary);

    std::size_t               length = stream.length();
    std::vector<std::uint8_t> buffer(length);

    std::size_t count = stream.read(reinterpret_cast<char*>(&buffer[0]), 0, length);

    EXPECT_EQ(length, stream.position());
    EXPECT_EQ(length, count);

    stream.close();
}

TEST_F(file_stream_test, read_int16)
{
    file_stream stream(file_stream_test::TEST_FILE);

    std::int16_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::int16_t));

    EXPECT_EQ(sizeof(std::int16_t), stream.position());
    EXPECT_NE(value, 0);

    stream.close();
}

TEST_F(file_stream_test, read_uint16)
{
    file_stream stream(file_stream_test::TEST_FILE);

    std::uint16_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::uint16_t));

    EXPECT_EQ(sizeof(std::uint16_t), stream.position());
    EXPECT_NE(value, 0);

    stream.close();
}

TEST_F(file_stream_test, read_int32)
{
    file_stream stream(file_stream_test::TEST_FILE);

    std::int32_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::int32_t));

    EXPECT_EQ(sizeof(std::int32_t), stream.position());
    EXPECT_NE(value, 0);

    stream.close();
}

TEST_F(file_stream_test, read_uint32)
{
    file_stream stream(file_stream_test::TEST_FILE);

    std::uint32_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::uint32_t));

    EXPECT_EQ(sizeof(std::uint32_t), stream.position());
    EXPECT_NE(value, static_cast<std::uint32_t>(0));

    stream.close();
}

TEST_F(file_stream_test, read_int64)
{
    file_stream stream(file_stream_test::TEST_FILE);

    std::int64_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::int64_t));

    EXPECT_EQ(sizeof(std::int64_t), stream.position());
    EXPECT_NE(value, static_cast<std::int64_t>(0));

    stream.close();
}

TEST_F(file_stream_test, read_uint64)
{
    file_stream stream(file_stream_test::TEST_FILE);

    std::uint64_t value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(std::uint64_t));

    EXPECT_EQ(sizeof(std::uint64_t), stream.position());
    EXPECT_NE(value, static_cast<std::uint64_t>(0));

    stream.close();
}

TEST_F(file_stream_test, read_single)
{
    file_stream stream(file_stream_test::TEST_FILE);

    float value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(float));

    EXPECT_EQ(sizeof(float), stream.position());
    EXPECT_NE(value, 0);

    stream.close();
}

TEST_F(file_stream_test, read_double)
{
    file_stream stream(file_stream_test::TEST_FILE);

    double value;

    stream.read(reinterpret_cast<char*>(&value), 0, sizeof(double));

    EXPECT_EQ(sizeof(double), stream.position());
    EXPECT_NE(value, 0);

    stream.close();
}
