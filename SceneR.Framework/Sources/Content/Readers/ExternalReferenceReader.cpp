// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ExternalReferenceReader.hpp>

#include <System/IO/Path.hpp>
#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>

using namespace SceneR::Content;

ExternalReferenceReader::ExternalReferenceReader()
{
}

ExternalReferenceReader::~ExternalReferenceReader()
{
}

std::shared_ptr<void> ExternalReferenceReader::Read(ContentReader& input)
{
    return nullptr;
}
