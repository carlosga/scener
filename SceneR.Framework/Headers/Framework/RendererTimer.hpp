// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_RENDERERTIMER_HPP
#define FRAMEWORK_RENDERERTIMER_HPP

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
            RendererTimer() = default;

            /**
             * Releases all resources being used by this RendererTimer.
             */
            ~RendererTimer() = default;

        public:
            /**
             * Resets the renderer time points.
             */
            void reset();

            /*
             * Updates the last time step time point.
             */
            void update_time_step();

            /*
             * Gets the time elapsed since the last timer reset.
             */
            System::TimeSpan elapsed_time() const;

            /*
             * Gets the time elapsed since the last time step update.
             */
            System::TimeSpan elapsed_time_step_time() const;

        private:
            System::TimeSpan::clock::time_point current_time() const;

        private:
            RendererTimer(const RendererTimer& timer) = delete;
            RendererTimer& operator=(const RendererTimer& timer) = delete;

        private:
            System::TimeSpan::clock::time_point _start          = System::TimeSpan::clock::now();
            System::TimeSpan::clock::time_point _last_time_step = System::TimeSpan::clock::now();
        };
    }
}

#endif // FRAMEWORK_RENDERERTIMER_HPP
