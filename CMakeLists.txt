cmake_minimum_required(VERSION 4.0)
project(GLSimplify LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

find_package(OpenGL REQUIRED)

add_library(GLSimplify STATIC
        src/Window.cpp
        include/gls/Window.h
        include/gls/ContextSettings.h
        src/backends/sfml/ContextFlags.h
        src/Shader.cpp
        include/gls/Shader.h
        include/gls/KeyTypes.h
        src/Mesh.cpp
        include/gls/Mesh.h
        src/VertexLayout.cpp
        include/gls/VertexLayout.h
        src/Render.cpp
        include/gls/Render.h
        src/Debug.cpp
        include/gls/Debug.h
)

target_include_directories(GLSimplify
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(GLSimplify PRIVATE
        external/glad/src/glad.c
)
target_include_directories(GLSimplify PRIVATE
        external/glad/include
)
target_link_libraries(GLSimplify
        PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
        OpenGL::GL
        PUBLIC
        glm::glm
)

add_executable(triangle
        examples/triangle/main.cpp
)

target_link_libraries(triangle
        PRIVATE
        GLSimplify
)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(GLSimplify PRIVATE GLS_DEBUG)
endif()