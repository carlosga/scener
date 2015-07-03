// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

#ifndef EFFECTHELPERS_HPP
#define EFFECTHELPERS_HPP

#include <System/Core.hpp>
#include <Framework/Matrix.hpp>
#include <Graphics/EffectDirtyFlags.hpp>
#include <Graphics/EffectParameter.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct Vector3;
        struct Matrix;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class EffectParameter;
        class DirectionalLight;

        /**
         * @brief  Helper code shared between the various built-in effects.
         */
        class EffectHelpers
        {
        public:
                /// <summary>
                /// Sets up the standard key/fill/back lighting rig.
                /// </summary>
                static SceneR::Framework::Vector3 EnableDefaultLighting(DirectionalLight& light0
                                                                      , DirectionalLight& light1
                                                                      , DirectionalLight& light2);

                /// <summary>
                /// Lazily recomputes the world+view+projection matrix and
                /// fog vector based on the current effect parameter settings.
                /// </summary>
                static EffectDirtyFlags SetWorldViewProjAndFog(const EffectDirtyFlags&          dirtyFlags
                                                             , const SceneR::Framework::Matrix& world
                                                             , const SceneR::Framework::Matrix& view
                                                             , const SceneR::Framework::Matrix& projection
                                                             , SceneR::Framework::Matrix&       worldView
                                                             , const bool&                      fogEnabled
                                                             , const System::Single&            fogStart
                                                             , const System::Single&            fogEnd
                                                             , EffectParameter&                 worldViewProjParam
                                                             , EffectParameter&                 fogVectorParam);

                /// <summary>
                /// Sets a vector which can be dotted with the object space vertex position to compute fog amount.
                /// </summary>
                static void SetFogVector(const SceneR::Framework::Matrix& worldView
                                       , const System::Single&            fogStart
                                       , const System::Single&            fogEnd
                                       , EffectParameter&                 fogVectorParam);

                /// <summary>
                /// Lazily recomputes the world inverse transpose matrix and
                /// eye position based on the current effect parameter settings.
                /// </summary>
                static EffectDirtyFlags SetLightingMatrices(const EffectDirtyFlags&          dirtyFlags
                                                          , const SceneR::Framework::Matrix& world
                                                          , const SceneR::Framework::Matrix& view
                                                          , EffectParameter&                 worldParam
                                                          , EffectParameter&                 worldInverseTransposeParam
                                                          , EffectParameter&                 eyePositionParam);

                /// <summary>
                /// Sets the diffuse/emissive/alpha material color parameters.
                /// </summary>
                static void SetMaterialColor(const bool&                       lightingEnabled
                                           , const System::Single&             alpha
                                           , const SceneR::Framework::Vector3& diffuseColor
                                           , const SceneR::Framework::Vector3& emissiveColor
                                           , const SceneR::Framework::Vector3& ambientLightColor
                                           , EffectParameter&                  diffuseColorParam
                                           , EffectParameter&                  emissiveColorParam);

        private:
            EffectHelpers() = delete;
            EffectHelpers& operator=(const EffectHelpers& helpers) = delete;
        };
    }
}

#endif /* EFFECTHELPERS_HPP */
