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

#ifndef SHAREDRESOURCEACTION_HPP
#define SHAREDRESOURCEACTION_HPP

#include <System/Core.hpp>
#include <functional>
#include <memory>

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
             * @param action the shared resource fixup action callback.
             */
            SharedResourceAction(const System::UInt32&                                    sharedResourceId
                               , const std::function<void(const std::shared_ptr<void>&)>& action);

            /**
             * Releases all resources being used by this SharedResourceAction
             */
            ~SharedResourceAction();

        public:
            /**
             * Gets the shared resource id.
             */
            const System::Int32& Id() const;

            /**
             * Gets the shared resource fixup action callback.
             */
            void Callback(const std::shared_ptr<void>& value);

        private:
            System::Int32                                     id;
            std::function<void(const std::shared_ptr<void>&)> action;
        };
    }
}

#endif /* SHAREDRESOURCEACTION_HPP_ */
