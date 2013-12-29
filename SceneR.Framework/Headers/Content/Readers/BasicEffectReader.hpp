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

#ifndef BASICEFFECTREADER_HPP
#define BASICEFFECTREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <memory>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * BasicEffect reader
         */
        class BasicEffectReader: public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the BasicEffectReader class.
             */
            BasicEffectReader();

        public:
            /**
             * Reads the string contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* BASICEFFECTREADER_HPP */