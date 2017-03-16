#include "scener/graphics/vulkan/swap_chain.hpp"

#include <vector>

#include "scener/graphics/vulkan/display_surface.hpp"
#include "scener/graphics/vulkan/physical_device.hpp"

namespace scener::graphics::vulkan
{
    swap_chain::swap_chain(display_surface* surface, physical_device* pyhiscal_device) noexcept
        : _surface         { surface }
        , _pyhiscal_device { pyhiscal_device }
    {
    }

    swap_chain::~swap_chain() noexcept
    {
    }
}
