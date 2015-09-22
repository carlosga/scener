// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Component.hpp>

#include <Framework/Renderer.hpp>

namespace SceneR
{
    namespace Framework
    {
        Component::Component(Renderer* renderer)
            : _renderer ( renderer )
        {
        }

        Renderer* Component::renderer()
        {
            return _renderer;
        }

        void Component::update(const RenderTime& renderTime)
        {
        }

        bool Component::enabled() const
        {
            return _enabled;
        }

        void Component::enabled(const bool& enabled)
        {
            _enabled = enabled;
        }

        std::uint32_t Component::update_order() const
        {
            return _update_order;
        }

        void Component::update_order(const std::uint32_t& updateOrder)
        {
            _update_order = updateOrder;
        }
    }
}
