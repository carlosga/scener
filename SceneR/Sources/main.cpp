// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// #include <SampleRenderer.hpp>

#include <Content/ContentManager.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Graphics/Model.hpp>

int main()
{
    using SceneR::Content::ContentManager;
    using SceneR::Framework::RendererServiceContainer;
    using SceneR::Graphics::Model;

    RendererServiceContainer container;
    ContentManager manager(container, u"/home/carlos/development/projects/cpp/opengl/scener/SceneR/Content");

    manager.LoadModel(u"WildCentaur");

    // SceneR::Sample::SampleRenderer renderer;
    //     renderer.Run();
    // renderer.Exit();

    return 0;
}
