#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include <map>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * @brief The ShaderManager class
         */
        class ShaderManager final
        {
        public:
            /**
             * @brief Root path for shader includes.
             */
            static const std::string IncludesRootPath;

            static const std::string StructuresIncludePath;
            static const std::string CommonIncludePath;
            static const std::string LightingIncludePath;
            static const std::string BasicEffectIncludePath;
            static const std::string SkinnedEffectIncludePath;

            static std::string FormatIncludePath(const std::string& path);

        public:
            /**
             * @brief Initializes a new instance of the ShaderManager class
             */
            ShaderManager();

            /**
             * Destructor
             */
            ~ShaderManager();

        public:
            /**
             * @brief Loads system shaders and includes
             */
            void Load();

            /**
             * @brief Unloads system shaders and includes
             */
            void Unload();

            const char* GetPathReference(const std::string& path);

        private:
            void LoadShaderIncludes();
            void UnloadShaderIncludes();
            void LoadInclude(const std::string& path, const std::string& shaderInclude);
            void UnloadInclude(const std::string& path);
            bool IsIncludeRegistered(const std::string& path) const;
            bool IsIncludeDeclared(const std::string& path) const;

        private:
            static std::map<std::string, std::string> ShaderIncludes;
        };
    }
}

#endif
