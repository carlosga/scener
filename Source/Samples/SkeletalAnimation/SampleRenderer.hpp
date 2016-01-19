// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SKELETAL_ANIMATION_SAMPLERENDERER_HPP
#define SKELETAL_ANIMATION_SAMPLERENDERER_HPP

#include <SceneR/Graphics/Renderer.hpp>

namespace SceneR { namespace Graphics { struct StepTime; } }

namespace SkeletalAnimation {

class SampleRenderer : public SceneR::Graphics::Renderer
{
public:
    SampleRenderer() noexcept;
    ~SampleRenderer() override = default;

protected:
    void begin_run() noexcept override;
    void load_content() noexcept override;
    void draw(const SceneR::Graphics::StepTime &renderTime) noexcept override;
};

}

#endif // SKELETAL_ANIMATION_SAMPLERENDERER_HPP
