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

#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <GL/Regal.h>
#include <GLFW/glfw3.h>

#ifdef __linux__
    // Prevent name collisions with X11 defines
    #ifdef None
    #undef None
    #endif
    #ifdef Always
    #undef Always
    #endif
    #ifdef Bool
    #undef Bool
    #endif
    #ifdef CurrentTime
    #undef CurrentTime
    #endif
#endif

#endif /* PLATFORM_HPP */
