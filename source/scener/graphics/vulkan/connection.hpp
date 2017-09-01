#ifndef SCENER_GRAPHICS_VULKAN_CONNECTION_HPP
#define SCENER_GRAPHICS_VULKAN_CONNECTION_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <vulkan/vulkan.hpp>

#include "scener/graphics/vulkan/display_surface.hpp"
#include "scener/graphics/vulkan/physical_device.hpp"

PFN_vkCreateDebugReportCallbackEXT fpCreateDebugReportCallbackEXT = nullptr;
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(
    VkInstance                                instance
  , const VkDebugReportCallbackCreateInfoEXT* pCreateInfo
  , const VkAllocationCallbacks*              pAllocator
  , VkDebugReportCallbackEXT*                 pCallback)
{
    return fpCreateDebugReportCallbackEXT(instance, pCreateInfo, pAllocator, pCallback);
}

PFN_vkDestroyDebugReportCallbackEXT fpDestroyDebugReportCallbackEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(
    VkInstance                   instance
  , VkDebugReportCallbackEXT     callback
  , const VkAllocationCallbacks* pAllocator)
{
    fpDestroyDebugReportCallbackEXT(instance, callback, pAllocator);
}

PFN_vkDebugReportCallbackEXT fpDebugReportCallbackEXT = nullptr;
VKAPI_ATTR std::uint32_t VKAPI_CALL vkDebugReportCallbackEXT(
    VkDebugReportFlagsEXT       flags
  , VkDebugReportObjectTypeEXT  objectType
  , std::uint64_t               object
  , std::size_t                 location
  , std::int32_t                messageCode
  , const char*                 pLayerPrefix
  , const char*                 pMessage
  , void*                       userData)
{
    return fpDebugReportCallbackEXT(flags, objectType, object, location, messageCode, pLayerPrefix, pMessage, userData);
}

namespace scener::graphics::vulkan
{
    class connection final
    {
        static std::uint32_t debug_report_callback(
            VkDebugReportFlagsEXT      flags
          , VkDebugReportObjectTypeEXT objType
          , std::uint64_t              object
          , std::size_t                location
          , std::int32_t               code
          , const char*                pLayerPrefix
          , const char*                pMessage
          , void*                      userData);

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
        vk::DebugReportCallbackEXT   _debug_callback;
        std::vector<physical_device> _physical_devices;
        std::uint32_t                _enabled_extension_count;
        const char*                  _extension_names[64];
        std::uint32_t                _enabled_layer_count;
        const char*                  _enabled_layers[64];
    };
}

#endif
