// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <algorithm>
#include <stdexcept>

#include "scener/graphics/graphics_adapter.hpp"
#include "scener/graphics/vulkan/adapter.hpp"
#include "scener/graphics/vulkan/physical_device.hpp"

namespace scener::graphics
{
    const graphics_adapter& graphics_adapter::default_adapter()
    {
        auto adapters = graphics_adapter::adapters();
        auto it       = std::find_if(adapters.begin(), adapters.end(),
                                     [](const graphics_adapter& adapter) -> bool
                                     {
                                         return adapter.is_default_adapter();
                                     });

        if (it != adapters.end())
        {
            return *it;
        }

        throw std::runtime_error("No default adapter available");
    }

    std::vector<graphics_adapter> graphics_adapter::adapters()
    {
        vulkan::adapter adapter { };
        const auto& devices = adapter.physical_devices();
        std::vector<graphics_adapter> adapters(devices.size());
        bool default_device_selected = false;

        for (const auto& device : devices)
        {
            const auto& properties = device.properties();
            graphics_adapter adapter;

            adapter._description        = std::string(properties.deviceName);
            adapter._vendor_id          = properties.vendorID;
            adapter._device_id          = properties.deviceID;

            if (!default_device_selected)
            {
                adapter._is_default_adapter = device.has_swapchain_support()
                                           && device.has_graphics_queue()
                                           && (device.is_discrete_gpu() || device.is_integrated_gpu());

                default_device_selected = adapter._is_default_adapter;
            }

            adapters.push_back(adapter);
        }

        return adapters;
    }

    graphics_adapter::graphics_adapter()
        : _description        {  }
        , _device_id          { 0 }
        , _device_name        { }
        , _is_default_adapter { false }
        , _is_wide_screen     { false }
        , _revision           { 0 }
        , _subsystem_id       { 0 }
        , _vendor_id          { 0 }
    {
        // , _monitorHandle         { nullptr }
        // , _supportedDisplayModes ( )
    }

    const std::string& graphics_adapter::description() const
    {
        return _description;
    }

    std::uint32_t graphics_adapter::device_id() const
    {
        return _device_id;
    }

    const std::string& graphics_adapter::device_name() const
    {
        return _device_name;
    }

    bool graphics_adapter::is_default_adapter() const
    {
        return _is_default_adapter;
    }

    bool graphics_adapter::is_wide_screen() const
    {
        return _is_wide_screen;
    }

//    GLFWmonitor* graphics_adapter::monitor_handle() const
//    {
//        return this->monitorHandle;
//    }

    std::uint32_t graphics_adapter::revision() const
    {
        return _revision;
    }

    std::uint32_t graphics_adapter::subsystem_id() const
    {
        return _subsystem_id;
    }

//    const std::vector<DisplayMode>& graphics_adapter::supported_display_modes() const
//    {
//        return this->supportedDisplayModes;
//    }

    std::uint32_t graphics_adapter::vendor_id() const
    {
        return _vendor_id;
    }
}
