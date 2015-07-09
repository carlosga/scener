// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Component.hpp>

#include <Framework/Renderer.hpp>

namespace SceneR
{
    namespace Framework
    {
        Component::Component(SceneR::Framework::Renderer& renderer)
            : renderer    ( renderer )
            , enabled     { true }
            , updateOrder { 0 }
        {
        }

        Component::~Component()
        {
        }

        SceneR::Framework::Renderer& Component::Renderer()
        {
            return this->renderer;
        }

        void Component::Update(const RenderTime& renderTime)
        {
        }

        bool Component::Enabled() const
        {
            return this->enabled;
        }

        void Component::Enabled(const bool& enabled)
        {
            this->enabled = enabled;
        }

        std::uint32_t Component::UpdateOrder() const
        {
            return this->updateOrder;
        }

        void Component::UpdateOrder(const std::uint32_t& updateOrder)
        {
            this->updateOrder = updateOrder;
        }
    }
}
