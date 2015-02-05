// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/SharedResourceAction.hpp>

using namespace System;
using namespace SceneR::Content;

SharedResourceAction::SharedResourceAction(const Int32&                                             sharedResourceId
                                         , const std::function<void(const std::shared_ptr<void>&)>& action)
    : id     { sharedResourceId }
    , action { action }
{
}

const Int32& SharedResourceAction::Id() const
{
    return this->id;
}

void SharedResourceAction::Callback(const std::shared_ptr<void>& value)
{
    this->action(value);
}
