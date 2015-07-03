// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECTPARAMETER_HPP
#define EFFECTPARAMETER_HPP

#include <memory>
#include <vector>

#include <System/Core.hpp>
#include <Graphics/Effect.hpp>
#include <Graphics/EffectParameterCollection.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct Matrix;
        struct Quaternion;
        struct Vector2;
        struct Vector3;
        struct Vector4;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Texture;
        class UniformBufferObject;

        /**
         * Represents an Effect parameter.
         */
        class EffectParameter final
        {
        public:
            /**
             * Initializes a new instance of the EffectParameter class.
             */
            EffectParameter();

            /**
             * Initializes a new instance of the EffectParameter class.
             * @param name the parameter name.
             * @param index the parameter index.
             * @param offset the parameter offset.
             * @param type the parameter raw type.
             */
            EffectParameter(const std::u16string&                      name
                          , const System::UInt32&                      index
                          , const System::UInt32&                      offset
                          , const System::UInt32&                      type
                          , const std::shared_ptr<UniformBufferObject> uniformBuffer);

            /**
             * Copy constructor.
             */
            EffectParameter(const EffectParameter& parameter);

            /**
             * Destructor
             */
            ~EffectParameter();

        public:
            /**
             * Gets the number of columns in the parameter description.
             */
            const System::Int32& ColumnCount() const;

            /**
             * Gets the collection of effect parameters.
             */
            EffectParameterCollection& Elements();

            /**
             * Gets the name of the parameter.
             */
            const std::u16string& Name() const;

            /**
             * Gets the class of the parameter.
             */
            const EffectParameterClass& ParameterClass() const;

            /**
             * Gets the type of the parameter.
             */
            const EffectParameterType& ParameterType() const;

            /**
             * Gets the number of rows in the parameter description.
             */
            const System::Int32& RowCount() const;

            /**
             * Gets the collection of structure members.
             */
            EffectParameterCollection& StructureMembers();

        public:
            /**
             * Gets the value of the EffectParameter as a System::Boolean.
             */
            bool GetValueBoolean() const;

            /**
             * Gets the value of the EffectParameter as an array of System::Boolean.
             */
            std::vector<bool> GetValueBooleanArray() const;

            /**
             * Gets the value of the EffectParameter as an System::Int32.
             */
            System::Int32 GetValueInt32() const;

            /**
             *  Gets the value of the EffectParameter as an array of System::Int32.
             */
            std::vector<System::Int32> GetValueInt32Array() const;

            /**
             * Gets the value of the EffectParameter as a Matrix.
             */
            SceneR::Framework::Matrix GetValueMatrix() const;

            /**
             * Gets the value of the EffectParameter as an array of Matrix.
             */
            std::vector<SceneR::Framework::Matrix> GetValueMatrixArray() const;

            /**
             * Gets the value of the EffectParameter as a Matrix transpose.
             */
            SceneR::Framework::Matrix GetValueMatrixTranspose() const;

            /**
             * Gets the value of the EffectParameter as an array of Matrix transpose.
             */
            std::vector<SceneR::Framework::Matrix> GetValueMatrixTransposeArray();

            /**
             * Gets the value of the EffectParameter as a Quaternion.
             */
            SceneR::Framework::Quaternion GetValueQuaternion() const;

            /**
             * Gets the value of the EffectParameter as an array of Quaternion.
             */
            std::vector<SceneR::Framework::Quaternion> GetValueQuaternionArray() const;

            /**
             * Gets the value of the EffectParameter as a System::Single.
             */
            System::Single GetValueSingle() const;

            /**
             * Gets the value of the EffectParameter as an array of System::Single.
             */
            std::vector<System::Single> GetValueSingleArray() const;

            /**
             * Gets the value of the EffectParameter as an String.
             */
            std::u16string GetValueString() const;

            // GetValueTexture2D    Gets the value of the EffectParameter as a Texture2D.
            // GetValueTexture3D    Gets the value of the EffectParameter as a Texture3D.
            // GetValueTextureCube  Gets the value of the EffectParameter as a TextureCube.
            // GetValueVector2  Gets the value of the EffectParameter as a Vector2.
            // GetValueVector2Array     Gets the value of the EffectParameter as an array of Vector2.

            /**
             * Gets the value of the EffectParameter as a Vector3.
             */
            SceneR::Framework::Vector3 GetValueVector3() const;

            /**
             * Gets the value of the EffectParameter as an array of Vector3.
             */
            std::vector<SceneR::Framework::Vector3> GetValueVector3Array() const;

            // GetValueVector4  Gets the value of the EffectParameter as a Vector4.
            // GetValueVector4Array     Gets the value of the EffectParameter as an array of Vector4.

        public:
            /**
             * Sets the value of the EffectParameter as a System::Boolean.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const bool& value) const;

            /**
             * Gets the value of the EffectParameter as an array of System::Boolean.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<bool>& value) const;

            /**
             * Sets the value of the EffectParameter as an System::Int32.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const System::Int32& value) const;

            /**
             *  Sets the value of the EffectParameter as an array of System::Int32.
             *  @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<System::Int32>& value) const;

            /**
             * Sets the value of the EffectParameter as an System::UInt32.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const System::UInt32& value) const;

            /**
             *  Sets the value of the EffectParameter as an array of System::UInt32.
             *  @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<System::UInt32>& value) const;

            /**
             * Sets the value of the EffectParameter as a Matrix.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Framework::Matrix& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Matrix.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<SceneR::Framework::Matrix>& value) const;

            /**
             * Sets the value of the EffectParameter as a Matrix transpose.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValueTranspose(const SceneR::Framework::Matrix& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Matrix transpose.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValueTranspose(const std::vector<SceneR::Framework::Matrix>& value) const;

            /**
             * Sets the value of the EffectParameter as a Quaternion.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Framework::Quaternion& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Quaternion.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<SceneR::Framework::Quaternion>& value) const;

            /**
             * Sets the value of the EffectParameter as a System::Single.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const System::Single& value) const;

            /**
             * Sets the value of the EffectParameter as an array of System::Single.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<System::Single>& value) const;

            /**
             * Sets the value of the EffectParameter as an String.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::u16string& value) const;

            /**
             * Sets the value of the EffectParameter as a Texture.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Graphics::Texture& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector2.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Framework::Vector2& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector2.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<SceneR::Framework::Vector2>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector3.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Framework::Vector3& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector3.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<SceneR::Framework::Vector3>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector4.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Framework::Vector4& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector4.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<SceneR::Framework::Vector4>& value) const;

        public:
            EffectParameter& operator=(const EffectParameter& parameter);

        private:
            void Describe(const System::Int32& type);

        private:
            System::Int32                        columnCount;
            EffectParameterCollection            elements;
            std::u16string                       name;
            EffectParameterClass                 parameterClass;
            EffectParameterType                  parameterType;
            System::Int32                        rowCount;
            EffectParameterCollection            structureMembers;
            System::UInt32                       index;
            System::UInt32                       offset;
            std::shared_ptr<UniformBufferObject> uniformBuffer;
        };
    }
}

#endif  /* EFFECTPARAMETER_HPP */
