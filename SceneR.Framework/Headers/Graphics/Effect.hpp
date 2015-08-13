// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

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
             * Sets the value of the EffectParameter as a boolean.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const bool& value) const;

            /**
             * Gets the value of the EffectParameter as an array of booleans.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const std::vector<bool>& value) const;

            /**
             * Sets the value of the EffectParameter as an int32_t.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const std::int32_t& value) const;

            /**
             * Sets the value of the EffectParameter as an array of int32_t
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const std::vector<std::int32_t>& value) const;

            /**
             * Sets the value of the EffectParameter as an uint32_t.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const std::uint32_t& value) const;

            /**
             * Sets the value of the EffectParameter as an array of uint32_t.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const std::vector<std::uint32_t>& value) const;

            /**
             * Sets the value of the EffectParameter as a Matrix.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const SceneR::Framework::Matrix& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Matrix.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const std::vector<SceneR::Framework::Matrix>& value) const;

            /**
             * Sets the value of the EffectParameter as a Matrix transpose.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValueTranspose(const std::u16string& uniformName, const SceneR::Framework::Matrix& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Matrix transpose.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValueTranspose(const std::u16string&                         uniformName
                                 , const std::vector<SceneR::Framework::Matrix>& value) const;

            /**
             * Sets the value of the EffectParameter as a Quaternion.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const SceneR::Framework::Quaternion& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Quaternion.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string&                             uniformName
                        , const std::vector<SceneR::Framework::Quaternion>& value) const;

            /**
             * Sets the value of the EffectParameter as a float.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const float& value) const;

            /**
             * Sets the value of the EffectParameter as an array of float.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const std::vector<float>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector2.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const SceneR::Framework::Vector2& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector2.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string&                          uniformName
                        , const std::vector<SceneR::Framework::Vector2>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector3.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const SceneR::Framework::Vector3& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector3.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string&                          uniformName
                        , const std::vector<SceneR::Framework::Vector3>& value) const;

            /**
             * Sets the value of the EffectParameter as a Vector4.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string& uniformName, const SceneR::Framework::Vector4& value) const;

            /**
             * Sets the value of the EffectParameter as an array of Vector4.
             * @param uniformName the uniform name
             * @param value the value to assign to the shader uniform.
             */
            void SetValue(const std::u16string&                          uniformName
                        , const std::vector<SceneR::Framework::Vector4>& value) const;

        protected:
            /**
             * @brief Adds the given shader sources to the shader program for later compilation.
             * @param name the name of the shader.
             * @param type the type of the shader.
             * @param source the shader sources.
             */
            void AddShader(const std::u16string&            name
                         , const ShaderType&                type
                         , const std::vector<std::uint8_t>& source);

            /**
             * @brief Adds the given shader sources and includes to the shader program for later compilation
             * @param name the name of the shader.
             * @param type the type of the shader.
             * @param source the shader sources.
             * @param includes the shader sources for "include" files.
             */
            void AddShader(const std::u16string&            name
                         , const ShaderType&                type
                         , const std::vector<std::uint8_t>& source
                         , const std::vector<std::string>&  includes);

            /**
             * Compiles and links the shader program sources.
             */
            void Build();

            /**
             * Activates the shader subroutine with the given index.
             */
            void ActivateSubroutine(const std::uint32_t& subroutineIndex) const;

            /**
             * Activates the shader subroutine with the given shader type and index.
             */
            void ActivateSubroutine(const ShaderType& type, const std::uint32_t& subroutineIndex) const;

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
            std::uint32_t                        id;
            std::vector<std::shared_ptr<Shader>> shaders;
            std::shared_ptr<UniformBufferObject> uniformBuffer;
        };
    }
}

#endif  /* EFFECT_HPP */
