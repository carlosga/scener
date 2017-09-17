// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_VULKAN_RESULT_HPP
#define SCENER_GRAPHICS_VULKAN_VULKAN_RESULT_HPP

namespace scener::graphics::vulkan
{
    inline void check_result(const vk::Result& result)
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
}

#endif // SCENER_GRAPHICS_VULKAN_VULKAN_RESULT_HPP
