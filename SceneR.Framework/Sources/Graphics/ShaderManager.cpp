#include <Graphics/ShaderManager.hpp>

#include <algorithm>
#include <cassert>

#include <System/Graphics/Platform.hpp>
#include <System/Text/Encoding.hpp>
#include <Graphics/Resources.hpp>

using namespace System;
using namespace System::Text;
using namespace SceneR::Graphics;

const std::string ShaderManager::IncludesRootPath       = "/SceneR/";
const std::string ShaderManager::BasicEffectIncludePath = "/SceneR/BasicEffect.glsl";
const std::string ShaderManager::StructuresIncludePath  = "/SceneR/Structures.glsl";
const std::string ShaderManager::CommonIncludePath      = "/SceneR/Common.glsl";
const std::string ShaderManager::LightingIncludePath    = "/SceneR/Lighting.glsl";

std::map<std::string, std::string> ShaderManager::ShaderIncludes;

std::string ShaderManager::FormatIncludePath(const std::string& path)
{
    return IncludesRootPath + path;
}

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::Load()
{
    this->LoadShaderIncludes();
}

void ShaderManager::Unload()
{
    this->UnloadShaderIncludes();
}

const char* ShaderManager::GetPathReference(const std::string& path)
{
    assert (this->IsIncludeRegistered(path));

    const auto& item = ShaderIncludes.find(path);

    return item->first.c_str();
}

void ShaderManager::LoadShaderIncludes()
{
    this->LoadInclude(BasicEffectIncludePath, Resources::BasicEffect_glslString);
    this->LoadInclude(StructuresIncludePath , Resources::Structures_glslString);
    this->LoadInclude(CommonIncludePath     , Resources::Common_glslString);
    this->LoadInclude(LightingIncludePath   , Resources::Lighting_glslString);
}

void ShaderManager::UnloadShaderIncludes()
{
    this->UnloadInclude(BasicEffectIncludePath);
    this->UnloadInclude(StructuresIncludePath);
    this->UnloadInclude(CommonIncludePath);
    this->UnloadInclude(LightingIncludePath);
}

void ShaderManager::LoadInclude(const std::string& path, const std::string& shaderInclude)
{
    if (!this->IsIncludeRegistered(path))
    {
        ShaderIncludes.emplace(path, shaderInclude);

        if (!this->IsIncludeDeclared(path))
        {
            const char* rpath = this->GetPathReference(path);

            glNamedStringARB(GL_SHADER_INCLUDE_ARB
                           , path.size()
                           , rpath
                           , shaderInclude.size()
                           , shaderInclude.c_str());
        }
    }
}

void ShaderManager::UnloadInclude(const std::string& path)
{
    if (this->IsIncludeDeclared(path))
    {
        glDeleteNamedStringARB(path.size(), path.c_str());
    }
    if (this->IsIncludeRegistered(path))
    {
        ShaderIncludes.erase(path);
    }
}

Boolean ShaderManager::IsIncludeRegistered(const std::string& path) const
{
    return (ShaderIncludes.find(path) != ShaderIncludes.end());
}

Boolean ShaderManager::IsIncludeDeclared(const std::string& path) const
{
    return (glIsNamedStringARB(path.size(), path.c_str()));
}
