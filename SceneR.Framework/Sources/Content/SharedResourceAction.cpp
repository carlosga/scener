// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/SharedResourceAction.hpp>

namespace SceneR
{
    namespace Content
    {
        SharedResourceAction::SharedResourceAction(const std::uint32_t&                                     sharedResourceId
                                                 , const std::function<void(const std::shared_ptr<void>&)>& callback)
            : id       { sharedResourceId }
            , callback { callback }
        {
        }

        SharedResourceAction::SharedResourceAction(const SharedResourceAction& action)
            : id { action.id }
            , callback { action.callback }
        {
        }

        SharedResourceAction::~SharedResourceAction()
        {
        }

        std::uint32_t SharedResourceAction::Id() const
        {
            return this->id;
        }

        void SharedResourceAction::Callback(const std::shared_ptr<void>& value) const
        {
            this->callback(value);
        }

        SharedResourceAction&SharedResourceAction::operator=(const SharedResourceAction& action)
        {
            if (this != &action)
            {
                this->id       = action.id;
                this->callback = action.callback;
            }

            return *this;
        }
    }
}
