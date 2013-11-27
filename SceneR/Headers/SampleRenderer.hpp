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

#ifndef CUSTOMRENDERER_HPP
#define CUSTOMRENDERER_HPP

#include <System/Core.hpp>
#include <Framework/Renderer.hpp>

namespace SceneR
{
    namespace Sample
    {
        class SampleRenderer : public SceneR::Framework::Renderer
        {
        public:
            SampleRenderer(const System::String& rootDirectory);

        protected:
            virtual void BeginRun() override;
        };
    }
}

#endif /* CUSTOMRENDERER_HPP */