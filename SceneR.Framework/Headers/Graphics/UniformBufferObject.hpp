// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UNIFORMBUFFEROBJECT_HPP
#define UNIFORMBUFFEROBJECT_HPP

#include <map>
#include <vector>

#include <System/Core.hpp>
#include <Graphics/BufferObject.hpp>
#include <Graphics/BufferUsage.hpp>

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
        class Uniform;

        /**
         * Represents an OpenGL Uniform Buffer Object
         *
         * http://www.opengl.org/wiki/Uniform_Buffer_Object
         */
        class UniformBufferObject
        {
        public:
            /**
             * Initializes a new instance of the UniformBufferObject class.
             */
            UniformBufferObject(const System::UInt32& programId, const System::String& name);

            /**
             * Releases all resources being used by this UniformBufferObject.
             */
            ~UniformBufferObject();

        public:
            /**
             * Sets the value of the given uniform as a System::Boolean.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const System::Boolean& value) const;

            /**
             * Gets the value of the given uniform as an array of System::Boolean.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<System::Boolean>& value) const;

            /**
             * Sets the value of the given uniform as an System::Int32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const System::Int32& value) const;

            /**
             * Sets the value of the given uniform as an array of System::Int32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<System::Int32>& value) const;

            /**
             * Sets the value of the given uniform as an System::UInt32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const System::UInt32& value) const;

            /**
             * Sets the value of the given uniform as an array of System::UInt32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<System::UInt32>& value) const;

            /**
             * Sets the value of the given uniform as a Matrix.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const SceneR::Framework::Matrix& value) const;

            /**
             * Sets the value of the given uniform as an array of Matrix.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Matrix>& value) const;

            /**
             * Sets the value of the given uniform as a Matrix transpose.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValueTranspose(const System::String& uniformName, const SceneR::Framework::Matrix& value) const;

            /**
             * Sets the value of the given uniform as an array of Matrix transpose.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValueTranspose(const System::String& uniformName, const std::vector<SceneR::Framework::Matrix>& value) const;

            /**
             * Sets the value of the given uniform as a Quaternion.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const SceneR::Framework::Quaternion& value) const;

            /**
             * Sets the value of the given uniform as an array of Quaternion.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Quaternion>& value) const;

            /**
             * Sets the value of the given uniform as a System::Single.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const System::Single& value) const;

            /**
             * Sets the value of the given uniform as an array of System::Single.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<System::Single>& value) const;

            /**
             * Sets the value of the given uniform as a Vector2.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const SceneR::Framework::Vector2& value) const;

            /**
             * Sets the value of the given uniform as an array of Vector2.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Vector2>& value) const;

            /**
             * Sets the value of the given uniform as a Vector3.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const SceneR::Framework::Vector3& value) const;

            /**
             * Sets the value of the given uniform as an array of Vector3.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Vector3>& value) const;

            /**
             * Sets the value of the given uniform as a Vector4.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const SceneR::Framework::Vector4& value) const;

            /**
             * Sets the value of the given uniform as an array of Vector4.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Vector4>& value) const;

        public:
            void Describe();
            void DescribeUniforms(const System::UInt32& uniformCount);

        private:
            System::UInt32                    programId;
            System::String                    name;
            System::UInt32                    binding;
            std::map<System::String, Uniform> uniforms;
            BufferObject                      bufferObject;
        };
    }
}

#endif /* UNIFORMBUFFEROBJECT_HPP */
