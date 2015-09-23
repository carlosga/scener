#ifndef GRAPHICS_SHADERINCLUDE_HPP
#define GRAPHICS_SHADERINCLUDE_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <System/IDisposable.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class ShaderInclude : public System::IDisposable
        {
        public:
            ShaderInclude(const std::string&               name
                        , const std::string&               path
                        , const std::vector<std::uint8_t>& source);

            ShaderInclude(const std::string& name, const std::string& path, const std::string& source);

            ~ShaderInclude() = default;

        public:
            void dispose() override;

        public:
            void declare() const;

            void remove() const;

            bool is_declared() const;

        public:
            const std::string name;
            const std::string path;
            const std::string source;
        };
    }
}

#endif	//  GRAPHICS_SHADERINCLUDE_HPP
