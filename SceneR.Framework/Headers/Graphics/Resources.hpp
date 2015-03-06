#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Resources
        {
        private:
            static const unsigned char SkinnedEffect_vert[];
            static const unsigned SkinnedEffect_vert_size;
        public:
            static const System::String SkinnedEffect_vertString;
        private:
            static const unsigned char BasicEffect_vert[];
            static const unsigned BasicEffect_vert_size;
        public:
            static const System::String BasicEffect_vertString;
        private:
            static const unsigned char BasicEffect_frag[];
            static const unsigned BasicEffect_frag_size;
        public:
            static const System::String BasicEffect_fragString;
        private:
            static const unsigned char SkinnedEffect_frag[];
            static const unsigned SkinnedEffect_frag_size;
        public:
            static const System::String SkinnedEffect_fragString;
        };
    }
}


#endif /* RESOURCES_HPP */
