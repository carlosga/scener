#include "scener/graphics/vulkan/physical_device.hpp"

#include <cassert>
#include <string>
#include <vector>

#include "scener/graphics/vulkan/display_surface.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"

namespace scener::graphics::vulkan
{
    physical_device::physical_device(const vk::PhysicalDevice& physical_device) noexcept
        : _extension_count   { 0 }
        , _extension_names   { nullptr }
        , _layer_count       { 0 }
        , _layer_names       { nullptr }
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

    logical_device physical_device::create_logical_device(gsl::not_null<const display_surface*> surface) const noexcept
    {
        auto graphics_queue_family_index = get_graphics_queue_family_index();
        auto present_queue_family_index  = get_present_queue_family_index(surface);

        assert(graphics_queue_family_index != UINT32_MAX);
        assert(present_queue_family_index != UINT32_MAX);

        const float priorities[1] = { 0.0 };

        // Features
        auto features = vk::PhysicalDeviceFeatures()
            .setTextureCompressionBC(VK_TRUE)
            .setDepthClamp(VK_TRUE)
            .setDepthBiasClamp(VK_TRUE)
            .setDepthBounds(VK_TRUE)
            .setFillModeNonSolid(VK_TRUE);

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
            .setEnabledLayerCount(_layer_count)
            .setPpEnabledLayerNames(_layer_names)
            .setEnabledExtensionCount(_extension_count)
            .setPpEnabledExtensionNames(_extension_names)
            .setPEnabledFeatures(&features);

        vk::Device device;

        auto result = _physical_device.createDevice(&deviceInfo, nullptr, &device);

        check_result(result);

        vk::Queue graphics_queue;
        vk::Queue present_queue;

        device.getQueue(graphics_queue_family_index, 0, &graphics_queue);
        device.getQueue(present_queue_family_index, 0, &present_queue);

        auto surface_caps   = identify_surface_capabilities(surface);
        auto surface_format = get_preferred_surface_format(surface);
        auto present_mode   = get_present_mode(surface);

        return { device
               , graphics_queue_family_index, graphics_queue
               , present_queue_family_index , present_queue
               , surface_caps
               , surface_format
               , present_mode };
    }

    void physical_device::identify_layers() noexcept
    {
        /* Look for device layers */
        std::uint32_t layer_count = 0;

        _layer_count = 0;
        memset(_layer_names, 0, sizeof(_layer_names));

        auto result = _physical_device.enumerateDeviceLayerProperties(&layer_count, nullptr);
        check_result(result);
        assert(layer_count < 64);

        if (layer_count > 0)
        {
            std::vector<vk::LayerProperties> layers(layer_count);

            result = _physical_device.enumerateDeviceLayerProperties(&layer_count, layers.data());
            check_result(result);

            for (std::uint32_t i = 0; i < layer_count; i++)
            {
                if (strcmp(layers[i].layerName, "VK_LAYER_LUNARG_standard_validation"))
                {
                    _layer_names[_layer_count++] = "VK_LAYER_LUNARG_standard_validation";
                }
            }
        }
    }

    void physical_device::identify_extensions() noexcept
    {
        /* Look for device extensions */
        std::uint32_t extension_count = 0;
        vk::Bool32    supports_swap_chains   = VK_FALSE;

        _extension_count = 0;
        memset(_extension_names, 0, sizeof(_extension_names));

        auto result = _physical_device.enumerateDeviceExtensionProperties(nullptr, &extension_count, nullptr);
        check_result(result);
        assert(extension_count < 64);

        if (extension_count > 0)
        {
            std::vector<vk::ExtensionProperties> extensions(extension_count);

            result = _physical_device.enumerateDeviceExtensionProperties(nullptr, &extension_count, extensions.data());
            check_result(result);

            for (std::uint32_t i = 0; i < extension_count; i++)
            {
                if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, extensions[i].extensionName))
                {
                    supports_swap_chains = VK_TRUE;
                    _extension_names[_extension_count++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
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

        assert(queue_family_count >= 1);

        _queue_families.clear();
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

    vk::SurfaceCapabilitiesKHR physical_device::identify_surface_capabilities(gsl::not_null<const display_surface*> surface) const noexcept
    {
        vk::SurfaceCapabilitiesKHR capabilities;

        // Surface capabilities basically describes what kind of image you can render to the user.
        auto result = _physical_device.getSurfaceCapabilitiesKHR(surface->_vk_surface, &capabilities);

        check_result(result);

        return capabilities;
    }

    std::vector<vk::Bool32> physical_device::get_surface_present_support(gsl::not_null<const display_surface*> surface) const noexcept
    {
        // Iterate over each queue to learn whether it supports presenting:
        std::vector<vk::Bool32> supports_present(_queue_families.size());
        for (std::uint32_t i = 0; i < _queue_families.size(); i++)
        {
            auto result = _physical_device.getSurfaceSupportKHR(i, surface->_vk_surface, &supports_present[i]);
            check_result(result);
        }
        return supports_present;
    }

    std::uint32_t physical_device::get_graphics_queue_family_index() const noexcept
    {
        for (std::uint32_t i = 0; i < _queue_families.size(); i++)
        {
            if (_queue_families[i].queueFlags & vk::QueueFlagBits::eGraphics)
            {
                return i;
            }
        }

        return UINT32_MAX;
    }

    std::uint32_t physical_device::get_present_queue_family_index(gsl::not_null<const display_surface*> surface) const noexcept
    {
        std::vector<vk::Bool32> supports_present = get_surface_present_support(surface);

        for (std::uint32_t i = 1; i < _queue_families.size(); i++)
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
        for (uint32_t i = 0; i < _queue_families.size(); ++i)
        {
            if (supports_present[i] == VK_TRUE)
            {
                return i;
            }
        }

        return UINT32_MAX;
    }

    std::vector<vk::SurfaceFormatKHR> physical_device::get_surface_formats(gsl::not_null<const display_surface*> surface) const noexcept
    {
        // Get the list of VkFormat's that are supported:
        uint32_t format_count;
        auto result = _physical_device.getSurfaceFormatsKHR(surface->_vk_surface, &format_count, nullptr);
        check_result(result);

        std::vector<vk::SurfaceFormatKHR> formats(format_count);
        result = _physical_device.getSurfaceFormatsKHR(surface->_vk_surface, &format_count, formats.data());
        check_result(result);

        return formats;
    }

    vk::SurfaceFormatKHR physical_device::get_preferred_surface_format(gsl::not_null<const display_surface*> surface) const noexcept
    {
        auto formats = get_surface_formats(surface);

        assert(formats.size() >= 1);

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

    vk::PresentModeKHR physical_device::get_present_mode(gsl::not_null<const display_surface*> surface) const noexcept
    {
        std::uint32_t present_mode_count = 0;

        _physical_device.getSurfacePresentModesKHR(surface->_vk_surface, &present_mode_count, nullptr);

        if (present_mode_count > 0)
        {
            std::vector<vk::PresentModeKHR> present_modes(present_mode_count);

            auto result = _physical_device.getSurfacePresentModesKHR(surface->_vk_surface, &present_mode_count, present_modes.data());

            check_result(result);

            for (const auto& present_mode : present_modes)
            {
                if (present_mode == vk::PresentModeKHR::eMailbox)
                {
                    return present_mode;
                }
                else if (present_mode == vk::PresentModeKHR::eImmediate)
                {
                    return present_mode;
                }
            }
        }

        return vk::PresentModeKHR::eFifo;
    }
}
