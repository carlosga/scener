// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <algorithm>
#include <stdexcept>

#include "scener/graphics/graphics_adapter.hpp"
#include "scener/graphics/vulkan/adapter.hpp"
#include "scener/graphics/vulkan/physical_device.hpp"

namespace scener::graphics
{
    graphics_adapter::graphics_adapter()
        : _description        {  }
        , _device_id          { 0 }
        , _device_name        { }
        , _is_default_adapter { false }
        , _is_wide_screen     { false }
        , _revision           { 0 }
        , _subsystem_id       { 0 }
        , _vendor_id          { 0 }
        , _adapter            { std::make_shared<vulkan::adapter>() }
    {
        const auto& devices    = _adapter->physical_devices();
        const auto& device     = devices[0];
        const auto& properties = device.properties();

        _description        = std::string(properties.deviceName);
        _vendor_id          = properties.vendorID;
        _device_id          = properties.deviceID;
        _is_default_adapter = device.has_swapchain_support()
                           && device.has_graphics_queue()
                           && (device.is_discrete_gpu() || device.is_integrated_gpu());
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

    std::unique_ptr<vulkan::render_surface> graphics_adapter::create_render_surface(vulkan::display_surface *window_handle) const noexcept
    {
        return std::make_unique<vulkan::render_surface>(_adapter, window_handle);
    }

    const vulkan::physical_device& graphics_adapter::get_physical_device() const
    {
        return _adapter->get_physical_device(_device_id);
    }
}
