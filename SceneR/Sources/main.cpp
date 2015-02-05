// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <SampleRenderer.hpp>

int main()
{
    SceneR::Sample::SampleRenderer renderer;

    renderer.Run();

    renderer.Exit();

    return 0;
}
