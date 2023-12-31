cmake_minimum_required(VERSION 3.20)

# Use the fancy version substitution
project(template
    VERSION 1.0
    DESCRIPTION "C TDD template using cmocka"
    LANGUAGES   C
)
enable_testing()

set(TARGET_GROUP production CACHE STRING "Group to build")

# For being able to used LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Request C 17 standard features
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic")

# Add CMocka CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmocka)

set (CMOCKA_PATH "" CACHE STRING "/usr/local/include")

# Search for the CMocka include directory
find_path(CMOCKA_INCLUDE_DIR
  NAMES cmocka.h
  PATHS ${CMOCKA_PATH}/include
  DOC "Where the CMocka header can be found"
)
set(CMOCKA_INCLUDE_DIRS "${CMOCKA_INCLUDE_DIR}")

# Search for the CMocka library directory
find_library(CMOCKA_LIBRARY
  NAMES cmocka
  PATHS ${CMOCKA_PATH}/lib
  DOC "Where the CMocka library can be found"
)
set(CMOCKA_LIBRARIES "${CMOCKA_LIBRARY}")

# Set CMOCKA_FOUND (if all required vars are found).
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CMocka DEFAULT_MSG CMOCKA_INCLUDE_DIRS CMOCKA_LIBRARIES)

# Hide variables from cmake GUIs.
mark_as_advanced(CMOCKA_PATH CMOCKA_INCLUDE_DIR CMOCKA_INCLUDE_DIRS CMOCKA_LIBRARY CMOCKA_LIBRARIES)

add_subdirectory(src)

if (UNIT_TESTING)
     find_package(cmocka 1.1.5 REQUIRED)
     include(AddCMockaTest)
     add_subdirectory(tests)
endif()

