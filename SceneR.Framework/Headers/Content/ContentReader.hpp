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

#ifndef CONTENTREADER_HPP
#define CONTENTREADER_HPP

#include <Content/ContentType.hpp>
#include <Content/ContentTypeReader.hpp>
#include <Content/ContentTypeReaderManager.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <System/Core.hpp>
#include <System/IO/BinaryReader.hpp>
#include <System/IO/FileStream.hpp>
#include <memory>

namespace SceneR
{
    namespace Framework
    {
        struct Color;
        struct Matrix;
        struct Quaternion;
        struct Vector2;
        struct Vector3;
        struct Vector4;
    }
}

namespace SceneR
{
    namespace Content
    {
        class ContentManager;

        /**
         * Reads application content from disk
         */
        class ContentReader : public System::IO::BinaryReader
        {
        public:
            /**
             * Initializes a new instance of the ContentReader.
             * @param assetName the name of the asset to be readed.
             * @param contentManager the content that owns this ContentReader.
             * @param stream the base stream.
             */
            ContentReader(const System::String& assetName,
                          ContentManager&       contentManager,
                          System::IO::Stream&   stream);

            /**
             * Releases all resources used by the current instance of the ContentReader class.
             */
            ~ContentReader();

        public:
            /**
             * Gets the name of the asset currently being read by this ContentReader.
             */
            System::String& AssetName();

            /**
             * Gets the content manager that owns this ContentReader.
             */
            SceneR::Content::ContentManager& ContentManager();

            /**
             * Reads a Color value from the current stream.
             */
            SceneR::Framework::Color ReadColor();

            /**
             * Reads a Matrix value from the current stream.
             */
            SceneR::Framework::Matrix ReadMatrix();

            /**
             * Reads a Vector2 value from the current stream.
             */
            SceneR::Framework::Vector2 ReadVector2();

            /**
             * Reads a Vector3 value from the current stream.
             */
            SceneR::Framework::Vector3 ReadVector3();

            /**
             * Reads a Vector4 value from the current stream.
             */
            SceneR::Framework::Vector4 ReadVector4();

            /**
             * Reads a Quaternion value from the current stream.
             */
            SceneR::Framework::Quaternion ReadQuaternion();

        public:
            /**
             * Reads a single object from the current stream.
             */
            template <class T>
            std::shared_ptr<T> ReadObject()
            {
                ContentType        contentType = static_cast<ContentType> (this->ReadInt32());
                ContentTypeReader* reader      = this->typeReaderManager.GetReaderForContentType(contentType);

                return this->ReadObject<T>(reader);
            };

            /**
             * Reads a single object from the current stream.
             */
            template <class T>
            std::shared_ptr<T> ReadObject(ContentTypeReader* typeReader)
            {
                return std::static_pointer_cast<T>(typeReader->Read(*this));
            };

//            template <class T>
//            void ReadSharedResource(std::function<void (const T&)> fixup)
//            {
//            };
//
//            template <class T>
//            std::shared_ptr<T> ReadExternalReference()
//            {
//            };

        private:
            void ReadHeader();

        private:
            System::String                   assetName;
            SceneR::Content::ContentManager& contentManager;
            ContentTypeReaderManager         typeReaderManager;
        };
    }
}

#endif  /* CONTENTREADER_HPP */
