// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_DEFAULT_CONSTANT_BUFFER_HPP
#define SCENER_GRAPHICS_DEFAULT_CONSTANT_BUFFER_HPP

#include "scener/math/matrix.hpp"
#include "scener/math/basic_quaternion.hpp"
#include "scener/math/basic_vector.hpp"

namespace scener::graphics
{
    class constant_buffer;

    struct default_constant_buffer final
    {
    public:
        // Fragment Shader
        scener::math::vector4 u_diffuse;
        scener::math::vector4 u_specular;
        // Vertex Shader
        scener::math::matrix4 u_normalMatrix;
        scener::math::matrix4 u_modelViewMatrix;
        scener::math::matrix4 u_projectionMatrix;
    };
}

#endif // SCENER_GRAPHICS_DEFAULT_CONSTANT_BUFFER_HPP
