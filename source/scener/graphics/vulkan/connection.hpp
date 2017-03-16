#ifndef SCENER_GRAPHICS_VULKAN_CONNECTION_HPP
#define SCENER_GRAPHICS_VULKAN_CONNECTION_HPP

#include <memory>
#include <string>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <cstdint>

#include "scener/graphics/vulkan/display_surface.hpp"
#include "scener/graphics/vulkan/physical_device.hpp"

namespace scener::graphics::vulkan
{
    inline void ensures(const vk::Result& result)
    {
        switch (result)
        {        
        case vk::Result::eSuccess:
            return;

        case vk::Result::eNotReady:
            throw std::runtime_error("not ready");

        case vk::Result::eTimeout:
            throw std::runtime_error("timeout");

        case vk::Result::eIncomplete:
            throw std::runtime_error("incomplete");

        case vk::Result::eErrorOutOfHostMemory:
            throw std::runtime_error("out of host memory");

        case vk::Result::eErrorOutOfDeviceMemory:
            throw std::runtime_error("out of device memory");

        case vk::Result::eErrorInitializationFailed:
            throw std::runtime_error("initialization failed");

        case vk::Result::eErrorDeviceLost:
            throw std::runtime_error("device lost");

        case vk::Result::eErrorMemoryMapFailed:
            throw std::runtime_error("memory map failed");

        case vk::Result::eErrorLayerNotPresent:
            throw std::runtime_error("layer not present");

        case vk::Result::eErrorExtensionNotPresent:
            throw std::runtime_error("Cannot find a specified extension library.\nMake sure your layers path is set appropriately.\n");

        case vk::Result::eErrorFeatureNotPresent:
            throw std::runtime_error("feature not present");

        case vk::Result::eErrorIncompatibleDriver:
            throw std::runtime_error("Cannot find a compatible Vulkan installable client driver (ICD).");

        case vk::Result::eErrorTooManyObjects:
            throw std::runtime_error("too many objects");

        case vk::Result::eErrorFormatNotSupported:
            throw std::runtime_error("format not supported");

        case vk::Result::eErrorSurfaceLostKHR:
            throw std::runtime_error("surface lost (KHR)");

        case vk::Result::eErrorNativeWindowInUseKHR:
            throw std::runtime_error("native window in use (KHR)");

        case vk::Result::eErrorOutOfDateKHR:
            throw std::runtime_error("out of date (KHR)");

        case vk::Result::eErrorIncompatibleDisplayKHR:
            throw std::runtime_error("incompatible display (KHR)");

        case vk::Result::eErrorValidationFailedEXT:
            throw std::runtime_error("validation failed (EXT)");

        default:
            throw std::runtime_error("unknown error");
        }
    }
    
    class connection final
    {
    public:
        connection(std::uint32_t api_version) noexcept;
        ~connection() noexcept;

    public:
        std::uint32_t api_version() const noexcept;
        const std::vector<physical_device>& physical_devices() const noexcept;

    public:
        void connect() noexcept;
        display_surface create_surface(std::uint32_t width, std::uint32_t height) noexcept;

    private:
        void identify_validation_layers() noexcept;
        void identify_supported_extensions() noexcept;
        void initialize_vulkan() noexcept;
        void identify_physical_devices() noexcept;

    private:
        vk::Bool32 check_layers(uint32_t                 check_count
                              , char const *const *const check_names
                              , uint32_t                 layer_count
                              , vk::LayerProperties*     layers);

    private:
        std::uint32_t                _api_version;
        vk::Instance                 _instance;
        std::vector<physical_device> _physical_devices;
        std::uint32_t                _enabled_extension_count;
        const char*                  _extension_names[64];
        std::uint32_t                _enabled_layer_count;
        const char*                  _enabled_layers[64];
    };
}

#endif
