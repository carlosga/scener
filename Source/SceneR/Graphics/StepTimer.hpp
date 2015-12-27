// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_RENDERERTIMER_HPP
#define SCENER_GRAPHICS_RENDERERTIMER_HPP

#include "SceneR/Core/TimeSpan.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Step timer.
         */
        class StepTimer
        {
        public:
            /**
             * Initializes a new instance of the RendererTimer class.
             */
            StepTimer() = default;

            /**
             * Releases all resources being used by this RendererTimer.
             */
            ~StepTimer() = default;

        public:
            /**
             * Resets the renderer time points.
             */
            void reset() noexcept;

            /*
             * Updates the last time step time point.
             */
            void update_time_step() noexcept;

            /*
             * Gets the time elapsed since the last timer reset.
             */
            SceneR::TimeSpan elapsed_time() const noexcept;

            /*
             * Gets the time elapsed since the last time step update.
             */
            SceneR::TimeSpan elapsed_time_step_time() const noexcept;

        private:
            SceneR::TimeSpan::clock::time_point current_time() const noexcept;

        private:
            StepTimer(const StepTimer& timer) = delete;
            StepTimer& operator=(const StepTimer& timer) = delete;

        private:
            SceneR::TimeSpan::clock::time_point _start          { SceneR::TimeSpan::clock::now() };
            SceneR::TimeSpan::clock::time_point _last_time_step { SceneR::TimeSpan::clock::now() };
        };
    }
}

#endif // SCENER_GRAPHICS_RENDERERTIMER_HPP
