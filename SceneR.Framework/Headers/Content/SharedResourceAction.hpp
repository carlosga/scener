// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SHAREDRESOURCEACTION_HPP
#define SHAREDRESOURCEACTION_HPP

#include <functional>
#include <memory>

#include <System/Core.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Represents a shared resource fixup action
         */
        struct SharedResourceAction
        {
        public:
            /**
             * Initializes a new instance of the SharedResourceAction class.
             * @param sharedResourceId the shared resource id.
             * @param callback the shared resource fixup action callback.
             */
            SharedResourceAction(const System::UInt32&                                    sharedResourceId
                               , const std::function<void(const std::shared_ptr<void>&)>& callback);

            /**
             * Copy constructor
             */
            SharedResourceAction(const SharedResourceAction& action);

            /**
             * Destructor
             */
            ~SharedResourceAction();

        public:
            /**
             * Gets the shared resource id.
             */
            const System::UInt32& Id() const;

            /**
             * Gets the shared resource fixup action callback.
             */
            void Callback(const std::shared_ptr<void>& value) const;

        public:
            SharedResourceAction& operator=(const SharedResourceAction& action);

        private:
            SharedResourceAction() = delete;

        private:
            System::UInt32                                    id;
            std::function<void(const std::shared_ptr<void>&)> callback;
        };
    }
}

#endif /* SHAREDRESOURCEACTION_HPP_ */
