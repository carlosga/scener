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

#ifndef BASICEFFECT_HPP
#define BASICEFFECT_HPP

#include <Framework/Color.hpp>
#include <System/Core.hpp>
#include <Framework/Matrix.hpp>
#include <Graphics/AmbientLight.hpp>
#include <Graphics/Effect.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/IEffectFog.hpp>
#include <Graphics/IEffectLights.hpp>
#include <Graphics/IEffectMatrices.hpp>
#include <memory>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;
        class Texture2D;

        //http://msdn.microsoft.com/en-us/library/bb194916(v=xnagamestudio.40).aspx
        /**
         * Contains a basic rendering effect.
         */
        class BasicEffect : public Effect, public IEffectMatrices, public IEffectLights, public IEffectFog
        {
        public:
            /**
             * Initializes a new instance of the BassicEffect class.
             *
             * @param graphicsDevice the graphics device
             */
            BasicEffect(GraphicsDevice& graphicsDevice);

            /**
             * Releases all resources being used by this BasicEffect.
             */
            ~BasicEffect();

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
             * Gets the ambient color for a light, the range of color values is from 0 to 1.
             */
            virtual const AmbientLight& GetAmbientLight() const override;

            /**
             * Gets the ambient color for a light, the range of color values is from 0 to 1.
             */
            virtual void SetAmbientLight(const AmbientLight& ambientLight) override;

            /**
             * Gets the ambient color for a light, the range of color values is from 0 to 1.
             */
            const SceneR::Framework::Color& DiffuseColor() const;

            /**
             * Gets the ambient color for a light, the range of color values is from 0 to 1.
             */
            void DiffuseColor(const SceneR::Framework::Color& diffuseColor);

            /**
             * Gets the lights of the current effect
             */
            virtual const std::vector<std::shared_ptr<Light>> &GetLights() const override;

            /**
             * Gets the lights of the current effect
             */
            virtual void SetLights(const std::vector<std::shared_ptr<Light>> lights) const override;

            /**
             * Gets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            const SceneR::Framework::Color& EmissiveColor() const;

            /**
             * Sets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            void EmissiveColor(const SceneR::Framework::Color& emissiveColor);

            /**
             * Gets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            virtual const SceneR::Framework::Color& FogColor() const override;

            /**
             * Sets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            virtual void FogColor(const SceneR::Framework::Color& fogColor) override;

            /**
             * Enables fog for the current effect.
             */
            virtual void EnableFog() override;

            /**
             * Disables fog for the current effect.
             */
            virtual void DisableFog() override;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            virtual const System::Boolean& IsFogEnabled() const override;

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
             * Enables lighting support for the current effect.
             */
            virtual void EnableLighting() override;

            /**
             * Enables lighting support for the current effect.
             */
            virtual void DisableLighting() override;

            /**
             * Gets a value indicating wheter lighting is enabled for the current effect.
             */
            virtual const System::Boolean& IsLightingEnabled() override;

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
            const SceneR::Framework::Color& SpecularColor() const;

            /**
             * Gets the specular color for a material,
             * the range of color values is from 0 to 1.
             */
            void SpecularColor(const SceneR::Framework::Color& specularColor);

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
            std::shared_ptr<Texture2D> Texture() const;

            /**
             * Sets a texture to be applied by this effect.
             */
            void Texture(std::shared_ptr<Texture2D> texture);

            /**
             * Enables textures for this effect.
             */
            void EnableTexture();

            /**
             * Enables textures for this effect.
             */
            void DisableTexture();

            /**
             * Gets a value indicating wheter textures are enabled for this effect
             */
            const System::Boolean& IsTextureEnabled() const;

            /**
             * Gets the view matrix in the current effect.
             */
            virtual const SceneR::Framework::Matrix& View() const override;

            /**
             * Sets the view matrix in the current effect.
             */
            virtual void View(const SceneR::Framework::Matrix& view) override;

            /**
             * Enables use vertex colors for this effect.
             */
            void EnableVertexColor();

            /**
             * Disables use vertex colors for this effect.
             */
            void DisableVertexColor();

            /**
             * Gets a value indicating wheter vertex colors are enabled for this effect
             */
            const System::Boolean& IsVertexColorEnabled() const;

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
             * Enables default lighting for this effect.
             */
            virtual void EnableDefaultLighting() override;

        protected:
            /**
             * Computes derived parameter values immediately before applying the effect.
             */
            virtual void OnApply() override;

        private:
            void LoadShader();

        private:
            System::Single                      alpha;
            AmbientLight                        ambientLight;
            SceneR::Framework::Color            diffuseColor;
            std::vector<std::shared_ptr<Light>> lights;
            System::Boolean                     lightingEnabled;
            SceneR::Framework::Color            emissiveColor;
            System::Boolean                     fogEnabled;
            SceneR::Framework::Color            fogColor;
            System::Single                      fogEnd;
            System::Single                      fogStart;
            System::Boolean                     preferPerPixelLighting;
            SceneR::Framework::Matrix           projection;
            SceneR::Framework::Color            specularColor;
            System::Single                      specularPower;
            System::Boolean                     textureEnabled;
            std::shared_ptr<Texture2D>          texture;
            System::Boolean                     vertexColorEnabled;
            SceneR::Framework::Matrix           view;
            SceneR::Framework::Matrix           world;
        };
    }
}

#endif  /* BASICEFFECT_HPP */
