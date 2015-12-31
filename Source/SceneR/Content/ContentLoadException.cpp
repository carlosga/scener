// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/ContentLoadException.hpp"

namespace SceneR { namespace Content {

ContentLoadException::ContentLoadException(const std::string m)
    : msg(m)
{
}

ContentLoadException::ContentLoadException(const ContentLoadException& exception)
    : msg(exception.msg)
{
}

ContentLoadException::~ContentLoadException() noexcept
{
}

const char* ContentLoadException::what() const noexcept
{
    return this->msg.c_str();
}

ContentLoadException& ContentLoadException::operator=(const ContentLoadException& exception)
{
    if (this != &exception)
    {
        this->msg = exception.msg;
    }

    return *this;
}

}}
