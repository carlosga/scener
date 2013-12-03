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

#ifndef RENDERERTIMER_HPP
#define RENDERERTIMER_HPP

#include <System/TimeSpan.hpp>
#include <chrono>

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
            virtual ~RendererTimer();

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
            System::TimeSpan::Clock::time_point start;
            System::TimeSpan::Clock::time_point lastTimeStep;
        };
    }
}

#endif /* RENDERERTIMER_HPP */
