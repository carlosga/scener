// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECTTECHNIQUE_HPP
#define SCENER_GRAPHICS_EFFECTTECHNIQUE_HPP

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "scener/graphics/DirectionalLight.hpp"
#include "scener/graphics/EffectDirtyFlags.hpp"
#include "scener/graphics/GraphicsResource.hpp"
#include "scener/graphics/IEffectMatrices.hpp"
#include "scener/graphics/IEffectLights.hpp"
#include "scener/math/matrix.hpp"
#include "scener/math/quaternion.hpp"
#include "scener/math/vector.hpp"

namespace scener { namespace content { namespace readers { template <typename T> class ContentTypeReader; } } }

namespace scener { namespace graphics {

class GrapicsDevice;
class effect_pass;
class effect_parameter;
class texture2d;

/// Used to set and query effects, and to choose techniques.
class effect_technique final : public graphics_resource, public ieffect_matrices, public ieffect_lights
{
public:
    /// Initializes a new instance of the EffectTechnique class
    /// \param device the graphics device associated with this EffectTechnique.
    effect_technique(gsl::not_null<graphics_device*> device) noexcept;

    /// Releases all resources being used by this EffectTechnique.
    ~effect_technique() override = default;

public:
    /// Gets the material alpha which determines its transparency.
    /// Range is between 1 (fully opaque) and 0 (fully transparent).
    float alpha() const noexcept;

    /// Sets the material alpha which determines its transparency.
    /// Range is between 1 (fully opaque) and 0 (fully transparent).
    void alpha(float alpha) noexcept;

    /// Gets the ambient light for the current effect
    const scener::math::vector3& ambient_light_color() const noexcept override;

    /// Gets the ambient light for the current effect
    void ambient_light_color(const scener::math::vector3& ambientLightColor) noexcept override;

    /// Gets the ambient color for a light, the range of color values is from 0 to 1.
    const scener::math::vector3& diffuse_color() const noexcept;

    /// Gets the ambient color for a light, the range of color values is from 0 to 1.
    void diffuse_color(const scener::math::vector3& diffuseColor) noexcept;

    /// Gets the first directional light
    const directional_light& directional_light_0() const noexcept override;

    /// Gets the second directional light
    const directional_light& directional_light_1() const noexcept override;

    /// Gets the third directional light
    const directional_light& directional_light_2() const noexcept override;

    /// Enables default lighting for this effect.
    void enable_default_lighting() noexcept override;

    /// Gets the emissive color for a material, the range of color values is from 0 to 1.
    const scener::math::vector3& emissive_color() const noexcept;

    /// Sets the emissive color for a material, the range of color values is from 0 to 1.
    void emissive_color(const scener::math::vector3& emissiveColor) noexcept;

    /// Gets a value indicating wheter lighting is enabled for the current effect.
    bool lighting_enabled() const noexcept override;

    /// Sets a value indicating wheter lighting is enabled for the current effect.
    void lighting_enabled(bool lightingEnabled) noexcept override;

    /// Gets a value indicating that per-pixel lighting should be used if it is available for the current adapter.
    bool prefer_per_pixel_lighting() const noexcept;

    /// Gets a value indicating that per-pixel lighting should be used if it is available for the current adapter.
    void prefer_per_pixel_lighting(bool preferPerPixelLighting) noexcept;

    /// Gets the projection matrix in the current effect.
    const scener::math::matrix4& projection() const noexcept override;

    /// Sets the projection matrix in the current effect.
    void projection(const scener::math::matrix4& projection) noexcept override;

    /// Gets the specular color for a material, the range of color values is from 0 to 1.
    const scener::math::vector3& specular_color() const noexcept;

    /// Gets the specular color for a material, the range of color values is from 0 to 1.
    void specular_color(const scener::math::vector3& specularColor) noexcept;

    /// Gets specular power of this effect material.
    float specular_power() const noexcept;

    /// Sets specular power of this effect material.
    void specular_power(float specularPower) noexcept;

    /// Gets the textures to be applied by this effect.
    std::vector<std::shared_ptr<texture2d>>& textures() noexcept;

    /// Gets a value indicating wheter textures are enabled for this effect.
    bool texture_enabled() const noexcept;

    /// Sets a value indicating wheter textures are enabled for this effect.
    void texture_enabled(bool textureEnabled) noexcept;

    /// Gets the view matrix in the current effect.
    const scener::math::matrix4& view() const noexcept override;

    /// Sets the view matrix in the current effect.
    void view(const scener::math::matrix4& view) noexcept override;

    /// Gets the world matrix in the current effect.
    const scener::math::matrix4& world() const noexcept override;

    /// Sets the world matrix in the current effect.
    void world(const scener::math::matrix4& world) noexcept override;

public:
    /// Gets the array of bone transform matrices of this SkinnedEffect.
    std::vector<scener::math::matrix4> bone_transforms(std::size_t count) const noexcept;

    /// Sets an array of bone transform matrices for a SkinnedEffect.
    void bone_transforms(const std::vector<scener::math::matrix4>& boneTransforms) noexcept;

public:
    /// Starts the application of the effect state just prior to rendering the effect.
    void begin() noexcept;

    /// Ends the application of the effect state just after rendering the effect.
    void end() noexcept;

private:
    void set_world_view_proj() const noexcept;

private:
    float                                   _alpha;
    scener::math::vector3                   _ambient_light_color;
    std::vector<scener::math::matrix4>       _bone_transforms;
    scener::math::vector3                   _diffuse_color;
    directional_light                        _light_0;
    directional_light                        _light_1;
    directional_light                        _light_2;
    bool                                    _lighting_enabled;
    scener::math::vector3                   _emissive_color;
    bool                                    _prefer_per_pixel_lighting;
    scener::math::matrix4                   _projection;
    scener::math::vector3                   _specular_color;
    float                                   _specular_power;
    bool                                    _texture_enabled;
    std::vector<std::shared_ptr<texture2d>> _textures;
    scener::math::matrix4                   _view;
    scener::math::matrix4                   _world;

    effect_dirty_flags                        _dirty_flags;

private:
    std::vector<std::shared_ptr<effect_pass>>                _passes;
    std::map<std::string, std::shared_ptr<effect_parameter>> _parameters;

    std::shared_ptr<effect_pass>      _pass                          = nullptr;
    std::shared_ptr<effect_parameter> _bones_param                   = nullptr;

    /// Transforms from model to world coordinates using the transform's node and all of its parents.
    std::shared_ptr<effect_parameter> _world_param                   = nullptr;
    /// Transforms from world to view coordinates using the active camera node.
    std::shared_ptr<effect_parameter> _view_param                    = nullptr;
    /// Transforms from view to clip coordinates using the active camera node.
    std::shared_ptr<effect_parameter> _projection_param              = nullptr;
    /// Combined WORLD and VIEW.
    std::shared_ptr<effect_parameter> _world_view_param              = nullptr;
    /// Combined WORLD, VIEW, and PROJECTION.
    std::shared_ptr<effect_parameter> _world_view_projection_param   = nullptr;
    /// Inverse of WORLD.
    std::shared_ptr<effect_parameter> _world_inverse_param           = nullptr;
    /// Inverse of VIEW.
    std::shared_ptr<effect_parameter> _view_inverse_param            = nullptr;
    /// Inverse of PROJECTION.
    std::shared_ptr<effect_parameter> _projection_inverse_param      = nullptr;
    /// Inverse of WORLDVIEW.
    std::shared_ptr<effect_parameter> _world_view_inverse_param      = nullptr;
    /// Inverse of MODELVIEWPROJECTION
    std::shared_ptr<effect_parameter> _world_view_projection_inverse_param = nullptr;
    /// The inverse-transpose of MODEL without the translation. This translates normals in model coordinates to world coordinates.
    std::shared_ptr<effect_parameter> _world_inverse_transpose_param = nullptr;
    /// The inverse-transpose of MODELVIEW without the translation. This translates normals in model coordinates to eye coordinates.
    std::shared_ptr<effect_parameter> _world_view_inverse_transpose_param = nullptr;

    template <typename T> friend class scener::content::readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_EFFECTTECHNIQUE_HPP
