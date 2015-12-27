// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECTTECHNIQUE_HPP
#define SCENER_GRAPHICS_EFFECTTECHNIQUE_HPP

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "SceneR/Graphics/DirectionalLight.hpp"
#include "SceneR/Graphics/EffectDirtyFlags.hpp"
#include "SceneR/Graphics/GraphicsResource.hpp"
#include "SceneR/Graphics/IEffectMatrices.hpp"
#include "SceneR/Graphics/IEffectLights.hpp"
#include "SceneR/Graphics/Texture2D.hpp"
#include "SceneR/Math/Matrix.hpp"
#include "SceneR/Math/Quaternion.hpp"
#include "SceneR/Math/Vector2.hpp"
#include "SceneR/Math/Vector3.hpp"
#include "SceneR/Math/Vector4.hpp"

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
        class EffectTechnique : public GraphicsResource, public IEffectMatrices, public IEffectLights
        {
        public:
            /**
             * Initializes a new instance of the EffectTechnique class
             * @param graphicsDevice the graphics device
             */
            EffectTechnique(gsl::not_null<GraphicsDevice*> graphicsDevice);

            /**
             * Initializes a new instance of the EffectTechnique class.
             * @param effect the effect to be copied
             */
            EffectTechnique(const EffectTechnique& effect) = default;

            /**
             * Destructor
             */
            virtual ~EffectTechnique() override = default;

        public:
            virtual void dispose() override;

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
            const SceneR::Math::Vector3& ambient_light_color() const override;

            /**
             * Gets the ambient light for the current effect
             */
            void ambient_light_color(const SceneR::Math::Vector3& ambientLightColor) override;

            /**
             * Gets the ambient color for a light, the range of color values is from 0 to 1.
             */
            const SceneR::Math::Vector3& diffuse_color() const;

            /**
             * Gets the ambient color for a light, the range of color values is from 0 to 1.
             */
            void diffuse_color(const SceneR::Math::Vector3& diffuseColor);

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
            const SceneR::Math::Vector3& emissive_color() const;

            /**
             * Sets the emissive color for a material,
             * the range of color values is from 0 to 1.
             */
            void emissive_color(const SceneR::Math::Vector3& emissiveColor);

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
            const SceneR::Math::Matrix& projection() const override;

            /**
             * Sets the projection matrix in the current effect.
             */
            void projection(const SceneR::Math::Matrix& projection) override;

            /**
             * Gets the specular color for a material,
             * the range of color values is from 0 to 1.
             */
            const SceneR::Math::Vector3& specular_color() const;

            /**
             * Gets the specular color for a material,
             * the range of color values is from 0 to 1.
             */
            void specular_color(const SceneR::Math::Vector3& specularColor);

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
            const SceneR::Math::Matrix& view() const override;

            /**
             * Sets the view matrix in the current effect.
             */
            void view(const SceneR::Math::Matrix& view) override;

            /**
             * Gets the world matrix in the current effect.
             */
            const SceneR::Math::Matrix& world() const override;

            /**
             * Sets the world matrix in the current effect.
             */
            void world(const SceneR::Math::Matrix& world) override;

        public:
            /**
             * Gets the array of bone transform matrices of this SkinnedEffect.
             */
            std::vector<SceneR::Math::Matrix> bone_transforms(const std::size_t& count) const;

            /**
             * Sets an array of bone transform matrices for a SkinnedEffect.
             */
            void bone_transforms(const std::vector<SceneR::Math::Matrix>& boneTransforms);

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
            void set_world_view_proj() const;

        private:
            float                                   _alpha;
            SceneR::Math::Vector3                   _ambient_light_color;
            std::vector<SceneR::Math::Matrix>       _bone_transforms;
            SceneR::Math::Vector3                   _diffuse_color;
            DirectionalLight                        _light_0;
            DirectionalLight                        _light_1;
            DirectionalLight                        _light_2;
            bool                                    _lighting_enabled;
            SceneR::Math::Vector3                   _emissive_color;
            bool                                    _prefer_per_pixel_lighting;
            SceneR::Math::Matrix                    _projection;
            SceneR::Math::Vector3                   _specular_color;
            float                                   _specular_power;
            bool                                    _texture_enabled;
            std::vector<std::shared_ptr<Texture2D>> _textures;
            SceneR::Math::Matrix                    _view;
            SceneR::Math::Matrix                    _world;

            EffectDirtyFlags                        _dirty_flags;

        private:
            std::vector<std::shared_ptr<EffectPass>>                _passes;
            std::map<std::string, std::shared_ptr<EffectParameter>> _parameters;

            std::shared_ptr<EffectPass>      _pass                          = nullptr;
            std::shared_ptr<EffectParameter> _bones_param                   = nullptr;

            /// Transforms from model to world coordinates using the transform's node and all of its parents.
            std::shared_ptr<EffectParameter> _world_param                   = nullptr;
            /// Transforms from world to view coordinates using the active camera node.
            std::shared_ptr<EffectParameter> _view_param                    = nullptr;
            /// Transforms from view to clip coordinates using the active camera node.
            std::shared_ptr<EffectParameter> _projection_param              = nullptr;
            /// Combined WORLD and VIEW.
            std::shared_ptr<EffectParameter> _world_view_param              = nullptr;
            /// Combined WORLD, VIEW, and PROJECTION.
            std::shared_ptr<EffectParameter> _world_view_projection_param   = nullptr;
            /// Inverse of WORLD.
            std::shared_ptr<EffectParameter> _world_inverse_param           = nullptr;
            /// Inverse of VIEW.
            std::shared_ptr<EffectParameter> _view_inverse_param            = nullptr;
            /// Inverse of PROJECTION.
            std::shared_ptr<EffectParameter> _projection_inverse_param      = nullptr;
            /// Inverse of WORLDVIEW.
            std::shared_ptr<EffectParameter> _world_view_inverse_param      = nullptr;
            /// Inverse of MODELVIEWPROJECTION
            std::shared_ptr<EffectParameter> _world_view_projection_inverse_param = nullptr;
            /// The inverse-transpose of MODEL without the translation. This translates normals in model coordinates to world coordinates.
            std::shared_ptr<EffectParameter> _world_inverse_transpose_param = nullptr;
            /// The inverse-transpose of MODELVIEW without the translation. This translates normals in model coordinates to eye coordinates.
            std::shared_ptr<EffectParameter> _world_view_inverse_transpose_param = nullptr;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif // SCENER_GRAPHICS_EFFECTTECHNIQUE_HPP
