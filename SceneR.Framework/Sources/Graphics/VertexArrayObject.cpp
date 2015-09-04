// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexArrayObject.hpp>

#include <System/Graphics/Platform.hpp>

namespace SceneR
{
    namespace Graphics
    {
        VertexArrayObject::VertexArrayObject()
            : _id { 0 }
        {
            this->create();
        }

        VertexArrayObject::~VertexArrayObject()
        {
        }

        void VertexArrayObject::dispose()
        {
            if (_id != 0)
            {
                glDeleteVertexArrays(1, &_id);
                _id = 0;
            }
        }

        std::uint32_t VertexArrayObject::id() const
        {
            return _id;
        }

        void VertexArrayObject::create()
        {
            glCreateVertexArrays(1, &_id);
        }

        void VertexArrayObject::activate() const
        {
            glBindVertexArray(_id);
        }

        void VertexArrayObject::deactivate() const
        {
            if (_id != 0)
            {
                glBindVertexArray(0);
            }
        }
    }
}
