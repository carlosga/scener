#include "SceneR/Graphics/ShaderInclude.hpp"

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR { namespace Graphics {

ShaderInclude::ShaderInclude(const std::string& 			  name
                           , const std::string& 			  path
                           , const std::vector<std::uint8_t>& source) noexcept
    : ShaderInclude(name, path, std::string(source.begin(), source.end()))
{
}

ShaderInclude::ShaderInclude(const std::string& name, const std::string& path, const std::string& source) noexcept
    : name(name)
    , path(path)
    , source(source)
{
}

void ShaderInclude::dispose() noexcept
{
    remove();
}

void ShaderInclude::declare() const noexcept
{
    if (!is_declared())
    {
        glNamedStringARB(GL_SHADER_INCLUDE_ARB, path.size(), path.c_str(), source.size(), source.c_str());
    }
}

void ShaderInclude::remove() const noexcept
{
    if (!is_declared())
    {
        glDeleteNamedStringARB(path.size(), path.c_str());
    }
}

bool ShaderInclude::is_declared() const noexcept
{
    return (glIsNamedStringARB(path.size(), path.c_str()));
}

}}
