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

#ifndef RENDERTIME_HPP
#define RENDERTIME_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        /**
         * Snapshot of the render timing state.
         */
        class RenderTime
        {
        public:
            /**
             * Initializes a new instance of the RenderTime class.
             */
            RenderTime();

            /**
             * Initializes a new instance of the RenderTime class.
             * @param totalRenderTime the amount of render time since the start of the game.
             * @param elapsedRenderTime the amount of elapsed render time since the last update.
             */
            RenderTime(const System::MilliSeconds& totalRenderTime,
                       const System::MilliSeconds& elapsedRenderTime);

            /**
             * Initializes a new instance of the RenderTime class.
             * @param totalRenderTime the amount of render time since the start of the game.
             * @param elapsedRenderTime the amount of elapsed render time since the last update.
             * @param isRunningSlowly a value indicating that the render loop is taking longer than its TargetElapsedTime.
             */
            RenderTime(const System::MilliSeconds& totalRenderTime,
                       const System::MilliSeconds& elapsedRenderTime,
                       const System::Boolean&  isRunningSlowly);

            /**
             * Releases all resources being used by this RenderTime instance.
             */
            virtual ~RenderTime();

        public:
            /**
             * Gets the amount of elapsed render time since the last update.
             */
            const System::MilliSeconds& ElapsedRenderTime() const;

            /**
             * Gets the amount of elapsed render time since the last update.
             */
            void ElapsedRenderTime(const System::MilliSeconds& elapsedRenderTime);

            /**
             * Gets a value indicating that the render loop is taking longer than its TargetElapsedTime.
             */
            const System::Boolean IsRunningSlowly() const;

            /**
             * Sets a value indicating that the render loop is taking longer than its TargetElapsedTime.
             */
            void IsRunningSlowly(const System::Boolean isRunningSlowly);

            /**
             * Gets the amount of render time since the start of the renderer.
             */
            const System::MilliSeconds& TotalRenderTime() const;

            /**
             * Gets the amount of render time since the start of the renderer.
             */
            void TotalRenderTime(const System::MilliSeconds& totalRenderTime);

        private:
            System::MilliSeconds totalRenderTime;
            System::MilliSeconds elapsedRenderTime;
            System::Boolean      isRunningSlowly;
        };
    }
}

#endif /* RENDERTIME_HPP */
