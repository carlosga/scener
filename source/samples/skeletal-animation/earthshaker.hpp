// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SKELETAL_ANIMATION_EARTHSHAKER_HPP
#define SKELETAL_ANIMATION_EARTHSHAKER_HPP

#include <memory>

#include <scener/graphics/drawable_component.hpp>
#include <scener/math/matrix.hpp>

namespace scener::graphics
{
    class  model;
    struct steptime;
}

namespace skeletal::animation
{
    class sample_renderer;

    class earthshaker : public scener::graphics::drawable_component
    {
    public:
        earthshaker(sample_renderer* renderer) noexcept;
        ~earthshaker() override = default;

    public:
        void initialize() noexcept override;
        void update(const scener::graphics::steptime& time) noexcept override;
        void draw() noexcept override;

    protected:
        void load_content() noexcept override;
        void unload_content() noexcept override;

    private:
        std::shared_ptr<scener::graphics::model> _model;
        scener::math::matrix4                    _world;
    };
}

#endif // SKELETAL_ANIMATION_EARTHSHAKER_HPP
