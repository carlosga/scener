// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MatrixReader.hpp>

#include <Content/ContentReader.hpp>
#include <Framework/Matrix.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Framework::Matrix;

        MatrixReader::MatrixReader()
        {
        }

        MatrixReader::~MatrixReader()
        {
        }


        std::shared_ptr<void> MatrixReader::Read(ContentReader& input)
        {
            return std::make_shared<Matrix>(input.ReadMatrix());
        }
    }
}
