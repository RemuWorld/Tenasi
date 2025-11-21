cmake_minimum_required(VERSION 3.11)

project(
    Tenasi
    VERSION 0.0.1
    DESCRIPTION "Graphic Design Engine"
    LANGUAGES CXX C
)

# ==========================================
# 1. DEPENDENCIES (FetchContent)
# ==========================================
include(FetchContent)

# --- GLFW ---
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

# --- GLM ---
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG master
)
FetchContent_MakeAvailable(glm)

# --- GLAD ---
# GLAD is tricky because the repo generates code. We build it manually here.
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG master
)
FetchContent_MakeAvailable(glad)

if (NOT TARGET glad)
  # Create a library from the GLAD source downloaded
  add_library(glad STATIC ${glad_SOURCE_DIR}/src/glad.c)
  target_include_directories(glad PUBLIC ${glad_SOURCE_DIR}/include)
endif()


message(STATUS "Compiler")
message(STATUS " - ID       \t: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS " - Version  \t: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS " - Path     \t: ${CMAKE_CXX_COMPILER}")


# ==========================================
# 2. SOURCE FILES (Auto-Discovery)
# ==========================================

# This command tells CMake: "Look inside src/ and all subfolders recursively for .cpp and .c files"
file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/*.c"
)

# Look for headers too (so they show up in your IDE)
file(GLOB_RECURSE HEADERS 
    "src/*.h"
    "include/*.h"
)

# ==========================================
# 3. EXECUTABLE SETUP
# ==========================================

# Create the executable using the files we found above
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# C++ Standard configuration
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

# Compiler warnings (Keep code clean)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -O2)

target_compile_definitions(${PROJECT_NAME} PUBLIC 
    GLFW_INCLUDE_NONE
)

# ==========================================
# 4. INCLUDE DIRECTORIES
# ==========================================

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include       # Allows #include "Tenasi.h"
    ${CMAKE_SOURCE_DIR}/src           # Allows #include "Gfx/camera.h"
)

# ==========================================
# 5. LINKING
# ==========================================

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    OpenGL::GL 
    glfw 
    glad 
    glm
)

# ==========================================
# 6. ASSETS & RESOURCES
# ==========================================

# Copy the "resource" folder to the build folder automatically
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/resource"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resource"
    COMMENT "Copying resources to binary directory..."
)