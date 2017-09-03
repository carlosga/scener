#include "scener/graphics/vulkan/connection.hpp"

#include <ctime>
#include <iostream>
#include <iomanip>
#include <memory>

#include <gsl/gsl>

#include "scener/graphics/vulkan/extensions.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define VK_EXT_DEBUG_REPORT_NAME "VK_EXT_debug_report"
#define VK_LAYER_LUNARG_standard_validation "VK_LAYER_LUNARG_standard_validation"

namespace scener::graphics::vulkan
{
    std::uint32_t connection::debug_report_callback(
        VkDebugReportFlagsEXT      flags
      , VkDebugReportObjectTypeEXT objType
      , std::uint64_t              object
      , std::size_t                location
      , std::int32_t               code
      , const char*                pLayerPrefix
      , const char*                pMessage
      , void*                      userData)
    {
        std::string sflags;

        switch (flags)
        {
        case VK_DEBUG_REPORT_INFORMATION_BIT_EXT:
            sflags = "INFORMATION";
            break;
        case VK_DEBUG_REPORT_WARNING_BIT_EXT:
            sflags = "WARNING";
            break;
        case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT:
            sflags = "PERFORMANCE_WARNING";
            break;
        case VK_DEBUG_REPORT_ERROR_BIT_EXT:
            sflags = "ERROR";
            break;
        case VK_DEBUG_REPORT_DEBUG_BIT_EXT:
            sflags = "DEBUG";
            break;
        }

        std::time_t t = std::time(nullptr);

        std::cout << "(" << sflags << ") " << std::put_time(std::gmtime(&t), "%c %Z  ") << pMessage << std::endl;

        return 0;
    }

    connection::connection(std::uint32_t api_version) noexcept
        : _api_version      { api_version }
        , _instance         { }
        , _debug_callback   { }
        , _layer_names      { }
        , _extension_names  { }
        , _physical_devices { }
    {
    }

    connection::~connection() noexcept
    {
        if (_instance)
        {
            _instance.destroyDebugReportCallbackEXT(_debug_callback, nullptr);
            _instance.destroy(nullptr);
        }
    }

    const vk::Instance& connection::vulkan() const noexcept
    {
        return _instance;
    }

    std::uint32_t connection::api_version() const noexcept
    {
        return _api_version;
    }

    const std::vector<physical_device>& connection::physical_devices() const noexcept
    {
        return _physical_devices;
    }

    void connection::connect() noexcept
    {
        identify_validation_layers();
        identify_supported_extensions();
        initialize_vulkan();
        enable_debug_support();
        identify_physical_devices();
    }

    void connection::initialize_vulkan() noexcept
    {
        auto const app = vk::ApplicationInfo()
            .setPApplicationName("SCENER")
            .setApplicationVersion(1)
            .setPEngineName("SCENER 0.1.0")
            .setEngineVersion(1)
            .setApiVersion(_api_version);

        auto const inst_info = vk::InstanceCreateInfo()
            .setPApplicationInfo(&app)
            .setEnabledLayerCount(static_cast<std::uint32_t>(_layer_names.size()))
            .setPpEnabledLayerNames(_layer_names.data())
            .setEnabledExtensionCount(static_cast<std::uint32_t>(_extension_names.size()))
            .setPpEnabledExtensionNames(_extension_names.data());

        auto result = vk::createInstance(&inst_info, nullptr, &_instance);

        check_result(result);
    }

    void connection::enable_debug_support() noexcept
    {
        fpCreateDebugReportCallbackEXT  = (PFN_vkCreateDebugReportCallbackEXT)_instance.getProcAddr("vkCreateDebugReportCallbackEXT");
        fpDebugReportCallbackEXT        = (PFN_vkDebugReportCallbackEXT)_instance.getProcAddr("vkDebugReportCallbackEXT");
        fpDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)_instance.getProcAddr("vkDestroyDebugReportCallbackEXT");

        auto debug_callback_create_info = vk::DebugReportCallbackCreateInfoEXT()
            .setFlags(vk::DebugReportFlagBitsEXT::eDebug
                    | vk::DebugReportFlagBitsEXT::eInformation
                    | vk::DebugReportFlagBitsEXT::eWarning
                    | vk::DebugReportFlagBitsEXT::eError
                    | vk::DebugReportFlagBitsEXT::ePerformanceWarning)
            .setPfnCallback(debug_report_callback);

        auto result = _instance.createDebugReportCallbackEXT(&debug_callback_create_info, nullptr, &_debug_callback);

        check_result(result);
    }

    void connection::identify_validation_layers() noexcept
    {
        std::uint32_t instance_layer_count = 0;

        auto result = vk::enumerateInstanceLayerProperties(&instance_layer_count, nullptr);

        check_result(result);

        Ensures(instance_layer_count > 0);

        std::vector<vk::LayerProperties> instance_layers(instance_layer_count);
        result = vk::enumerateInstanceLayerProperties(&instance_layer_count, instance_layers.data());

        check_result(result);

        for (const auto& instance_layer : instance_layers)
        {
            if (!strcmp(VK_LAYER_LUNARG_standard_validation, instance_layer.layerName))
            {
                _layer_names.push_back(VK_LAYER_LUNARG_standard_validation);
            }
        }

        if (_layer_names.size() == 0)
        {
            throw std::runtime_error("vkEnumerateInstanceLayerProperties failed to find required validation layer.");
        }
    }

    void connection::identify_supported_extensions() noexcept
    {
        std::uint32_t instance_extension_count = 0;

        /* Look for instance extensions */
        vk::Bool32 surfaceExtFound         = VK_FALSE;
        vk::Bool32 platformSurfaceExtFound = VK_FALSE;
        vk::Bool32 debugReportFound        = VK_FALSE;

        auto result = vk::enumerateInstanceExtensionProperties(nullptr, &instance_extension_count, nullptr);
        check_result(result);

        if (instance_extension_count > 0)
        {
            std::vector<vk::ExtensionProperties> instance_extensions(instance_extension_count);

            result = vk::enumerateInstanceExtensionProperties(nullptr, &instance_extension_count, instance_extensions.data());

            check_result(result);

            for (const auto& instance_extension : instance_extensions)
            {
                if (!strcmp(VK_KHR_SURFACE_EXTENSION_NAME, instance_extension.extensionName))
                {
                    surfaceExtFound = 1;
                    _extension_names.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
                }
                if (!strcmp(VK_EXT_DEBUG_REPORT_NAME, instance_extension.extensionName))
                {
                    debugReportFound = 1;
                    _extension_names.push_back(VK_EXT_DEBUG_REPORT_NAME);
                }
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
        }

        if (!surfaceExtFound)
        {
            throw std::runtime_error("VK_KHR_SURFACE_EXTENSION_NAME extension not found.");
        }

        if (!platformSurfaceExtFound)
        {
            throw std::runtime_error("No surface extension found for the current platform (XLIB, XCB, WAYLAND, ...");
        }

        if (!debugReportFound)
        {
            throw std::runtime_error("VK_EXT_debug_report extension not found");
        }
    }

    void connection::identify_physical_devices() noexcept
    {
        std::uint32_t gpu_count = 0;
        auto result = _instance.enumeratePhysicalDevices(&gpu_count, nullptr);
        check_result(result);
        Ensures(gpu_count > 0);

        std::vector<vk::PhysicalDevice> physical_devices(gpu_count);
        result = _instance.enumeratePhysicalDevices(&gpu_count, physical_devices.data());
        check_result(result);

        _physical_devices.reserve(gpu_count);

        for (const auto& pd : physical_devices)
        {
            _physical_devices.push_back({ pd });
        }
    }
}
