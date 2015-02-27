// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/GraphicsAdapter.hpp>

using namespace System;
using namespace SceneR::Graphics;

const GraphicsAdapter& GraphicsAdapter::DefaultAdapter()
{
    auto it = std::find_if(GraphicsAdapter::Adapters().begin(), GraphicsAdapter::Adapters().end(),
                           [](const GraphicsAdapter& adapter) -> bool
                           {
                               return adapter.IsDefaultAdapter();
                           });

    if (it != GraphicsAdapter::Adapters().end())
    {
        return *it;
    }

    throw std::runtime_error("No default adapter available");
}

const std::vector<GraphicsAdapter> GraphicsAdapter::Adapters()
{
    std::vector<GraphicsAdapter> adapters;
    Int32         monitorCount = 1;
    GLFWmonitor** monitors     = glfwGetMonitors(&monitorCount);

    for (Int32 i = 0; i < monitorCount; i++)
    {
        GraphicsAdapter adapter;
        GLFWmonitor*    monitorHandle    = monitors[i];
        Int32           displayModeCount = 0;

        const GLFWvidmode* modes = glfwGetVideoModes(monitorHandle, &displayModeCount);

        adapter.monitorHandle    = monitorHandle;
        adapter.isDefaultAdapter = (monitorHandle == glfwGetPrimaryMonitor());

        for (Int32 j = 0; j < displayModeCount; j++)
        {
            adapter.supportedDisplayModes.push_back(DisplayMode { &modes[j] });
        }

        adapters.push_back(adapter);
    }

    return adapters;
}

GraphicsAdapter::GraphicsAdapter()
    : description           { u"" }
    , deviceId              { 0 }
    , deviceName            { u"" }
    , isDefaultAdapter      { false }
    , isWideScreen          { false }
    , monitorHandle         { nullptr }
    , revision              { 0 }
    , subSystemId           { 0 }
    , supportedDisplayModes ( )
    , vendorId              { 0 }
{
}

GraphicsAdapter::GraphicsAdapter(const GraphicsAdapter& adapter)
    : description           { adapter.description }
    , deviceId              { adapter.deviceId }
    , deviceName            { adapter.deviceName }
    , isDefaultAdapter      { adapter.isDefaultAdapter }
    , isWideScreen          { adapter.isWideScreen }
    , monitorHandle         { adapter.monitorHandle }
    , revision              { adapter.revision }
    , subSystemId           { adapter.subSystemId }
    , supportedDisplayModes ( adapter.supportedDisplayModes )
    , vendorId              { adapter.vendorId }
{
}

GraphicsAdapter::~GraphicsAdapter()
{
}

DisplayMode GraphicsAdapter::CurrentDisplayMode() const
{
    return DisplayMode(glfwGetVideoMode(this->monitorHandle));
}

const System::String& GraphicsAdapter::Description() const
{
    return this->description;
}

const System::Int32& GraphicsAdapter::DeviceId() const
{
    return this->deviceId;
}

const System::String& GraphicsAdapter::DeviceName() const
{
    return this->deviceName;
}

const System::Boolean& GraphicsAdapter::IsDefaultAdapter() const
{
    return this->isDefaultAdapter;
}

const System::Boolean& GraphicsAdapter::IsWideScreen() const
{
    return this->isWideScreen;
}

GLFWmonitor* GraphicsAdapter::MonitorHandle() const
{
    return this->monitorHandle;
}

const System::Int32& GraphicsAdapter::Revision() const
{
    return this->revision;
}

const System::Int32& GraphicsAdapter::SubSystemId() const
{
    return this->subSystemId;
}

const std::vector<DisplayMode>& GraphicsAdapter::SupportedDisplayModes() const
{
    return this->supportedDisplayModes;
}

const System::Int32& GraphicsAdapter::VendorId() const
{
    return this->vendorId;
}

GraphicsAdapter&GraphicsAdapter::operator=(const GraphicsAdapter& adapter)
{
    if (this != &adapter)
    {
        this->description           = adapter.description;
        this->deviceId              = adapter.deviceId;
        this->deviceName            = adapter.deviceName;
        this->isDefaultAdapter      = adapter.isDefaultAdapter;
        this->isWideScreen          = adapter.isWideScreen;
        this->monitorHandle         = adapter.monitorHandle;
        this->revision              = adapter.revision;
        this->subSystemId           = adapter.subSystemId;
        this->supportedDisplayModes = adapter.supportedDisplayModes;
        this->vendorId              = adapter.vendorId;
    }

    return *this;
}
