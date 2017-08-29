#include "scener/graphics/vulkan/connection.hpp"

#include <algorithm>
#include <cstdint>

#include <gsl/gsl>

#include "scener/graphics/vulkan/vulkan_result.hpp"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

namespace scener::graphics::vulkan
{
    connection::connection(std::uint32_t api_version) noexcept
        : _api_version              { api_version }
        , _instance                 { }
        , _physical_devices         { }
        , _enabled_extension_count  { 0 }
        , _extension_names          { nullptr }
        , _enabled_layer_count      { 0 }
        , _enabled_layers           { nullptr }
    {
    }

    connection::~connection() noexcept
    {
        if (_instance)
        {
            _instance.destroy(nullptr);
        }
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
        identify_physical_devices();
    }

    display_surface connection::create_surface(std::uint32_t width, std::uint32_t height) noexcept
    {
        display_surface surface { &_instance };
        surface.create(width, height);

        return surface;
    }

    void connection::initialize_vulkan() noexcept
    {
        auto const app = vk::ApplicationInfo()
            .setPApplicationName("")
            .setApplicationVersion(1)
            .setPEngineName("")
            .setEngineVersion(1)
            .setApiVersion(_api_version);

        auto const inst_info = vk::InstanceCreateInfo()
            .setPApplicationInfo(&app)
            .setEnabledLayerCount(_enabled_layer_count)
            .setPpEnabledLayerNames(_enabled_layers)
            .setEnabledExtensionCount(_enabled_extension_count)
            .setPpEnabledExtensionNames(_extension_names);

        auto result = vk::createInstance(&inst_info, nullptr, &_instance);
        check_result(result);
    }

    void connection::identify_validation_layers() noexcept
    {
        vk::Bool32         validation_found                  = VK_FALSE;
        std::uint32_t      instance_layer_count              = 0;
        std::uint32_t      validation_layer_count            = 0;
        const char* const* instance_validation_layers        = nullptr;
        const char* const  instance_validation_layers_alt1[] = { "VK_LAYER_LUNARG_standard_validation" };
        const char* const  instance_validation_layers_alt2[] = 
        {
            "VK_LAYER_GOOGLE_threading"
          , "VK_LAYER_LUNARG_parameter_validation"
          , "VK_LAYER_LUNARG_object_tracker"
          , "VK_LAYER_LUNARG_core_validation"
          , "VK_LAYER_LUNARG_swapchain"
          , "VK_LAYER_GOOGLE_unique_objects"
        };

        auto result = vk::enumerateInstanceLayerProperties(&instance_layer_count, nullptr);
        check_result(result);

        instance_validation_layers = instance_validation_layers_alt1;
        if (instance_layer_count > 0) 
        {
            std::vector<vk::LayerProperties> instance_layers(instance_layer_count);
            result = vk::enumerateInstanceLayerProperties(&instance_layer_count, instance_layers.data());
            check_result(result);

            validation_found = check_layers(ARRAY_SIZE(instance_validation_layers_alt1), instance_validation_layers,
                                            instance_layer_count, instance_layers.data());
            if (validation_found) 
            {
                _enabled_layer_count   = ARRAY_SIZE(instance_validation_layers_alt1);
                _enabled_layers[0]     = "VK_LAYER_LUNARG_standard_validation";
                validation_layer_count = 1;
            }
            else 
            {
                // use alternative set of validation layers
                instance_validation_layers = instance_validation_layers_alt2;
                _enabled_layer_count       = ARRAY_SIZE(instance_validation_layers_alt2);
                validation_found           = check_layers(ARRAY_SIZE(instance_validation_layers_alt2), instance_validation_layers,
                                                instance_layer_count, instance_layers.data());
                validation_layer_count = ARRAY_SIZE(instance_validation_layers_alt2);

                for (std::uint32_t i = 0; i < validation_layer_count; i++) 
                {
                    _enabled_layers[i] = instance_validation_layers[i];
                }
            }
        }

        if (!validation_found) 
        {
            throw std::runtime_error("vkEnumerateInstanceLayerProperties failed to find required validation layer.");
        }
    }

    void connection::identify_supported_extensions() noexcept
    {
        uint32_t instance_extension_count = 0;

        /* Look for instance extensions */
        vk::Bool32 surfaceExtFound         = VK_FALSE;
        vk::Bool32 platformSurfaceExtFound = VK_FALSE;
        memset(_extension_names, 0, sizeof(_extension_names));

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
                    _extension_names[_enabled_extension_count++] = VK_KHR_SURFACE_EXTENSION_NAME;
                }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
                if (!strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, instance_extension.extensionName)) 
                {
                    platformSurfaceExtFound = 1;
                    _extension_names[_enabled_extension_count++] = VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
                }
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
                if (!strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, instance_extension.extensionName)) 
                {
                    platformSurfaceExtFound = 1;
                    _extension_names[_enabled_extension_count++] = VK_KHR_XLIB_SURFACE_EXTENSION_NAME;
                }
#elif defined(VK_USE_PLATFORM_XCB_KHR)
                if (!strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, instance_extension.extensionName)) 
                {
                    platformSurfaceExtFound = 1;
                    _extension_names[_enabled_extension_count++] = VK_KHR_XCB_SURFACE_EXTENSION_NAME;
                }
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
                if (!strcmp(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME, instance_extension.extensionName)) 
                {
                    platformSurfaceExtFound = 1;
                    _extension_names[_enabled_extension_count++] = VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME;
                }
#elif defined(VK_USE_PLATFORM_MIR_KHR)
#elif defined(VK_USE_PLATFORM_DISPLAY_KHR)
                if (!strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, instance_extension.extensionName)) 
                {
                    platformSurfaceExtFound = 1;
                    _extension_names[_enabled_extension_count++] = VK_KHR_DISPLAY_EXTENSION_NAME;
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
    }

    void connection::identify_physical_devices() noexcept
    {
        std::uint32_t gpu_count;
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

    vk::Bool32 connection::check_layers(uint32_t check_count
                                      , char const *const *const check_names
                                      , uint32_t layer_count
                                      , vk::LayerProperties *layers) 
    {
        for (std::uint32_t i = 0; i < check_count; i++) 
        {
            vk::Bool32 found = VK_FALSE;
            for (std::uint32_t j = 0; j < layer_count; j++) 
            {
                if (!strcmp(check_names[i], layers[j].layerName)) 
                {
                    found = VK_TRUE;
                    break;
                }
            }
            if (!found) 
            {
                return 0;
            }
        }
        return VK_TRUE;
    }
}
