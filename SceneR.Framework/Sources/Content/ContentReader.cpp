// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentReader.hpp>

#include <cassert>

#include <Framework/Color.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>

using namespace System;
using namespace System::IO;
using namespace SceneR::Content;
using namespace SceneR::Framework;

ContentTypeReaderManager ContentReader::TypeReaderManager { };

ContentReader::ContentReader(const String&                    assetName
                           , SceneR::Content::ContentManager& contentManager
                           , Stream&                          stream)
    : BinaryReader        { stream }
    , assetName           { assetName }
    , contentManager      ( contentManager )
    , typeReaders         ( 0 )
    , sharedResourceCount { 0 }
    , fixupActions        { }
{
    this->ReadHeader();
    this->ReadManifest();
}

ContentReader::~ContentReader()
{
    BinaryReader::Close();
    this->typeReaders.clear();
    this->fixupActions.clear();
    this->sharedResourceCount = 0;
}

String& ContentReader::AssetName()
{
    return this->assetName;
}

SceneR::Content::ContentManager& ContentReader::ContentManager()
{
    return this->contentManager;
}

Color ContentReader::ReadColor()
{
    return { this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle() };
}

Matrix ContentReader::ReadMatrix()
{
    return { this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle()
           , this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle()
           , this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle()
           , this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle() };
}

Vector2 ContentReader::ReadVector2()
{
    return { this->ReadSingle(), this->ReadSingle() };
}

Vector3 ContentReader::ReadVector3()
{
    return { this->ReadSingle(), this->ReadSingle(), this->ReadSingle() };
}

Vector4 ContentReader::ReadVector4()
{
    return { this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle() };
}

Quaternion ContentReader::ReadQuaternion()
{
    return { this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle() };
}

void ContentReader::ReadSharedResource(const std::function<void(const std::shared_ptr<void>&)>& fixup)
{
    auto sharedResourceId = this->Read7BitEncodedInt();

    if (sharedResourceId != 0)
    {
        this->fixupActions.push_back({ sharedResourceId - 1, fixup });
    }
};

void ContentReader::ReadHeader()
{
    this->ReadByte();   // ‘X’
    this->ReadByte();   // ‘N’
    this->ReadByte();   // ‘B’
    this->ReadByte();   // Target platform
    this->ReadByte();   // XNB format version
    this->ReadByte();   // Flag bits
                        // Bit 0x01 = content is for HiDef profile (otherwise Reach)
                        // Bit 0x80 = asset data is compressed
    this->ReadUInt32(); // Compressed file size
                        // Total size of the (optionally compressed) .xnb file as stored on disk (including this header block)

    if (false)  // Compressed files not supported
    {
        this->ReadUInt32(); // Decompressed data size
                            // Only included for compressed .xnb files, where it indicates the expanded size of
                            // the compressed data which starts immediately after this field (unlike the compressed
                            // file size, this does not include the uncompressed portion of the header)
    }
}

void ContentReader::ReadManifest()
{
    auto typeReaderCount = this->Read7BitEncodedInt();

    typeReaders.clear();

    for (Int32 i = 0; i < typeReaderCount; i++)
    {
        // Read the type reader name.
        auto readerName = this->ReadString();

        // Read the type reader version.
        this->ReadInt32();

        // Look up and store this type reader implementation class.
        auto reader = ContentReader::TypeReaderManager.GetByReaderName(readerName);

        assert(reader != nullptr);

        this->typeReaders.push_back(reader);
    }

    this->sharedResourceCount = this->Read7BitEncodedInt();
}

void ContentReader::ReadSharedResources()
{
    for (Int32 i = 0; i < this->sharedResourceCount; i++)
    {
        auto sharedResourceType = this->Read7BitEncodedInt();

        if (sharedResourceType != 0)
        {
            auto resource = this->typeReaders[sharedResourceType - 1]->Read(*this);

            for (auto& fixup : this->fixupActions)
            {
                if (fixup.Id() == i)
                {
                    fixup.Callback(resource);
                }
            }
        }
    }
}
