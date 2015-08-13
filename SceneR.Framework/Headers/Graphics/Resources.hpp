#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>

namespace SceneR
{
    namespace Graphics
    {
        class Resources
        {
        public:
            static const std::string BasicEffect_fragString;
            static const std::string SkinnedEffect_vertString;
            static const std::string BasicEffect_glslString;
            static const std::string SkinnedEffect_glslString;
            static const std::string Structures_glslString;
            static const std::string Common_glslString;
            static const std::string SkinnedEffect_fragString;
            static const std::string Lighting_glslString;
            static const std::string BasicEffect_vertString;
        private:
            static const unsigned char BasicEffect_frag[];
            static const unsigned BasicEffect_frag_size;
            static const unsigned char SkinnedEffect_vert[];
            static const unsigned SkinnedEffect_vert_size;
            static const unsigned char BasicEffect_glsl[];
            static const unsigned BasicEffect_glsl_size;
            static const unsigned char SkinnedEffect_glsl[];
            static const unsigned SkinnedEffect_glsl_size;
            static const unsigned char Structures_glsl[];
            static const unsigned Structures_glsl_size;
            static const unsigned char Common_glsl[];
            static const unsigned Common_glsl_size;
            static const unsigned char SkinnedEffect_frag[];
            static const unsigned SkinnedEffect_frag_size;
            static const unsigned char Lighting_glsl[];
            static const unsigned Lighting_glsl_size;
            static const unsigned char BasicEffect_vert[];
            static const unsigned BasicEffect_vert_size;
        };
    }
}


#endif /* RESOURCES_HPP */
