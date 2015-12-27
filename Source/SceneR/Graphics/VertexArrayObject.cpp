// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "VertexArrayObject.hpp"

#include "OpenGL/Platform.hpp"

namespace SceneR
{
    namespace Graphics
    {
        void VertexArrayObject::dispose()
        {
            if (_id != 0)
            {
                glDeleteVertexArrays(1, &_id);
                _id = 0;
            }
        }

        std::uint32_t VertexArrayObject::id() const noexcept
        {
            return _id;
        }

        void VertexArrayObject::bind() const
        {
            glBindVertexArray(_id);
        }

        void VertexArrayObject::create()
        {
            glCreateVertexArrays(1, &_id);
        }

        void VertexArrayObject::unbind() const
        {
            if (_id != 0)
            {
                glBindVertexArray(0);
            }
        }
    }
}
