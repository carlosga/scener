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

#ifndef SKINNEDEFFECT_HPP
#define SKINNEDEFFECT_HPP

#include <memory>
#include <vector>

#include <Graphics/IEffectFog.hpp>
#include <Graphics/IEffectLights.hpp>
#include <Graphics/IEffectMatrices.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/Texture2D.hpp>
#include <Graphics/Effect.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class DirectionalLight;
        class GraphicsDevice;

        /**
         * Contains a configurable effect for rendering skinned character models.
         */
        class SkinnedEffect: public Effect, public IEffectMatrices, public IEffectLights, public IEffectFog
        {
            static System::String VSSource;
            static System::String FSSource;

        public:
            /**
             * Initializes a new instance of the SkinnedEffect class.
             *
             * @param graphicsDevice the graphics device
             */
            SkinnedEffect(GraphicsDevice& graphicsDevice);

            /**
             * Initializes a new instance of the SkinnedEffect class.
             */
            SkinnedEffect(const SkinnedEffect& effect);

            /**
             * Releases all resources being used by this BasicEffect.
             */
            virtual ~SkinnedEffect();

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
            virtual const SceneR::Framework::Vector3& AmbientLightColor() const override;

            /**
             * Gets the ambient light for the current effect
             */
            virtual void AmbientLightColor(const SceneR::Framework::Vector3& ambientLightColor) override;

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
            virtual const std::shared_ptr<DirectionalLight>& DirectionalLight0() const override;

            /**
             * Sets the first directional light
             */
            virtual void DirectionalLight0(const std::shared_ptr<DirectionalLight>& directionalLight) override;

            /**
             * Gets the second directional light
             */
            virtual const std::shared_ptr<DirectionalLight>& DirectionalLight1() const override;

            /**
             * Sets the second directional light
             */
            virtual void DirectionalLight1(const std::shared_ptr<DirectionalLight>& directionalLight) override;

            /**
             * Gets the third directional light
             */
            virtual const std::shared_ptr<DirectionalLight>& DirectionalLight2() const override;

            /**
             * Sets the third directional light
             */
            virtual void DirectionalLight2(const std::shared_ptr<DirectionalLight>& directionalLight) override;

            /**
             * Enables default lighting for this effect.
             */
            virtual void EnableDefaultLighting() override;

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
            virtual const SceneR::Framework::Vector3& FogColor() const override;

            /**
             * Sets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            virtual void FogColor(const SceneR::Framework::Vector3& fogColor) override;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            virtual const System::Boolean& FogEnabled() const override;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            virtual void FogEnabled(const System::Boolean& fogEnabled) override;

            /**
             * Gets maximum z value for fog, which ranges from 0 to 1.
             */
            virtual const System::Single& FogEnd() const override;

            /**
             * Sets maximum z value for fog, which ranges from 0 to 1.
             */
            virtual void FogEnd(const System::Single& fogEnd) override;

            /**
             * Gets minimum z value for fog, which ranges from 0 to 1.
             */
            virtual const System::Single& FogStart() const override;

            /**
             * Sets minimum z value for fog, which ranges from 0 to 1.
             */
            virtual void FogStart(const System::Single& fogStart) override;

            /**
             * Gets a value indicating wheter lighting is enabled for the current effect.
             */
            virtual const System::Boolean& LightingEnabled() const override;

            /**
             * Sets a value indicating wheter lighting is enabled for the current effect.
             */
            virtual void LightingEnabled(const System::Boolean& lightingEnabled) override;

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
            virtual const SceneR::Framework::Matrix& Projection() const override;

            /**
             * Sets the projection matrix in the current effect.
             */
            virtual void Projection(const SceneR::Framework::Matrix& projection) override;

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
            virtual const SceneR::Framework::Matrix& View() const override;

            /**
             * Sets the view matrix in the current effect.
             */
            virtual void View(const SceneR::Framework::Matrix& view) override;

            /**
             * Gets the world matrix in the current effect.
             */
            virtual const SceneR::Framework::Matrix& World() const override;

            /**
             * Sets the world matrix in the current effect.
             */
            virtual void World(const SceneR::Framework::Matrix& world) override;

        public:
            /**
             * Gets the array of bone transform matrices of this SkinnedEffect.
             */
            std::vector<SceneR::Framework::Matrix> GetBoneTransforms(const System::Size& count) const;

            /**
             * Sets an array of bone transform matrices for a SkinnedEffect.
             */
            void SetBoneTransforms(const std::vector<SceneR::Framework::Matrix>& boneTransforms);

            /**
             * Gets the number of per-vertex skinning weights to evaluate, which is either 1, 2, or 4.
             */
            const System::UInt32& WeightsPerVertex() const;

            /**
             * Sets the number of per-vertex skinning weights to evaluate, which is either 1, 2, or 4.
             */
            void WeightsPerVertex(const System::UInt32& weightsPerVertex);

        protected:
            /**
             * Starts the application of the effect state just prior to rendering the effect.
             */
            virtual void Begin() override;

            /**
             * Ends the application of the effect state just after rendering the effect.
             */
            virtual void End() override;

            /**
             * Computes derived parameter values immediately before applying the effect.
             */
            virtual void OnApply() override;

        private:
            void Initialize();

        private:
            System::Single                         alpha;
            SceneR::Framework::Vector3             ambientLightColor;
            std::vector<SceneR::Framework::Matrix> boneTransforms;
            SceneR::Framework::Vector3             diffuseColor;
            std::shared_ptr<DirectionalLight>      directionalLight0;
            std::shared_ptr<DirectionalLight>      directionalLight1;
            std::shared_ptr<DirectionalLight>      directionalLight2;
            System::Boolean                        enableDefaultLighting;
            SceneR::Framework::Vector3             emissiveColor;
            System::Boolean                        fogEnabled;
            SceneR::Framework::Vector3             fogColor;
            System::Single                         fogEnd;
            System::Single                         fogStart;
            System::Boolean                        preferPerPixelLighting;
            SceneR::Framework::Matrix              projection;
            SceneR::Framework::Vector3             specularColor;
            System::Single                         specularPower;
            System::Boolean                        textureEnabled;
            std::shared_ptr<Texture2D>             texture;
            SceneR::Framework::Matrix              view;
            System::UInt32                         weightsPerVertex;
            SceneR::Framework::Matrix              world;
        };
    }
}

#endif /* SKINNEDEFFECT_HPP */
