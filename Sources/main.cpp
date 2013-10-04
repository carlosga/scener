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

#include <string>
#include "Graphics/PresentationParameters.hpp"
#include "CustomRenderer.hpp"

using namespace SceneR::Graphics;
using namespace SceneR::Custom;

int main()
{
    std::string rootPath = "/home/carlos/development/projects/cpp/opengl/workspace/SceneR/Content";

    CustomRenderer renderer(rootPath);

    renderer.Run();
    
    renderer.Exit();
    
    return 0;
}
