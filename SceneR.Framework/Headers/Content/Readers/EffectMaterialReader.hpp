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

#ifndef EFFECTMATERIALREADER_HPP
#define EFFECTMATERIALREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <System/Core.hpp>
#include <memory>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;
        enum class ContentType : System::UInt32;

        /**
         * Effect material reader
         */
        class EffectMaterialReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the EffectMaterialReader class.
             */
            EffectMaterialReader();

        public:
            /**
             * Gets the the reader content type.
             */
            virtual const SceneR::Content::ContentType ContentType() const override;

            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* EFFECTMATERIALREADER_HPP */