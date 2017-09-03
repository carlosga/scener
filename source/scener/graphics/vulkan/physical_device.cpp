#include "scener/graphics/vulkan/physical_device.hpp"

#include <gsl/gsl>

#include "scener/graphics/vulkan/platform.hpp"
#include "scener/graphics/vulkan/logical_device.hpp"

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

    logical_device physical_device::create_logical_device(const render_surface& surface) const noexcept
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

        auto deviceInfo = vk::DeviceCreateInfo()
            .setQueueCreateInfoCount(queue_count)
            .setPQueueCreateInfos(queues)
            // .setEnabledLayerCount(static_cast<std::uint32_t>(_layer_names.size()))
            // .setPpEnabledLayerNames(_layer_names.data())
            .setEnabledExtensionCount(static_cast<std::uint32_t>(_extension_names.size()))
            .setPpEnabledExtensionNames(_extension_names.data())
            .setPEnabledFeatures(&_features);

        auto logical_device    = _physical_device.createDevice(deviceInfo, nullptr);
        auto present_mode      = get_present_mode(surface);
        auto surface_caps      = get_surface_capabilities(surface);
        auto surface_format    = get_preferred_surface_format(surface);
        auto format_properties = get_format_properties(surface_format.format);
        auto allocator         = memory_allocator(_physical_device, logical_device);

        return {
            logical_device
          , allocator
          , graphics_queue_family_index
          , present_queue_family_index
          , surface_caps
          , surface_format
          , present_mode
          , format_properties
        };
    }

    void physical_device::identify_layers() noexcept
    {
        /* Look for device layers */
        std::uint32_t layer_count = 0;

        _layer_names.resize(0);

        auto result = _physical_device.enumerateDeviceLayerProperties(&layer_count, nullptr);
        check_result(result);
        Ensures(layer_count < 64);

        if (layer_count > 0)
        {
            std::vector<vk::LayerProperties> layers(layer_count);

            result = _physical_device.enumerateDeviceLayerProperties(&layer_count, layers.data());
            check_result(result);

            for (std::uint32_t i = 0; i < layer_count; ++i)
            {
                if (strcmp(layers[i].layerName, "VK_LAYER_LUNARG_standard_validation"))
                {
                    _layer_names.push_back("VK_LAYER_LUNARG_standard_validation");
                }
            }
        }
    }

    void physical_device::identify_extensions() noexcept
    {
        /* Look for device extensions */
        std::uint32_t extension_count      = 0;
        vk::Bool32    supports_swap_chains = VK_FALSE;

        _extension_names.resize(0);

        auto result = _physical_device.enumerateDeviceExtensionProperties(nullptr, &extension_count, nullptr);
        check_result(result);
        Ensures(extension_count < 64);

        if (extension_count > 0)
        {
            std::vector<vk::ExtensionProperties> extensions(extension_count);

            result = _physical_device.enumerateDeviceExtensionProperties(nullptr, &extension_count, extensions.data());
            check_result(result);

            for (std::uint32_t i = 0; i < extension_count; ++i)
            {
                if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, extensions[i].extensionName))
                {
                    supports_swap_chains = VK_TRUE;
                    _extension_names.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
                }
            }
        }

        if (supports_swap_chains == VK_FALSE)
        {
            throw std::runtime_error("Swap chain not supported");
        }
    }

    void physical_device::identify_properties() noexcept
    {
        _physical_device.getProperties(&_properties);
        _physical_device.getMemoryProperties(&_memory_properties);
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
        _physical_device.getFeatures(&_features);
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
            auto result = _physical_device.getSurfaceSupportKHR(i, surface.surface(), &supports_present[i]);
            check_result(result);
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

        for (std::uint32_t i = 0; i < _queue_families.size(); i++)
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
        auto formats = get_surface_formats(surface);

        Ensures(formats.size() >= 1);

        // If the format list includes just one entry of VK_FORMAT_UNDEFINED,
        // the surface has no preferred format. Otherwise, at least one
        // supported format will be returned.
        if (formats.size() == 1 && formats[0].format == vk::Format::eUndefined)
        {
            vk::SurfaceFormatKHR format;

            format.format     = vk::Format::eB8G8R8A8Unorm;
            format.colorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;

            return format;
        }

        // Favor 32 bit rgba and srgb nonlinear colorspace
        for (const auto& format : formats)
        {
            if (format.format     == vk::Format::eB8G8R8A8Unorm
             && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
            {
                return format;
            }
        }

        return formats[0];
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
}
