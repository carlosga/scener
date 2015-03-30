// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BASICEFFECT_HPP
#define BASICEFFECT_HPP

#include <memory>
#include <vector>

#include <System/Core.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectDirtyFlags.hpp>
#include <Graphics/IEffectFog.hpp>
#include <Graphics/IEffectLights.hpp>
#include <Graphics/IEffectMatrices.hpp>
#include <Graphics/Texture2D.hpp>
#include <Graphics/Effect.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class DirectionalLight;
        class GraphicsDevice;

        /**
         * Contains a basic rendering effect.
         * http://msdn.microsoft.com/en-us/library/bb194916(v=xnagamestudio.40).aspx
         */
        class BasicEffect final : public Effect, public IEffectMatrices, public IEffectLights, public IEffectFog
        {
        public:
            /**
             * Initializes a new instance of the BassicEffect class.
             *
             * @param graphicsDevice the graphics device
             */
            BasicEffect(GraphicsDevice& graphicsDevice);

            /**
             * Initializes a new instance of the BasicEffect class.
             */
            BasicEffect(const BasicEffect& effect);

            /**
             * Releases all resources being used by this BasicEffect.
             */
            ~BasicEffect() override;

        public:
            void Dispose() override;

        public:
            /**
             * Gets the material alpha which determines its transparency.
             * Range is between 1 (fully opaque) and 0 (fully transparent).
             */
            const System::Single& Alpha() const;

            /**
             * Sets the material alpha which determines its transparency.
             * Range is between 1 (fully opaque) and 0 (fully transparent).
             */
            void Alpha(const System::Single& alpha);

            /**
             * Gets the ambient light for the current effect
             */
            const SceneR::Framework::Vector3& AmbientLightColor() const override;

            /**
             * Gets the ambient light for the current effect
             */
            void AmbientLightColor(const SceneR::Framework::Vector3& ambientLightColor) override;

            /**
             * Gets the ambient color for a light, the range of color values is from 0 to 1.
             */
            const SceneR::Framework::Vector3& DiffuseColor() const;

            /**
             * Gets the ambient color for a light, the range of color values is from 0 to 1.
             */
            void DiffuseColor(const SceneR::Framework::Vector3& diffuseColor);

            /**
             * Gets the first directional light
             */
            const DirectionalLight& DirectionalLight0() const override;

            /**
             * Gets the second directional light
             */
            const DirectionalLight& DirectionalLight1() const override;

            /**
             * Gets the third directional light
             */
            const DirectionalLight& DirectionalLight2() const override;

            /**
             * Enables default lighting for this effect.
             */
            void EnableDefaultLighting() override;

            /**
             * Gets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            const SceneR::Framework::Vector3& EmissiveColor() const;

            /**
             * Sets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            void EmissiveColor(const SceneR::Framework::Vector3& emissiveColor);

            /**
             * Gets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            const SceneR::Framework::Vector3& FogColor() const override;

            /**
             * Sets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            void FogColor(const SceneR::Framework::Vector3& fogColor) override;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            const System::Boolean& FogEnabled() const override;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            void FogEnabled(const System::Boolean& fogEnabled) override;

            /**
             * Gets maximum z value for fog, which ranges from 0 to 1.
             */
            const System::Single& FogEnd() const override;

            /**
             * Sets maximum z value for fog, which ranges from 0 to 1.
             */
            void FogEnd(const System::Single& fogEnd) override;

            /**
             * Gets minimum z value for fog, which ranges from 0 to 1.
             */
            const System::Single& FogStart() const override;

            /**
             * Sets minimum z value for fog, which ranges from 0 to 1.
             */
            void FogStart(const System::Single& fogStart) override;

            /**
             * Gets a value indicating wheter lighting is enabled for the current effect.
             */
            const System::Boolean& LightingEnabled() const override;

            /**
             * Sets a value indicating wheter lighting is enabled for the current effect.
             */
            void LightingEnabled(const System::Boolean& lightingEnabled) override;

            /**
             * Gets a value indicating that per-pixel lighting should be used if it is
             * available for the current adapter.
             */
            const System::Boolean& PreferPerPixelLighting() const;

            /**
             * Gets a value indicating that per-pixel lighting should be used if it is
             * available for the current adapter.
             */
            void PreferPerPixelLighting(const System::Boolean& preferPerPixelLighting);

            /**
             * Gets the projection matrix in the current effect.
             */
            const SceneR::Framework::Matrix& Projection() const override;

            /**
             * Sets the projection matrix in the current effect.
             */
            void Projection(const SceneR::Framework::Matrix& projection) override;

            /**
             * Gets the specular color for a material,
             * the range of color values is from 0 to 1.
             */
            const SceneR::Framework::Vector3& SpecularColor() const;

            /**
             * Gets the specular color for a material,
             * the range of color values is from 0 to 1.
             */
            void SpecularColor(const SceneR::Framework::Vector3& specularColor);

            /**
             * Gets specular power of this effect material.
             */
            const System::Single& SpecularPower() const;

            /**
             * Sets specular power of this effect material.
             */
            void SpecularPower(const System::Single& specularPower);

            /**
             * Gets a texture to be applied by this effect.
             */
            const std::shared_ptr<Texture2D>& Texture() const;

            /**
             * Sets a texture to be applied by this effect.
             */
            void Texture(const std::shared_ptr<Texture2D>& texture);

            /**
             * Gets a value indicating wheter textures are enabled for this effect
             */
            const System::Boolean& TextureEnabled() const;

            /**
             * Sets a value indicating wheter textures are enabled for this effect
             */
            void TextureEnabled(const System::Boolean& textureEnabled);

            /**
             * Gets the view matrix in the current effect.
             */
            const SceneR::Framework::Matrix& View() const override;

            /**
             * Sets the view matrix in the current effect.
             */
            void View(const SceneR::Framework::Matrix& view) override;

            /**
             * Gets a value indicating wheter vertex colors are enabled for this effect
             */
            const System::Boolean& VertexColorEnabled() const;

            /**
             * Gets a value indicating wheter vertex colors are enabled for this effect
             */
            void VertexColorEnabled(const System::Boolean& vertexColorEnabled);

            /**
             * Gets the world matrix in the current effect.
             */
            const SceneR::Framework::Matrix& World() const override;

            /**
             * Sets the world matrix in the current effect.
             */
            void World(const SceneR::Framework::Matrix& world) override;

        public:
            /**
             * Ends the application of the effect state just after rendering the effect.
             */
            void End() override;

        protected:
            /**
             * Computes derived parameter values immediately before applying the effect.
             */
            void OnApply() override;

        private:
            void CreateShader();
            void CacheEffectParameters();

        private:
            System::Single             alpha;
            SceneR::Framework::Vector3 ambientLightColor;
            SceneR::Framework::Vector3 diffuseColor;
            DirectionalLight           light0;
            DirectionalLight           light1;
            DirectionalLight           light2;
            System::Boolean            lightingEnabled;
            SceneR::Framework::Vector3 emissiveColor;
            System::Boolean            fogEnabled;
            SceneR::Framework::Vector3 fogColor;
            System::Single             fogEnd;
            System::Single             fogStart;
            System::Boolean            preferPerPixelLighting;
            SceneR::Framework::Matrix  projection;
            SceneR::Framework::Vector3 specularColor;
            System::Single             specularPower;
            System::Boolean            textureEnabled;
            std::shared_ptr<Texture2D> texture;
            System::Boolean            vertexColorEnabled;
            SceneR::Framework::Matrix  view;
            SceneR::Framework::Matrix  world;
            SceneR::Framework::Matrix  worldView;
            System::Boolean            oneLight;
            System::UInt32             shaderIndex;

            EffectDirtyFlags           dirtyFlags;

            EffectParameter            textureParam;
            EffectParameter            diffuseColorParam;
            EffectParameter            emissiveColorParam;
            EffectParameter            specularColorParam;
            EffectParameter            specularPowerParam;
            EffectParameter            eyePositionParam;
            EffectParameter            fogColorParam;
            EffectParameter            fogVectorParam;
            EffectParameter            worldParam;
            EffectParameter            worldInverseTransposeParam;
            EffectParameter            worldViewProjParam;

        private:
            static int VSIndices[32];
            static int PSIndices[32];
        };
    }
}

#endif  /* BASICEFFECT_HPP */
