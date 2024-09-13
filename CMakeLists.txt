cmake_minimum_required(VERSION 3.20)
project(kitok LANGUAGES C CXX)

# Policies
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

# Includes modules
include(FetchContent)
include(cmake/json.cmake)

# Some properties
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(PROJECT_NAME kitok)

# Some options
option(KITOK_BUILD_TESTS "Flag to build the unittest" OFF)
option(KITOK_BUILD_EXAMPLES "Flag to build the examples" OFF)

# Define the global library
add_library(kitok SHARED
        csrc/kitok.cpp
        csrc/vocabulary.cpp
        csrc/reader.cpp)

target_link_libraries(kitok nlohmann_json)

# Makes sure:
# - external call to kitok requires #include "kitok/<>" (not part of the lib)
# - internal call to kitok requires #include "<>.hpp" (part of the lib)
target_include_directories(kitok PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/kitok>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(kitok PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/>
)

if(KITOK_BUILD_TESTS)
    fetchcontent_declare(
        Catch2
        URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.0.tar.gz
    )
    fetchcontent_makeavailable(Catch2)

    add_executable(kitok_tests tests/reader.cpp)
    target_link_libraries(kitok_tests Catch2::Catch2WithMain)
endif()

if(KITOK_BUILD_EXAMPLES)
    add_executable(kitok_examples examples/hf_llama_example.cpp)
    target_link_libraries(kitok_examples PRIVATE kitok)
endif()