// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef VK_ENABLE_DEBUG_SUPPORT
//#define VK_ENABLE_DEBUG_SUPPORT
#endif

#include "scener/graphics/vulkan/adapter.hpp"

#include <algorithm>

#include "scener/graphics/vulkan/extensions.hpp"
#include "scener/graphics/vulkan/physical_device.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"

namespace scener::graphics::vulkan
{
    adapter::adapter() noexcept
        : _instance         { }
        , _layer_names      { }
        , _extension_names  { }
        , _physical_devices { }
        , _dispatcher       { }
        , _debug_messenger  { }
    {
        identify_validation_layers();
        identify_supported_extensions();
        initialize_vulkan();
        enable_debug_support();
        identify_physical_devices();
    }

    adapter::~adapter() noexcept
    {        
#ifdef VK_ENABLE_DEBUG_SUPPORT
        _instance.destroyDebugUtilsMessengerEXT(_debug_messenger, nullptr, _dispatcher);
#endif
        _instance.destroy(nullptr);
    }

    const vk::Instance& adapter::instance() const noexcept
    {
        return _instance;
    }

    const std::vector<physical_device>& adapter::physical_devices() const noexcept
    {
        return _physical_devices;
    }

    const physical_device& adapter::get_physical_device(std::uint32_t device_id) const noexcept
    {
        auto it = std::find_if(_physical_devices.begin(), _physical_devices.end(),
                               [device_id](const physical_device& device) -> bool
                               {
                                   return device.properties().deviceID == device_id;
                               });

        if (it != _physical_devices.end())
        {
            return *it;
        }

        throw std::runtime_error("Unknown physical device");
    }

    void adapter::initialize_vulkan() noexcept
    {
        auto const app = vk::ApplicationInfo()
            .setPApplicationName("SCENER")
            .setApplicationVersion(1)
            .setPEngineName("SCENER 0.1.0")
            .setEngineVersion(1)
            .setApiVersion(VK_MAKE_VERSION(1, 1, VK_HEADER_VERSION));

        auto const inst_info = vk::InstanceCreateInfo()
            .setPApplicationInfo(&app)
            .setEnabledLayerCount(static_cast<std::uint32_t>(_layer_names.size()))
            .setPpEnabledLayerNames(_layer_names.data())
            .setEnabledExtensionCount(static_cast<std::uint32_t>(_extension_names.size()))
            .setPpEnabledExtensionNames(_extension_names.data());

        auto result = vk::createInstance(&inst_info, nullptr, &_instance);

        check_result(result);

        _dispatcher.init(_instance);
    }

    void adapter::enable_debug_support() noexcept
    {
#if defined(VK_ENABLE_DEBUG_SUPPORT)
        auto create_info = vk::DebugUtilsMessengerCreateInfoEXT()
            .setMessageSeverity(vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
                              | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo
                              | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
                              | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError)
            .setMessageType(vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
                          | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
                          | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance)
            .setPfnUserCallback(debug_callback);

        auto result = _instance.createDebugUtilsMessengerEXT(&create_info, nullptr, &_debug_messenger, _dispatcher);

        check_result(result);
#endif
    }

    void adapter::identify_validation_layers() noexcept
    {
#if defined(VK_ENABLE_DEBUG_SUPPORT)
        auto layers = vk::enumerateInstanceLayerProperties();

        const auto it = std::find_if(layers.begin(), layers.end(), [] (const vk::LayerProperties& layer) -> bool
        {
            return !strcmp(VK_LAYER_KHRONOS_VALIDATION, layer.layerName);
        });

        if (it != layers.end())
        {
            _layer_names.push_back(VK_LAYER_KHRONOS_VALIDATION);
        }

        if (_layer_names.size() == 0)
        {
            throw std::runtime_error("vkEnumerateInstanceLayerProperties failed to find required validation layer.");
        }
#endif
    }

    void adapter::identify_supported_extensions() noexcept
    {
        /* Look for instance extensions */
        vk::Bool32 surfaceExtFound         = VK_FALSE;
        vk::Bool32 platformSurfaceExtFound = VK_FALSE;
        vk::Bool32 debugReportFound        = VK_FALSE;
        vk::Bool32 debugUtilsFound         = VK_FALSE;

        const auto instance_extensions = vk::enumerateInstanceExtensionProperties(nullptr);

        for (const auto& instance_extension : instance_extensions)
        {
            if (!strcmp(VK_KHR_SURFACE_EXTENSION_NAME, instance_extension.extensionName))
            {
                surfaceExtFound = 1;
                _extension_names.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
            }
#if defined(VK_ENABLE_DEBUG_SUPPORT)
            if (!strcmp(VK_EXT_DEBUG_REPORT_NAME, instance_extension.extensionName))
            {
                debugReportFound = 1;
                _extension_names.push_back(VK_EXT_DEBUG_REPORT_NAME);
            }
            if (!strcmp(VK_EXT_DEBUG_UTILS_NAME, instance_extension.extensionName))
            {
                debugUtilsFound = 1;
                _extension_names.push_back(VK_EXT_DEBUG_UTILS_NAME);
            }
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
            if (!strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, instance_extension.extensionName))
            {
                platformSurfaceExtFound = 1;
                _extension_names.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
            }
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
            if (!strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, instance_extension.extensionName))
            {
                platformSurfaceExtFound = 1;
                _extension_names.push_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
            }
#elif defined(VK_USE_PLATFORM_XCB_KHR)
            if (!strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, instance_extension.extensionName))
            {
                platformSurfaceExtFound = 1;
                _extension_names.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
            }
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
            if (!strcmp(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME, instance_extension.extensionName))
            {
                platformSurfaceExtFound = 1;
                _extension_names.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
            }
#elif defined(VK_USE_PLATFORM_MIR_KHR)
#elif defined(VK_USE_PLATFORM_DISPLAY_KHR)
            if (!strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, instance_extension.extensionName))
            {
                platformSurfaceExtFound = 1;
                _extension_names.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);
            }
#endif
        }

        if (!surfaceExtFound)
        {
            throw std::runtime_error("VK_KHR_SURFACE_EXTENSION_NAME extension not found.");
        }

        if (!platformSurfaceExtFound)
        {
            throw std::runtime_error("No surface extension found for the current platform (XLIB, XCB, WAYLAND, ...");
        }
#if defined(VK_ENABLE_DEBUG_SUPPORT)
        if (!debugReportFound)
        {
            throw std::runtime_error("VK_EXT_debug_report extension not found");
        }

        if (!debugUtilsFound)
        {
            throw std::runtime_error("VK_EXT_debug_utils extension not found");
        }
#endif
    }

    void adapter::identify_physical_devices() noexcept
    {
        auto physical_devices = _instance.enumeratePhysicalDevices();

        _physical_devices.reserve(physical_devices.size());

        for (const auto& pd : physical_devices)
        {
            _physical_devices.push_back({ pd });
        }
    }
}
