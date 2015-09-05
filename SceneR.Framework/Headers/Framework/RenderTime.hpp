// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef RENDERTIME_HPP
#define RENDERTIME_HPP

#include <System/TimeSpan.hpp>

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
            RenderTime(const System::TimeSpan& totalRenderTime
                     , const System::TimeSpan& elapsedRenderTime);

            /**
             * Initializes a new instance of the RenderTime class.
             * @param totalRenderTime the amount of render time since the start of the game.
             * @param elapsedRenderTime the amount of elapsed render time since the last update.
             * @param isRunningSlowly a value indicating that the render loop is taking longer than its target_elapsed_time.
             */
            RenderTime(const System::TimeSpan& totalRenderTime
                     , const System::TimeSpan& elapsedRenderTime
                     , const bool&             isRunningSlowly);

            /**
             * Releases all resources being used by this RenderTime instance.
             */
            ~RenderTime();

        public:
            /**
             * Gets or sets the amount of elapsed render time since the last update.
             */
            System::TimeSpan total_render_time;

            /**
             * Gets or sets a value indicating that the render loop is taking longer than its target_elapsed_time.
             */
            System::TimeSpan elapsed_render_time;

            /**
             * Gets or sets the amount of render time since the start of the renderer.
             */
            bool is_running_slowly;
        };
    }
}

#endif /* RENDERTIME_HPP */
