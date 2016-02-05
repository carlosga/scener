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
#include "SceneR/Math/Matrix.hpp"
#include "SceneR/Math/Quaternion.hpp"
#include "SceneR/Math/Vector2.hpp"
#include "SceneR/Math/Vector3.hpp"
#include "SceneR/Math/Vector4.hpp"

namespace SceneR { namespace Content { namespace Readers { template <typename T> class ContentTypeReader; } } }

namespace SceneR { namespace Graphics {

class GrapicsDevice;
class EffectPass;
class EffectParameter;
class Texture2D;

/// Used to set and query effects, and to choose techniques.
class EffectTechnique final : public GraphicsResource, public IEffectMatrices, public IEffectLights
{
public:
    /// Initializes a new instance of the EffectTechnique class
    /// @param graphicsDevice the graphics device
    EffectTechnique(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept;

public:
    /// Gets the material alpha which determines its transparency.
    /// Range is between 1 (fully opaque) and 0 (fully transparent).
    float alpha() const noexcept;

    /// Sets the material alpha which determines its transparency.
    /// Range is between 1 (fully opaque) and 0 (fully transparent).
    void alpha(float alpha) noexcept;

    /// Gets the ambient light for the current effect
    const SceneR::Math::Vector3& ambient_light_color() const noexcept override;

    /// Gets the ambient light for the current effect
    void ambient_light_color(const SceneR::Math::Vector3& ambientLightColor) noexcept override;

    /// Gets the ambient color for a light, the range of color values is from 0 to 1.
    const SceneR::Math::Vector3& diffuse_color() const noexcept;

    /// Gets the ambient color for a light, the range of color values is from 0 to 1.
    void diffuse_color(const SceneR::Math::Vector3& diffuseColor) noexcept;

    /// Gets the first directional light
    const DirectionalLight& directional_light_0() const noexcept override;

    /// Gets the second directional light
    const DirectionalLight& directional_light_1() const noexcept override;

    /// Gets the third directional light
    const DirectionalLight& directional_light_2() const noexcept override;

    /// Enables default lighting for this effect.
    void enable_default_lighting() noexcept override;

    /// Gets the emissive color for a material, the range of color values is from 0 to 1.
    const SceneR::Math::Vector3& emissive_color() const noexcept;

    /// Sets the emissive color for a material, the range of color values is from 0 to 1.
    void emissive_color(const SceneR::Math::Vector3& emissiveColor) noexcept;

    /// Gets a value indicating wheter lighting is enabled for the current effect.
    bool lighting_enabled() const noexcept override;

    /// Sets a value indicating wheter lighting is enabled for the current effect.
    void lighting_enabled(bool lightingEnabled) noexcept override;

    /// Gets a value indicating that per-pixel lighting should be used if it is available for the current adapter.
    bool prefer_per_pixel_lighting() const noexcept;

    /// Gets a value indicating that per-pixel lighting should be used if it is available for the current adapter.
    void prefer_per_pixel_lighting(bool preferPerPixelLighting) noexcept;

    /// Gets the projection matrix in the current effect.
    const SceneR::Math::Matrix& projection() const noexcept override;

    /// Sets the projection matrix in the current effect.
    void projection(const SceneR::Math::Matrix& projection) noexcept override;

    /// Gets the specular color for a material, the range of color values is from 0 to 1.
    const SceneR::Math::Vector3& specular_color() const noexcept;

    /// Gets the specular color for a material, the range of color values is from 0 to 1.
    void specular_color(const SceneR::Math::Vector3& specularColor) noexcept;

    /// Gets specular power of this effect material.
    float specular_power() const noexcept;

    /// Sets specular power of this effect material.
    void specular_power(float specularPower) noexcept;

    /// Gets the textures to be applied by this effect.
    std::vector<std::shared_ptr<Texture2D>>& textures() noexcept;

    /// Gets a value indicating wheter textures are enabled for this effect.
    bool texture_enabled() const noexcept;

    /// Sets a value indicating wheter textures are enabled for this effect.
    void texture_enabled(bool textureEnabled) noexcept;

    /// Gets the view matrix in the current effect.
    const SceneR::Math::Matrix& view() const noexcept override;

    /// Sets the view matrix in the current effect.
    void view(const SceneR::Math::Matrix& view) noexcept override;

    /// Gets the world matrix in the current effect.
    const SceneR::Math::Matrix& world() const noexcept override;

    /// Sets the world matrix in the current effect.
    void world(const SceneR::Math::Matrix& world) noexcept override;

public:
    /// Gets the array of bone transform matrices of this SkinnedEffect.
    std::vector<SceneR::Math::Matrix> bone_transforms(std::size_t count) const noexcept;

    /// Sets an array of bone transform matrices for a SkinnedEffect.
    void bone_transforms(const std::vector<SceneR::Math::Matrix>& boneTransforms) noexcept;

public:
    /// Starts the application of the effect state just prior to rendering the effect.
    void begin() noexcept;

    /// Ends the application of the effect state just after rendering the effect.
    void end() noexcept;

private:
    void set_world_view_proj() const noexcept;

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

    template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_EFFECTTECHNIQUE_HPP
