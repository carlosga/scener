// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "skeletal-animation/sample_renderer.hpp"

int main()
{
    skeletal::animation::sample_renderer renderer;

    renderer.run();
    renderer.exit();

    return 0;
}
