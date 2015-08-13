set(needs_rebuild 0)

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
    file(APPEND ${output} "        public:\n")
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
        file(APPEND ${output} "            static const std::string ${filename}String;\n")
    endforeach()
    file(APPEND ${output} "        private:\n")
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
        file(APPEND ${output} "            static const unsigned char ${filename}[];\n")
        file(APPEND ${output} "            static const unsigned ${filename}_size;\n")
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
    file(APPEND ${output} "namespace SceneR\n")
    file(APPEND ${output} "{\n")
    file(APPEND ${output} "namespace Graphics\n")
    file(APPEND ${output} "{\n")
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
        file(APPEND ${output} "const std::string Resources::${filename}String = std::string(Resources::${filename}, Resources::${filename} + Resources::${filename}_size);\n")
    endforeach()
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
    endforeach()
    file(APPEND ${output} "}\n")
    file(APPEND ${output} "}\n")
endfunction()

function(check_state dir output)
    # Collect input files
    file(GLOB bins ${dir}/*)
    # Iterate through input files
    foreach(bin ${bins})
        if (${bin} IS_NEWER_THAN ${output})
            set(needs_rebuild 1 PARENT_SCOPE)
        endif()
    endforeach()
endfunction()

check_state(${ROOT_DIRECTORY}/Resources ${ROOT_DIRECTORY}/Sources/Graphics/Resources.cpp)

# generate resource header and source files
if (${needs_rebuild} EQUAL 1)
    generate_resources_header(${ROOT_DIRECTORY}/Resources ${ROOT_DIRECTORY}/Headers/Graphics/Resources.hpp)
    generate_resources_source(${ROOT_DIRECTORY}/Resources ${ROOT_DIRECTORY}/Sources/Graphics/Resources.cpp)
endif()
