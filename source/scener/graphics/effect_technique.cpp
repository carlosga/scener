// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/effect_technique.hpp"

#include "scener/graphics/effect_parameter.hpp"
#include "scener/graphics/effect_pass.hpp"
#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/texture2d.hpp"

namespace scener::graphics
{
    using math::matrix4;
    using math::vector3;

    effect_technique::effect_technique(gsl::not_null<graphics_device*> device) noexcept
        : graphics_resource          { device }
        , _alpha                     { 1.0 }
        , _ambient_light_color       { vector3::zero() }
        , _bone_transforms           { }
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
        , _textures                  { }
        , _view                      { matrix4::identity() }
        , _world                     { matrix4::identity() }
        , _dirty_flags               { effect_dirty_flags::all }
        , _passes                    { }
        , _parameters                { }
    {
    }

    float effect_technique::alpha() const noexcept
    {
        return _alpha;
    }

    void effect_technique::alpha(float alpha) noexcept
    {
        if (math::equal(_alpha, alpha))
        {
            _alpha        = alpha;
            _dirty_flags |= effect_dirty_flags::material_color;
        }
    }

    const vector3& effect_technique::ambient_light_color() const noexcept
    {
        return _ambient_light_color;
    }

    void effect_technique::ambient_light_color(const vector3& ambient_light_color) noexcept
    {
        if (_ambient_light_color != ambient_light_color)
        {
            _ambient_light_color = ambient_light_color;
            _dirty_flags        |= effect_dirty_flags::material_color;
        }
    }

    const vector3& effect_technique::diffuse_color() const noexcept
    {
        return _diffuse_color;
    }

    void effect_technique::diffuse_color(const vector3& diffuse_color) noexcept
    {
        if (_diffuse_color != diffuse_color)
        {
            _diffuse_color = diffuse_color;
            _dirty_flags  |= effect_dirty_flags::material_color;
        }
    }

    const directional_light& effect_technique::directional_light_0() const noexcept
    {
        return _light_0;
    }

    const directional_light& effect_technique::directional_light_1() const noexcept
    {
        return _light_1;
    }

    const directional_light& effect_technique::directional_light_2() const noexcept
    {
        return _light_2;
    }

    void effect_technique::enable_default_lighting() noexcept
    {
        //ambient_light_color(EffectHelpers::enable_default_lighting(_light_0, _light_1, _light_2));
    }

    const vector3& effect_technique::emissive_color() const noexcept
    {
        return _emissive_color;
    }

    void effect_technique::emissive_color(const vector3& emissive_color) noexcept
    {
        if (_emissive_color != emissive_color)
        {
            _emissive_color = emissive_color;
            _dirty_flags   |= effect_dirty_flags::material_color;
        }
    }

    bool effect_technique::lighting_enabled() const noexcept
    {
        return _lighting_enabled;
    }

    void effect_technique::lighting_enabled(bool lighting_enabled) noexcept
    {
        _lighting_enabled = lighting_enabled;
    }

    bool effect_technique::prefer_per_pixel_lighting() const noexcept
    {
        return _prefer_per_pixel_lighting;
    }

    void effect_technique::prefer_per_pixel_lighting(bool prefer_per_pixel_lighting) noexcept
    {
        if (_prefer_per_pixel_lighting != prefer_per_pixel_lighting)
        {
            _prefer_per_pixel_lighting = prefer_per_pixel_lighting;
            _dirty_flags              |= effect_dirty_flags::shader_index;
        }
    }

    const matrix4& effect_technique::projection() const noexcept
    {
        return _projection;
    }

    void effect_technique::projection(const matrix4& projection) noexcept
    {
        if (_projection != projection)
        {
            _projection   = projection;
            _dirty_flags |= effect_dirty_flags::world_view_proj;
        }
    }

    const vector3& effect_technique::specular_color() const noexcept
    {
        return _specular_color;
    }

    void effect_technique::specular_color(const vector3& specular_color) noexcept
    {
    //            if (_specularColor != specularColor)
    //            {
    //                _specularColor = specularColor;
    //
    //                _specularColorParam.SetValue(_specularColor);
    //            }
    }

    float effect_technique::specular_power() const noexcept
    {
        return _specular_power;
    }

    void effect_technique::specular_power(float specular_power) noexcept
    {
    //            if (!Math::equal(_specularPower, specularPower))
    //            {
    //                _specularPower = specularPower;
    //
    //                _specularPowerParam.SetValue(_specularPower);
    //            }
    }

    std::vector<std::shared_ptr<texture2d>>& effect_technique::textures() noexcept
    {
        return _textures;
    }

    bool effect_technique::texture_enabled() const noexcept
    {
        return _texture_enabled;
    }

    void effect_technique::texture_enabled(bool textureEnabled) noexcept
    {
        if (_texture_enabled != textureEnabled)
        {
            _texture_enabled = textureEnabled;
            _dirty_flags    |= effect_dirty_flags::shader_index;
        }
    }

    const matrix4& effect_technique::view() const noexcept
    {
        return _view;
    }

    void effect_technique::view(const matrix4& view) noexcept
    {
        if (view != _view)
        {
            _view         = view;
            _dirty_flags |= effect_dirty_flags::world_view_proj | effect_dirty_flags::eye_position | effect_dirty_flags::fog;
        }
    }

    const matrix4& effect_technique::world() const noexcept
    {
        return _world;
    }

    void effect_technique::world(const matrix4& world) noexcept
    {
        if (_world != world)
        {
            _world        = world;
            _dirty_flags |= effect_dirty_flags::world | effect_dirty_flags::world_view_proj | effect_dirty_flags::fog;
        }
    }

    std::vector<matrix4> effect_technique::bone_transforms(std::size_t count) const noexcept
    {
        Expects(count >= _bone_transforms.size());

        std::vector<matrix4> transforms;

        transforms.reserve(count);
        transforms.assign(_bone_transforms.begin(), _bone_transforms.begin() + count);

        return transforms;
    }

    void effect_technique::bone_transforms(const std::vector<matrix4>& boneTransforms) noexcept
    {
        _bone_transforms.clear();
        _bone_transforms.reserve(boneTransforms.size());
        _bone_transforms.assign(boneTransforms.begin(), boneTransforms.end());

        _bones_param->set_value(_bone_transforms);
    }

    const std::vector<std::shared_ptr<effect_pass>>& effect_technique::passes() const noexcept
    {
        return _passes;
    }

    void effect_technique::begin() noexcept
    {
        // std::for_each(_passes.begin(), _passes.end(), [](const auto& pass) -> void { pass->begin(); });

        if ((_dirty_flags & effect_dirty_flags::world_view_proj) != 0 || (_dirty_flags & effect_dirty_flags::world) != 0)
        {
            set_world_view_proj();

            _dirty_flags &= ~effect_dirty_flags::world_view_proj;
            _dirty_flags &= ~effect_dirty_flags::world;
        }

        if (_texture_enabled)
        {
            std::for_each(_textures.begin(), _textures.end(), [](const auto& texture) -> void { texture->bind(); });
        }
    }

    void effect_technique::end() noexcept
    {
        if (_texture_enabled)
        {
            std::for_each(_textures.begin(), _textures.end(), [](const auto& texture) -> void { texture->unbind(); });
        }

        // std::for_each(_passes.begin(), _passes.end(), [](const auto& pass) -> void { pass->end(); });
    }

    void effect_technique::set_world_view_proj() const noexcept
    {
        auto world_view      = _world * _view;
        auto world_view_proj = world_view * _projection;

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
            _world_view_param->set_value(world_view);
        }
        if (_world_view_projection_param.get())
        {
            _world_view_projection_param->set_value(world_view_proj);
        }
        if (_world_inverse_param.get())
        {
            _world_inverse_param->set_value(math::matrix::invert(_world));
        }
        if (_view_inverse_param.get())
        {
            _view_inverse_param->set_value(math::matrix::invert(_view));
        }
        if (_projection_inverse_param.get())
        {
            _projection_inverse_param->set_value(math::matrix::invert(_projection));
        }
        if (_world_view_inverse_param.get())
        {
            _world_view_inverse_param->set_value(math::matrix::invert(world_view));
        }
        if (_world_view_projection_inverse_param.get())
        {
            _world_view_projection_inverse_param->set_value(math::matrix::invert(world_view_proj));
        }
        if (_world_inverse_transpose_param.get())
        {
            _world_inverse_transpose_param->set_value(math::matrix::transpose(math::matrix::invert(_world)));
        }
        if (_world_view_inverse_transpose_param.get())
        {
            _world_view_inverse_transpose_param->set_value(math::matrix::transpose(math::matrix::invert(world_view)));
        }
    }
}
