//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef SAMPLERSTATE_HPP
#define SAMPLERSTATE_HPP

#include <Graphics/GraphicsResource.hpp>
#include <Graphics/TextureAddressMode.hpp>
#include <Graphics/TextureFilter.hpp>
#include <Graphics/TextureTarget.hpp>
#include <System/Core.hpp>

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
             * Releases all resources being used by this SamplerState.
             */
            virtual ~SamplerState() = default;

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
            const System::Int32& MaxAnisotropy() const;

            /**
             * Sets the maximum anisotropy. The default value is 0.
             */
            void MaxAnisotropy(const System::Int32& maxAnisotropy);

            /**
             * Gets the level of detail (LOD) index of the largest map to use.
             */
            const System::Int32& MaxMipLevel() const;

            /**
             * Sets the level of detail (LOD) index of the largest map to use.
             */
            void MaxMipLevel(const System::Int32& maxMipLevel);

            /**
             * Gets the mipmap LOD bias, which ranges from -1.0 to +1.0. The default value is 0.
             */
            const System::Single& MipMapLevelOfDetailBias() const;

            /**
             * Sets the mipmap LOD bias, which ranges from -1.0 to +1.0. The default value is 0.
             */
            void MipMapLevelOfDetailBias(const System::Single& mipMapLevelOfDetailBias);

        private:
            void OnApply(const TextureTarget& target, const System::Int32& mipmapLevels) const;

        private:
            TextureAddressMode addressU;
            TextureAddressMode addressV;
            TextureAddressMode addressW;
            TextureFilter      filter;
            System::Int32      maxAnisotropy;
            System::Int32      maxMipLevel;
            System::Single     mipMapLevelOfDetailBias;

            friend class BasicEffect;
            friend class SkinnedEffect;
        };
    }
}

#endif /* SAMPLERSTATE_HPP */
