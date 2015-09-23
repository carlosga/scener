// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_GRAPHICSADAPTER_HPP
#define GRAPHICS_GRAPHICSADAPTER_HPP

#include <cstdint>
#include <string>
#include <vector>

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
            static const GraphicsAdapter& default_adapter();

            /**
             * Gets the collection of available adapters.
             */
            static const std::vector<GraphicsAdapter> adapters();

        public:
            /**
             * Initializes a new instance of the GraphicsAdapter class.
             */
            GraphicsAdapter();

            /**
             * @brief Copy constructor.
             * @param adapter The graphics adapter to copy from.
             */
            GraphicsAdapter(const GraphicsAdapter& adapter) = default;

            /**
             * Destructor
             */
            ~GraphicsAdapter() = default;

        public:
            /**
             * Gets the current display mode.
             */
            DisplayMode current_display_mode() const;

            /**
             * Retrieves a string used for presentation to the user.
             */
            const std::string& description() const;

            /**
             * Retrieves a value that is used to help identify a particular chip set.
             */
            std::int32_t device_id() const;

            /**
             * Retrieves a string that contains the device name for a Microsoft Windows Graphics Device Interface (GDI).
             */
            const std::string& device_name() const;

            /**
             * Determines if this instance of GraphicsAdapter is the default adapter.
             */
            bool is_default_adapter() const;

            /**
             * Determines if the graphics adapter is in widescreen mode.
             */
            bool is_wide_screen() const;

            /**
             * Retrieves the handle of the monitor associated with the Microsoft Direct3D object.
             */
            GLFWmonitor* monitor_handle() const;

            /**
             * Retrieves a value used to help identify the revision level of a particular chip set.
             */
            std::int32_t revision() const;

            /**
             * Retrieves a value used to identify the subsystem.
             */
            std::int32_t sub_system_id() const;

            /**
             * Returns a collection of supported display modes for the current adapter.
             */
            const std::vector<DisplayMode>& supported_display_modes() const;

            /**
             * Retrieves a value used to identify the manufacturer.
             */
            std::int32_t vendor_id() const;

        public:
            GraphicsAdapter& operator=(const GraphicsAdapter& adapter) = default;

        private:
            std::string              _description;
            std::int32_t             _device_id;
            std::string              _device_name;
            bool                     _is_default_adapter;
            bool                     _is_wide_screen;
            GLFWmonitor*             _monitor_handle;
            std::int32_t             _revision;
            std::int32_t             _sub_system_id;
            std::vector<DisplayMode> _supported_display_modes;
            std::int32_t             _vendor_id;
        };
    }
}

#endif  // GRAPHICS_GRAPHICSADAPTER_HPP
