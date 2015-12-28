// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SKELETAL_ANIMATION_SAMPLERENDERER_HPP
#define SKELETAL_ANIMATION_SAMPLERENDERER_HPP

#include <SceneR/Graphics/Renderer.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class StepTime;
    }
}

namespace SceneR
{
    namespace Sample
    {
        class SampleRenderer : public SceneR::Graphics::Renderer
        {
        public:
            SampleRenderer();
            virtual ~SampleRenderer() = default;

        protected:
            virtual void begin_run() override;
            virtual void load_content() override;
            virtual void draw(const SceneR::Graphics::StepTime &renderTime) override;
        };
    }
}

#endif // SKELETAL_ANIMATION_SAMPLERENDERER_HPP
