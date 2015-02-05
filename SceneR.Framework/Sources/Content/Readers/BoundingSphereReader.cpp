// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BoundingSphereReader.hpp>

#include <Framework/BoundingSphere.hpp>
#include <Content/ContentReader.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;

std::shared_ptr<void> BoundingSphereReader::Read(ContentReader& input)
{
	return std::make_shared<BoundingSphere>(input.ReadVector3()	    // Center
										  , input.ReadSingle());	// Radius
}
