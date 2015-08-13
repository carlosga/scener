#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <cstdint>

#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        class Resources
        {
        public:
            static const std::vector<std::uint8_t> BasicEffect_frag;
            static const std::vector<std::uint8_t> SkinnedEffect_vert;
            static const std::vector<std::uint8_t> BasicEffect_glsl;
            static const std::vector<std::uint8_t> SkinnedEffect_glsl;
            static const std::vector<std::uint8_t> Structures_glsl;
            static const std::vector<std::uint8_t> Common_glsl;
            static const std::vector<std::uint8_t> SkinnedEffect_frag;
            static const std::vector<std::uint8_t> Lighting_glsl;
            static const std::vector<std::uint8_t> BasicEffect_vert;
        };
    }
}


#endif /* RESOURCES_HPP */
