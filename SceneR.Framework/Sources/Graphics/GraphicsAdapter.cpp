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

#include <Graphics/GraphicsAdapter.hpp>
#include <System/Graphics/Platform.hpp>
#include <algorithm>
#include <stdexcept>

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
    : description(u""),
      deviceId(0),
      deviceName(u""),
      isDefaultAdapter(false),
      isWideScreen(false),
      monitorHandle(nullptr),
      revision(0),
      subSystemId(0),
      supportedDisplayModes(),
      vendorId(0)
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
