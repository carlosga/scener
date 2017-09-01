// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/connection.hpp"
#include "scener/graphics/vulkan/display_surface.hpp"

using scener::graphics::vulkan::connection;
using scener::graphics::vulkan::display_surface;

int main()
{    
    connection connection(VK_MAKE_VERSION(1, 0, VK_HEADER_VERSION));

    connection.connect();
    
    auto pdevice = connection.physical_devices()[0];
    auto surface = connection.create_surface(1600, 900);
    auto ldevice = pdevice.create_logical_device(&surface);

    ldevice.create_swap_chain(&surface);

    surface.show();

    return 0;
}
