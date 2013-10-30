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

#ifndef MODELREADER_HPP
#define MODELREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <System/Core.hpp>
#include <memory>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Model reader.
         */
        class ModelReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the ModelReader class.
             */
            ModelReader();

            /**
             * Gets the the reader content type.
             */
            virtual const ContentType GetContentType() const override;

            /**
             * Reads the model contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader* input) override;

        private:
            UInt32 ReadBoneReference(ContentReader* input, const UInt16& boneCount);
        };
    }
}

#endif  /* MODELREADER_HPP */
