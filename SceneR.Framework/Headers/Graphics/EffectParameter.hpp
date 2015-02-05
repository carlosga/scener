// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECTPARAMETER_HPP
#define EFFECTPARAMETER_HPP

#include <memory>
#include <vector>

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
        class ShaderProgram;
        class Texture;

        /**
         * Represents an Effect parameter.
         */
        class EffectParameter
        {
        public:
            /**
             * Initializes a new instance of the EffectParameter class.
             */
            EffectParameter(const System::String&                 name,
                            const EffectParameterClass&           parameterClass,
                            const EffectParameterType&            parameterType,
                            const std::shared_ptr<ShaderProgram>& shaderProgram);

            /**
             * Releases all resources being used by this EffectParameter.
             */
            ~EffectParameter() = default;

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
            const System::String& Name() const;

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
            const System::Boolean& GetValueBoolean() const;

            /**
             * Gets the value of the EffectParameter as an array of System::Boolean.
             */
            const std::vector<System::Boolean>& GetValueBooleanArray() const;

            /**
             * Gets the value of the EffectParameter as an System::Int32.
             */
            const System::Int32& GetValueInt32() const;

            /**
             *  Gets the value of the EffectParameter as an array of System::Int32.
             */
            const std::vector<System::Int32>& GetValueInt32Array() const;

            /**
             * Gets the value of the EffectParameter as a Matrix.
             */
            const SceneR::Framework::Matrix& GetValueMatrix() const;

            /**
             * Gets the value of the EffectParameter as an array of Matrix.
             */
            const std::vector<SceneR::Framework::Matrix>& GetValueMatrixArray() const;

            /**
             * Gets the value of the EffectParameter as a Matrix transpose.
             */
            const SceneR::Framework::Matrix& GetValueMatrixTranspose() const;

            /**
             * Gets the value of the EffectParameter as an array of Matrix transpose.
             */
            const std::vector<SceneR::Framework::Matrix>& GetValueMatrixTransposeArray();

            /**
             * Gets the value of the EffectParameter as a Quaternion.
             */
            const SceneR::Framework::Quaternion& GetValueQuaternion() const;

            /**
             * Gets the value of the EffectParameter as an array of Quaternion.
             */
            const std::vector<SceneR::Framework::Quaternion>& GetValueQuaternionArray() const;

            /**
             * Gets the value of the EffectParameter as a System::Single.
             */
            const System::Single& GetValueSingle() const;

            /**
             * Gets the value of the EffectParameter as an array of System::Single.
             */
            const std::vector<System::Single>& GetValueSingleArray() const;

            /**
             * Gets the value of the EffectParameter as an String.
             */
            const System::String& GetValueString() const;

            // GetValueTexture2D    Gets the value of the EffectParameter as a Texture2D.
            // GetValueTexture3D    Gets the value of the EffectParameter as a Texture3D.
            // GetValueTextureCube  Gets the value of the EffectParameter as a TextureCube.
            // GetValueVector2  Gets the value of the EffectParameter as a Vector2.
            // GetValueVector2Array     Gets the value of the EffectParameter as an array of Vector2.

            /**
             * Gets the value of the EffectParameter as a Vector3.
             */
            const SceneR::Framework::Vector3& GetValueVector3() const;

            /**
             * Gets the value of the EffectParameter as an array of Vector3.
             */
            const std::vector<SceneR::Framework::Vector3>& GetValueVector3Array() const;

            // GetValueVector4  Gets the value of the EffectParameter as a Vector4.
            // GetValueVector4Array     Gets the value of the EffectParameter as an array of Vector4.

        public:
            /**
             * Sets the value of the EffectParameter as a System::Boolean.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const System::Boolean& value) const;

            /**
             * Gets the value of the EffectParameter as an array of System::Boolean.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<System::Boolean>& value) const;

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
            void SetValue(const System::String& value) const;

            /**
             * Sets the value of the EffectParameter as a Texture.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Graphics::Texture& value);

            /**
             * Sets the value of the EffectParameter as a Vector2.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Framework::Vector2& value);

            /**
             * Sets the value of the EffectParameter as an array of Vector2.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<SceneR::Framework::Vector2>& value);

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

        private:
            System::Int32                  columnCount;
            EffectParameterCollection      elements;
            System::String                 name;
            EffectParameterClass           parameterClass;
            EffectParameterType            parameterType;
            System::Int32                  rowCount;
            EffectParameterCollection      structureMembers;
            std::shared_ptr<ShaderProgram> shader;
            System::Int32                  parameterLocation;
        };
    }
}

#endif  /* EFFECTPARAMETER_HPP */
