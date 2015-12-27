// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// Based on https://github.com/gamedevtech/X11OpenGLWindow

#ifndef SCENER_CORE_GRAPHICS_DISPLAY_DEVICE_HPP
#define SCENER_CORE_GRAPHICS_DISPLAY_DEVICE_HPP

#include <cstdint>

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR
{
    namespace Graphics
    {
        class DisplayDevice final
        {
        public:
            DisplayDevice() = default;

            ~DisplayDevice();

        public:
            Display* handle() const noexcept;

            uint32_t screen_id() const noexcept;

            XVisualInfo* visual_info() const noexcept;

            const GLXFBConfig& frame_buffer_config() const noexcept;

            bool open() noexcept;

            void destroy() noexcept;

            void sync() const noexcept;

        private:
            bool check_glx_version() noexcept;

            void open_display() noexcept;

            bool configure_frame_buffer() noexcept;

            GLXFBConfig get_best_frame_buffer_configuration() const noexcept;

        private:
            // X11
            Display*     _display   = nullptr;
            Screen*      _screen    = nullptr;
            std::int32_t _screen_id = 0;

            // GLX
            XVisualInfo* _visual_info = nullptr;
            GLXFBConfig  _fbc         = 0;
        };
    }
}

#endif // SCENER_CORE_GRAPHICS_DISPLAY_DEVICE_HPP
