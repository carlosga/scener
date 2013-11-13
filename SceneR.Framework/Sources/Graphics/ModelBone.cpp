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

#include <Graphics/ModelBone.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

ModelBone::ModelBone()
    : children(0), index(0), name(), parent(nullptr), transform(Matrix::Identity)
{
}

ModelBone::~ModelBone()
{
}

const std::vector<std::shared_ptr<ModelBone>>& ModelBone::Children() const
{
    return this->children;
}

const UInt32& ModelBone::Index() const
{
    return this->index;
}

const String& ModelBone::GetName() const
{
    return this->name;
}

void ModelBone::SetName(const String& name)
{
    this->name = name;
}

const std::shared_ptr<ModelBone> ModelBone::Parent() const
{
    return this->parent;
}

const Matrix& ModelBone::GetTransform() const
{
    return this->transform;
}

void ModelBone::SetTransform(const Matrix& transform)
{
    this->transform = transform;
}
