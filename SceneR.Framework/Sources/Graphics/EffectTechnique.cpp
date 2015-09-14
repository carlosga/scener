// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/EffectTechnique.hpp>

#include <cassert>

#include <Graphics/EffectDirtyFlags.hpp>
#include <Graphics/EffectHelpers.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectPass.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <System/Math.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Vector3;
        using System::Math;

        EffectTechnique::EffectTechnique(GraphicsDevice& graphicsDevice)
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
            , _fog_enabled               { false }
            , _fog_color                 { Vector3::zero }
            , _fog_end                   { 1.0f }
            , _fog_start                 { 0.0f }
            , _prefer_per_pixel_lighting { false }
            , _projection                { Matrix::identity }
            , _specular_color            { Vector3::one }
            , _specular_power            { 16.0f }
            , _texture_enabled           { false }
            , _textures                  ( 0 )
            , _view                      { Matrix::identity }
            , _weights_per_vertex        { 2 }
            , _world                     { Matrix::identity }
            , _world_view                { Matrix::identity }
            , _one_light                 { false }
            , _dirty_flags               { EffectDirtyFlags::All }
            , _passes                    ()
            , _parameters                ()
        {
        }

        EffectTechnique::~EffectTechnique()
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
            ambient_light_color(EffectHelpers::enable_default_lighting(_light_0, _light_1, _light_2));
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

        const Vector3& EffectTechnique::fog_color() const
        {
            return _fog_color;
        }

        void EffectTechnique::fog_color(const Vector3& fogColor)
        {
//            if (_fogColor != fogColor)
//            {
//                _fogColor = fogColor;
//
//                _fogColorParam.SetValue(_fogColor);
//            }
        }

        bool EffectTechnique::fog_enabled() const
        {
            return _fog_enabled;
        }

        void EffectTechnique::fog_enabled(const bool& fogEnabled)
        {
            if (_fog_enabled != fogEnabled)
            {
                _fog_enabled  = fogEnabled;
                _dirty_flags |= EffectDirtyFlags::Fog;
            }
        }

        float EffectTechnique::fog_end() const
        {
            return _fog_end;
        }

        void EffectTechnique::fog_end(const float& fogEnd)
        {
            if (!Math::equal(_fog_end, fogEnd))
            {
                _fog_end      = fogEnd;
                _dirty_flags |= EffectDirtyFlags::Fog;
            }
        }

        float EffectTechnique::fog_start() const
        {
            return _fog_start;
        }

        void EffectTechnique::fog_start(const float& fogStart)
        {
            if (!Math::equal(_fog_start, fogStart))
            {
                _fog_start    = fogStart;
                _dirty_flags |= EffectDirtyFlags::Fog;
            }
        }

        bool EffectTechnique::lighting_enabled() const
        {
            return _lighting_enabled;
        }

        void EffectTechnique::lighting_enabled(const bool& lightingEnabled)
        {
            assert(false);
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
            assert(count < _bone_transforms.size());

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

        std::size_t EffectTechnique::weights_per_vertex() const
        {
            return _weights_per_vertex;
        }

        void EffectTechnique::weights_per_vertex(const std::size_t& weightsPerVertex)
        {
            assert(weightsPerVertex == 1 || weightsPerVertex == 2 || weightsPerVertex == 4);

            _weights_per_vertex = weightsPerVertex;
            _dirty_flags       |= EffectDirtyFlags::ShaderIndex;
        }

        void EffectTechnique::begin()
        {
            if (_pass != nullptr)
            {
                _pass->apply();
            }
            else
            {
                for (const auto& pass : _passes)
                {
                    pass.second->apply();
                }
            }

            // Recompute the world+view+projection matrix or fog vector
            _dirty_flags = EffectHelpers::set_world_view_proj(_dirty_flags
                                                            , _world
                                                            , _view
                                                            , _projection
                                                            , _world_view
                                                            , _world_view_proj_param);

            // Recompute the world inverse transpose and eye position
            _dirty_flags = EffectHelpers::set_lighting_matrices(_dirty_flags
                                                              , _world
                                                              , _view
                                                              , _world_param
                                                              , _world_inverse_transpose_param
                                                              , nullptr);

            if (_texture_enabled)
            {
                for (auto texture : _textures)
                {
                    texture->activate();
                }
            }

//
//            // Recompute the diffuse/emissive/alpha material color parameters
//            if ((dirtyFlags & EffectDirtyFlags::MaterialColor) != 0)
//            {
//                EffectHelpers::SetMaterialColor(_lightingEnabled
//                    , _alpha
//                    , _diffuseColor
//                    , _emissiveColor
//                    , _ambientLightColor
//                    , _diffuseColorParam
//                    , _emissiveColorParam);
//
//                _dirty_flags &= ~EffectDirtyFlags::MaterialColor;
//            }
//
//            if (_lightingEnabled)
//            {
//                // Recompute the world inverse transpose and eye position
//                _dirty_flags = EffectHelpers::SetLightingMatrices(_dirty_flags
//                    , _world
//                    , _view
//                    , _worldParam
//                    , _worldInverseTransposeParam
//                    , _eyePositionParam);
//
//                // Check if we can use the only-bother-with-the-first-light shader optimization.
//                bool newOneLight = !_light1.Enabled() && !_light2.Enabled();
//
//                if (_oneLight != newOneLight)
//                {
//                    _oneLight    = newOneLight;
//                    _dirty_flags |= EffectDirtyFlags::ShaderIndex;
//                }
//                else
//                {
//                    if (_light0.Enabled())
//                    {
//                        _parameters[u"DirLight0Direction"].SetValue(_light0.Direction());
//                        _parameters[u"DirLight0DiffuseColor"].SetValue(_light0.DiffuseColor());
//                        _parameters[u"DirLight0SpecularColor"].SetValue(_light0.SpecularColor());
//                    }
//
//                    if (_light1.Enabled())
//                    {
//                        _parameters[u"DirLight1Direction"].SetValue(_light1.Direction());
//                        _parameters[u"DirLight1DiffuseColor"].SetValue(_light1.DiffuseColor());
//                        _parameters[u"DirLight1SpecularColor"].SetValue(_light1.SpecularColor());
//                    }
//
//                    if (_light2.Enabled())
//                    {
//                        _parameters[u"DirLight2Direction"].SetValue(_light2.Direction());
//                        _parameters[u"DirLight2DiffuseColor"].SetValue(_light2.DiffuseColor());
//                        _parameters[u"DirLight2SpecularColor"].SetValue(_light2.SpecularColor());
//                    }
//                }
//            }
//
//            // Recompute the shader index
//            if ((_dirty_flags & EffectDirtyFlags::ShaderIndex) != 0)
//            {
//                _shaderIndex = 0;
//
//                if (!_fogEnabled)
//                {
//                    _shaderIndex += 1;
//                }
//
//                if (_weightsPerVertex == 2)
//                {
//                    _shaderIndex += 2;
//                }
//                else if (weightsPerVertex == 4)
//                {
//                    _shaderIndex += 4;
//                }
//
//                if (_preferPerPixelLighting)
//                {
//                    _shaderIndex += 12;
//                }
//                else if (_oneLight)
//                {
//                    _shaderIndex += 6;
//                }
//
//                _dirty_flags &= ~EffectDirtyFlags::ShaderIndex;
//            }
        }

        void EffectTechnique::end()
        {
        }
    }
}
