// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_DEFAULT_CONSTANT_BUFFER_HPP
#define SCENER_GRAPHICS_DEFAULT_CONSTANT_BUFFER_HPP

#include "scener/math/matrix.hpp"
#include "scener/math/basic_matrix.hpp"
#include "scener/math/basic_quaternion.hpp"
#include "scener/math/basic_vector.hpp"

namespace scener::graphics
{
    class constant_buffer;

    struct default_constant_buffer final
    {
    public:       
        // Vertex shader
        math::matrix4 u_jointMat[57];
        math::matrix4 u_normalMatrix;
        math::matrix4 u_modelViewMatrix;
        math::matrix4 u_projectionMatrix;
        math::matrix4 u_light0Transform;

        // Fragment Shader
        math::vector4 u_ambient;
        math::vector4 u_emission;
        math::vector4 u_specular;
        float         u_shininess;
        float         u_light0ConstantAttenuation;
        float         u_light0LinearAttenuation;
        float         u_light0QuadraticAttenuation;
        math::vector3 u_light0Color;
    };
}

#endif // SCENER_GRAPHICS_DEFAULT_CONSTANT_BUFFER_HPP
