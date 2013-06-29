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

#include <memory>
#include "Core/Color.hpp"
#include "Core/Matrix.hpp"
#include "Graphics/AmbientLight.hpp"
#include "Graphics/Effect.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Graphics/IEffectMatrices.hpp"
#include "Graphics/IEffectLights.hpp"
#include "Graphics/IEffectFog.hpp"
#include "Graphics/Texture2D.hpp"

namespace SceneR
{
    namespace Graphics
    {
        //http://msdn.microsoft.com/en-us/library/bb194916(v=xnagamestudio.40).aspx
        /**
         * Contains a basic rendering effect.
         */
        class BasicEffect : public Effect,
                            public IEffectMatrices,
                            public IEffectLights,
                            public IEffectFog
        {
        public:
            /**
             * Initializes a new instance of the BassicEffect class.
             *
             * @param graphicsDevice the graphics device
             */
            BasicEffect(GraphicsDevice& graphicsDevice);

        public:
            /**
             * Gets the material alpha which determines its transparency.
             * Range is between 1 (fully opaque) and 0 (fully transparent).
             */
            const Single& GetAlpha() const;

            /**
             * Sets the material alpha which determines its transparency.
             * Range is between 1 (fully opaque) and 0 (fully transparent).
             */
            void SetAlpha(const Single& alpha);

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
            const SceneR::Core::Color& GetDiffuseColor() const;

            /**
             * Gets the ambient color for a light, the range of color values is from 0 to 1.
             */
            void SetDiffuseColor(SceneR::Core::Color& diffuseColor);

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
            const SceneR::Core::Color& GetEmissiveColor() const;

            /**
             * Sets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            void SetEmissiveColor(SceneR::Core::Color& emissiveColor);

            /**
             * Gets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            virtual const SceneR::Core::Color& GetFogColor() const override;

            /**
             * Sets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            virtual void SetFogColor(const SceneR::Core::Color& fogColor) override;

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
            virtual const Boolean& IsFogEnabled() const override;

            /**
             * Gets maximum z value for fog, which ranges from 0 to 1.
             */
            virtual const Single& GetFogEnd() const override;

            /**
             * Sets maximum z value for fog, which ranges from 0 to 1.
             */
            virtual void SetFogEnd(const Single& fogEnd) override;

            /**
             * Gets minimum z value for fog, which ranges from 0 to 1.
             */
            virtual const Single& GetFogStart() const override;

            /**
             * Sets minimum z value for fog, which ranges from 0 to 1.
             */
            virtual void SetFogStart(const Single& fogStart) override;

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
            virtual const Boolean& IsLightingEnabled() override;

            /**
             * Gets a value indicating that per-pixel lighting should be used if it is
             * available for the current adapter.
             */
            const Boolean& GetPreferPerPixelLighting() const;

            /**
             * Gets a value indicating that per-pixel lighting should be used if it is
             * available for the current adapter.
             */
            void SetPreferPerPixelLighting(const Boolean& preferPerPixelLighting);

            /**
             * Gets the projection matrix in the current effect.
             */
            virtual const SceneR::Core::Matrix& GetProjection() const override;

            /**
             * Sets the projection matrix in the current effect.
             */
            virtual void SetProjection(const SceneR::Core::Matrix& projection) override;

            /**
             * Gets the specular color for a material,
             * the range of color values is from 0 to 1.
             */
            const SceneR::Core::Color& GetSpecularColor() const;

            /**
             * Gets the specular color for a material,
             * the range of color values is from 0 to 1.
             */
            void SetSpecularColor(const SceneR::Core::Color& specularColor);

            /**
             * Gets specular power of this effect material.
             */
            const Single& GetSpecularPower() const;

            /**
             * Sets specular power of this effect material.
             */
            void SetSpecularPower(const Single& specularPower);

            /**
             * Gets a texture to be applied by this effect.
             */
            std::shared_ptr<Texture2D> GetTexture() const;

            /**
             * Sets a texture to be applied by this effect.
             */
            void SetTexture(std::shared_ptr<Texture2D> texture);

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
            const Boolean& IsTextureEnabled() const;

            /**
             * Gets the view matrix in the current effect.
             */
            virtual const SceneR::Core::Matrix& GetView() const override;

            /**
             * Sets the view matrix in the current effect.
             */
            virtual void SetView(const SceneR::Core::Matrix& view) override;

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
            const Boolean& IsVertexColorEnabled() const;

            /**
             * Gets the world matrix in the current effect.
             */
            virtual const SceneR::Core::Matrix& GetWorld() const override;

            /**
             * Sets the world matrix in the current effect.
             */
            virtual void SetWorld(const SceneR::Core::Matrix& world) override;

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
            Single                              alpha;
            AmbientLight                        ambientLight;
            SceneR::Core::Color                 diffuseColor;
            std::vector<std::shared_ptr<Light>> lights;
            Boolean                             lightingEnabled;
            SceneR::Core::Color                 emissiveColor;
            Boolean                             fogEnabled;
            SceneR::Core::Color                 fogColor;
            Single                              fogEnd;
            Single                              fogStart;
            Boolean                             preferPerPixelLighting;
            SceneR::Core::Matrix                projection;
            SceneR::Core::Color                 specularColor;
            Single                              specularPower;
            Boolean                             textureEnabled;
            std::shared_ptr<Texture2D>          texture;
            Boolean                             vertexColorEnabled;
            SceneR::Core::Matrix                view;
            SceneR::Core::Matrix                world;
        };
    }
}

#endif // BASICEFFECT_HPP
