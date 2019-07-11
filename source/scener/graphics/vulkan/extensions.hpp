// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#include <vulkan/vulkan.h>
#include <iostream>
#include <iomanip>

#ifndef SCENER_GRAPHICS_VULKAN_EXTENSIONS
#define SCENER_GRAPHICS_VULKAN_EXTENSIONS

#ifndef VK_EXT_DEBUG_REPORT_NAME
#define VK_EXT_DEBUG_REPORT_NAME "VK_EXT_debug_report"
#endif
#ifndef VK_EXT_DEBUG_UTILS_NAME
#define VK_EXT_DEBUG_UTILS_NAME "VK_EXT_debug_utils"
#endif

#ifndef VK_LAYER_KHRONOS_validation
#define VK_LAYER_KHRONOS_validation "VK_LAYER_KHRONOS_validation"
#endif

#ifndef VULKAN_DEBUG_CALLBACK
#define VULKAN_DEBUG_CALLBACK
VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity
                                            , VkDebugUtilsMessageTypeFlagsEXT             messageType
                                            , const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData
                                            , void*                                       pUserData)
{
    if (pUserData != nullptr)
    {
        std::string sflags;

        switch (messageSeverity)
        {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            sflags = "INFORMATION";
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            sflags = "WARNING";
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            sflags = "ERROR";
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            sflags = "DEBUG";
            break;
        }

        std::time_t t = std::time(nullptr);
        std::cout << "(" << sflags << ") " << std::put_time(std::gmtime(&t), "%c %Z  ") << pUserData << std::endl;
    }

    return 0;
}
#endif

#endif

//#ifndef VULKAN_CREATE_DEBUG_DEBUG_UTILS_MESSENGER_EXT
//#define VULKAN_CREATE_DEBUG_DEBUG_UTILS_MESSENGER_EXT
//VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
//{
//    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
//    if (func != nullptr)
//    {
//        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
//    }
//    else
//    {
//        return VK_ERROR_EXTENSION_NOT_PRESENT;
//    }
//}



//#endif

//#ifndef VULKAN_DESTROY_DEBUG_DEBUG_UTILS_MESSENGER_EXT
//#define VULKAN_DESTROY_DEBUG_DEBUG_UTILS_MESSENGER_EXT
//void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
//{
//    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
//    if (func != nullptr)
//    {
//        func(instance, debugMessenger, pAllocator);
//    }
//}
//#endif

////#ifndef VULKAN_DEBUG_REPORT_CALLBACK_EXT
////#define VULKAN_DEBUG_REPORT_CALLBACK_EXT
////PFN_vkDebugReportCallbackEXT fpDebugReportCallbackEXT = nullptr;
////VKAPI_ATTR std::uint32_t VKAPI_CALL vkDebugReportCallbackEXT(
////    VkDebugReportFlagsEXT       flags
////  , VkDebugReportObjectTypeEXT  objectType
////  , std::uint64_t               object
////  , std::size_t                 location
////  , std::int32_t                messageCode
////  , const char*                 pLayerPrefix
////  , const char*                 pMessage
////  , void*                       userData)
////{
////    return fpDebugReportCallbackEXT(flags, objectType, object, location, messageCode, pLayerPrefix, pMessage, userData);
////}
////#endif

//#endif
