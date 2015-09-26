// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Component.hpp>

#include <Framework/Renderer.hpp>

namespace SceneR
{
    namespace Framework
    {
        Component::Component(Guide::not_null<Renderer*> renderer)
            : _renderer ( renderer )
        {
        }

        Renderer* Component::renderer() noexcept
        {
            return _renderer;
        }

        void Component::update(const RenderTime& renderTime)
        {
        }

        bool Component::enabled() const noexcept
        {
            return _enabled;
        }

        void Component::enabled(const bool& enabled) noexcept
        {
            _enabled = enabled;
        }

        std::uint32_t Component::update_order() const noexcept
        {
            return _update_order;
        }

        void Component::update_order(const std::uint32_t& updateOrder) noexcept
        {
            _update_order = updateOrder;
        }
    }
}
