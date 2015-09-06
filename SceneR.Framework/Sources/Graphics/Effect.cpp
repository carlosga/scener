// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Effect.hpp>

#include <cassert>

#include <Graphics/EffectDirtyFlags.hpp>
#include <Graphics/EffectHelpers.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/UniformBufferObject.hpp>
#include <System/Math.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using System::Math;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Vector3;

        Effect::Effect(GraphicsDevice& graphicsDevice)
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
            , _projection                { Matrix::Identity }
            , _specular_color            { Vector3::one }
            , _specular_power            { 16.0f }
            , _texture_enabled           { false }
            , _texture                   { nullptr }
            , _view                      { Matrix::Identity }
            , _weights_per_vertex        { 2 }
            , _world                     { Matrix::Identity }
            , _world_view                { Matrix::Identity }
            , _one_light                 { false }
            , _shader_index              { 0 }
            , _dirty_flags               { EffectDirtyFlags::All }
            , _passes                    { }
            , _parameters                { }
        {
            // _Name(u"Effect");

            // _CreateShader();
            // _CacheEffectParameters();

            // _light0.Enabled(true);
        }

        Effect::~Effect()
        {
        }

        void Effect::dispose()
        {
            if (_id != 0)
            {
                if (_texture)
                {
                    _texture = nullptr;
                }

                // Clear parameter collection
                // _parameters.Clear();

                // Dipose all the shader instances
                if (_shaders.size() > 0)
                {
                    for (auto& shader : _shaders)
                    {
                        shader->dispose();
                    }

                    _shaders.clear();
                }

                // dispose the uniform buffer object
                _uniform_buffer->dispose();
                _uniform_buffer = nullptr;

                // Delete the shader program
                glDeleteProgram(_id);

                // Reset the shader program name
                _id = 0;
            }
        }

        float Effect::alpha() const
        {
            return _alpha;
        }

        void Effect::alpha(const float& alpha)
        {
            if (Math::equal(_alpha, alpha))
            {
                _alpha        = alpha;
                _dirty_flags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& Effect::ambient_light_color() const
        {
            return _ambient_light_color;
        }

        void Effect::ambient_light_color(const Vector3& ambientLightColor)
        {
            if (_ambient_light_color != ambientLightColor)
            {
                _ambient_light_color = ambientLightColor;
                _dirty_flags        |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& Effect::diffuse_color() const
        {
            return _diffuse_color;
        }

        void Effect::diffuse_color(const Vector3& diffuseColor)
        {
            if (_diffuse_color != diffuseColor)
            {
                _diffuse_color = diffuseColor;
                _dirty_flags  |= EffectDirtyFlags::MaterialColor;
            }
        }

        const DirectionalLight& Effect::directional_light_0() const
        {
            return _light_0;
        }

        const DirectionalLight& Effect::directional_light_1() const
        {
            return _light_1;
        }

        const DirectionalLight& Effect::directional_light_2() const
        {
            return _light_2;
        }

        void Effect::enable_default_lighting()
        {
            ambient_light_color(EffectHelpers::enable_default_lighting(_light_0, _light_1, _light_2));
        }

        const Vector3& Effect::emissive_color() const
        {
            return _emissive_color;
        }

        void Effect::emissive_color(const Vector3& emissiveColor)
        {
            if (_emissive_color != emissiveColor)
            {
                _emissive_color = emissiveColor;
                _dirty_flags   |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& Effect::fog_color() const
        {
            return _fog_color;
        }

        void Effect::fog_color(const Vector3& fogColor)
        {
//            if (_fogColor != fogColor)
//            {
//                _fogColor = fogColor;
//
//                _fogColorParam.SetValue(_fogColor);
//            }
        }

        bool Effect::fog_enabled() const
        {
            return _fog_enabled;
        }

        void Effect::fog_enabled(const bool& fogEnabled)
        {
            if (_fog_enabled != fogEnabled)
            {
                _fog_enabled  = fogEnabled;
                _dirty_flags |= EffectDirtyFlags::Fog;
            }
        }

        float Effect::fog_end() const
        {
            return _fog_end;
        }

        void Effect::fog_end(const float& fogEnd)
        {
            if (!Math::equal(_fog_end, fogEnd))
            {
                _fog_end      = fogEnd;
                _dirty_flags |= EffectDirtyFlags::Fog;
            }
        }

        float Effect::fog_start() const
        {
            return _fog_start;
        }

        void Effect::fog_start(const float& fogStart)
        {
            if (!Math::equal(_fog_start, fogStart))
            {
                _fog_start    = fogStart;
                _dirty_flags |= EffectDirtyFlags::Fog;
            }
        }

        bool Effect::lighting_enabled() const
        {
            return _lighting_enabled;
        }

        void Effect::lighting_enabled(const bool& lightingEnabled)
        {
            assert(false);
        }

        bool Effect::prefer_per_pixel_lighting() const
        {
            return _prefer_per_pixel_lighting;
        }

        void Effect::prefer_per_pixel_lighting(const bool& preferPerPixelLighting)
        {
            if (_prefer_per_pixel_lighting != preferPerPixelLighting)
            {
                _prefer_per_pixel_lighting = preferPerPixelLighting;
                _dirty_flags              |= EffectDirtyFlags::ShaderIndex;
            }
        }

        const Matrix& Effect::projection() const
        {
            return _projection;
        }

        void Effect::projection(const Matrix& projection)
        {
            _projection   = projection;
            _dirty_flags |= EffectDirtyFlags::WorldViewProj;
        }

        const Vector3& Effect::specular_color() const
        {
            return _specular_color;
        }

        void Effect::specular_color(const Vector3& specularColor)
        {
//            if (_specularColor != specularColor)
//            {
//                _specularColor = specularColor;
//
//                _specularColorParam.SetValue(_specularColor);
//            }
        }

        float Effect::specular_power() const
        {
            return _specular_power;
        }

        void Effect::specular_power(const float& specularPower)
        {
//            if (!Math::equal(_specularPower, specularPower))
//            {
//                _specularPower = specularPower;
//
//                _specularPowerParam.SetValue(_specularPower);
//            }
        }

        const std::shared_ptr<Texture2D>& Effect::texture() const
        {
            return _texture;
        }

        void Effect::texture(const std::shared_ptr<Texture2D>& texture)
        {
            if (_texture != texture)
            {
                _texture      = texture;
                _dirty_flags |= EffectDirtyFlags::ShaderIndex;
            }
        }

        bool Effect::texture_enabled() const
        {
            return _texture_enabled;
        }

        void Effect::texture_enabled(const bool& textureEnabled)
        {
            if (_texture_enabled != textureEnabled)
            {
                _texture_enabled = textureEnabled;
                _dirty_flags    |= EffectDirtyFlags::ShaderIndex;
            }
        }

        const Matrix& Effect::view() const
        {
            return _view;
        }

        void Effect::view(const Matrix& view)
        {
            _view         = view;
            _dirty_flags |= EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::EyePosition | EffectDirtyFlags::Fog;
        }

        const Matrix& Effect::world() const
        {
            return _world;
        }

        void Effect::world(const Matrix& world)
        {
            _world        = world;
            _dirty_flags |= EffectDirtyFlags::World | EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::Fog;
        }

        std::vector<Matrix> Effect::bone_transforms(const std::size_t& count) const
        {
            assert(count < _bone_transforms.size());

            std::vector<Matrix> transforms;

            transforms.reserve(count);
            transforms.assign(_bone_transforms.begin(), _bone_transforms.begin() + count);

            return transforms;
        }

        void Effect::bone_transforms(const std::vector<Matrix>& boneTransforms)
        {
            _bone_transforms = boneTransforms;
//            _bonesParam.SetValue(_boneTransforms);
        }

        std::size_t Effect::weights_per_vertex() const
        {
            return _weights_per_vertex;
        }

        void Effect::weights_per_vertex(const std::size_t& weightsPerVertex)
        {
            assert(weightsPerVertex == 1 || weightsPerVertex == 2 || weightsPerVertex == 4);

            _weights_per_vertex = weightsPerVertex;
            _dirty_flags       |= EffectDirtyFlags::ShaderIndex;
        }

        void Effect::apply()
        {
//            _ActivateSubroutine(ShaderType::Vertex, VSIndices[_shaderIndex]);
//            _ActivateSubroutine(ShaderType::Fragment, PSIndices[_shaderIndex]);
//
//            if (_textureEnabled)
//            {
//                SamplerState& sampler = _graphics_device().SamplerStates()[0];
//
//                sampler.MaxMipLevel(_texture->LevelCount());
//                sampler.OnApply(_texture->Id());
//
//                _texture->Activate();
//            }
//
//            // Recompute the world+view+projection matrix or fog vector
//            _dirtyFlags = EffectHelpers::SetWorldViewProjAndFog(_dirtyFlags
//                , _world
//                , _view
//                , _projection
//                , _worldView
//                , _fogEnabled
//                , _fogStart
//                , _fogEnd
//                , _worldViewProjParam
//                , _fogVectorParam);
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
//                _dirtyFlags &= ~EffectDirtyFlags::MaterialColor;
//            }
//
//            if (_lightingEnabled)
//            {
//                // Recompute the world inverse transpose and eye position
//                _dirtyFlags = EffectHelpers::SetLightingMatrices(_dirtyFlags
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
//                    _dirtyFlags |= EffectDirtyFlags::ShaderIndex;
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
//            if ((_dirtyFlags & EffectDirtyFlags::ShaderIndex) != 0)
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
//                _dirtyFlags &= ~EffectDirtyFlags::ShaderIndex;
//            }
        }

        void Effect::create_shader()
        {
//            const auto& includes = std::vector<std::string> { ShaderManager::EffectIncludePath
//                , ShaderManager::StructuresIncludePath
//                , ShaderManager::CommonIncludePath
//                , ShaderManager::LightingIncludePath };
//
//            _AddShader(u"VSEffect", ShaderType::Vertex, Resources::Effect_vert, includes);
//            _AddShader(u"FSEffect", ShaderType::Fragment, Resources::Effect_frag, includes);
//            _Build();
        }

        void Effect::cache_effect_parameters()
        {
//            _diffuseColorParam          = _parameters[u"DiffuseColor"];
//            _emissiveColorParam         = _parameters[u"EmissiveColor"];
//            _specularColorParam         = _parameters[u"SpecularColor"];
//            _specularPowerParam         = _parameters[u"SpecularPower"];
//            _fogColorParam              = _parameters[u"FogColor"];
//            _fogVectorParam             = _parameters[u"FogVector"];
//            _eyePositionParam           = _parameters[u"EyePosition"];
//            _worldParam                 = _parameters[u"World"];
//            _worldViewProjParam         = _parameters[u"WorldViewProj"];
//            _worldInverseTransposeParam = _parameters[u"WorldInverseTranspose"];
//            _bonesParam                 = _parameters[u"Bones[0]"];
        }

        void Effect::begin()
        {
//            glUseProgram(_id);
//            _uniformBuffer->Activate();
//
//            _OnApply();
        }

        void Effect::end()
        {
//            if (_textureEnabled)
//            {
//                _texture->Deactivate();
//            }
//
//            _uniformBuffer->Deactivate();
//
//            glUseProgram(0);
        }

        void Effect::add_shader(const std::u16string&            name
                             , const ShaderType&                type
                             , const std::vector<std::uint8_t>& source)
        {
            add_shader(name, type, source, std::vector<std::string>());
        }

        void Effect::add_shader(const std::u16string&            name
                              , const ShaderType&                type
                              , const std::vector<std::uint8_t>& source
                              , const std::vector<std::string>&  includes)
        {
//            _shaders.push_back(std::make_shared<Shader>(name, type, source, includes));
        }

        void Effect::build_program()
        {
//            // Compile the shaders ...
//            for (auto& s : _shaders)
//            {
//                s->Compile();
//            }
//
//            // ... Create the program object
//            _id = glCreateProgram();
//
//            if (_id == 0)
//            {
//                throw std::runtime_error("glCreateProgram failed");
//            }
//
//            // ... attach the shaders to the new shader program
//            for (const auto& s : _shaders)
//            {
//                // Attach the shader
//                glAttachShader(_id, s->id);
//            }
//
//            // ... link the shader program
//            glLinkProgram(_id);
//
//            // ... verify program linking
//            _VerifyLinkingState();
//
//            // ... fill uniform buffer info
//            _uniformBuffer = std::make_shared<UniformBufferObject>(u"ConstantBuffer", _id);
//            _uniformBuffer->Describe();
//
//            // ... describe efffect parameters
//            _DescribeParameters();
        }

        void Effect::activate_subroutine(const std::uint32_t& subroutineIndex) const
        {
            for (const auto& shader : _shaders)
            {
                activate_subroutine(shader->type(), subroutineIndex);
            }
        }

        void Effect::activate_subroutine(const ShaderType& type, const std::uint32_t& subroutineIndex) const
        {
            glUniformSubroutinesuiv(static_cast<GLenum>(type), 1, &subroutineIndex);
        }

        void Effect::verify_linking_state()
        {
            // ... verify program linking
            GLint status;
            glGetProgramiv(_id, GL_LINK_STATUS, &status);

            if (status == GL_FALSE)
            {
                auto msg = std::string("Program linking failure: ");

                GLint infoLogLength;
                glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);

                if (infoLogLength)
                {
                    std::string linkErrorMessage("", static_cast<std::size_t>(infoLogLength));

                    glGetProgramInfoLog(_id, infoLogLength, NULL, &linkErrorMessage[0]);

                    msg += linkErrorMessage;
                }

                //_dispose();

                throw std::runtime_error(msg);
            }
        }

        void Effect::describe_parameters()
        {
//            // Check the number of active uniforms
//            std::int32_t activeUniforms = 0;
//
//            glGetActiveUniformBlockiv(_id, _uniformBuffer->Index(), GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUniforms);
//
//            std::vector<std::int32_t> indices(activeUniforms, 0);
//            std::vector<std::int32_t> nameLengths(activeUniforms, 0);
//            std::vector<std::int32_t> offsets(activeUniforms, 0);
//            std::vector<std::int32_t> types(activeUniforms, 0);
//
//            glGetActiveUniformBlockiv(_id, _uniformBuffer->Index(), GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, indices.data());
//
//            GLuint* address = reinterpret_cast<GLuint*>(indices.data());
//
//            glGetActiveUniformsiv(_id, activeUniforms, address, GL_UNIFORM_NAME_LENGTH, nameLengths.data());
//            glGetActiveUniformsiv(_id, activeUniforms, address, GL_UNIFORM_OFFSET     , offsets.data());
//            glGetActiveUniformsiv(_id, activeUniforms, address, GL_UNIFORM_TYPE       , types.data());
//
//            for (std::int32_t i = 0; i < activeUniforms; i++)
//            {
//                GLsizei length = 0;
//                GLint   size   = 0;
//                GLenum  type   = GL_ZERO;
//                auto    name   = std::vector<char>(nameLengths[i], 0);
//
//                glGetActiveUniform(_id, indices[i], nameLengths[i], &length, &size, &type, name.data());
//
//                _parameters.Add({ name.begin(), name.begin() + length }
//                                   , static_cast<std::uint32_t>(indices[i])
//                                   , static_cast<std::uint32_t>(offsets[i])
//                                   , static_cast<std::uint32_t>(types[i])
//                                   , _uniformBuffer);
//            }
        }

        std::uint32_t Effect::VSIndices[18] =
        {
            0,      // vertex lighting, one bone
            0,      // vertex lighting, one bone, no fog
            1,      // vertex lighting, two bones
            1,      // vertex lighting, two bones, no fog
            2,      // vertex lighting, four bones
            2,      // vertex lighting, four bones, no fog

            3,      // one light, one bone
            3,      // one light, one bone, no fog
            4,      // one light, two bones
            4,      // one light, two bones, no fog
            5,      // one light, four bones
            5,      // one light, four bones, no fog

            6,      // pixel lighting, one bone
            6,      // pixel lighting, one bone, no fog
            7,      // pixel lighting, two bones
            7,      // pixel lighting, two bones, no fog
            8,      // pixel lighting, four bones
            8,      // pixel lighting, four bones, no fog
        };

        std::uint32_t Effect::PSIndices[18] =
        {
            0,      // vertex lighting, one bone
            1,      // vertex lighting, one bone, no fog
            0,      // vertex lighting, two bones
            1,      // vertex lighting, two bones, no fog
            0,      // vertex lighting, four bones
            1,      // vertex lighting, four bones, no fog

            0,      // one light, one bone
            1,      // one light, one bone, no fog
            0,      // one light, two bones
            1,      // one light, two bones, no fog
            0,      // one light, four bones
            1,      // one light, four bones, no fog

            2,      // pixel lighting, one bone
            2,      // pixel lighting, one bone, no fog
            2,      // pixel lighting, two bones
            2,      // pixel lighting, two bones, no fog
            2,      // pixel lighting, four bones
            2,      // pixel lighting, four bones, no fog
        };
    }
}
