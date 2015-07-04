// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IGRAPHICSDEVICEMANAGER_HPP
#define IGRAPHICSDEVICEMANAGER_HPP

#include <System/IDisposable.hpp>

namespace SceneR
{
    namespace Framework
    {
        /**
         * Defines the interface for an object that manages a GraphicsDevice.
         */
        class IGraphicsDeviceManager : System::IDisposable
        {
        public:
            /**
             * Destructor
             */
            virtual ~IGraphicsDeviceManager();

        public:
            /**
             * Releases all resources being used by this IGraphicsDeviceManager instance
             */
            virtual void Dispose() override = 0;

        public:
           /**
             * Starts the drawing of a frame
             */
            virtual bool BeginDraw() = 0;

            /**
             * Called to ensure that the device manager has created a valid device.
             */
            virtual void CreateDevice() = 0;

            /**
             * Called by the game at the end of drawing; presents the final rendering.
             */
            virtual void EndDraw() = 0;
        };
    }
}

#endif  /* IGRAPHICSDEVICEMANAGER_HPP */
