// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IGRAPHICSDEVICEMANAGER_HPP
#define SCENER_GRAPHICS_IGRAPHICSDEVICEMANAGER_HPP

#include "SceneR/IDisposable.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines the interface for an object that manages a GraphicsDevice.
         */
        class IGraphicsDeviceManager : SceneR::IDisposable
        {
        public:
            /**
             * Destructor
             */
            virtual ~IGraphicsDeviceManager() = default;

        public:
            /**
             * Releases all resources being used by this IGraphicsDeviceManager instance
             */
            virtual void dispose() override = 0;

        public:
           /**
             * Starts the drawing of a frame
             */
            virtual bool begin_draw() = 0;

            /**
             * Called to ensure that the device manager has created a valid device.
             */
            virtual void create_device() = 0;

            /**
             * Called by the game at the end of drawing; presents the final rendering.
             */
            virtual void end_draw() = 0;
        };
    }
}

#endif // SCENER_GRAPHICS_IGRAPHICSDEVICEMANAGER_HPP
