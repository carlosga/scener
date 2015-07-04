// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SHADERTYPE_HPP
#define SHADERTYPE_HPP

#include <System/Graphics/Platform.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Declares the supported shader types
         */
        enum class ShaderType : uint32_t
        {
            /**
             * A shader that is intended to run on the programmable vertex processor.
             */
            Vertex         = GL_VERTEX_SHADER,
            /**
             * A shader that is intended to run on the programmable tessellation processor in the control stage
             */
            TessControl    = GL_TESS_CONTROL_SHADER,
            /**
             * A shader that is intended to run on the programmable tessellation processor in the evaluation stage.
             */
            TessEvaluation = GL_TESS_EVALUATION_SHADER,
            /**
             * A shader that is intended to run on the programmable geometry processor.
             */
            Geometry       = GL_GEOMETRY_SHADER,
            /**
             * A shader that is intended to run on the programmable fragment processor.
             */
            Fragment       = GL_FRAGMENT_SHADER
        };
    }
}

#endif /* SHADERTYPE_HPP */
