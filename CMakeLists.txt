cmake_minimum_required(VERSION 3.20)

project(gdext VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  godot-cpp
  GIT_REPOSITORY https://github.com/godotengine/godot-cpp.git
  GIT_TAG        godot-4.3-stable
)

FetchContent_MakeAvailable(godot-cpp)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(GDEXTENSION_LIBRARY_TYPE_NAME "")

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
      if (CMAKE_SIZEOF_VOID_P EQUAL 4) # 32-bit
          set(GDEXTENSION_LIBRARY_TYPE_NAME "windows.debug.x86_32")
      elseif (CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
          set(GDEXTENSION_LIBRARY_TYPE_NAME "windows.debug.x86_64")
      endif()
  elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
      if (CMAKE_SIZEOF_VOID_P EQUAL 4) # 32-bit
          set(GDEXTENSION_LIBRARY_TYPE_NAME "windows.release.x86_32")
      elseif (CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
          set(GDEXTENSION_LIBRARY_TYPE_NAME "windows.release.x86_64")
      endif()
  endif()
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(${PROJECT_NAME} PUBLIC godot::cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/lib"
    SUFFIX ".${GDEXTENSION_LIBRARY_TYPE_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}"
)

install(DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/"
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gdextension-config")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX src FILES ${SOURCES})