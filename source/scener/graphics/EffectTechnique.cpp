// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/EffectTechnique.hpp"

#include "scener/graphics/EffectParameter.hpp"
#include "scener/graphics/EffectPass.hpp"
#include "scener/graphics/GraphicsDevice.hpp"
#include "scener/graphics/Texture2D.hpp"

namespace scener { namespace graphics {

using scener::math::matrix4;
using scener::math::vector3;

EffectTechnique::EffectTechnique(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept
    : GraphicsResource           { graphicsDevice }
    , _alpha                     { 1.0 }
    , _ambient_light_color       { vector3::zero() }
    , _bone_transforms           ( 0 )
    , _diffuse_color             { vector3::one() }
    , _light_0                   { }
    , _light_1                   { }
    , _light_2                   { }
    , _lighting_enabled          { true }
    , _emissive_color            { vector3::zero() }
    , _prefer_per_pixel_lighting { false }
    , _projection                { matrix4::identity() }
    , _specular_color            { vector3::one() }
    , _specular_power            { 16.0f }
    , _texture_enabled           { false }
    , _textures                  ( 0 )
    , _view                      { matrix4::identity() }
    , _world                     { matrix4::identity() }
    , _dirty_flags               { EffectDirtyFlags::all }
    , _passes                    ()
    , _parameters                ()
{
}

float EffectTechnique::alpha() const noexcept
{
    return _alpha;
}

void EffectTechnique::alpha(float alpha) noexcept
{
    if (math::equal(_alpha, alpha))
    {
        _alpha        = alpha;
        _dirty_flags |= EffectDirtyFlags::material_color;
    }
}

const vector3& EffectTechnique::ambient_light_color() const noexcept
{
    return _ambient_light_color;
}

void EffectTechnique::ambient_light_color(const vector3& ambientLightColor) noexcept
{
    if (_ambient_light_color != ambientLightColor)
    {
        _ambient_light_color = ambientLightColor;
        _dirty_flags        |= EffectDirtyFlags::material_color;
    }
}

const vector3& EffectTechnique::diffuse_color() const noexcept
{
    return _diffuse_color;
}

void EffectTechnique::diffuse_color(const vector3& diffuseColor) noexcept
{
    if (_diffuse_color != diffuseColor)
    {
        _diffuse_color = diffuseColor;
        _dirty_flags  |= EffectDirtyFlags::material_color;
    }
}

const DirectionalLight& EffectTechnique::directional_light_0() const noexcept
{
    return _light_0;
}

const DirectionalLight& EffectTechnique::directional_light_1() const noexcept
{
    return _light_1;
}

const DirectionalLight& EffectTechnique::directional_light_2() const noexcept
{
    return _light_2;
}

void EffectTechnique::enable_default_lighting() noexcept
{
    //ambient_light_color(EffectHelpers::enable_default_lighting(_light_0, _light_1, _light_2));
}

const vector3& EffectTechnique::emissive_color() const noexcept
{
    return _emissive_color;
}

void EffectTechnique::emissive_color(const vector3& emissiveColor) noexcept
{
    if (_emissive_color != emissiveColor)
    {
        _emissive_color = emissiveColor;
        _dirty_flags   |= EffectDirtyFlags::material_color;
    }
}

bool EffectTechnique::lighting_enabled() const noexcept
{
    return _lighting_enabled;
}

void EffectTechnique::lighting_enabled(bool lightingEnabled) noexcept
{
    _lighting_enabled = lightingEnabled;
}

bool EffectTechnique::prefer_per_pixel_lighting() const noexcept
{
    return _prefer_per_pixel_lighting;
}

void EffectTechnique::prefer_per_pixel_lighting(bool preferPerPixelLighting) noexcept
{
    if (_prefer_per_pixel_lighting != preferPerPixelLighting)
    {
        _prefer_per_pixel_lighting = preferPerPixelLighting;
        _dirty_flags              |= EffectDirtyFlags::shader_index;
    }
}

const matrix4& EffectTechnique::projection() const noexcept
{
    return _projection;
}

void EffectTechnique::projection(const matrix4& projection) noexcept
{
    if (_projection != projection)
    {
        _projection   = projection;
        _dirty_flags |= EffectDirtyFlags::world_view_proj;
    }
}

const vector3& EffectTechnique::specular_color() const noexcept
{
    return _specular_color;
}

void EffectTechnique::specular_color(const vector3& specularColor) noexcept
{
//            if (_specularColor != specularColor)
//            {
//                _specularColor = specularColor;
//
//                _specularColorParam.SetValue(_specularColor);
//            }
}

float EffectTechnique::specular_power() const noexcept
{
    return _specular_power;
}

void EffectTechnique::specular_power(float specularPower) noexcept
{
//            if (!Math::equal(_specularPower, specularPower))
//            {
//                _specularPower = specularPower;
//
//                _specularPowerParam.SetValue(_specularPower);
//            }
}

std::vector<std::shared_ptr<Texture2D>>& EffectTechnique::textures() noexcept
{
    return _textures;
}

bool EffectTechnique::texture_enabled() const noexcept
{
    return _texture_enabled;
}

void EffectTechnique::texture_enabled(bool textureEnabled) noexcept
{
    if (_texture_enabled != textureEnabled)
    {
        _texture_enabled = textureEnabled;
        _dirty_flags    |= EffectDirtyFlags::shader_index;
    }
}

const matrix4& EffectTechnique::view() const noexcept
{
    return _view;
}

void EffectTechnique::view(const matrix4& view) noexcept
{
    if (view != _view)
    {
        _view         = view;
        _dirty_flags |= EffectDirtyFlags::world_view_proj | EffectDirtyFlags::eye_position | EffectDirtyFlags::fog;
    }
}

const matrix4& EffectTechnique::world() const noexcept
{
    return _world;
}

void EffectTechnique::world(const matrix4& world) noexcept
{
    if (_world != world)
    {
        _world        = world;
        _dirty_flags |= EffectDirtyFlags::world | EffectDirtyFlags::world_view_proj | EffectDirtyFlags::fog;
    }
}

std::vector<matrix4> EffectTechnique::bone_transforms(std::size_t count) const noexcept
{
    Expects(count >= _bone_transforms.size());

    std::vector<matrix4> transforms;

    transforms.reserve(count);
    transforms.assign(_bone_transforms.begin(), _bone_transforms.begin() + count);

    return transforms;
}

void EffectTechnique::bone_transforms(const std::vector<matrix4>& boneTransforms) noexcept
{
    _bone_transforms.clear();
    _bone_transforms.reserve(boneTransforms.size());
    _bone_transforms.assign(boneTransforms.begin(), boneTransforms.end());

    _bones_param->set_value(_bone_transforms);
}

void EffectTechnique::begin() noexcept
{
    if (_pass != nullptr)
    {
        _pass->begin();
    }
    else
    {
        for (const auto& pass : _passes)
        {
            pass->begin();
        }
    }

    if ((_dirty_flags & EffectDirtyFlags::world_view_proj) != 0 || (_dirty_flags & EffectDirtyFlags::world) != 0)
    {
        set_world_view_proj();

        _dirty_flags &= ~EffectDirtyFlags::world_view_proj;
        _dirty_flags &= ~EffectDirtyFlags::world;
    }

    if (_texture_enabled)
    {
        for (const auto& texture : _textures)
        {
            texture->bind();
        }
    }
}

void EffectTechnique::end() noexcept
{
    if (_texture_enabled)
    {
        for (const auto& texture : _textures)
        {
            texture->unbind();
        }
    }

    if (_pass != nullptr)
    {
        _pass->end();
    }
    else
    {
        for (const auto& pass : _passes)
        {
            pass->end();
        }
    }
}

void EffectTechnique::set_world_view_proj() const noexcept
{
    auto worldView     = _world * _view;
    auto worldViewProj = worldView * _projection;

    if (_world_param.get())
    {
        _world_param->set_value(_world);
    }
    if (_view_param.get())
    {
        _view_param->set_value(_view);
    }
    if (_projection_param.get())
    {
        _projection_param->set_value(_projection);
    }
    if (_world_view_param.get())
    {
        _world_view_param->set_value(worldView);
    }
    if (_world_view_projection_param.get())
    {
        _world_view_projection_param->set_value(worldViewProj);
    }
    if (_world_inverse_param.get())
    {
        _world_inverse_param->set_value(scener::math::matrix::invert(_world));
    }
    if (_view_inverse_param.get())
    {
        _view_inverse_param->set_value(scener::math::matrix::invert(_view));
    }
    if (_projection_inverse_param.get())
    {
        _projection_inverse_param->set_value(scener::math::matrix::invert(_projection));
    }
    if (_world_view_inverse_param.get())
    {
        _world_view_inverse_param->set_value(scener::math::matrix::invert(worldView));
    }
    if (_world_view_projection_inverse_param.get())
    {
        _world_view_projection_inverse_param->set_value(scener::math::matrix::invert(worldViewProj));
    }
    if (_world_inverse_transpose_param.get())
    {
        _world_inverse_transpose_param->set_value(scener::math::matrix::transpose(scener::math::matrix::invert(_world)));
    }
    if (_world_view_inverse_transpose_param.get())
    {
        _world_view_inverse_transpose_param->set_value(scener::math::matrix::transpose(scener::math::matrix::invert(worldView)));
    }
}

}}
