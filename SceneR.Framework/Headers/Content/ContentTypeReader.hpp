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

#ifndef CONTENTTYPEREADER_HPP
#define CONTENTTYPEREADER_HPP

#include <memory>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Interface for content type reader implementations.
         */
        class ContentTypeReader
        {
        public:
            /**
             * Releases all resources being used by this ContentTypeReader.
             */
            virtual ~ContentTypeReader() = default;

        public:
            /**
             * Reads a object from the current stream.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) = 0;
        };
    }
}

#endif  /* CONTENTTYPEREADER_HPP */
