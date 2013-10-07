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

#ifndef EFFECTPARAMETER_HPP
#define EFFECTPARAMETER_HPP

#include <memory>
#include <string>
#include <vector>
#include "Core/Matrix.hpp"
#include "Core/Quaternion.hpp"
#include "Core/Vector3.hpp"
#include "Core/Vector4.hpp"
#include "Graphics/EffectParameterClass.hpp"
#include "Graphics/EffectParameterType.hpp"
#include "Shaders/ShaderProgram.hpp"

namespace SceneR
{
    namespace Graphics
    {
        class Effect;

        /**
         * Represents an Effect parameter.
         */
        class EffectParameter
        {
        public:
            /**
             * Initializes a new instance of the EffectParameter class.
             */
            EffectParameter();

            /**
             * Initializes a new instance of the EffectParameter class.
             */
            EffectParameter(const std::wstring&                                   name,
                            const EffectParameterClass&                           parameterClass,
                            const EffectParameterType&                            parameterType,
                            const std::shared_ptr<SceneR::Shaders::ShaderProgram> shader);

        public:
            /**
             * Gets the number of columns in the parameter description.
             */
            const Int32& ColumnCount() const;

            /**
             * Gets the collection of effect parameters.
             */
            const std::vector<EffectParameter>& Elements() const;

            /**
             * Gets the name of the parameter.
             */
            const std::wstring& Name() const;

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
            const Int32& RowCount() const;

            /**
             * Gets the collection of structure members.
             */
            const std::vector<EffectParameter>& StructureMembers() const;

        public:
            /**
             * Gets the value of the EffectParameter as a Boolean.
             */
            const Boolean& GetValueBoolean() const;

            /**
             * Gets the value of the EffectParameter as an array of Boolean.
             */
            const std::vector<Boolean>& GetValueBooleanArray() const;

            /**
             * Gets the value of the EffectParameter as an Int32.
             */
            const Int32& GetValueInt32() const;

            /**
             *  Gets the value of the EffectParameter as an array of Int32.
             */
            const std::vector<Int32>& GetValueInt32Array() const;

            /**
             * Gets the value of the EffectParameter as a Matrix.
             */
            const SceneR::Core::Matrix& GetValueMatrix() const;

            /**
             * Gets the value of the EffectParameter as an array of Matrix.
             */
            const std::vector<SceneR::Core::Matrix>& GetValueMatrixArray() const;

            /**
             * Gets the value of the EffectParameter as a Matrix transpose.
             */
            const SceneR::Core::Matrix& GetValueMatrixTranspose() const;

            /**
             * Gets the value of the EffectParameter as an array of Matrix transpose.
             */
            const std::vector<SceneR::Core::Matrix>& GetValueMatrixTransposeArray();

            /**
             * Gets the value of the EffectParameter as a Quaternion.
             */
            const SceneR::Core::Quaternion& GetValueQuaternion() const;

            /**
             * Gets the value of the EffectParameter as an array of Quaternion.
             */
            const std::vector<SceneR::Core::Quaternion>& GetValueQuaternionArray() const;

            /**
             * Gets the value of the EffectParameter as a Single.
             */
            const Single& GetValueSingle() const;

            /**
             * Gets the value of the EffectParameter as an array of Single.
             */
            const std::vector<Single>& GetValueSingleArray() const;

            /**
             * Gets the value of the EffectParameter as an String.
             */
            const std::wstring& GetValueString() const;

            // GetValueTexture2D    Gets the value of the EffectParameter as a Texture2D.
            // GetValueTexture3D    Gets the value of the EffectParameter as a Texture3D.
            // GetValueTextureCube  Gets the value of the EffectParameter as a TextureCube.
            // GetValueVector2  Gets the value of the EffectParameter as a Vector2.
            // GetValueVector2Array     Gets the value of the EffectParameter as an array of Vector2.

            /**
             * Gets the value of the EffectParameter as a Vector3.
             */
            const SceneR::Core::Vector3& GetValueVector3() const;

            /**
             * Gets the value of the EffectParameter as an array of Vector3.
             */
            const std::vector<SceneR::Core::Vector3>& GetValueVector3Array() const;

            // GetValueVector4  Gets the value of the EffectParameter as a Vector4.
            // GetValueVector4Array     Gets the value of the EffectParameter as an array of Vector4.

        public:
            /**
             * Sets the value of the EffectParameter as a Boolean.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const Boolean& value) const;

            /**
             * Gets the value of the EffectParameter as an array of Boolean.
             * @param value the value to assign to the EffectParameter.
             */
             void SetValue(const std::vector<Boolean> value) const;

            /**
             * Sets the value of the EffectParameter as an Int32.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const Int32& value) const;

            /**
             *  Sets the value of the EffectParameter as an array of Int32.
             *  @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<Int32>& value) const;

            /**
             * Sets the value of the EffectParameter as a Matrix.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Core::Matrix& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Matrix.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<SceneR::Core::Matrix>& value) const;

            /**
             * Sets the value of the EffectParameter as a Matrix transpose.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValueTranspose(const SceneR::Core::Matrix& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Matrix transpose.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValueTranspose(const std::vector<SceneR::Core::Matrix>& value) const;

            /**
             * Sets the value of the EffectParameter as a Quaternion.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Core::Quaternion& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Quaternion.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<SceneR::Core::Quaternion>& value) const;

            /**
             * Sets the value of the EffectParameter as a Single.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const Single& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Single.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<Single>& value) const;

            /**
             * Sets the value of the EffectParameter as an String.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::wstring& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector3.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Core::Vector3& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector3.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<SceneR::Core::Vector3>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector4.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const SceneR::Core::Vector4& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector4.
             * @param value the value to assign to the EffectParameter.
             */
            void SetValue(const std::vector<SceneR::Core::Vector4>& value) const;

        private:
            Int32                                           columnCount;
            std::vector<EffectParameter>                    elements;
            std::wstring                                    name;
            EffectParameterClass                            parameterClass;
            EffectParameterType                             parameterType;
            Int32                                           rowCount;
            std::vector<EffectParameter>                    structureMembers;
            std::shared_ptr<SceneR::Shaders::ShaderProgram> shader;
            Int32                                           parameterLocation;

            friend class Effect;
        };
    }
}

#endif  /* EFFECTPARAMETER_HPP */
