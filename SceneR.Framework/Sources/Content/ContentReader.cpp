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

#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Framework/Color.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <System/IO/FileStream.hpp>

using namespace System;
using namespace System::IO;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

ContentReader::ContentReader(const String&                    assetName,
                             SceneR::Content::ContentManager& contentManager,
                             Stream&                          stream)
    : BinaryReader(stream),
      assetName(assetName),
      contentManager(contentManager),
      typeReaderManager()
{
    this->ReadHeader();
}

ContentReader::~ContentReader()
{
    BinaryReader::Close();
}

/**
 * Gets the name of the asset currently being read by this ContentReader.
 */
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
    return Color(this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle());
}

Matrix ContentReader::ReadMatrix()
{
    return Matrix(this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle(),
                  this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle(),
                  this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle(),
                  this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle());
}

Vector2 ContentReader::ReadVector2()
{
    return Vector2(this->ReadSingle(), this->ReadSingle());
}

Vector3 ContentReader::ReadVector3()
{
    return Vector3(this->ReadSingle(), this->ReadSingle(), this->ReadSingle());
}

Vector4 ContentReader::ReadVector4()
{
    return Vector4(this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle());
}

Quaternion ContentReader::ReadQuaternion()
{
    return Quaternion(this->ReadSingle(), this->ReadSingle(), this->ReadSingle(), this->ReadSingle());
}

void ContentReader::ReadHeader()
{
    // Magic number.
    this->ReadByte();
    this->ReadByte();
    this->ReadByte();
    this->ReadByte();

    // Format version.
    this->ReadInt32();
}
