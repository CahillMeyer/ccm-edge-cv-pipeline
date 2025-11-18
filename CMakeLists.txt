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

# --- Project Configuration ---
# Add the 'include' directory to the global include path
include_directories(include)

# --- Library: ccm_core (Business Logic) ---
# We build the logic as a library so it's testable
add_library(ccm_core
    # Add source files here later, e.g.:
    # src/core/pipeline.cpp
    src/io/opencv_camera.cpp
)

target_link_libraries(ccm_core PUBLIC ${OpenCV_LIBS})
target_include_directories(ccm_core PUBLIC include)

# --- Executable: Edge Pipeline App ---
add_executable(ccm-pipeline src/app/main.cpp)
target_link_libraries(ccm-pipeline PRIVATE ccm_core ${OpenCV_LIBS})

message(STATUS "CCM Edge Pipeline Configured. OpenCV Version: ${OpenCV_VERSION}")