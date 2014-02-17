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

#ifndef KEYFRAME_HPP
#define KEYFRAME_HPP

#include <Framework/Matrix.hpp>
#include <System/Core.hpp>
#include <System/TimeSpan.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Keyframe
        {
        public:
            Keyframe();

            Keyframe(const System::Int32&             bone
                   , const System::TimeSpan&          time
                   , const SceneR::Framework::Matrix& transform);

            Keyframe(const Keyframe& keyframe);

            ~Keyframe() = default;

        public:
            const System::Int32& Bone() const;

            const System::TimeSpan& Time() const;

            const SceneR::Framework::Matrix& Transform() const;

        private:
            System::Int32             bone;
            System::TimeSpan          time;
            SceneR::Framework::Matrix transform;
        };
    }
}

#endif
