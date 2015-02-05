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

    UByte value = reader.ReadByte();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadBytes().
TEST_F(BinaryReaderTest, ReadBytes)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);
    Size length = reader.BaseStream().Length();

    std::vector<UByte> buffer = reader.ReadBytes(length);

    reader.Close();

    EXPECT_TRUE(buffer.size() == length);
}

// Tests ReadInt16().
TEST_F(BinaryReaderTest, ReadInt16)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    Int16 value = reader.ReadInt16();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadUInt16().
TEST_F(BinaryReaderTest, ReadUInt16)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    UInt16 value = reader.ReadUInt16();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadInt32().
TEST_F(BinaryReaderTest, ReadInt32)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    Int32 value = reader.ReadInt32();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadInt32().
TEST_F(BinaryReaderTest, ReadUInt32)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    UInt32 value = reader.ReadUInt32();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadInt64().
TEST_F(BinaryReaderTest, ReadInt64)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    UInt32 value = reader.ReadInt64();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadUInt64().
TEST_F(BinaryReaderTest, ReadUInt64)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    UInt32 value = reader.ReadUInt64();

    reader.Close();

    EXPECT_TRUE(value != 0);
}

// Tests ReadUInt64().
TEST_F(BinaryReaderTest, ReadSingle)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    Single value = reader.ReadSingle();

    EXPECT_TRUE(value != 0);
}

// Tests ReadUInt64().
TEST_F(BinaryReaderTest, ReadDouble)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    Double value = reader.ReadDouble();

    EXPECT_TRUE(value != 0);
}

// Tests ReadUInt64().
TEST_F(BinaryReaderTest, ReadString)
{
    FileStream stream(BinaryReaderTest::TEST_FILE);
    BinaryReader reader(stream);

    Double value = reader.ReadDouble();

    EXPECT_TRUE(value != 0);
}
