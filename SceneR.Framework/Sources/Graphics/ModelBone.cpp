// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/ModelBone.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

ModelBone::ModelBone()
    : children  ( 0 )
    , index     ( 0 )
    , name      { u"" }
    , parent    { nullptr }
    , transform { Matrix::Identity }
{
}

ModelBone::~ModelBone()
{
}

const std::vector<std::shared_ptr<ModelBone>>& ModelBone::Children() const
{
    return this->children;
}

const Size& ModelBone::Index() const
{
    return this->index;
}

const std::u16string& ModelBone::Name() const
{
    return this->name;
}

void ModelBone::Name(const std::u16string& name)
{
    this->name = name;
}

const std::shared_ptr<ModelBone>& ModelBone::Parent() const
{
    return this->parent;
}

const Matrix& ModelBone::Transform() const
{
    return this->transform;
}

void ModelBone::Transform(const Matrix& transform)
{
    this->transform = transform;
}
