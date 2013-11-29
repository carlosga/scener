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

ContentReader::ContentReader(const String&   assetName,
                             ContentManager& contentManager,
                             Stream&         stream)
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

ContentManager& ContentReader::GetContentManager()
{
    return this->contentManager;
}

Color ContentReader::ReadColor()
{
    Single r = this->ReadSingle();
    Single g = this->ReadSingle();
    Single b = this->ReadSingle();
    Single a = this->ReadSingle();

    return Color(r, g, b, a);
}

Matrix ContentReader::ReadMatrix()
{
    Single m11 = this->ReadSingle();
    Single m12 = this->ReadSingle();
    Single m13 = this->ReadSingle();
    Single m14 = this->ReadSingle();

    Single m21 = this->ReadSingle();
    Single m22 = this->ReadSingle();
    Single m23 = this->ReadSingle();
    Single m24 = this->ReadSingle();

    Single m31 = this->ReadSingle();
    Single m32 = this->ReadSingle();
    Single m33 = this->ReadSingle();
    Single m34 = this->ReadSingle();

    Single m41 = this->ReadSingle();
    Single m42 = this->ReadSingle();
    Single m43 = this->ReadSingle();
    Single m44 = this->ReadSingle();

    return Matrix(m11, m12, m13, m14,
                  m21, m22, m23, m24,
                  m31, m32, m33, m34,
                  m41, m42, m43, m44);
}

Vector2 ContentReader::ReadVector2()
{
    Single x = this->ReadSingle();
    Single y = this->ReadSingle();

    return Vector2(x, y);
}

Vector3 ContentReader::ReadVector3()
{
    Single x = this->ReadSingle();
    Single y = this->ReadSingle();
    Single z = this->ReadSingle();

    return Vector3(x, y, z);
}

Vector4 ContentReader::ReadVector4()
{
    Single x = this->ReadSingle();
    Single y = this->ReadSingle();
    Single z = this->ReadSingle();
    Single w = this->ReadSingle();

    return Vector4(x, y, z, w);
}

Quaternion ContentReader::ReadQuaternion()
{
    Single x = this->ReadSingle();
    Single y = this->ReadSingle();
    Single z = this->ReadSingle();
    Single w = this->ReadSingle();

    return Quaternion(x, y, z, w);
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
