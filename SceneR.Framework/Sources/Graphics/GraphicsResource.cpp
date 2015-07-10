// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/GraphicsResource.hpp>

namespace SceneR
{
    namespace Graphics
    {
        GraphicsResource::GraphicsResource(GraphicsDevice& graphicsDevice)
            : graphicsDevice ( graphicsDevice )
            , name           { u""  }
            , tag            { u""  }
        {
        }

        GraphicsResource::~GraphicsResource()
        {
        }

        GraphicsDevice& GraphicsResource::CurrentGraphicsDevice()
        {
            return this->graphicsDevice;
        }

        const std::u16string& GraphicsResource::Name() const
        {
            return this->name;
        }

        void GraphicsResource::Name(const std::u16string& name)
        {
            this->name = name;
        }

        const std::u16string& GraphicsResource::Tag() const
        {
            return this->tag;
        }

        void GraphicsResource::Tag(const std::u16string& tag)
        {
            this->tag = tag;
        }
    }
}
