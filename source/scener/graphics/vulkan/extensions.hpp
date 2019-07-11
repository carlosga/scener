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

#ifndef VK_LAYER_KHRONOS_VALIDATION
#define VK_LAYER_KHRONOS_VALIDATION "VK_LAYER_KHRONOS_validation"
#endif

#ifndef VK_EXT_DEBUG_REPORT_NAME
#define VK_EXT_DEBUG_REPORT_NAME "VK_EXT_debug_report"
#endif
#ifndef VK_EXT_DEBUG_UTILS_NAME
#define VK_EXT_DEBUG_UTILS_NAME "VK_EXT_debug_utils"
#endif

#ifndef VULKAN_DEBUG_CALLBACK
#define VULKAN_DEBUG_CALLBACK
VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity
                                            , VkDebugUtilsMessageTypeFlagsEXT             messageType
                                            , const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData
                                            , void*                                       pUserData)
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
    std::cout << "(" << sflags << ") " << std::put_time(std::gmtime(&t), "%c %Z  ") << pCallbackData->pMessageIdName << " - " << pCallbackData->pMessage << std::endl;

    return 0;
}
#endif

#endif
