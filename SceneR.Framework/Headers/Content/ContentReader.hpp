// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTREADER_HPP
#define CONTENTREADER_HPP

#include <memory>
#include <vector>

#include <System/Core.hpp>
#include <System/IO/BinaryReader.hpp>
#include <System/IO/Stream.hpp>
#include <Content/ContentTypeReaderManager.hpp>
#include <Content/SharedResourceAction.hpp>

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
        class ContentReader final : public System::IO::BinaryReader
        {
        private:
            static ContentTypeReaderManager TypeReaderManager;

        public:
            /**
             * Initializes a new instance of the ContentReader.
             * @param assetName the name of the asset to be readed.
             * @param contentManager the content that owns this ContentReader.
             * @param stream the base stream.
             */
            ContentReader(const System::String&            assetName
                        , SceneR::Content::ContentManager& contentManager
                        , System::IO::Stream&              stream);

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
            template <typename T>
            std::shared_ptr<T> ReadObject();

            /**
             * Reads a single object from the current stream.
             */
            template <typename T>
            std::shared_ptr<T> ReadObject(ContentTypeReader* typeReader);

            /**
             * Reads a shared resource ID, and records it for subsequent fix-up.
             */
            void ReadSharedResource(const std::function<void(const std::shared_ptr<void>&)>& fixup);

            /**
             * Reads a link to an external file.
             * @returns The asset stored in the external file.
             */
            template <class T>
            std::shared_ptr<T> ReadExternalReference();

        private:
            void ReadHeader();
            void ReadManifest();
            void ReadSharedResources();

        private:
            System::String                    assetName;
            SceneR::Content::ContentManager&  contentManager;
            std::vector<ContentTypeReader*>   typeReaders;
            System::UInt32                    sharedResourceCount;
            std::vector<SharedResourceAction> fixupActions;

            friend class ContentManager;
        };
    }
}

#include <System/IO/Path.hpp>
#include <Content/ContentManager.hpp>
#include <Content/ContentTypeReader.hpp>

template <class T>
std::shared_ptr<T> SceneR::Content::ContentReader::ReadObject()
{
    auto readerId = this->Read7BitEncodedInt();

    // A reader id 0 means a NULL object
    if (readerId == 0)
    {
        return nullptr;
    }
    else
    {
        return this->ReadObject<T>(this->typeReaders[readerId - 1]);
    }
}

template <class T>
std::shared_ptr<T> SceneR::Content::ContentReader::ReadObject(SceneR::Content::ContentTypeReader* typeReader)
{
    return std::static_pointer_cast<T>(typeReader->Read(*this));
}

template <class T>
std::shared_ptr<T> SceneR::Content::ContentReader::ReadExternalReference()
{
    auto assetName = this->ReadString();

    if (assetName.size() > 0)
    {
        assetName = System::IO::Path::Combine(System::IO::Path::GetDirectoryName(this->assetName), assetName);

        return this->contentManager.Load<T>(assetName);
    }

    return nullptr;
}

#endif  /* CONTENTREADER_HPP */
