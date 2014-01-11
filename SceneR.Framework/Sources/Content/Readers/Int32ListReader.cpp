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
#include <Content/Readers/Int32ListReader.hpp>
#include <System/Core.hpp>
#include <System/IO/BinaryReader.hpp>
#include <memory>

using namespace System;
using namespace SceneR::Content;

Int32ListReader::Int32ListReader()
{
}

std::shared_ptr<void> Int32ListReader::Read(ContentReader& input)
{
    auto  values = std::make_shared<std::vector<Int32>>();
    Int32 count  = input.ReadInt32();

    values->reserve(count);

    for (Int32 i = 0; i < count; i++)
    {
        values->push_back(input.ReadInt32());
    }

    return values;
}
