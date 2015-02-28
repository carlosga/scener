// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICSADAPTER_HPP
#define GRAPHICSADAPTER_HPP

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
            const System::String& Description() const;

            /**
             * Retrieves a value that is used to help identify a particular chip set.
             */
            const System::Int32& DeviceId() const;

            /**
             * Retrieves a string that contains the device name for a Microsoft Windows Graphics Device Interface (GDI).
             */
            const System::String& DeviceName() const;

            /**
             * Determines if this instance of GraphicsAdapter is the default adapter.
             */
            const System::Boolean& IsDefaultAdapter() const;

            /**
             * Determines if the graphics adapter is in widescreen mode.
             */
            const System::Boolean& IsWideScreen() const;

            /**
             * Retrieves the handle of the monitor associated with the Microsoft Direct3D object.
             */
            GLFWmonitor* MonitorHandle() const;

            /**
             * Retrieves a value used to help identify the revision level of a particular chip set.
             */
            const System::Int32& Revision() const;

            /**
             * Retrieves a value used to identify the subsystem.
             */
            const System::Int32& SubSystemId() const;

            /**
             * Returns a collection of supported display modes for the current adapter.
             */
            const std::vector<DisplayMode>& SupportedDisplayModes() const;

            /**
             * Retrieves a value used to identify the manufacturer.
             */
            const System::Int32& VendorId() const;

        public:
            GraphicsAdapter& operator=(const GraphicsAdapter& adapter);

        private:
            System::String           description;
            System::Int32            deviceId;
            System::String           deviceName;
            System::Boolean          isDefaultAdapter;
            System::Boolean          isWideScreen;
            GLFWmonitor*             monitorHandle;
            System::Int32            revision;
            System::Int32            subSystemId;
            std::vector<DisplayMode> supportedDisplayModes;
            System::Int32            vendorId;
        };
    }
}

#endif /* GRAPHICSADAPTER_HPP_ */
