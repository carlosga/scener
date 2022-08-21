// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHIcS_VULKAN_PHYSICAL_DEVICE_HPP
#define SCENER_GRAPHIcS_VULKAN_PHYSICAL_DEVICE_HPP

#include <cstdint>
#include <vector>

#include <vulkan/vulkan.hpp>

namespace scener::graphics
{
    struct viewport;
}

namespace scener::graphics::vulkan
{
    class render_surface;
    class logical_device;

    class physical_device final
    {
    public:
        physical_device(const vk::Instance& instance, const vk::PhysicalDevice& physical_device) noexcept;
        ~physical_device() noexcept;

    public:
        const vk::PhysicalDeviceProperties& properties() const noexcept;
        const vk::PhysicalDeviceMemoryProperties& memory_properties() const noexcept;
        const vk::PhysicalDeviceFeatures& features() const noexcept;
        bool has_swapchain_support() const noexcept;
        bool has_graphics_queue() const noexcept;
        bool is_integrated_gpu() const noexcept;
        bool is_discrete_gpu() const noexcept;
        bool is_virtual_gpu() const noexcept;
        bool is_cpu_gpu() const noexcept;

    public:
        std::unique_ptr<logical_device> create_logical_device(const render_surface& surface
                                                            , const graphics::viewport& viewport) const noexcept;

    private:
        void identify_layers() noexcept;
        void identify_extensions() noexcept;
        void identify_properties() noexcept;
        void identify_queue_families() noexcept;
        void identify_features() noexcept;

    private:
        vk::SurfaceCapabilitiesKHR get_surface_capabilities(const render_surface& surface) const noexcept;
        std::vector<vk::Bool32> get_surface_present_support(const render_surface& surface) const noexcept;
        std::uint32_t get_graphics_queue_family_index() const noexcept;
        std::uint32_t get_present_queue_family_index(const render_surface& surface) const noexcept;
        std::vector<vk::SurfaceFormatKHR> get_surface_formats(const render_surface& surface) const noexcept;
        vk::SurfaceFormatKHR get_preferred_surface_format(const render_surface& surface) const noexcept;
        vk::PresentModeKHR get_present_mode(const render_surface& surface) const noexcept;
        vk::FormatProperties get_format_properties(const vk::Format& format) const noexcept;
        vk::Format get_preferred_depth_format(
            const std::vector<vk::Format>& formats
          , const vk::ImageTiling&         tiling
          , const vk::FormatFeatureFlags&  features) const noexcept;

    private:
        std::vector<const char*>               _layer_names;
        std::vector<const char*>               _extension_names;
        vk::PhysicalDeviceProperties           _properties;
        vk::PhysicalDeviceMemoryProperties     _memory_properties;
        vk::PhysicalDeviceFeatures             _features;
        std::vector<vk::QueueFamilyProperties> _queue_families;
        vk::Instance                           _instance;
        vk::PhysicalDevice                     _physical_device;
    };
}

#endif
