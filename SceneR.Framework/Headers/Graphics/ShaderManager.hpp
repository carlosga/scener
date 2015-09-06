#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include <cstdint>
#include <map>
#include <string>
#include <vector>

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
            static const std::string includes_root_path;
            static const std::string structures_include_path;
            static const std::string common_include_path;
            static const std::string lighting_include_path;
            static const std::string basic_effect_include_path;
            static const std::string skinned_effect_include_path;

            static std::string format_include_path(const std::string& path);

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
            void load();

            /**
             * @brief Unloads system shaders and includes
             */
            void unload();

            const char* get_path_reference(const std::string& path);

        private:
            void load_shader_includes();
            void unload_shader_includes();
            void load_include(const std::string& path, const std::vector<std::uint8_t>& shaderInclude);
            void unload_include(const std::string& path);
            bool is_include_registered(const std::string& path) const;
            bool is_include_declared(const std::string& path) const;

        private:
            static std::map<std::string, std::string> _shader_includes;
        };
    }
}

#endif
