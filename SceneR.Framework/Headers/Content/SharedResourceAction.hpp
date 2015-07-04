// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SHAREDRESOURCEACTION_HPP
#define SHAREDRESOURCEACTION_HPP

#include <functional>
#include <memory>

namespace SceneR
{
    namespace Content
    {
        /**
         * Represents a shared resource fixup action
         */
        struct SharedResourceAction final
        {
        public:
            /**
             * Initializes a new instance of the SharedResourceAction class.
             * @param sharedResourceId the shared resource id.
             * @param callback the shared resource fixup action callback.
             */
            SharedResourceAction(const uint32_t&                                          sharedResourceId
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
            uint32_t Id() const;

            /**
             * Gets the shared resource fixup action callback.
             */
            void Callback(const std::shared_ptr<void>& value) const;

        public:
            SharedResourceAction& operator=(const SharedResourceAction& action);

        private:
            SharedResourceAction() = delete;

        private:
            uint32_t                                          id;
            std::function<void(const std::shared_ptr<void>&)> callback;
        };
    }
}

#endif /* SHAREDRESOURCEACTION_HPP_ */
