// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_GRAPHICS_ADAPTER_HPP
#define SCENER_GRAPHICS_GRAPHICS_ADAPTER_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "scener/graphics/vulkan/adapter.hpp"
#include "scener/graphics/vulkan/surface.hpp"

namespace scener::graphics
{
    /**
     * Provides methods to manipulate graphics adapters.
     */
    class graphics_adapter final
    {
    public:
        /**
         * Initializes a new instance of the graphics adapter class.
         */
        graphics_adapter();

    public:
        /**
         * Retrieves a string used for presentation to the user.
         */
        const std::string& description() const;

        /**
         * Retrieves a value that is used to help identify a particular chip set.
         */
        std::uint32_t device_id() const;

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
         * Retrieves a value used to help identify the revision level of a particular chip set.
         */
        std::uint32_t revision() const;

        /**
         * Retrieves a value used to identify the subsystem.
         */
        std::uint32_t subsystem_id() const;

        /**
         * Retrieves a value used to identify the manufacturer.
         */
        std::uint32_t vendor_id() const;

    public:
        std::unique_ptr<vulkan::render_surface> create_render_surface(vulkan::display_surface* display_surface) const noexcept;
        const vulkan::physical_device& get_physical_device() const;

    private:
        std::string                      _description;
        std::uint32_t                    _device_id;
        std::string                      _device_name;
        bool                             _is_default_adapter;
        bool                             _is_wide_screen;
        std::uint32_t                    _revision;
        std::uint32_t                    _subsystem_id;
        std::uint32_t                    _vendor_id;
        std::shared_ptr<vulkan::adapter> _adapter;
    };
}

#endif // SCENER_GRAPHICS_GRAPHICS_ADAPTER_HPP
