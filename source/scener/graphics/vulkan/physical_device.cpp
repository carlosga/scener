#include "scener/graphics/vulkan/physical_device.hpp"

#include <cassert>

#include "scener/graphics/vulkan/display_surface.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"

namespace scener::graphics::vulkan
{
    physical_device::physical_device(const vk::PhysicalDevice& physical_device) noexcept
        : _extension_names  { nullptr }
        , _properties       { }
        , _queue_families   { }
        , _physical_device  { physical_device }
    {
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

    device physical_device::create_device(const display_surface* surface) const noexcept
    {
        auto graphics_queue_family_index = get_graphics_queue_family_index();
        auto present_queue_family_index  = get_present_queue_family_index(surface);

        assert(graphics_queue_family_index != UINT32_MAX);
        assert(present_queue_family_index != UINT32_MAX);

        const float priorities[1] = { 0.0 };

        vk::Device device;
        vk::DeviceQueueCreateInfo queues[2];

        // graphics queue
        queues[0].setQueueFamilyIndex(graphics_queue_family_index);
        queues[0].setQueueCount(1);
        queues[0].setPQueuePriorities(priorities);

        // present queue
        queues[1].setQueueFamilyIndex(present_queue_family_index);
        queues[1].setQueueCount(1);
        queues[1].setPQueuePriorities(priorities);

        auto deviceInfo = vk::DeviceCreateInfo()
            .setQueueCreateInfoCount(2)
            .setPQueueCreateInfos(queues)
            .setEnabledLayerCount(0)
            .setPpEnabledLayerNames(nullptr)
            .setEnabledExtensionCount(_extension_count)
            .setPpEnabledExtensionNames(_extension_names)
            .setPEnabledFeatures(nullptr);

        auto result = _physical_device.createDevice(&deviceInfo, nullptr, &device);
        check_result(result);

        vk::Queue graphics_queue;
        vk::Queue present_queue;

        device.getQueue(graphics_queue_family_index, 0, &graphics_queue);
        device.getQueue(present_queue_family_index, 0, &present_queue);

        return { device, graphics_queue, present_queue };
    }

    void physical_device::identify_extensions() noexcept
    {
        /* Look for device extensions */
        std::uint32_t device_extension_count = 0;
        vk::Bool32    supports_swap_chains   = VK_FALSE;

        _extension_count = 0;
        memset(_extension_names, 0, sizeof(_extension_names));

        auto result = _physical_device.enumerateDeviceExtensionProperties(nullptr, &device_extension_count, nullptr);
        assert(result == vk::Result::eSuccess);

        if (device_extension_count > 0) 
        {
            std::vector<vk::ExtensionProperties> device_extensions(device_extension_count);
            result = _physical_device.enumerateDeviceExtensionProperties(nullptr, &device_extension_count, device_extensions.data());
            assert(result == vk::Result::eSuccess);

            for (std::uint32_t i = 0; i < device_extension_count; i++) 
            {
                if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, device_extensions[i].extensionName)) 
                {
                    supports_swap_chains = VK_TRUE;
                    _extension_names[_extension_count++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
                }
                assert(_extension_count < 64);
            }
        }

        if (!supports_swap_chains)
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

    std::vector<vk::Bool32> physical_device::get_surface_present_support(const display_surface* surface) const noexcept
    {
        // Iterate over each queue to learn whether it supports presenting:
        std::vector<vk::Bool32> supports_present(_queue_families.size());
        for (std::uint32_t i = 0; i < _queue_families.size(); i++) 
        {
            _physical_device.getSurfaceSupportKHR(i, surface->_vk_surface, &supports_present[i]);
        }
        return supports_present;
    }

    std::uint32_t physical_device::get_graphics_queue_family_index() const noexcept
    {
        std::uint32_t graphics_queue_index = UINT32_MAX;

        for (std::uint32_t i = 0; i < _queue_families.size(); i++) 
        {
            if (_queue_families[i].queueFlags & vk::QueueFlagBits::eGraphics) 
            {
                graphics_queue_index = i;
                break;
            }
        }

        return graphics_queue_index;
    }

    std::uint32_t physical_device::get_present_queue_family_index(const display_surface* surface) const noexcept
    {
        std::vector<vk::Bool32> supports_present    = get_surface_present_support(surface);
        std::uint32_t           present_queue_index = UINT32_MAX;

        for (std::uint32_t i = 0; i < _queue_families.size(); i++) 
        {
            if (_queue_families[i].queueFlags & vk::QueueFlagBits::eGraphics) 
            {
                if (supports_present[i] == VK_TRUE) 
                {
                    present_queue_index = i;
                    break;
                }
            }
        }

        // If didn't find a queue that supports both graphics and present,
        // then find a separate present queue.
        for (uint32_t i = 0; i < _queue_families.size(); ++i) 
        {
            if (supports_present[i] == VK_TRUE) 
            {
                present_queue_index = i;
                break;
            }
        }

        return present_queue_index;
    }

    std::vector<vk::SurfaceFormatKHR> physical_device::get_surface_formats(const display_surface* surface) const noexcept
    {
        // Get the list of VkFormat's that are supported:
        uint32_t formatCount;
        auto result = _physical_device.getSurfaceFormatsKHR(surface->_vk_surface, &formatCount, nullptr);
        assert(result == vk::Result::eSuccess);

        std::vector<vk::SurfaceFormatKHR> formats(formatCount);
        result = _physical_device.getSurfaceFormatsKHR(surface->_vk_surface, &formatCount, formats.data());
        assert(result == vk::Result::eSuccess);

        return formats;
    }

    vk::SurfaceFormatKHR physical_device::get_preferred_surface_format(const display_surface* surface) const noexcept
    {
        auto formats = get_surface_formats(surface);

        // If the format list includes just one entry of VK_FORMAT_UNDEFINED,
        // the surface has no preferred format. Otherwise, at least one
        // supported format will be returned.
        if (formats.size() == 1 && formats[0].format == vk::Format::eUndefined) 
        {
            //return vk::Format::eB8G8R8A8Unorm;
        }

        assert(formats.size() >= 1);
        return formats[0];
    }

        // color_space = surfFormats[0].colorSpace;

        // quit = false;
        // curFrame = 0;

        // // Create semaphores to synchronize acquiring presentable buffers before
        // // rendering and waiting for drawing to be complete before presenting
        // auto const semaphoreCreateInfo = vk::SemaphoreCreateInfo();

        // // Create fences that we can use to throttle if we get too far
        // // ahead of the image presents
        // auto const fence_ci = vk::FenceCreateInfo().setFlags(vk::FenceCreateFlagBits::eSignaled);
        // for (uint32_t i = 0; i < FRAME_LAG; i++) {
        //     device.createFence(&fence_ci, nullptr, &fences[i]);
        //     result = device.createSemaphore(&semaphoreCreateInfo, nullptr, &image_acquired_semaphores[i]);
        //     VERIFY(result == vk::Result::eSuccess);

        //     result = device.createSemaphore(&semaphoreCreateInfo, nullptr, &draw_complete_semaphores[i]);
        //     VERIFY(result == vk::Result::eSuccess);

        //     if (separate_present_queue) {
        //         result = device.createSemaphore(&semaphoreCreateInfo, nullptr, &image_ownership_semaphores[i]);
        //         VERIFY(result == vk::Result::eSuccess);
        //     }
        // }
        // frame_index = 0;

        // // Get Memory information and properties
        // gpu.getMemoryProperties(&memory_properties);        
}
