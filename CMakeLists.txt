cmake_minimum_required(VERSION 3.11)

project(
    Tenasi
    VERSION 0.0.1
    DESCRIPTION "Graphic Design"
    LANGUAGES CXX
)

include(FetchContent)

# === GLFW ===
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

# === GLAD ===
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG master
)
FetchContent_MakeAvailable(glad)

# === GLM ===
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG master
)
FetchContent_MakeAvailable(glm)

if (NOT TARGET glad)
  add_library(glad STATIC ${glad_SOURCE_DIR}/src/glad.c)
  target_include_directories(glad PUBLIC ${glad_SOURCE_DIR}/include)
else()
  message(STATUS "Using glad target provided by FetchContent")
endif()

message(STATUS "Compiler")
message(STATUS " - ID       \t: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS " - Version  \t: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS " - Path     \t: ${CMAKE_CXX_COMPILER}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/shader.cpp
    src/mesh_vao.cpp
    src/mesh_vbo.cpp
    src/mesh_ebo.cpp
    src/mesh.cpp
    )

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Werror -O2)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw glad glm)