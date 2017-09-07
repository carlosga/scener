#include "scener/graphics/vulkan/adapter.hpp"

#include <algorithm>
#include <ctime>
#include <iostream>
#include <iomanip>

#include "scener/graphics/vulkan/extensions.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"

namespace scener::graphics::vulkan
{
    std::uint32_t adapter::debug_report_callback(
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

    adapter::adapter() noexcept
        : _instance         { }
        , _debug_callback   { }
        , _layer_names      { }
        , _extension_names  { }
        , _physical_devices { }
    {
        create();
    }

    adapter::~adapter() noexcept
    {
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

    void adapter::create() noexcept
    {
        identify_validation_layers();
        identify_supported_extensions();
        initialize_vulkan();
        enable_debug_support();
        identify_physical_devices();
    }

    void adapter::initialize_vulkan() noexcept
    {
        auto const app = vk::ApplicationInfo()
            .setPApplicationName("SCENER")
            .setApplicationVersion(1)
            .setPEngineName("SCENER 0.1.0")
            .setEngineVersion(1)
            .setApiVersion(VK_MAKE_VERSION(1, 0, VK_HEADER_VERSION));

        auto const inst_info = vk::InstanceCreateInfo()
            .setPApplicationInfo(&app)
            .setEnabledLayerCount(static_cast<std::uint32_t>(_layer_names.size()))
            .setPpEnabledLayerNames(_layer_names.data())
            .setEnabledExtensionCount(static_cast<std::uint32_t>(_extension_names.size()))
            .setPpEnabledExtensionNames(_extension_names.data());

        auto result = vk::createInstance(&inst_info, nullptr, &_instance);

        check_result(result);
    }

    void adapter::enable_debug_support() noexcept
    {
        fpCreateDebugReportCallbackEXT  = (PFN_vkCreateDebugReportCallbackEXT)_instance
            .getProcAddr("vkCreateDebugReportCallbackEXT");

        fpDebugReportCallbackEXT        = (PFN_vkDebugReportCallbackEXT)_instance
            .getProcAddr("vkDebugReportCallbackEXT");

        fpDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)_instance
            .getProcAddr("vkDestroyDebugReportCallbackEXT");

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

    void adapter::identify_validation_layers() noexcept
    {
        auto layers = vk::enumerateInstanceLayerProperties();

        const auto it = std::find_if(layers.begin(), layers.end(), [] (const vk::LayerProperties& layer) -> bool
        {
            return !strcmp(VK_LAYER_LUNARG_standard_validation, layer.layerName);
        });

        if (it != layers.end())
        {
            _layer_names.push_back(VK_LAYER_LUNARG_standard_validation);
        }

        if (_layer_names.size() == 0)
        {
            throw std::runtime_error("vkEnumerateInstanceLayerProperties failed to find required validation layer.");
        }
    }

    void adapter::identify_supported_extensions() noexcept
    {
        /* Look for instance extensions */
        vk::Bool32 surfaceExtFound         = VK_FALSE;
        vk::Bool32 platformSurfaceExtFound = VK_FALSE;
        vk::Bool32 debugReportFound        = VK_FALSE;

        auto instance_extensions = vk::enumerateInstanceExtensionProperties(nullptr);

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
