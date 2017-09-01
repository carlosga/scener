// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/connection.hpp"
#include "scener/graphics/vulkan/platform.hpp"

using scener::graphics::vulkan::connection;
using scener::graphics::vulkan::display_surface;
using scener::graphics::vulkan::render_surface;

int main()
{
    connection connection(VK_MAKE_VERSION(1, 0, VK_HEADER_VERSION));

    connection.connect();

    // display surface (Wayland based)
    auto dsurface = display_surface();

    dsurface.create("SceneR", { 0, 0, 1900, 600 });

    // Physical device (GPU)
    auto pdevice  = connection.physical_devices()[0];

    // Render surface (Vulkan - Wayland based)
    auto rsurface = render_surface(connection, dsurface);

    // Logical device (Vulkan)
    auto ldevice = pdevice.create_logical_device(rsurface);

    // Create the Swap Chain
    ldevice.create_swap_chain(rsurface);

    dsurface.show();

    return 0;
}
