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

#include <GL/glew.h>
#include <Graphics/VertexArrayObject.hpp>
#include <Graphics/VertexDeclaration.hpp>
#include <Graphics/VertexElement.hpp>

using namespace System;
using namespace SceneR::Graphics;

VertexArrayObject::VertexArrayObject()
    : id(0)
{
    this->Create();
}

VertexArrayObject::~VertexArrayObject()
{
}

const UInt32& VertexArrayObject::Id() const
{
    return this->id;
}

void SceneR::Graphics::VertexArrayObject::Create()
{
    glGenVertexArrays(1, &this->id);
}

void SceneR::Graphics::VertexArrayObject::Activate() const
{
    glBindVertexArray(this->id);
}

void SceneR::Graphics::VertexArrayObject::Deactivate() const
{
    if (this->id != 0)
    {
        glBindVertexArray(0);
    }
}

void SceneR::Graphics::VertexArrayObject::Delete()
{
    if (this->id != 0)
    {
        this->Deactivate();
        glDeleteVertexArrays(1, &this->id);
        this->id = 0;
    }
}

void SceneR::Graphics::VertexArrayObject::DeclareVertexFormat(const VertexDeclaration& vDecl) const
{
    // Activate the vertex array object...
    this->Activate();

    // ... declare vertex elements
    for (const VertexElement& ve : vDecl.VertexElements())
    {
        glVertexAttribFormat(ve.UsageIndex(),
                             ve.ComponentCount(),
                             GL_FLOAT,
                             false,
                             ve.Offset());

        glVertexAttribBinding(ve.UsageIndex(), 0);
        glEnableVertexAttribArray(ve.UsageIndex());
    }

    // ... and finally deactivate the vertex array object
    this->Deactivate();
}
