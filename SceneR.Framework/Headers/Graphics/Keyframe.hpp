// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//-----------------------------------------------------------------------------
// Ported from a Microsoft XNA Community Game Platform example
//-----------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef KEYFRAME_HPP
#define KEYFRAME_HPP

#include <Framework/Matrix.hpp>
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

        public:
            Keyframe& operator=(const Keyframe& keyframe);

        private:
            System::Int32             bone;
            System::TimeSpan          time;
            SceneR::Framework::Matrix transform;
        };
    }
}

#endif
