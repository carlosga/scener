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

#include <GLFW/glfw3.h>
#include <Graphics/DisplayMode.hpp>

using namespace System;
using namespace SceneR::Graphics;

DisplayMode::DisplayMode(const GLFWvidmode* mode)
    : aspectRatio(mode->width / mode->height),
      format(SurfaceFormat::Color),
      height(mode->height),
      width(mode->width)
{
    Int32 bitDepth = mode->redBits + mode->blueBits + mode->greenBits;

    switch (bitDepth)
    {
      case 16:
      case 8:
          this->format = SurfaceFormat::Bgr565;
          break;
    }
}

DisplayMode::~DisplayMode()
{
}

const System::Single& DisplayMode::AspectRatio() const
{
    return this->aspectRatio;
}

const SurfaceFormat& DisplayMode::Format() const
{
    return this->format;
}

const System::UInt32& DisplayMode::Height() const
{
    return this->height;
}

const System::UInt32& DisplayMode::Width() const
{
    return this->width;
}