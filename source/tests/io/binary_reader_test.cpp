// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "BinaryReaderTest.hpp"

#include <cstddef>

#include <scener/io/binary_reader.hpp>
#include <scener/io/file_stream.hpp>

using namespace scener;
using namespace scener::io;

// Tests the default c'tor.
TEST_F(BinaryReaderTest, DefaultConstructor)
{
    file_stream   stream(BinaryReaderTest::TEST_FILE);
    binary_reader reader(stream);

    reader.close();
}

// Tests ReadByte().
TEST_F(BinaryReaderTest, ReadByte)
{
    file_stream   stream(BinaryReaderTest::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::uint8_t>();

    reader.close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadBytes().
TEST_F(BinaryReaderTest, ReadBytes)
{
    file_stream   stream(BinaryReaderTest::TEST_FILE);
    binary_reader reader(stream);
    std::size_t  length = reader.base_stream().length();

    auto buffer = reader.read_bytes(length);

    reader.close();

    EXPECT_TRUE(buffer.size() == length);
}

// Tests ReadInt16().
TEST_F(BinaryReaderTest, ReadInt16)
{
    file_stream   stream(BinaryReaderTest::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::int16_t>();

    reader.close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadUInt16().
TEST_F(BinaryReaderTest, ReadUInt16)
{
    file_stream   stream(BinaryReaderTest::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::uint16_t>();

    reader.close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadInt32().
TEST_F(BinaryReaderTest, ReadInt32)
{
    file_stream   stream(BinaryReaderTest::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::int32_t>();

    reader.close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadInt32().
TEST_F(BinaryReaderTest, ReadUInt32)
{
    file_stream   stream(BinaryReaderTest::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::uint32_t>();

    reader.close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadInt64().
TEST_F(BinaryReaderTest, ReadInt64)
{
    file_stream   stream(BinaryReaderTest::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::int64_t>();

    reader.close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadUInt64().
TEST_F(BinaryReaderTest, ReadUInt64)
{
    file_stream   stream(BinaryReaderTest::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<std::uint64_t>();

    reader.close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadSingle().
TEST_F(BinaryReaderTest, ReadSingle)
{
    file_stream   stream(BinaryReaderTest::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<float>();

    reader.close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadDouble().
TEST_F(BinaryReaderTest, ReadDouble)
{
    file_stream   stream(BinaryReaderTest::TEST_FILE);
    binary_reader reader(stream);

    auto value = reader.read<double>();

    reader.close();

    EXPECT_TRUE(value != 0);
}
