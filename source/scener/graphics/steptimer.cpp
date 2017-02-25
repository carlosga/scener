// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/steptimer.hpp"

namespace scener::graphics
{
    using scener::timespan;

    void steptimer::reset() noexcept
    {
        _start          = current_time();
        _last_time_step = current_time();
    }

    void steptimer::update_time_step() noexcept
    {
        _last_time_step = current_time();
    }

    timespan::clock::time_point steptimer::current_time() const noexcept
    {
        return timespan::clock::now();
    }
}
