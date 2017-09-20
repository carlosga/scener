// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#include "scener/graphics/vulkan/physical_device.hpp"

#include <gsl/gsl>

#include "scener/graphics/vulkan/surface.hpp"
#include "scener/graphics/vulkan/logical_device.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"

namespace scener::graphics::vulkan
{
    physical_device::physical_device(const vk::PhysicalDevice& physical_device) noexcept
        : _layer_names       { }
        , _extension_names   { }
        , _properties        { }
        , _memory_properties { }
        , _features          { }
        , _queue_families    { }
        , _physical_device   { physical_device }
    {
        identify_layers();
        identify_extensions();
        identify_properties();
        identify_queue_families();
        identify_features();
    }

    physical_device::~physical_device() noexcept
    {
    }

    const vk::PhysicalDeviceProperties& physical_device::properties() const noexcept
    {
        return _properties;
    }

    const vk::PhysicalDeviceMemoryProperties& physical_device::memory_properties() const noexcept
    {
        return _memory_properties;
    }

    const vk::PhysicalDeviceFeatures& physical_device::features() const noexcept
    {
        return _features;
    }

    bool physical_device::has_swapchain_support() const noexcept
    {
        return _extension_names.size() > 0;
    }

    bool physical_device::has_graphics_queue() const noexcept
    {
        for (std::uint32_t i = 0; i < _queue_families.size(); i++)
        {
            if (_queue_families[i].queueFlags & vk::QueueFlagBits::eGraphics)
            {
                return true;
            }
        }

        return false;
    }

    bool physical_device::is_integrated_gpu() const noexcept
    {
        return _physical_device.getProperties().deviceType == vk::PhysicalDeviceType::eIntegratedGpu;
    }

    bool physical_device::is_discrete_gpu() const noexcept
    {
        return _physical_device.getProperties().deviceType == vk::PhysicalDeviceType::eDiscreteGpu;
    }

    bool physical_device::is_virtual_gpu() const noexcept
    {
        return _physical_device.getProperties().deviceType == vk::PhysicalDeviceType::eVirtualGpu;
    }

    bool physical_device::is_cpu_gpu() const noexcept
    {
        return _physical_device.getProperties().deviceType == vk::PhysicalDeviceType::eCpu;
    }

    std::unique_ptr<logical_device> physical_device::create_logical_device(const render_surface& surface) const noexcept
    {
        auto graphics_queue_family_index = get_graphics_queue_family_index();
        auto present_queue_family_index  = get_present_queue_family_index(surface);

        Ensures(graphics_queue_family_index != UINT32_MAX);
        Ensures(present_queue_family_index != UINT32_MAX);

        const float priorities[1] = { 0.0 };

        std::uint32_t queue_count = 1;

        // graphics queue
        vk::DeviceQueueCreateInfo queues[2];

        queues[0].setQueueFamilyIndex(graphics_queue_family_index);
        queues[0].setQueueCount(1);
        queues[0].setPQueuePriorities(priorities);

        if (graphics_queue_family_index != present_queue_family_index)
        {
            // present queue
            queues[1].setQueueFamilyIndex(present_queue_family_index);
            queues[1].setQueueCount(1);
            queues[1].setPQueuePriorities(priorities);

            queue_count++;
        }

        std::vector<vk::Format> formats = {
            vk::Format::eD32SfloatS8Uint
          , vk::Format::eD24UnormS8Uint
        };

        auto deviceInfo = vk::DeviceCreateInfo()
            .setQueueCreateInfoCount(queue_count)
            .setPQueueCreateInfos(queues)
            .setEnabledExtensionCount(static_cast<std::uint32_t>(_extension_names.size()))
            .setPpEnabledExtensionNames(_extension_names.data())
            .setPEnabledFeatures(&_features);

        auto device            = _physical_device.createDevice(deviceInfo, nullptr);
        auto present_mode      = get_present_mode(surface);
        auto surface_caps      = get_surface_capabilities(surface);
        auto surface_format    = get_preferred_surface_format(surface);
        auto format_properties = get_format_properties(surface_format.format);
        auto depth_format      = get_preferred_depth_format(
            formats
          , vk::ImageTiling::eOptimal
          , vk::FormatFeatureFlagBits::eDepthStencilAttachment
        );

        return std::make_unique<logical_device>(
            _physical_device
          , device
          , graphics_queue_family_index
          , present_queue_family_index
          , surface_caps
          , surface_format
          , depth_format
          , present_mode
          , format_properties);
    }

    void physical_device::identify_layers() noexcept
    {
        /* Look for device layers */
        _layer_names.clear();

        auto layers = _physical_device.enumerateDeviceLayerProperties();

        const auto it = std::find_if(layers.begin(), layers.end(), [] (const vk::LayerProperties& layer) -> bool
        {
            return !strcmp("VK_LAYER_LUNARG_standard_validation", layer.layerName);
        });

        if (it != layers.end())
        {
            _layer_names.push_back("VK_LAYER_LUNARG_standard_validation");
        }
    }

    void physical_device::identify_extensions() noexcept
    {
        _extension_names.clear();

        auto extensions = _physical_device.enumerateDeviceExtensionProperties(nullptr);

        for (std::uint32_t i = 0; i < extensions.size(); ++i)
        {
            if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, extensions[i].extensionName))
            {
                _extension_names.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
            }
        }
    }

    void physical_device::identify_properties() noexcept
    {
        _properties        = _physical_device.getProperties();
        _memory_properties = _physical_device.getMemoryProperties();
    }

    void physical_device::identify_queue_families() noexcept
    {
        std::uint32_t queue_family_count = 0;

        _physical_device.getQueueFamilyProperties(&queue_family_count, nullptr);

        Ensures(queue_family_count >= 1);

        _queue_families.resize(queue_family_count);

        _physical_device.getQueueFamilyProperties(&queue_family_count, _queue_families.data());
    }

    void physical_device::identify_features() noexcept
    {
        // Query fine-grained feature support for this device.
        //  If app has specific feature requirements it should check supported
        //  features based on this query
        _features = _physical_device.getFeatures();
    }

    vk::SurfaceCapabilitiesKHR physical_device::get_surface_capabilities(const render_surface& surface) const noexcept
    {
        // Surface capabilities basically describes what kind of image you can render to the user.
        return _physical_device.getSurfaceCapabilitiesKHR(surface.surface());
    }

    std::vector<vk::Bool32> physical_device::get_surface_present_support(const render_surface& surface) const noexcept
    {
        // Iterate over each queue to learn whether it supports presenting:
        std::vector<vk::Bool32> supports_present(_queue_families.size());

        for (std::uint32_t i = 0; i < _queue_families.size(); ++i)
        {
            supports_present[i] = _physical_device.getSurfaceSupportKHR(i, surface.surface());
        }

        return supports_present;
    }

    std::uint32_t physical_device::get_graphics_queue_family_index() const noexcept
    {
        for (std::uint32_t i = 0; i < _queue_families.size(); ++i)
        {
            if (_queue_families[i].queueFlags & vk::QueueFlagBits::eGraphics)
            {
                return i;
            }
        }

        return UINT32_MAX;
    }

    std::uint32_t physical_device::get_present_queue_family_index(const render_surface& surface) const noexcept
    {
        std::vector<vk::Bool32> supports_present = get_surface_present_support(surface);

        for (std::uint32_t i = 0; i < _queue_families.size(); ++i)
        {
            if (_queue_families[i].queueFlags & vk::QueueFlagBits::eGraphics)
            {
                if (supports_present[i] == VK_TRUE)
                {
                    return i;
                }
            }
        }

        // If didn't find a queue that supports both graphics and present,
        // then find a separate present queue.
        for (std::uint32_t i = 0; i < _queue_families.size(); ++i)
        {
            if (supports_present[i] == VK_TRUE)
            {
                return i;
            }
        }

        return UINT32_MAX;
    }

    std::vector<vk::SurfaceFormatKHR> physical_device::get_surface_formats(const render_surface& surface) const noexcept
    {
        // Get the list of VkFormat's that are supported:
        std::uint32_t format_count = 0;
        auto result = _physical_device.getSurfaceFormatsKHR(surface.surface(), &format_count, nullptr);
        check_result(result);

        std::vector<vk::SurfaceFormatKHR> formats(format_count);
        result = _physical_device.getSurfaceFormatsKHR(surface.surface(), &format_count, formats.data());
        check_result(result);

        return formats;
    }

    vk::SurfaceFormatKHR physical_device::get_preferred_surface_format(const render_surface& surface) const noexcept
    {
        auto surface_formats = get_surface_formats(surface);

        Ensures(surface_formats.size() >= 1);

        // If the format list includes just one entry of VK_FORMAT_UNDEFINED,
        // the surface has no preferred format. Otherwise, at least one
        // supported format will be returned.
        if (surface_formats.size() == 1 && surface_formats[0].format == vk::Format::eUndefined)
        {
            vk::SurfaceFormatKHR format;

            format.format     = vk::Format::eB8G8R8A8Unorm;
            format.colorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;

            return format;
        }

        // Favor 32 bit rgba and srgb nonlinear colorspace
        for (const auto& format : surface_formats)
        {
            if (format.format     == vk::Format::eB8G8R8A8Unorm
             && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
            {
                return format;
            }
        }

        return surface_formats[0];
    }

    vk::PresentModeKHR physical_device::get_present_mode(const render_surface& surface) const noexcept
    {
        std::uint32_t present_mode_count = 0;

        auto result = _physical_device.getSurfacePresentModesKHR(surface.surface(), &present_mode_count, nullptr);

        check_result(result);

        Ensures(present_mode_count > 0);

        std::vector<vk::PresentModeKHR> present_modes(present_mode_count);

        result = _physical_device.getSurfacePresentModesKHR(surface.surface(), &present_mode_count, present_modes.data());

        check_result(result);

        for (const auto& present_mode : present_modes)
        {
            if (present_mode == vk::PresentModeKHR::eMailbox)
            {
                return present_mode;
            }
        }

        return vk::PresentModeKHR::eFifo;
    }

    vk::FormatProperties physical_device::get_format_properties(const vk::Format& format) const noexcept
    {
        vk::FormatProperties format_properties;

        _physical_device.getFormatProperties(format, &format_properties);

        return format_properties;
    }

    vk::Format physical_device::get_preferred_depth_format(
        const std::vector<vk::Format>& formats
      , const vk::ImageTiling&         tiling
      , const vk::FormatFeatureFlags&  features) const noexcept
    {
        for (const auto& format : formats)
        {
            auto properties = get_format_properties(format);

            if (tiling == vk::ImageTiling::eLinear && (properties.linearTilingFeatures & features) == features)
            {
                return format;
            }
            else if (tiling == vk::ImageTiling::eOptimal && ( properties.optimalTilingFeatures & features) == features)
            {
                return format;
            }
        }

        throw std::runtime_error("Failed to find a supported depth format.");
    }
}
