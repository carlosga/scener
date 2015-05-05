#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>

namespace SceneR
{
    namespace Graphics
    {
        class Resources
        {
        private:
            static const unsigned char BasicEffect_frag[];
            static const unsigned BasicEffect_frag_size;
        public:
            static const std::string BasicEffect_fragString;
        private:
            static const unsigned char SkinnedEffect_vert[];
            static const unsigned SkinnedEffect_vert_size;
        public:
            static const std::string SkinnedEffect_vertString;
        private:
            static const unsigned char BasicEffect_glsl[];
            static const unsigned BasicEffect_glsl_size;
        public:
            static const std::string BasicEffect_glslString;
        private:
            static const unsigned char SkinnedEffect_glsl[];
            static const unsigned SkinnedEffect_glsl_size;
        public:
            static const std::string SkinnedEffect_glslString;
        private:
            static const unsigned char Structures_glsl[];
            static const unsigned Structures_glsl_size;
        public:
            static const std::string Structures_glslString;
        private:
            static const unsigned char Common_glsl[];
            static const unsigned Common_glsl_size;
        public:
            static const std::string Common_glslString;
        private:
            static const unsigned char SkinnedEffect_frag[];
            static const unsigned SkinnedEffect_frag_size;
        public:
            static const std::string SkinnedEffect_fragString;
        private:
            static const unsigned char Lighting_glsl[];
            static const unsigned Lighting_glsl_size;
        public:
            static const std::string Lighting_glslString;
        private:
            static const unsigned char BasicEffect_vert[];
            static const unsigned BasicEffect_vert_size;
        public:
            static const std::string BasicEffect_vertString;
        };
    }
}


#endif /* RESOURCES_HPP */
