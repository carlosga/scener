// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SKELETAL_ANIMATION_SAMPLERENDERER_HPP
#define SKELETAL_ANIMATION_SAMPLERENDERER_HPP

#include <scener/graphics/renderer.hpp>

namespace scener { namespace graphics { struct steptime; } }

namespace skeletal_animation {

class SampleRenderer : public scener::graphics::renderer
{
public:
    SampleRenderer() noexcept;
    ~SampleRenderer() override = default;

protected:
    void begin_run() noexcept override;
    void load_content() noexcept override;
    void draw(const scener::graphics::steptime& time) noexcept override;
};

}

#endif // SKELETAL_ANIMATION_SAMPLERENDERER_HPP
