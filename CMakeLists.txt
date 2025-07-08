cmake_minimum_required(VERSION 3.30)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# prevent installing to system directories.
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

project(PongGame)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
        add_definitions(/MP)				# parallelize each target, unless Ninja is the generator
    endif()
endif()

if (MSVC)
    set(GCC_COVERAGE_COMPILE_FLAGS "/W4 /Zi /MDd /utf-8")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fsanitize=address")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors -fexperimental-library -fsanitize=address,undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
elseif (CMAKE_CXX_PLATFORM_ID STREÅQUAL "Linux")
    set(GCC_COVERAGE_COMPILE_FLAGS
            "-Wall -Wextra -Wnrvo -Wpedantic -pedantic-errors -fdiagnostics-all-candidates")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(GCC_COVERAGE_COMPILE_FLAGS
            "-Wall -Wextra -Wnrvo -Wpedantic -pedantic-errors")
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# External Libraries
find_package(fmt CONFIG REQUIRED)
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)