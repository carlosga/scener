// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_RENDERTIME_HPP
#define SCENER_GRAPHICS_RENDERTIME_HPP

#include "SceneR/TimeSpan.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Snapshot of the render timing state.
         */
        class StepTime
        {
        public:
            /**
             * Initializes a new instance of the RenderTime class.
             */
            StepTime();

            /**
             * Initializes a new instance of the RenderTime class.
             * @param totalRenderTime the amount of render time since the start of the game.
             * @param elapsedRenderTime the amount of elapsed render time since the last update.
             */
            StepTime(const SceneR::TimeSpan& totalRenderTime
                   , const SceneR::TimeSpan& elapsedRenderTime);

            /**
             * Initializes a new instance of the RenderTime class.
             * @param totalRenderTime the amount of render time since the start of the game.
             * @param elapsedRenderTime the amount of elapsed render time since the last update.
             * @param isRunningSlowly a value indicating that the render loop is taking longer than its target_elapsed_time.
             */
            StepTime(const SceneR::TimeSpan& totalRenderTime
                   , const SceneR::TimeSpan& elapsedRenderTime
                   , const bool&             isRunningSlowly);

            /**
             * Releases all resources being used by this RenderTime instance.
             */
            ~StepTime() = default;

        public:
            /**
             * Gets or sets the amount of elapsed render time since the last update.
             */
            SceneR::TimeSpan total_render_time;

            /**
             * Gets or sets a value indicating that the render loop is taking longer than its target_elapsed_time.
             */
            SceneR::TimeSpan elapsed_render_time;

            /**
             * Gets or sets the amount of render time since the start of the renderer.
             */
            bool is_running_slowly;
        };
    }
}

#endif // SCENER_GRAPHICS_RENDERTIME_HPP
