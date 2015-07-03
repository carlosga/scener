// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <memory>
#include <vector>

#include <System/Core.hpp>
#include <Graphics/EffectParameterCollection.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <Graphics/ShaderType.hpp>

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
        class GrapicsDevice;
        class Shader;
        class UniformBufferObject;

        /**
         * Used to set and query effects, and to choose techniques.
         */
        class Effect : public GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the Effect class
             *
             * @param graphicsDevice the graphics device
             */
            Effect(GraphicsDevice& graphicsDevice);

            /**
             * Initializes a new instance of the Effect class.
             *
             * @param effect the effect to be copied
             */
            Effect(const Effect& effect);

            /**
             * Destructor
             */
            ~Effect() override;

        public:
            void Dispose() override;

        public:
            /**
             * Gets a collection of parameters used for this effect.
             */
            EffectParameterCollection& Parameters();

        public:
            /**
             * Starts the application of the effect state just prior to rendering the effect.
             */
            virtual void Begin();

            /**
             * Ends the application of the effect state just after rendering the effect.
             */
            virtual void End();

        public:
            /**
             * Sets the value of the EffectParameter as a System::Boolean.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const bool& value) const;

            /**
             * Gets the value of the EffectParameter as an array of System::Boolean.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<bool>& value) const;

            /**
             * Sets the value of the EffectParameter as an System::Int32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const System::Int32& value) const;

            /**
             * Sets the value of the EffectParameter as an array of System::Int32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<System::Int32>& value) const;

            /**
             * Sets the value of the EffectParameter as an System::UInt32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const System::UInt32& value) const;

            /**
             * Sets the value of the EffectParameter as an array of System::UInt32.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<System::UInt32>& value) const;

            /**
             * Sets the value of the EffectParameter as a Matrix.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const SceneR::Framework::Matrix& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Matrix.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Matrix>& value) const;

            /**
             * Sets the value of the EffectParameter as a Matrix transpose.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValueTranspose(const System::String& uniformName, const SceneR::Framework::Matrix& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Matrix transpose.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValueTranspose(const System::String& uniformName, const std::vector<SceneR::Framework::Matrix>& value) const;

            /**
             * Sets the value of the EffectParameter as a Quaternion.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const SceneR::Framework::Quaternion& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Quaternion.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Quaternion>& value) const;

            /**
             * Sets the value of the EffectParameter as a System::Single.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const System::Single& value) const;

            /**
             * Sets the value of the EffectParameter as an array of System::Single.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<System::Single>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector2.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const SceneR::Framework::Vector2& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector2.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Vector2>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector3.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const SceneR::Framework::Vector3& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector3.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Vector3>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector4.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const SceneR::Framework::Vector4& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector4.
             * @param location the uniform location
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Vector4>& value) const;

        protected:
            /**
             * @brief Adds the given shader sources to the shader program for later compilation.
             * @param name the name of the shader.
             * @param type the type of the shader.
             * @param source the shader sources.
             */
            void AddShader(const System::String& name
                         , const ShaderType&     type
                         , const std::string&    source);

            /**
             * @brief Adds the given shader sources and includes to the shader program for later compilation
             * @param name the name of the shader.
             * @param type the type of the shader.
             * @param source the shader sources.
             * @param includes the shader sources for "include" files.
             */
            void AddShader(const System::String&           name
                         , const ShaderType&               type
                         , const std::string&              source
                         , const std::vector<std::string>& includes);

            /**
             * Compiles and links the shader program sources.
             */
            void Build();

            /**
             * Activates the shader subroutine with the given index.
             */
            void ActivateSubroutine(const System::UInt32& subroutineIndex) const;

            /**
             * Activates the shader subroutine with the given shader type and index.
             */
            void ActivateSubroutine(const ShaderType& type, const System::UInt32& subroutineIndex) const;

        protected:
            /**
             * Verify if the shader program has been linked correctly.
             */
            void VerifyLinkingState();

        protected:
            /**
             * Computes derived parameter values immediately before applying the effect.
             */
            virtual void OnApply() = 0;

        private:
            void DescribeParameters();

        protected:
            EffectParameterCollection            parameters;
            System::UInt32                       id;
            std::vector<std::shared_ptr<Shader>> shaders;
            std::shared_ptr<UniformBufferObject> uniformBuffer;
        };
    }
}

#endif  /* EFFECT_HPP */
