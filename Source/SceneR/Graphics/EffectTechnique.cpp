// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/EffectTechnique.hpp"

#include "SceneR/Graphics/EffectDirtyFlags.hpp"
#include "SceneR/Graphics/EffectParameter.hpp"
#include "SceneR/Graphics/EffectPass.hpp"
#include "SceneR/Graphics/GraphicsDevice.hpp"
#include "SceneR/Graphics/Texture2D.hpp"
#include "SceneR/Math/Math.hpp"

namespace SceneR { namespace Graphics {

using SceneR::Math::Matrix;
using SceneR::Math::Vector3;

EffectTechnique::EffectTechnique(gsl::not_null<GraphicsDevice*> graphicsDevice)
    : GraphicsResource           { graphicsDevice }
    , _alpha                     { 1.0 }
    , _ambient_light_color       { Vector3::zero }
    , _bone_transforms           ( 0 )
    , _diffuse_color             { Vector3::one }
    , _light_0                   { }
    , _light_1                   { }
    , _light_2                   { }
    , _lighting_enabled          { true }
    , _emissive_color            { Vector3::zero }
    , _prefer_per_pixel_lighting { false }
    , _projection                { Matrix::identity }
    , _specular_color            { Vector3::one }
    , _specular_power            { 16.0f }
    , _texture_enabled           { false }
    , _textures                  ( 0 )
    , _view                      { Matrix::identity }
    , _world                     { Matrix::identity }
    , _dirty_flags               { EffectDirtyFlags::All }
    , _passes                    ()
    , _parameters                ()
{
}

void EffectTechnique::dispose()
{
}

float EffectTechnique::alpha() const
{
    return _alpha;
}

void EffectTechnique::alpha(const float& alpha)
{
    if (Math::equal(_alpha, alpha))
    {
        _alpha        = alpha;
        _dirty_flags |= EffectDirtyFlags::MaterialColor;
    }
}

const Vector3& EffectTechnique::ambient_light_color() const
{
    return _ambient_light_color;
}

void EffectTechnique::ambient_light_color(const Vector3& ambientLightColor)
{
    if (_ambient_light_color != ambientLightColor)
    {
        _ambient_light_color = ambientLightColor;
        _dirty_flags        |= EffectDirtyFlags::MaterialColor;
    }
}

const Vector3& EffectTechnique::diffuse_color() const
{
    return _diffuse_color;
}

void EffectTechnique::diffuse_color(const Vector3& diffuseColor)
{
    if (_diffuse_color != diffuseColor)
    {
        _diffuse_color = diffuseColor;
        _dirty_flags  |= EffectDirtyFlags::MaterialColor;
    }
}

const DirectionalLight& EffectTechnique::directional_light_0() const
{
    return _light_0;
}

const DirectionalLight& EffectTechnique::directional_light_1() const
{
    return _light_1;
}

const DirectionalLight& EffectTechnique::directional_light_2() const
{
    return _light_2;
}

void EffectTechnique::enable_default_lighting()
{
    //ambient_light_color(EffectHelpers::enable_default_lighting(_light_0, _light_1, _light_2));
}

const Vector3& EffectTechnique::emissive_color() const
{
    return _emissive_color;
}

void EffectTechnique::emissive_color(const Vector3& emissiveColor)
{
    if (_emissive_color != emissiveColor)
    {
        _emissive_color = emissiveColor;
        _dirty_flags   |= EffectDirtyFlags::MaterialColor;
    }
}

bool EffectTechnique::lighting_enabled() const
{
    return _lighting_enabled;
}

void EffectTechnique::lighting_enabled(const bool& lightingEnabled)
{
    _lighting_enabled = lightingEnabled;
}

bool EffectTechnique::prefer_per_pixel_lighting() const
{
    return _prefer_per_pixel_lighting;
}

void EffectTechnique::prefer_per_pixel_lighting(const bool& preferPerPixelLighting)
{
    if (_prefer_per_pixel_lighting != preferPerPixelLighting)
    {
        _prefer_per_pixel_lighting = preferPerPixelLighting;
        _dirty_flags              |= EffectDirtyFlags::ShaderIndex;
    }
}

const Matrix& EffectTechnique::projection() const
{
    return _projection;
}

void EffectTechnique::projection(const Matrix& projection)
{
    if (_projection != projection)
    {
        _projection   = projection;
        _dirty_flags |= EffectDirtyFlags::WorldViewProj;
    }
}

const Vector3& EffectTechnique::specular_color() const
{
    return _specular_color;
}

void EffectTechnique::specular_color(const Vector3& specularColor)
{
//            if (_specularColor != specularColor)
//            {
//                _specularColor = specularColor;
//
//                _specularColorParam.SetValue(_specularColor);
//            }
}

float EffectTechnique::specular_power() const
{
    return _specular_power;
}

void EffectTechnique::specular_power(const float& specularPower)
{
//            if (!Math::equal(_specularPower, specularPower))
//            {
//                _specularPower = specularPower;
//
//                _specularPowerParam.SetValue(_specularPower);
//            }
}

std::vector<std::shared_ptr<Texture2D>>& EffectTechnique::textures()
{
    return _textures;
}

bool EffectTechnique::texture_enabled() const
{
    return _texture_enabled;
}

void EffectTechnique::texture_enabled(const bool& textureEnabled)
{
    if (_texture_enabled != textureEnabled)
    {
        _texture_enabled = textureEnabled;
        _dirty_flags    |= EffectDirtyFlags::ShaderIndex;
    }
}

const Matrix& EffectTechnique::view() const
{
    return _view;
}

void EffectTechnique::view(const Matrix& view)
{
    if (view != _view)
    {
        _view         = view;
        _dirty_flags |= EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::EyePosition | EffectDirtyFlags::Fog;
    }
}

const Matrix& EffectTechnique::world() const
{
    return _world;
}

void EffectTechnique::world(const Matrix& world)
{
    if (_world != world)
    {
        _world        = world;
        _dirty_flags |= EffectDirtyFlags::World | EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::Fog;
    }
}

std::vector<Matrix> EffectTechnique::bone_transforms(const std::size_t& count) const
{
    Expects(count >= _bone_transforms.size());

    std::vector<Matrix> transforms;

    transforms.reserve(count);
    transforms.assign(_bone_transforms.begin(), _bone_transforms.begin() + count);

    return transforms;
}

void EffectTechnique::bone_transforms(const std::vector<Matrix>& boneTransforms)
{
    _bone_transforms = boneTransforms;
    _bones_param->set_value(_bone_transforms);
}

void EffectTechnique::begin()
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

    if ((_dirty_flags & EffectDirtyFlags::WorldViewProj) != 0 || (_dirty_flags & EffectDirtyFlags::World) != 0)
    {
        set_world_view_proj();

        _dirty_flags &= ~EffectDirtyFlags::WorldViewProj;
        _dirty_flags &= ~EffectDirtyFlags::World;
    }

    if (_texture_enabled)
    {
        for (auto texture : _textures)
        {
            texture->bind();
        }
    }
}

void EffectTechnique::end()
{
    if (_texture_enabled)
    {
        for (auto texture : _textures)
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

void EffectTechnique::set_world_view_proj() const
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
        _world_inverse_param->set_value(Matrix::invert(_world));
    }
    if (_view_inverse_param.get())
    {
        _view_inverse_param->set_value(Matrix::invert(_view));
    }
    if (_projection_inverse_param.get())
    {
        _projection_inverse_param->set_value(Matrix::invert(_projection));
    }
    if (_world_view_inverse_param.get())
    {
        _world_view_inverse_param->set_value(Matrix::invert(worldView));
    }
    if (_world_view_projection_inverse_param.get())
    {
        _world_view_projection_inverse_param->set_value(Matrix::invert(worldViewProj));
    }
    if (_world_inverse_transpose_param.get())
    {
        _world_inverse_transpose_param->set_value(Matrix::transpose(Matrix::invert(_world)));
    }
    if (_world_view_inverse_transpose_param.get())
    {
        _world_view_inverse_transpose_param->set_value(Matrix::transpose(Matrix::invert(worldView)));
    }
}

}}
