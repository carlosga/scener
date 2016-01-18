// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/OpenGL/VertexArrayObject.hpp"

#include <gsl_assert.h>

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

VertexArrayObject::~VertexArrayObject() noexcept
{
    if (_id != 0)
    {
        glDeleteVertexArrays(1, &_id);
        _id = 0;
    }
}

std::uint32_t VertexArrayObject::id() const noexcept
{
    return _id;
}

void VertexArrayObject::bind() const noexcept
{
    glBindVertexArray(_id);
}

void VertexArrayObject::create() noexcept
{
    glCreateVertexArrays(1, &_id);

    Ensures(_id > 0);
}

void VertexArrayObject::unbind() const noexcept
{
    if (_id != 0)
    {
        glBindVertexArray(0);
    }
}

}}}
