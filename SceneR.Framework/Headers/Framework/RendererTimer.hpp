// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef RENDERERTIMER_HPP
#define RENDERERTIMER_HPP

#include <System/TimeSpan.hpp>

namespace SceneR
{
    namespace Framework
    {
        /**
         * Renderer timer.
         */
        class RendererTimer
        {
        public:
            /**
             * Initializes a new instance of the RendererTimer class.
             */
            RendererTimer();

            /**
             * Releases all resources being used by this RendererTimer.
             */
            ~RendererTimer();

        public:
            /**
             * Resets the renderer time points.
             */
            void Reset();

            /*
             * Updates the last time step time point.
             */
            void UpdateTimeStep();

            /*
             * Gets the time elapsed since the last timer reset.
             */
            System::TimeSpan ElapsedTime() const;

            /*
             * Gets the time elapsed since the last time step update.
             */
            System::TimeSpan ElapsedTimeStepTime() const;

        private:
            System::TimeSpan::Clock::time_point CurrentTime() const;

        private:
            RendererTimer(const RendererTimer& timer) = delete;
            RendererTimer& operator=(const RendererTimer& timer) = delete;

        private:
            System::TimeSpan::Clock::time_point start;
            System::TimeSpan::Clock::time_point lastTimeStep;
        };
    }
}

#endif /* RENDERERTIMER_HPP */
