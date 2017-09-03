// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_EXTENSIONS
#define SCENER_GRAPHICS_VULKAN_EXTENSIONS

#ifndef VULKAN_CREATE_DEBUG_REPORT_CALLBACK_EXT
#define VULKAN_CREATE_DEBUG_REPORT_CALLBACK_EXT
PFN_vkCreateDebugReportCallbackEXT fpCreateDebugReportCallbackEXT = nullptr;
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(
    VkInstance                                instance
  , const VkDebugReportCallbackCreateInfoEXT* pCreateInfo
  , const VkAllocationCallbacks*              pAllocator
  , VkDebugReportCallbackEXT*                 pCallback)
{
    return fpCreateDebugReportCallbackEXT(instance, pCreateInfo, pAllocator, pCallback);
}
#endif

#ifndef VULKAN_DESTROY_DEBUG_REPORT_CALLBACK_EXT
#define VULKAN_DESTROY_DEBUG_REPORT_CALLBACK_EXT
PFN_vkDestroyDebugReportCallbackEXT fpDestroyDebugReportCallbackEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(
    VkInstance                   instance
  , VkDebugReportCallbackEXT     callback
  , const VkAllocationCallbacks* pAllocator)
{
    fpDestroyDebugReportCallbackEXT(instance, callback, pAllocator);
}
#endif

#ifndef VULKAN_DEBUG_REPORT_CALLBACK_EXT
#define VULKAN_DEBUG_REPORT_CALLBACK_EXT
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
#endif

#endif
