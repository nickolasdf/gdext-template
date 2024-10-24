
# Set the template and output file
set(CONFIG_TEMPLATE "${CMAKE_CURRENT_SOURCE_DIR}/template.gdextension.in")
set(CONFIG_OUTPUT "${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.gdextension")
set(LIBRARY_ENTRY "")

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        if (CMAKE_SIZEOF_VOID_P EQUAL 4) # 32-bit
            set(LIBRARY_ENTRY "windows.debug.x86_32 = \"res://lib/${PROJECT_NAME}.windows.debug.x86_32.dll\"")
        elseif (CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
            set(LIBRARY_ENTRY "windows.debug.x86_64 = \"res://lib/${PROJECT_NAME}.windows.debug.x86_64.dll\"")
        endif()
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        if (CMAKE_SIZEOF_VOID_P EQUAL 4) # 32-bit
            set(LIBRARY_ENTRY "windows.release.x86_32 = \"res://lib/${PROJECT_NAME}.windows.release.x86_32.dll\"")
        elseif (CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
            set(LIBRARY_ENTRY "windows.release.x86_64 = \"res://lib/${PROJECT_NAME}.windows.release.x86_64.dll\"")
        endif()
    endif()
endif()

# Configure the file to substitute @LIBRARY_ENTRY@ with the actual value
configure_file(${CONFIG_TEMPLATE} ${CONFIG_OUTPUT} @ONLY)

# Add custom target to generate the config file during build
add_custom_target(GenerateConfig ALL DEPENDS ${CONFIG_OUTPUT})