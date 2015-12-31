// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SkeletalAnimation/SampleRenderer.hpp"

int main()
{
    SkeletalAnimation::SampleRenderer renderer;

    renderer.run();

    renderer.exit();

    return 0;
}
