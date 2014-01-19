//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef SHADERTYPE_HPP
#define SHADERTYPE_HPP

#include <System/Core.hpp>
#include <System/Graphics/Platform.hpp>

namespace System
{
    namespace Graphics
    {
        /**
         * Declares the supported shader types
         */
        enum class ShaderType : System::UInt32
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
            Fragment       = GL_FRAGMENT_SHADER,
            /**
             * A shader that is intended to be used for computing arbitrary information.
             */
            Compute        = GL_COMPUTE_SHADER
        };
    }
}

#endif /* SHADERTYPE_HPP */
