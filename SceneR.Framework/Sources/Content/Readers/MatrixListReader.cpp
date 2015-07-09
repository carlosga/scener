// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MatrixListReader.hpp>

#include <cstdint>
#include <vector>

#include <Content/ContentReader.hpp>
#include <Framework/Matrix.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Framework::Matrix;

        MatrixListReader::MatrixListReader()
        {
        }

        MatrixListReader::~MatrixListReader()
        {
        }

        std::shared_ptr<void> MatrixListReader::Read(ContentReader& input)
        {
            auto matrices    = std::make_shared<std::vector<Matrix>>();
            auto matrixCount = input.ReadUInt32();

            matrices->reserve(matrixCount);

            for (std::uint32_t i = 0; i < matrixCount; i++)
            {
                matrices->push_back(input.ReadMatrix());
            }

            return matrices;
        }
    }
}
