// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MatrixReader.hpp>

#include <Framework/Matrix.hpp>
#include <Content/ContentReader.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;

std::shared_ptr<void> MatrixReader::Read(ContentReader& input)
{
    return std::make_shared<Matrix>(input.ReadMatrix());
}
