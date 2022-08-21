// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_CONNECTION_HPP
#define SCENER_GRAPHICS_VULKAN_CONNECTION_HPP

#include <cstdint>
#include <vector>

#include <vulkan/vulkan.hpp>

namespace scener::graphics::vulkan
{
    class physical_device;

    class adapter final
    {
    public:
        adapter() noexcept;
        ~adapter() noexcept;

    public:
        const vk::Instance& instance() const noexcept;
        const std::vector<physical_device>& physical_devices() const noexcept;
        const physical_device& get_physical_device(std::uint32_t device_id) const noexcept;

    private:
        void identify_validation_layers() noexcept;
        void identify_supported_extensions() noexcept;
        void initialize_vulkan() noexcept;
        void enable_debug_support() noexcept;
        void identify_physical_devices() noexcept;

    private:
        vk::Instance                 _instance;
        std::vector<const char*>     _layer_names;
        std::vector<const char*>     _extension_names;
        std::vector<physical_device> _physical_devices;
        //vk::DispatchLoaderDynamic    _dispatcher;
        vk::DebugUtilsMessengerEXT   _debug_messenger;
    };
}

#endif
