// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SAMPLERSTATE_HPP
#define SAMPLERSTATE_HPP

#include <System/Core.hpp>
#include <Graphics/TextureFilter.hpp>
#include <Graphics/TextureTarget.hpp>
#include <Graphics/TextureAddressMode.hpp>
#include <Graphics/GraphicsResource.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class BasicEffect;
        class GraphicsDevice;
        class SkinnedEffect;

        /**
         * Contains sampler state, which determines how to sample texture data.
         */
        class SamplerState: public GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the SamplerState class.
             */
            SamplerState(GraphicsDevice& graphicsDevice);

            /**
             * @brief Copy constructor.
             * @param samplerState The sampler state to copy from.
             */
            SamplerState(const SamplerState& samplerState);

            /**
             * Destructor
             */
            ~SamplerState();

        public:
            void Dispose() override;

        public:
            /**
             *  Gets the texture-address mode for the u-coordinate.
             */
            const TextureAddressMode& AddressU() const;

            /**
             * Sets the texture-address mode for the u-coordinate.
             */
            void AddressU(const TextureAddressMode& addressU);

            /**
             *  Gets the texture-address mode for the v-coordinate.
             */
            const TextureAddressMode& AddressV() const;

            /**
             * Sets the texture-address mode for the v-coordinate.
             */
            void AddressV(const TextureAddressMode& addressV);

            /**
             *  Gets the texture-address mode for the w-coordinate.
             */
            const TextureAddressMode& AddressW() const;

            /**
             * Sets the texture-address mode for the w-coordinate.
             */
            void AddressW(const TextureAddressMode& addressW);

            /**
             *  Gets the type of filtering during sampling.
             */
            const TextureFilter& Filter() const;

            /**
             * Sets the type of filtering during sampling.
             */
            void Filter(const TextureFilter& filter);

            /**
             * Gets the maximum anisotropy. The default value is 0.
             */
            const int32_t& MaxAnisotropy() const;

            /**
             * Sets the maximum anisotropy. The default value is 0.
             */
            void MaxAnisotropy(const int32_t& maxAnisotropy);

            /**
             * Gets the level of detail (LOD) index of the largest map to use.
             */
            uint32_t MaxMipLevel() const;

            /**
             * Sets the level of detail (LOD) index of the largest map to use.
             */
            void MaxMipLevel(const uint32_t& maxMipLevel);

            /**
             * Gets the mipmap LOD bias, which ranges from -1.0 to +1.0. The default value is 0.
             */
            const System::Single& MipMapLevelOfDetailBias() const;

            /**
             * Sets the mipmap LOD bias, which ranges from -1.0 to +1.0. The default value is 0.
             */
            void MipMapLevelOfDetailBias(const System::Single& mipMapLevelOfDetailBias);

        public:
            SamplerState& operator=(const SamplerState& samplerState);

        private:
            void OnApply(const TextureTarget& target) const;
            void GetMinMaxFilters(GLenum& minfilter, GLenum& maxfilter) const;

        private:
            TextureAddressMode addressU;
            TextureAddressMode addressV;
            TextureAddressMode addressW;
            TextureFilter      filter;
            int32_t            maxAnisotropy;
            uint32_t           maxMipLevel;
            System::Single     mipMapLevelOfDetailBias;

            friend class BasicEffect;
            friend class SkinnedEffect;
            friend class EffectMaterial;
        };
    }
}

#endif /* SAMPLERSTATE_HPP */
