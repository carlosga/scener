// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexArrayObject.hpp>

#include <System/Graphics/Platform.hpp>

using namespace System;
using namespace SceneR::Graphics;

VertexArrayObject::VertexArrayObject()
    : id { 0 }
{
    this->Create();
}

VertexArrayObject::~VertexArrayObject()
{
}

void VertexArrayObject::Dispose()
{
    if (this->id != 0)
    {
        glDeleteVertexArrays(1, &this->id);
        this->id = 0;
    }
}

uint32_t VertexArrayObject::Id() const
{
    return this->id;
}

void VertexArrayObject::Create()
{
    glGenVertexArrays(1, &this->id);
}

void VertexArrayObject::Activate() const
{
    glBindVertexArray(this->id);
}

void VertexArrayObject::Deactivate() const
{
    if (this->id != 0)
    {
        glBindVertexArray(0);
    }
}
