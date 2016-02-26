// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/ContentLoadException.hpp"

namespace scener { namespace content {

ContentLoadException::ContentLoadException(const std::string m)
    : msg(m)
{
}

const char* ContentLoadException::what() const noexcept
{
    return this->msg.c_str();
}

}}
