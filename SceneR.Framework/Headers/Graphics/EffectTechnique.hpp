// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_EFFECTTECHNIQUE_HPP
#define GRAPHICS_EFFECTTECHNIQUE_HPP

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/DirectionalLight.hpp>
#include <Graphics/EffectDirtyFlags.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <Graphics/IEffectMatrices.hpp>
#include <Graphics/IEffectLights.hpp>
#include <Graphics/IEffectFog.hpp>
#include <Graphics/Texture2D.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
        class GrapicsDevice;
        class EffectPass;
        class EffectParameter;

        /**
         * Used to set and query effects, and to choose techniques.
         */
        class EffectTechnique : public GraphicsResource, public IEffectMatrices, public IEffectLights, public IEffectFog
        {
        public:
            /**
             * Initializes a new instance of the EffectTechnique class
             *
             * @param graphicsDevice the graphics device
             */
            EffectTechnique(GraphicsDevice* graphicsDevice);

            /**
             * Initializes a new instance of the EffectTechnique class.
             *
             * @param effect the effect to be copied
             */
            EffectTechnique(const EffectTechnique& effect);

            /**
             * Destructor
             */
            ~EffectTechnique();

        public:
            void dispose() override;

        public:
            /**
             * Gets the material alpha which determines its transparency.
             * Range is between 1 (fully opaque) and 0 (fully transparent).
             */
            float alpha() const;

            /**
             * Sets the material alpha which determines its transparency.
             * Range is between 1 (fully opaque) and 0 (fully transparent).
             */
            void alpha(const float& alpha);

            /**
             * Gets the ambient light for the current effect
             */
            const SceneR::Framework::Vector3& ambient_light_color() const override;

            /**
             * Gets the ambient light for the current effect
             */
            void ambient_light_color(const SceneR::Framework::Vector3& ambientLightColor) override;

            /**
             * Gets the ambient color for a light, the range of color values is from 0 to 1.
             */
            const SceneR::Framework::Vector3& diffuse_color() const;

            /**
             * Gets the ambient color for a light, the range of color values is from 0 to 1.
             */
            void diffuse_color(const SceneR::Framework::Vector3& diffuseColor);

            /**
             * Gets the first directional light
             */
            const DirectionalLight& directional_light_0() const override;

            /**
             * Gets the second directional light
             */
            const DirectionalLight& directional_light_1() const override;

            /**
             * Gets the third directional light
             */
            const DirectionalLight& directional_light_2() const override;

            /**
             * Enables default lighting for this effect.
             */
            void enable_default_lighting() override;

            /**
             * Gets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            const SceneR::Framework::Vector3& emissive_color() const;

            /**
             * Sets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            void emissive_color(const SceneR::Framework::Vector3& emissiveColor);

            /**
             * Gets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            const SceneR::Framework::Vector3& fog_color() const override;

            /**
             * Sets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            void fog_color(const SceneR::Framework::Vector3& fogColor) override;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            bool fog_enabled() const override;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            void fog_enabled(const bool& fogEnabled) override;

            /**
             * Gets maximum z value for fog, which ranges from 0 to 1.
             */
            float fog_end() const override;

            /**
             * Sets maximum z value for fog, which ranges from 0 to 1.
             */
            void fog_end(const float& fogEnd) override;

            /**
             * Gets minimum z value for fog, which ranges from 0 to 1.
             */
            float fog_start() const override;

            /**
             * Sets minimum z value for fog, which ranges from 0 to 1.
             */
            void fog_start(const float& fogStart) override;

            /**
             * Gets a value indicating wheter lighting is enabled for the current effect.
             */
            bool lighting_enabled() const override;

            /**
             * Sets a value indicating wheter lighting is enabled for the current effect.
             */
            void lighting_enabled(const bool& lightingEnabled) override;

            /**
             * Gets a value indicating that per-pixel lighting should be used if it is
             * available for the current adapter.
             */
            bool prefer_per_pixel_lighting() const;

            /**
             * Gets a value indicating that per-pixel lighting should be used if it is
             * available for the current adapter.
             */
            void prefer_per_pixel_lighting(const bool& preferPerPixelLighting);

            /**
             * Gets the projection matrix in the current effect.
             */
            const SceneR::Framework::Matrix& projection() const override;

            /**
             * Sets the projection matrix in the current effect.
             */
            void projection(const SceneR::Framework::Matrix& projection) override;

            /**
             * Gets the specular color for a material,
             * the range of color values is from 0 to 1.
             */
            const SceneR::Framework::Vector3& specular_color() const;

            /**
             * Gets the specular color for a material,
             * the range of color values is from 0 to 1.
             */
            void specular_color(const SceneR::Framework::Vector3& specularColor);

            /**
             * Gets specular power of this effect material.
             */
            float specular_power() const;

            /**
             * Sets specular power of this effect material.
             */
            void specular_power(const float& specularPower);

            /**
             * Gets the textures to be applied by this effect.
             */
            std::vector<std::shared_ptr<Texture2D>>& textures();

            /**
             * Gets a value indicating wheter textures are enabled for this effect
             */
            bool texture_enabled() const;

            /**
             * Sets a value indicating wheter textures are enabled for this effect
             */
            void texture_enabled(const bool& textureEnabled);

            /**
             * Gets the view matrix in the current effect.
             */
            const SceneR::Framework::Matrix& view() const override;

            /**
             * Sets the view matrix in the current effect.
             */
            void view(const SceneR::Framework::Matrix& view) override;

            /**
             * Gets the world matrix in the current effect.
             */
            const SceneR::Framework::Matrix& world() const override;

            /**
             * Sets the world matrix in the current effect.
             */
            void world(const SceneR::Framework::Matrix& world) override;

        public:
            /**
             * Gets the array of bone transform matrices of this SkinnedEffect.
             */
            std::vector<SceneR::Framework::Matrix> bone_transforms(const std::size_t& count) const;

            /**
             * Sets an array of bone transform matrices for a SkinnedEffect.
             */
            void bone_transforms(const std::vector<SceneR::Framework::Matrix>& boneTransforms);

            /**
             * Gets the number of per-vertex skinning weights to evaluate, which is either 1, 2, or 4.
             */
            std::size_t weights_per_vertex() const;

            /**
             * Sets the number of per-vertex skinning weights to evaluate, which is either 1, 2, or 4.
             */
            void weights_per_vertex(const std::size_t& weightsPerVertex);

        public:
            /**
             * Starts the application of the effect state just prior to rendering the effect.
             */
            void begin();

            /**
             * Ends the application of the effect state just after rendering the effect.
             */
            void end();

        private:
            float                                   _alpha;
            SceneR::Framework::Vector3              _ambient_light_color;
            std::vector<SceneR::Framework::Matrix>  _bone_transforms;
            SceneR::Framework::Vector3              _diffuse_color;
            DirectionalLight                        _light_0;
            DirectionalLight                        _light_1;
            DirectionalLight                        _light_2;
            bool                                    _lighting_enabled;
            SceneR::Framework::Vector3              _emissive_color;
            bool                                    _fog_enabled;
            SceneR::Framework::Vector3              _fog_color;
            float                                   _fog_end;
            float                                   _fog_start;
            bool                                    _prefer_per_pixel_lighting;
            SceneR::Framework::Matrix               _projection;
            SceneR::Framework::Vector3              _specular_color;
            float                                   _specular_power;
            bool                                    _texture_enabled;
            std::vector<std::shared_ptr<Texture2D>> _textures;
            SceneR::Framework::Matrix               _view;
            std::size_t                             _weights_per_vertex;
            SceneR::Framework::Matrix               _world;
            SceneR::Framework::Matrix               _world_view;
            bool                                    _one_light;

            EffectDirtyFlags                        _dirty_flags;

        private:
            std::map<std::string, std::shared_ptr<EffectPass>>      _passes;
            std::map<std::string, std::shared_ptr<EffectParameter>> _parameters;

            std::shared_ptr<EffectPass>      _pass                          = nullptr;
            std::shared_ptr<EffectParameter> _world_param                   = nullptr;
            std::shared_ptr<EffectParameter> _world_view_proj_param         = nullptr;
            std::shared_ptr<EffectParameter> _world_inverse_transpose_param = nullptr;
            std::shared_ptr<EffectParameter> _bones_param                   = nullptr;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_EFFECTTECHNIQUE_HPP
