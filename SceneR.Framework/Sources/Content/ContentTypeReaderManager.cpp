// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentTypeReaderManager.hpp>

#include <Content/Readers/AnimationClipMapReader.hpp>
#include <Content/Readers/AnimationClipReader.hpp>
#include <Content/Readers/BasicEffectReader.hpp>
#include <Content/Readers/BoundingSphereReader.hpp>
#include <Content/Readers/DictionaryReader.hpp>
#include <Content/Readers/EffectMaterialReader.hpp>
#include <Content/Readers/ExternalReferenceReader.hpp>
#include <Content/Readers/IndexBufferReader.hpp>
#include <Content/Readers/Int32ListReader.hpp>
#include <Content/Readers/Int32Reader.hpp>
#include <Content/Readers/KeyframeListReader.hpp>
#include <Content/Readers/KeyframeReader.hpp>
#include <Content/Readers/MatrixListReader.hpp>
#include <Content/Readers/MatrixReader.hpp>
#include <Content/Readers/ModelReader.hpp>
#include <Content/Readers/SkinnedEffectReader.hpp>
#include <Content/Readers/SkinningDataReader.hpp>
#include <Content/Readers/StringReader.hpp>
#include <Content/Readers/Texture2DReader.hpp>
#include <Content/Readers/TextureReader.hpp>
#include <Content/Readers/TimeSpanReader.hpp>
#include <Content/Readers/VertexBufferReader.hpp>
#include <Content/Readers/VertexDeclarationReader.hpp>

using namespace SceneR::Content;

ContentTypeReaderManager::ContentTypeReaderManager()
{
    this->RegisterKnownTypeReaders();
}

ContentTypeReaderManager::~ContentTypeReaderManager()
{
    if (this->readers.size() > 0)
    {
        for (auto& reader : this->readers)
        {
            delete reader.second;
        }

        this->readers.clear();
    }
}

ContentTypeReader* ContentTypeReaderManager::GetByReaderName(const std::u16string& name)
{
    return this->readers[name];
}

void ContentTypeReaderManager::RegisterKnownTypeReaders()
{
    this->RegisterTypeReader<AnimationClipMapReader>(u"Microsoft.Xna.Framework.Content.DictionaryReader`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[SkinnedModel.AnimationClip, SkinnedModel, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null]]");
    this->RegisterTypeReader<AnimationClipReader>(u"Microsoft.Xna.Framework.Content.ReflectiveReader`1[[SkinnedModel.AnimationClip, SkinnedModel, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null]]");
    this->RegisterTypeReader<BasicEffectReader>(u"Microsoft.Xna.Framework.Content.BasicEffectReader, Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553");
    this->RegisterTypeReader<BoundingSphereReader>(u"Microsoft.Xna.Framework.Content.BoundingSphereReader, Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553");
    this->RegisterTypeReader<DictionaryReader>(u"Microsoft.Xna.Framework.Content.DictionaryReader`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[System.Object, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]]");
    this->RegisterTypeReader<EffectMaterialReader>(u"Microsoft.Xna.Framework.Content.EffectMaterialReader, Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553");
    this->RegisterTypeReader<ExternalReferenceReader>(u"Microsoft.Xna.Framework.Content.ExternalReferenceReader");
    this->RegisterTypeReader<IndexBufferReader>(u"Microsoft.Xna.Framework.Content.IndexBufferReader, Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553");
    this->RegisterTypeReader<Int32ListReader>(u"Microsoft.Xna.Framework.Content.ListReader`1[[System.Int32, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]]");
    this->RegisterTypeReader<Int32Reader>(u"Microsoft.Xna.Framework.Content.Int32Reader");
    this->RegisterTypeReader<KeyframeListReader>(u"Microsoft.Xna.Framework.Content.ListReader`1[[SkinnedModel.Keyframe, SkinnedModel, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null]]");
    this->RegisterTypeReader<KeyframeReader>(u"Microsoft.Xna.Framework.Content.ReflectiveReader`1[[SkinnedModel.Keyframe, SkinnedModel, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null]]");
    this->RegisterTypeReader<MatrixListReader>(u"Microsoft.Xna.Framework.Content.ListReader`1[[Microsoft.Xna.Framework.Matrix, Microsoft.Xna.Framework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553]]");
    this->RegisterTypeReader<MatrixReader>(u"Microsoft.Xna.Framework.Content.MatrixReader");
    this->RegisterTypeReader<ModelReader>(u"Microsoft.Xna.Framework.Content.ModelReader, Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553");
    this->RegisterTypeReader<SkinnedEffectReader>(u"Microsoft.Xna.Framework.Content.SkinnedEffectReader, Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553");
    this->RegisterTypeReader<SkinningDataReader>(u"Microsoft.Xna.Framework.Content.ReflectiveReader`1[[SkinnedModel.SkinningData, SkinnedModel, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null]]");
    this->RegisterTypeReader<StringReader>(u"Microsoft.Xna.Framework.Content.StringReader");
    this->RegisterTypeReader<Texture2DReader>(u"Microsoft.Xna.Framework.Content.Texture2DReader, Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553");
    this->RegisterTypeReader<TextureReader>(u"Microsoft.Xna.Framework.Content.TextureReader, Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553");
    this->RegisterTypeReader<VertexBufferReader>(u"Microsoft.Xna.Framework.Content.VertexBufferReader, Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553");
    this->RegisterTypeReader<VertexDeclarationReader>(u"Microsoft.Xna.Framework.Content.VertexDeclarationReader, Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553");
    this->RegisterTypeReader<TimeSpanReader>(u"Microsoft.Xna.Framework.Content.TimeSpanReader");

    // Built-In Readers
    // Microsoft.Xna.Framework.Content.ByteReader
    // Microsoft.Xna.Framework.Content.SByteReader
    // Microsoft.Xna.Framework.Content.Int16Reader
    // Microsoft.Xna.Framework.Content.UInt16Reader
    // Microsoft.Xna.Framework.Content.Int32Reader
    // Microsoft.Xna.Framework.Content.UInt32Reader
    // Microsoft.Xna.Framework.Content.Int64Reader
    // Microsoft.Xna.Framework.Content.UInt64Reader
    // Microsoft.Xna.Framework.Content.SingleReader
    // Microsoft.Xna.Framework.Content.DoubleReader
    // Microsoft.Xna.Framework.Content.BooleanReader
    // Microsoft.Xna.Framework.Content.CharReader
    // Microsoft.Xna.Framework.Content.StringReader
    // Microsoft.Xna.Framework.Content.ObjectReader

    // System Type readers
    // Microsoft.Xna.Framework.Content.EnumReader`1[[T]]
    // Microsoft.Xna.Framework.Content.NullableReader`1[[T]]
    // Microsoft.Xna.Framework.Content.ArrayReader`1[[T]]
    // Microsoft.Xna.Framework.Content.ListReader`1[[T]]
    // Microsoft.Xna.Framework.Content.DictionaryReader`2[[K],[V]]
    // Microsoft.Xna.Framework.Content.TimeSpanReader
    // Microsoft.Xna.Framework.Content.DateTimeReader
    // Microsoft.Xna.Framework.Content.DecimalReader

    // External reference reader
    // Microsoft.Xna.Framework.Content.ExternalReferenceReader
    // Filename (relative to the current .xnb file, and not including the .xnb file extension)
    // pointing to a separate .xnb file which contains an object of type T, the contents of
    // which should be inserted at the current location into the file currently being read.
    // If the string is empty, the resulting object is null.

    // Math readers
    // Microsoft.Xna.Framework.Content.Vector2Reader
    // Microsoft.Xna.Framework.Content.Vector3Reader
    // Microsoft.Xna.Framework.Content.Vector4Reader
    // Microsoft.Xna.Framework.Content.MatrixReader
    // Microsoft.Xna.Framework.Content.QuaternionReader
    // Microsoft.Xna.Framework.Content.ColorReader
    // Microsoft.Xna.Framework.Content.PlaneReader
    // Microsoft.Xna.Framework.Content.PointReader
    // Microsoft.Xna.Framework.Content.RectangleReader
    // Microsoft.Xna.Framework.Content.BoundingBoxReader
    // Microsoft.Xna.Framework.Content.BoundingSphereReader
    // Microsoft.Xna.Framework.Content.BoundingFrustumReader
    // Microsoft.Xna.Framework.Content.RayReader
    // Microsoft.Xna.Framework.Content.CurveReader

    // Graphics readers
    // Microsoft.Xna.Framework.Content.TextureReader
    // Microsoft.Xna.Framework.Content.Texture2DReader
    // Microsoft.Xna.Framework.Content.Texture3DReader
    // Microsoft.Xna.Framework.Content.TextureCubeReader
    // Microsoft.Xna.Framework.Content.IndexBufferReader
    // Microsoft.Xna.Framework.Content.VertexBufferReader
    // Microsoft.Xna.Framework.Content.VertexDeclarationReader
    // Microsoft.Xna.Framework.Content.EffectReader
    // Microsoft.Xna.Framework.Content.EffectMaterialReader
    // Microsoft.Xna.Framework.Content.BasicEffectReader
    // Microsoft.Xna.Framework.Content.AlphaTestEffectReader
    // Microsoft.Xna.Framework.Content.DualTextureEffectReader
    // Microsoft.Xna.Framework.Content.EnvironmentMapEffectReader
    // Microsoft.Xna.Framework.Content.SkinnedEffectReader
    // Microsoft.Xna.Framework.Content.SpriteFontReader
    // Microsoft.Xna.Framework.Content.ModelReader

    // Media readers
    // Microsoft.Xna.Framework.Content.SoundEffectReader
    // Microsoft.Xna.Framework.Content.SongReader
    // Microsoft.Xna.Framework.Content.VideoReader

    // Other readers
    //  Microsoft.Xna.Framework.Content.ReflectiveReader`1[[T]]
}
