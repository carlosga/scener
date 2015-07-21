// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexPositionColor.hpp>

#include <Graphics/VertexDeclaration.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Color;
        using SceneR::Framework::Vector3;

        const VertexDeclaration VertexPositionColor::Declaration
        {
            28
          , {
                { 0 , VertexElementFormat::Vector3, VertexElementUsage::Position, 0 }
              , { 12, VertexElementFormat::Vector4, VertexElementUsage::Color, 3 }
            }
        };

        const VertexDeclaration& VertexPositionColor::GetVertexDeclaration()
        {
            return VertexPositionColor::Declaration;
        }

        VertexPositionColor::VertexPositionColor(const Vector3&                  position
                                               , const SceneR::Framework::Color& color)
            : position { position }
            , color    { color }
        {
        }

        VertexPositionColor::~VertexPositionColor()
        {
        }

        const Vector3& VertexPositionColor::Position() const
        {
            return this->position;
        }

        const SceneR::Framework::Color& VertexPositionColor::Color() const
        {
            return this->color;
        }
    }
}
