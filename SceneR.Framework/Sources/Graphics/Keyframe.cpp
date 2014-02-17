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
//
// Ported from a Microsoft XNA Community Game Platform example
//-----------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#include <Graphics/Keyframe.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

Keyframe::Keyframe()
    : Keyframe { 0, TimeSpan::Zero, Matrix::Identity }
{
}

Keyframe::Keyframe(const Int32& bone, const TimeSpan& time, const Matrix& transform)
    : bone      { bone }
    , time      { time }
    , transform { transform }
{
}

Keyframe::Keyframe(const Keyframe& keyframe)
    : bone      { keyframe.bone }
    , time      { keyframe.time }
    , transform { keyframe.transform }
{
}

const System::Int32& Keyframe::Bone() const
{
    return this->bone;
}

const TimeSpan& Keyframe::Time() const
{
    return this->time;
}

const Matrix& Keyframe::Transform() const
{
    return this->transform;
}
