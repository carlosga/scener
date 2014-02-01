//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#include <Content/ContentReader.hpp>
#include <Content/Readers/MatrixListReader.hpp>
#include <Framework/Matrix.hpp>
#include <vector>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;

MatrixListReader::MatrixListReader()
{
}

std::shared_ptr<void> MatrixListReader::Read(ContentReader& input)
{
    auto matrices    = std::make_shared<std::vector<Matrix>>();
    auto matrixCount = input.ReadInt32();

    matrices->reserve(matrixCount);

    for (Int32 i = 0; i < matrixCount; i++)
    {
        matrices->push_back(input.ReadMatrix());
    }

    return matrices;
}

