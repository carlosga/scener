// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "MemoryStreamTest.hpp"

#include <cstddef>
#include <cstdint>

#include <gsl.h>

#include <scener/io/binary_reader.hpp>
#include <scener/io/memory_stream.hpp>

using namespace gsl;
using namespace scener;
using namespace scener::io;

TEST_F(MemoryStreamTest, DefaultConstructor)
{
    std::vector<std::uint8_t> vec(3);
    auto dv = as_span(vec);
    memory_stream stream(dv);
}

TEST_F(MemoryStreamTest, Read)
{
    std::vector<std::uint8_t> vec = { 1, 2, 3 };
    auto dv = as_span(vec);
    memory_stream stream(dv);
    std::vector<std::uint8_t> out(3, 0);

    stream.read(reinterpret_cast<char*>(out.data()), 0, 3);

    EXPECT_TRUE(3 == out.size());
    EXPECT_TRUE(1 == out[0]);
    EXPECT_TRUE(2 == out[1]);
    EXPECT_TRUE(3 == out[2]);
}

TEST_F(MemoryStreamTest, ReadFloat)
{
    std::vector<std::uint8_t> vec = { 0x00, 0x00, 0x00, 0x00
                                    , 0x00, 0x00, 0x80, 0x3F
                                    , 0x00, 0x00, 0x70, 0x41
                                    , 0x00, 0xFF, 0x7F, 0x47 };

    memory_stream stream(vec);
    binary_reader reader(stream);

    EXPECT_TRUE(0.0f           == reader.read<float>());
    EXPECT_TRUE(1.0f           == reader.read<float>());
    EXPECT_TRUE(1.5000000E+001 == reader.read<float>());
    EXPECT_TRUE(6.5535000E+004 == reader.read<float>());
}
