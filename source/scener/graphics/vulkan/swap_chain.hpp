#ifndef SCENER_GRAPHICS_VULKAN_SWAP_CHAIN_HPP
#define SCENER_GRAPHICS_VULKAN_SWAP_CHAIN_HPP

namespace scener::graphics::vulkan
{
    class display_surface;
    class physical_device;

    class swap_chain final
    {
    public:
        swap_chain(display_surface* surface, physical_device* pyhiscal_device) noexcept;
        ~swap_chain() noexcept;

    private:
        void initialize() noexcept;

    private:
        display_surface* _surface;
        physical_device* _pyhiscal_device;
    };
}

#endif
