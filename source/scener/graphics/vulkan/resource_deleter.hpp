#ifndef SCENER_GRAPHICS_VULKAN_RESOURCE_DELETER
#define SCENER_GRAPHICS_VULKAN_RESOURCE_DELETER

#include <algorithm>
#include <any>
#include <functional>

#include "scener/graphics/vulkan/buffer.hpp"
#include "scener/graphics/vulkan/image_storage.hpp"

namespace scener::graphics::vulkan
{
    template <typename TResource>
    struct resource_deleter final
    {
    public:
        resource_deleter()
        {
        }

        resource_deleter(const std::any& allocator, const std::function<void(const std::any&, const TResource&)>& deleter)
            : _allocator { allocator }
            , _deleter   { deleter }
        {
        }

        void operator()(TResource* resource)
        {
            if (resource != nullptr)
            {
                _deleter(_allocator, *resource);
                delete resource;
                resource = nullptr;
            }
        }

    private:
        std::any                                               _allocator;
        std::function<void(const std::any&, const TResource&)> _deleter;
    };

    using buffer_deleter = resource_deleter<buffer>;
    using image_deleter  = resource_deleter<image_storage>;
}

#endif
