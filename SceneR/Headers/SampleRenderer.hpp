// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SAMPLERENDERER_HPP
#define SAMPLERENDERER_HPP

#include <Framework/Renderer.hpp>

namespace SceneR
{
    namespace Framework
    {
        class RenderTime;
    }
}

namespace SceneR
{
    namespace Sample
    {
        class SampleRenderer : public SceneR::Framework::Renderer
        {
        public:
            SampleRenderer();

        protected:
            virtual void begin_run() override;
            virtual void draw(const SceneR::Framework::RenderTime &renderTime) override;
        };
    }
}

#endif  // SAMPLERENDERER_HPP
