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

#include "Graphics/PresentationParameters.hpp"

using namespace SceneR::Graphics;

PresentationParameters::PresentationParameters()
    : fullScreen(false),
      backBufferHeight(0),
      backBufferWidth(0)
{
}

const Size PresentationParameters::GetBackBufferWidth() const
{
    return this->backBufferWidth;
}

void PresentationParameters::SetBackBufferWidth(const Size& backBufferWidth)
{
    this->backBufferWidth = backBufferWidth;
}

const Size PresentationParameters::GetBackBufferHeight() const
{
    return this->backBufferHeight;
}

void PresentationParameters::SetBackBufferHeight(const Size& backBufferHeight)
{
    this->backBufferHeight = backBufferHeight;
}

const Boolean PresentationParameters::GetFullScreen() const
{
    return this->fullScreen;
}

void PresentationParameters::SetFullScreen(const Boolean& fullScreen)
{
    this->fullScreen = fullScreen;
}
