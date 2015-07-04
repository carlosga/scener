// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <BinaryReaderTest.hpp>

#include <System/IO/BinaryReader.hpp>
#include <System/IO/FileStream.hpp>

using namespace System;
using namespace System::IO;

// Tests the default c'tor.
TEST_F(BinaryReaderTest, DefaultConstructor)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    reader.Close();
}

// Tests ReadByte().
TEST_F(BinaryReaderTest, ReadByte)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    uint8_t value = reader.ReadByte();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadBytes().
TEST_F(BinaryReaderTest, ReadBytes)
{
    FileStream   stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);
    size_t       length = reader.BaseStream().Length();

    std::vector<uint8_t> buffer = reader.ReadBytes(length);

    reader.Close();

    EXPECT_TRUE(buffer.size() == length);
}

// Tests ReadInt16().
TEST_F(BinaryReaderTest, ReadInt16)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    int16_t value = reader.ReadInt16();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadUInt16().
TEST_F(BinaryReaderTest, ReadUInt16)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    uint16_t value = reader.ReadUInt16();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadInt32().
TEST_F(BinaryReaderTest, ReadInt32)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    int32_t value = reader.ReadInt32();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadInt32().
TEST_F(BinaryReaderTest, ReadUInt32)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    uint32_t value = reader.ReadUInt32();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadInt64().
TEST_F(BinaryReaderTest, ReadInt64)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    uint64_t value = reader.ReadInt64();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadUInt64().
TEST_F(BinaryReaderTest, ReadUInt64)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    uint64_t value = reader.ReadUInt64();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadSingle().
TEST_F(BinaryReaderTest, ReadSingle)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    auto value = reader.ReadSingle();

    EXPECT_TRUE(value != 0);
}

// Tests ReadDouble().
TEST_F(BinaryReaderTest, ReadDouble)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    auto value = reader.ReadDouble();

    EXPECT_TRUE(value != 0);
}
