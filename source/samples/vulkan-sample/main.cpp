// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/adapter.hpp"
#include "scener/graphics/vulkan/image_options.hpp"
#include "scener/graphics/vulkan/image.hpp"
#include "scener/graphics/vulkan/memory_allocator.hpp"
#include "scener/graphics/vulkan/physical_device.hpp"
#include "scener/graphics/vulkan/logical_device.hpp"
#include "scener/graphics/vulkan/surface.hpp"
#include "scener/graphics/texture_target.hpp"

using scener::graphics::vulkan::adapter;
using scener::graphics::vulkan::display_surface;
using scener::graphics::vulkan::image_options;
using scener::graphics::vulkan::image;
using scener::graphics::vulkan::render_surface;
using scener::graphics::texture_target;

int main()
{
    // display surface (Wayland/XCB/...)
    auto dsurface = display_surface("SceneR", { 0, 0, 1600, 900 });

    // Vulkan instance
    auto instance = adapter();

    // Render surface (Vulkan - Wayland based)
    auto rsurface = render_surface(&instance, &dsurface);

    // Physical device (GPU)
    auto pdevice = instance.physical_devices()[0];

    // Logical device (Vulkan)
    auto ldevice = pdevice.create_logical_device(rsurface);

    // Create the Swap Chain
    ldevice.create_swap_chain(rsurface);

    // Try to allocate an image
    image_options options = {
        vk::ImageUsageFlagBits::eColorAttachment
      , texture_target::texture_2d
      , { 1600, 900, 1 }
      , 1
    };

    auto image = ldevice.create_image(options);

    // Record present command buffers
    //ldevice.record_command_buffers();

    // Create the render targets
    // ldevice.create_render_targets(dsurface.rect().size());

    return 0;
}
