// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "binary_reader_test.hpp"

#include <cstddef>

#include <scener/io/binary_reader.hpp>
#include <scener/io/file_stream.hpp>

using namespace scener;
using namespace scener::io;

// Tests the default c'tor.
TEST_F(binary_reader_test, constructor)
{
    file_stream   stream(binary_reader_test::TEST_FILE);
    binary_reader reader(stream);

    reader.close();
}

// Tests ReadByte().
TEST_F(binary_reader_test, read_byte)
{
    file_stream   stream(binary_reader_test::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::uint8_t>();

    reader.close();

    EXPECT_NE(value, 0);
}

// Tests ReadBytes().
TEST_F(binary_reader_test, read_bytes)
{
    file_stream   stream(binary_reader_test::TEST_FILE);
    binary_reader reader(stream);
    std::size_t  length = reader.base_stream().length();

    auto buffer = reader.read_bytes(length);

    reader.close();

    EXPECT_EQ(buffer.size(), length);
}

// Tests ReadInt16().
TEST_F(binary_reader_test, read_int16)
{
    file_stream   stream(binary_reader_test::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::int16_t>();

    reader.close();

    EXPECT_NE(value, 0);
}

// Tests ReadUInt16().
TEST_F(binary_reader_test, read_uint16)
{
    file_stream   stream(binary_reader_test::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::uint16_t>();

    reader.close();

    EXPECT_NE(value, 0);
}

// Tests ReadInt32().
TEST_F(binary_reader_test, read_int32)
{
    file_stream   stream(binary_reader_test::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::int32_t>();

    reader.close();

    EXPECT_NE(value, 0);
}

// Tests ReadInt32().
TEST_F(binary_reader_test, read_uint32)
{
    file_stream   stream(binary_reader_test::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::uint32_t>();

    reader.close();

    EXPECT_NE(value, static_cast<std::uint32_t>(0));
}

// Tests ReadInt64().
TEST_F(binary_reader_test, read_int64)
{
    file_stream   stream(binary_reader_test::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::int64_t>();

    reader.close();

    EXPECT_NE(value, 0);
}

// Tests ReadUInt64().
TEST_F(binary_reader_test, read_uint64)
{
    file_stream   stream(binary_reader_test::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::uint64_t>();

    reader.close();

    EXPECT_NE(value, static_cast<std::uint64_t>(0));
}

// Tests ReadSingle().
TEST_F(binary_reader_test, read_single)
{
    file_stream   stream(binary_reader_test::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<float>();

    reader.close();

    EXPECT_NE(value, 0);
}

// Tests ReadDouble().
TEST_F(binary_reader_test, read_double)
{
    file_stream   stream(binary_reader_test::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<double>();

    reader.close();

    EXPECT_NE(value, 0);
}
