// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/connection.hpp"
#include "scener/graphics/vulkan/display_surface.hpp"

using scener::graphics::vulkan::connection;
using scener::graphics::vulkan::display_surface;

int main()
{    
    {
        connection connection(VK_MAKE_VERSION(1, 0, 0));

        connection.connect();
        
        auto surface = connection.create_surface(1600, 1900);
        auto pdevice = connection.physical_devices()[0];
        auto device  = pdevice.create_device(&surface);

        surface.show();
    }

    return 0;
}
