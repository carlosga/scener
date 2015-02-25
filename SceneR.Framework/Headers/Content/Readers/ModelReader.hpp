// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MODELREADER_HPP
#define MODELREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct BoundingSphere;
    }
}

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
             * Destructor
             */
            ~ModelReader();

        public:
            /**
             * Reads the model contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;

        private:
            System::UInt32 ReadBoneReference(ContentReader& input, const System::UInt32& boneCount);
            System::String ReadString(ContentReader& input);
            std::shared_ptr<SceneR::Framework::BoundingSphere> ReadBoundingSphere(ContentReader& input);
        };
    }
}

#endif  /* MODELREADER_HPP */
