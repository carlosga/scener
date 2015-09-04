// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/GraphicsAdapter.hpp>

namespace SceneR
{
    namespace Graphics
    {
        const GraphicsAdapter& GraphicsAdapter::default_adapter()
        {
            auto it = std::find_if(GraphicsAdapter::adapters().begin(), GraphicsAdapter::adapters().end(),
                                   [](const GraphicsAdapter& adapter) -> bool
                                   {
                                       return adapter.is_default_adapter();
                                   });

            if (it != GraphicsAdapter::adapters().end())
            {
                return *it;
            }

            throw std::runtime_error("No default adapter available");
        }

        const std::vector<GraphicsAdapter> GraphicsAdapter::adapters()
        {
            std::vector<GraphicsAdapter> adapters;
            std::int32_t                 monitorCount = 1;
            GLFWmonitor**                monitors     = glfwGetMonitors(&monitorCount);

            for (std::int32_t i = 0; i < monitorCount; i++)
            {
                GraphicsAdapter adapter;
                GLFWmonitor*    monitorHandle    = monitors[i];
                std::int32_t    displayModeCount = 0;

                const GLFWvidmode* modes = glfwGetVideoModes(monitorHandle, &displayModeCount);

                adapter._monitor_handle     = monitorHandle;
                adapter._is_default_adapter = (monitorHandle == glfwGetPrimaryMonitor());

                for (std::int32_t j = 0; j < displayModeCount; j++)
                {
                    adapter._supported_display_modes.push_back(DisplayMode { &modes[j] });
                }

                adapters.push_back(adapter);
            }

            return adapters;
        }

        GraphicsAdapter::GraphicsAdapter()
            : _description             { }
            , _device_id               { 0 }
            , _device_name             { }
            , _is_default_adapter      { false }
            , _is_wide_screen          { false }
            , _monitor_handle          { nullptr }
            , _revision                { 0 }
            , _sub_system_id           { 0 }
            , _supported_display_modes ( )
            , _vendor_id               { 0 }
        {
        }

        GraphicsAdapter::GraphicsAdapter(const GraphicsAdapter& adapter)
            : _description             { adapter._description }
            , _device_id               { adapter._device_id }
            , _device_name             { adapter._device_name }
            , _is_default_adapter      { adapter._is_default_adapter }
            , _is_wide_screen          { adapter._is_wide_screen }
            , _monitor_handle          { adapter._monitor_handle }
            , _revision                { adapter._revision }
            , _sub_system_id           { adapter._sub_system_id }
            , _supported_display_modes ( adapter._supported_display_modes )
            , _vendor_id               { adapter._vendor_id }
        {
        }

        GraphicsAdapter::~GraphicsAdapter()
        {
        }

        DisplayMode GraphicsAdapter::current_display_mode() const
        {
            return DisplayMode(glfwGetVideoMode(_monitor_handle));
        }

        const std::u16string& GraphicsAdapter::description() const
        {
            return _description;
        }

        std::int32_t GraphicsAdapter::device_id() const
        {
            return _device_id;
        }

        const std::u16string& GraphicsAdapter::device_name() const
        {
            return _device_name;
        }

        bool GraphicsAdapter::is_default_adapter() const
        {
            return _is_default_adapter;
        }

        bool GraphicsAdapter::is_wide_screen() const
        {
            return _is_wide_screen;
        }

        GLFWmonitor* GraphicsAdapter::monitor_handle() const
        {
            return _monitor_handle;
        }

        std::int32_t GraphicsAdapter::revision() const
        {
            return _revision;
        }

        std::int32_t GraphicsAdapter::sub_system_id() const
        {
            return _sub_system_id;
        }

        const std::vector<DisplayMode>& GraphicsAdapter::supported_display_modes() const
        {
            return _supported_display_modes;
        }

        std::int32_t GraphicsAdapter::vendor_id() const
        {
            return _vendor_id;
        }

        GraphicsAdapter&GraphicsAdapter::operator=(const GraphicsAdapter& adapter)
        {
            if (this != &adapter)
            {
                _description             = adapter._description;
                _device_id               = adapter._device_id;
                _device_name             = adapter._device_name;
                _is_default_adapter      = adapter._is_default_adapter;
                _is_wide_screen          = adapter._is_wide_screen;
                _monitor_handle          = adapter._monitor_handle;
                _revision                = adapter._revision;
                _sub_system_id           = adapter._sub_system_id;
                _supported_display_modes = adapter._supported_display_modes;
                _vendor_id               = adapter._vendor_id;
            }

            return *this;
        }
    }
}
