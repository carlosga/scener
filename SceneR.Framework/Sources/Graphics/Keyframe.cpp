// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//-------------------------------------------------------------------------------
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

Keyframe::Keyframe(const std::uint32_t& bone, const TimeSpan& time, const Matrix& transform)
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

Keyframe::~Keyframe()
{
}

std::uint32_t Keyframe::Bone() const
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

Keyframe& Keyframe::operator=(const Keyframe& keyframe)
{
    if (this != &keyframe)
    {
        this->bone      = keyframe.bone;
        this->time      = keyframe.time;
        this->transform = keyframe.transform;
    }

    return *this;
}
