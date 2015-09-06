#include <Graphics/ShaderManager.hpp>

#include <algorithm>
#include <cassert>

#include <System/Graphics/Platform.hpp>
#include <System/Text/Encoding.hpp>
#include <Graphics/Resources.hpp>

namespace SceneR
{
    namespace Graphics
    {
        const std::string ShaderManager::includes_root_path          = "/SceneR/";
        const std::string ShaderManager::structures_include_path     = "/SceneR/Structures.glsl";
        const std::string ShaderManager::common_include_path         = "/SceneR/Common.glsl";
        const std::string ShaderManager::lighting_include_path       = "/SceneR/Lighting.glsl";
        const std::string ShaderManager::basic_effect_include_path   = "/SceneR/BasicEffect.glsl";
        const std::string ShaderManager::skinned_effect_include_path = "/SceneR/SkinnedEffect.glsl";

        std::map<std::string, std::string> ShaderManager::_shader_includes;

        std::string ShaderManager::format_include_path(const std::string& path)
        {
            return includes_root_path + path;
        }

        ShaderManager::ShaderManager()
        {
        }

        ShaderManager::~ShaderManager()
        {
        }

        void ShaderManager::load()
        {
            load_shader_includes();
        }

        void ShaderManager::unload()
        {
            unload_shader_includes();
        }

        const char* ShaderManager::get_path_reference(const std::string& path)
        {
            assert (is_include_registered(path));

            const auto& item = _shader_includes.find(path);

            return item->first.c_str();
        }

        void ShaderManager::load_shader_includes()
        {
            load_include(structures_include_path    , Resources::Structures_glsl);
            load_include(common_include_path        , Resources::Common_glsl);
            load_include(lighting_include_path      , Resources::Lighting_glsl);
            load_include(basic_effect_include_path  , Resources::BasicEffect_glsl);
            load_include(skinned_effect_include_path, Resources::SkinnedEffect_glsl);
        }

        void ShaderManager::unload_shader_includes()
        {
            for (const auto& kvp : _shader_includes)
            {
                unload_include(kvp.first);
            }

            _shader_includes.clear();
        }

        void ShaderManager::load_include(const std::string& path, const std::vector<std::uint8_t>& shaderInclude)
        {
            if (!is_include_registered(path))
            {
                auto source = std::string(shaderInclude.begin(), shaderInclude.end());

                _shader_includes.emplace(path, source);

                if (!is_include_declared(path))
                {
                    const char* rpath = get_path_reference(path);

                    glNamedStringARB(GL_SHADER_INCLUDE_ARB, path.size(), rpath, source.size(), source.c_str());
                }
            }
        }

        void ShaderManager::unload_include(const std::string& path)
        {
            if (is_include_declared(path))
            {
                glDeleteNamedStringARB(path.size(), path.c_str());
            }
            if (is_include_registered(path))
            {
                _shader_includes.erase(path);
            }
        }

        bool ShaderManager::is_include_registered(const std::string& path) const
        {
            return (_shader_includes.find(path) != _shader_includes.end());
        }

        bool ShaderManager::is_include_declared(const std::string& path) const
        {
            return (glIsNamedStringARB(path.size(), path.c_str()));
        }
    }
}
