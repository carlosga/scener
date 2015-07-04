// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICSADAPTER_HPP
#define GRAPHICSADAPTER_HPP

#include <string>
#include <vector>

#include <System/Core.hpp>
#include <Graphics/DisplayMode.hpp>

struct GLFWmonitor;

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Provides methods to manipulate graphics adapters.
         */
        class GraphicsAdapter final
        {
        public:
            /**
             * Gets the default adapter.
             */
            static const GraphicsAdapter& DefaultAdapter();

            /**
             * Gets the collection of available adapters.
             */
            static const std::vector<GraphicsAdapter> Adapters();

        public:
            /**
             * Initializes a new instance of the GraphicsAdapter class.
             */
            GraphicsAdapter();

            /**
             * @brief Copy constructor.
             * @param adapter The graphics adapter to copy from.
             */
            GraphicsAdapter(const GraphicsAdapter& adapter);

            /**
             * Destructor
             */
            ~GraphicsAdapter();

        public:
            /**
             * Gets the current display mode.
             */
            DisplayMode CurrentDisplayMode() const;

            /**
             * Retrieves a string used for presentation to the user.
             */
            const std::u16string& Description() const;

            /**
             * Retrieves a value that is used to help identify a particular chip set.
             */
            int32_t DeviceId() const;

            /**
             * Retrieves a string that contains the device name for a Microsoft Windows Graphics Device Interface (GDI).
             */
            const std::u16string& DeviceName() const;

            /**
             * Determines if this instance of GraphicsAdapter is the default adapter.
             */
            bool IsDefaultAdapter() const;

            /**
             * Determines if the graphics adapter is in widescreen mode.
             */
            bool IsWideScreen() const;

            /**
             * Retrieves the handle of the monitor associated with the Microsoft Direct3D object.
             */
            GLFWmonitor* MonitorHandle() const;

            /**
             * Retrieves a value used to help identify the revision level of a particular chip set.
             */
            int32_t Revision() const;

            /**
             * Retrieves a value used to identify the subsystem.
             */
            int32_t SubSystemId() const;

            /**
             * Returns a collection of supported display modes for the current adapter.
             */
            const std::vector<DisplayMode>& SupportedDisplayModes() const;

            /**
             * Retrieves a value used to identify the manufacturer.
             */
            int32_t VendorId() const;

        public:
            GraphicsAdapter& operator=(const GraphicsAdapter& adapter);

        private:
            std::u16string           description;
            int32_t                  deviceId;
            std::u16string           deviceName;
            bool                     isDefaultAdapter;
            bool                     isWideScreen;
            GLFWmonitor*             monitorHandle;
            int32_t                  revision;
            int32_t                  subSystemId;
            std::vector<DisplayMode> supportedDisplayModes;
            int32_t                  vendorId;
        };
    }
}

#endif /* GRAPHICSADAPTER_HPP_ */
