# http://stackoverflow.com/questions/11813271/embed-resources-eg-shader-code-images-into-executable-library-with-cmake
# Creates C resources file from files in given directory
function(generate_resources_header dir output)
    # Create empty output file
    file(WRITE ${output} "")
    # Collect input files
    file(GLOB bins ${dir}/*)
    # Write header
    file(APPEND ${output} "#ifndef RESOURCES_HPP\n")
    file(APPEND ${output} "#define RESOURCES_HPP\n\n")
    file(APPEND ${output} "#include <string>\n\n")
    file(APPEND ${output} "namespace SceneR\n")
    file(APPEND ${output} "{\n")
    file(APPEND ${output} "    namespace Graphics\n")
    file(APPEND ${output} "    {\n")
    file(APPEND ${output} "        class Resources\n")
    file(APPEND ${output} "        {\n")
    # Iterate through input files
    foreach(bin ${bins})
        # Get short filename
        string(REGEX MATCH "([^/]+)$" filename ${bin})
        # Replace filename spaces & extension separator for C compatibility
        string(REGEX REPLACE "\\.| " "_" filename ${filename})
        # Read hex data from file
        file(READ ${bin} filedata HEX)
        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        # Append data to output file
        file(APPEND ${output} "        private:\n")
        file(APPEND ${output} "            static const unsigned char ${filename}[];\n")
        file(APPEND ${output} "            static const unsigned ${filename}_size;\n")
        file(APPEND ${output} "        public:\n")
        file(APPEND ${output} "            static const std::string ${filename}String;\n")
    endforeach()
    # Write footer
    file(APPEND ${output} "        };\n")
    file(APPEND ${output} "    }\n")
    file(APPEND ${output} "}\n\n")
    file(APPEND ${output} "\n#endif /* RESOURCES_HPP */\n")
endfunction()

function(generate_resources_source dir output)
    # Create empty output file
    file(WRITE ${output} "")
    # Collect input files
    file(GLOB bins ${dir}/*)
    # Write header
    file(APPEND ${output} "#include <Graphics/Resources.hpp>\n\n")
    file(APPEND ${output} "using namespace SceneR::Graphics;\n\n")
    # Iterate through input files
    foreach(bin ${bins})
        # Get short filename
        string(REGEX MATCH "([^/]+)$" filename ${bin})
        # Replace filename spaces & extension separator for C compatibility
        string(REGEX REPLACE "\\.| " "_" filename ${filename})
        # Read hex data from file
        file(READ ${bin} filedata HEX)
        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        # Append data to output file
        file(APPEND ${output} "const unsigned char Resources::${filename}[]   = {${filedata}};\n")
        file(APPEND ${output} "const unsigned Resources::${filename}_size     = sizeof(${filename});\n")
        file(APPEND ${output} "const std::string Resources::${filename}String = std::string(Resources::${filename}, Resources::${filename} + Resources::${filename}_size);\n")
    endforeach()
endfunction()

# generate resource header and source files
if (${GENERATE_HEADER})
    message(STATUS "generating header resource file")
    generate_resources_header(${ROOT_DIRECTORY}/Resources ${ROOT_DIRECTORY}/Headers/Graphics/Resources.hpp)
endif()
if (${GENERATE_SOURCE})
    message(STATUS "generating source resource file")
    generate_resources_source(${ROOT_DIRECTORY}/Resources ${ROOT_DIRECTORY}/Sources/Graphics/Resources.cpp)
endif()
