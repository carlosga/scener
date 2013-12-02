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

#include <System/Core.hpp>
#include <chrono>

namespace SceneR
{
    namespace Framework
    {
        class RendererTimer
        {
        public:
            RendererTimer();
            virtual ~RendererTimer();

        public:
            void Reset();
            void UpdateTimeStep();
            System::MilliSeconds ElapsedTime() const;
            System::MilliSeconds ElapsedTimeStepTime() const;
            System::Clock::time_point CurrentTime() const;

       private:
            System::MilliSeconds CalculateDuration(const System::Clock::time_point& t0,
                                                   const System::Clock::time_point& t1) const;

        private:
            System::Clock::time_point start;
            System::Clock::time_point lastTimeStep;
        };
    }
}

#endif /* RENDERERTIMER_HPP */
