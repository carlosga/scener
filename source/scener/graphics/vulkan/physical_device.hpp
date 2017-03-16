#ifndef SCENER_GRAPHIcS_VULKAN_PHYSICAL_DEVICE_HPP
#define SCENER_GRAPHIcS_VULKAN_PHYSICAL_DEVICE_HPP

#include <vulkan/vulkan.hpp>
#include <cstdint>
#include <vector>

#include "scener/graphics/vulkan/device.hpp"

namespace scener::graphics::vulkan
{
    class display_surface;

    class physical_device final
    {
    public:
        physical_device(const vk::PhysicalDevice& _physical_device) noexcept;
        ~physical_device() noexcept;

    public:
        std::vector<vk::Bool32> get_surface_support(const display_surface* surface) const noexcept;

    public:
        device create_device(const display_surface* surface) const noexcept;

    private:
        void setup() noexcept;
        void identify_extensions() noexcept;
        void identify_properties() noexcept;
        void identify_queue_families() noexcept;
        void identify_features() noexcept;

    private:
        std::vector<vk::Bool32> get_surface_present_support(const display_surface* surface) const noexcept;
        std::uint32_t get_graphics_queue_family_index() const noexcept;
        std::uint32_t get_present_queue_family_index(const display_surface* surface) const noexcept;
        std::vector<vk::SurfaceFormatKHR> get_surface_formats(const display_surface* surface) const noexcept;
        vk::SurfaceFormatKHR get_preferred_surface_format(const display_surface* surface) const noexcept;

    private:
        std::uint32_t                          _extension_count;
        const char*                            _extension_names[64];
        vk::PhysicalDeviceProperties           _properties;
        vk::PhysicalDeviceFeatures             _features; 
        std::vector<vk::QueueFamilyProperties> _queue_families;
        vk::PhysicalDevice                     _physical_device;
    };
}

#endif
