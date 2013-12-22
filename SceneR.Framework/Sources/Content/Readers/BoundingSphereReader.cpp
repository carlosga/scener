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
#include <Content/Readers/BoundingSphereReader.hpp>
#include <Framework/BoundingSphere.hpp>
#include <System/Core.hpp>
#include <memory>
#include <string>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;

BoundingSphereReader::BoundingSphereReader()
{
}

std::shared_ptr<void> BoundingSphereReader::Read(ContentReader& input)
{
	return std::make_shared<BoundingSphere>(input.ReadVector3()	    // Center
										  , input.ReadSingle());	// Radius
}