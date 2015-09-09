// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SYSTEM_GRAPHICS_PLATFORM_HPP
#define SYSTEM_GRAPHICS_PLATFORM_HPP

#ifdef _USE_GLEW_
#include <GL/glew.h>
#else
#include <GL/Regal.h>
#endif
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

#endif  // SYSTEM_GRAPHICS_PLATFORM_HPP
