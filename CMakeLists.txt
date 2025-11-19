cmake_minimum_required(VERSION 3.15)
project(ccm_edge_cv_pipeline VERSION 0.1.0 LANGUAGES CXX)

# --- Performance & Safety Flags ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Enforce ISO C++

# Enable strict warnings for high-quality code
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion)
endif()

# --- Dependencies ---
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

# Fetch yaml-cpp automatically using FetchContent (Built-in CMake module)
include(FetchContent)

# --- OPTIMIZATION: Disable yaml-cpp tests and tools ---
set(YAML_CPP_BUILD_TESTS OFF CACHE INTERNAL "")
set(YAML_CPP_BUILD_TOOLS OFF CACHE INTERNAL "")
set(YAML_CPP_BUILD_CONTRIB OFF CACHE INTERNAL "")
# ------------------------------------------------------

FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG 0.8.0 # Version tag
)
FetchContent_MakeAvailable(yaml-cpp)

# --- Project Configuration ---
# Add the 'include' directory to the global include path
include_directories(include)

# --- Library: ccm_core (Business Logic) ---
# We build the logic as a library so it's testable
add_library(ccm_core
    src/core/config_loader.cpp
    src/io/opencv_camera.cpp
    src/stages/grayscale_stage.cpp
)

target_link_libraries(ccm_core PUBLIC ${OpenCV_LIBS})
target_include_directories(ccm_core PUBLIC include)

# --- Executable: Edge Pipeline App ---
add_executable(ccm-pipeline src/app/main.cpp)
target_link_libraries(ccm-pipeline PRIVATE ccm_core ${OpenCV_LIBS})

# Link yaml-cpp to the core library
target_link_libraries(ccm_core PUBLIC ${OpenCV_LIBS} yaml-cpp)

message(STATUS "CCM Edge Pipeline Configured. OpenCV Version: ${OpenCV_VERSION}")