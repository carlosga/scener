// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentReader.hpp>

#include <cassert>
#include <cstdint>
#include <stdexcept>

#include <Content/json11.hpp>

namespace SceneR
{
    namespace Content
    {
        using System::IO::Stream;
        using json11::Json;

        ContentTypeReaderManager ContentReader::TypeReaderManager;

        ContentReader::ContentReader(const std::u16string&            assetName
                                   , SceneR::Content::ContentManager& contentManager
                                   , Stream&                          stream)
            : BinaryReader        { stream }
            , assetName           { assetName }
            , contentManager      ( contentManager )
            , sharedResourceCount { 0 }
            , fixupActions        { }
        {
        }

        ContentReader::~ContentReader()
        {
            BinaryReader::Close();
            this->fixupActions.clear();
            this->sharedResourceCount = 0;
        }

        const std::u16string& ContentReader::AssetName() const
        {
            return this->assetName;
        }

        ContentManager& ContentReader::ContentManager()
        {
            return this->contentManager;
        }

        void ContentReader::ReadSharedResource(const std::function<void(const std::shared_ptr<void>&)>& fixup)
        {
            auto sharedResourceId = this->Read7BitEncodedInt();

            if (sharedResourceId != 0)
            {
                this->fixupActions.push_back({ sharedResourceId - 1, fixup });
            }
        }

        bool ContentReader::ReadHeader()
        {
            // Binary glTF layout
            //
            // -------------------------------
            // 20-byte header
            // -------------------------------
            // magic         unsigned char[4]
            // version       uint32
            // length        uint32
            // jsonOffset    uint32
            // jsonLength    uint32
            // -------------------------------
            // body
            //  JSON UTF-8
            // -------------------------------
            auto magic = ReadBytes(4);
            auto mstr = std::string(magic.begin(), magic.end());

            if (mstr != "glTF")
            {
                return false;
            }

            ReadUInt32();   // version
            ReadUInt32();   // file length

            return true;
        }

        void ContentReader::ReadSharedResources()
        {
            /*
            for (std::size_t i = 0; i < this->sharedResourceCount; i++)
            {
                auto sharedResourceType = this->Read7BitEncodedInt();

                if (sharedResourceType != 0)
                {
                    auto sreader  = this->typeReaders[sharedResourceType - 1];
                    auto resource = sreader->Read(*this);

                    for (auto& fixup : this->fixupActions)
                    {
                        if (fixup.Id() == i)
                        {
                            fixup.Callback(resource);
                        }
                    }
                }
            }
            */
        }
    }
}
