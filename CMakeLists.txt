cmake_minimum_required(VERSION 3.15)
if(${CMAKE_VERSION} VERSION_LESS 3.27)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.27)
endif()

project(scn-editor VERSION 0.1.0)
set(SCN_EDITOR_ROOT ${CMAKE_CURRENT_LIST_DIR})


# {{{ Set default variables and options
option(SC_CLANG_FORMAT_CODE "Flag to add clangformat and clangformat_check targets" OFF)
option(AUTO_CCACHE "Use ccache to speed up rebuilds" ON)

include(CMakeDependentOption)
option(SC_BUILD_SUBSYSTEMS_TESTS "Flag to build unit tests in submodules" OFF)
option(SC_BUILD_TESTS "Flag to build unit tests" OFF)
cmake_dependent_option(INITIAL_SC_BUILD_TESTS "Flag to store SC_BUILD_TESTS value" ON "SC_BUILD_TESTS" OFF)
cmake_dependent_option(SC_BUILD_TESTS "" OFF "NOT INITIAL_SC_BUILD_TESTS;NOT SC_BUILD_SUBSYSTEMS_TESTS" ON)
# }}} Set default variables and options

# {{{ Include sc-machine
set(SC_MACHINE_PATH "${CMAKE_CURRENT_LIST_DIR}/problem-solver/sc-machine")
include("${SC_MACHINE_PATH}/CMakeLists.txt")
set(SC_BUILD_TESTS ${INITIAL_SC_BUILD_TESTS})

# platform doesn't support multi-extensions. Have to put project binaries to sc-machine extensions
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SC_EXTENSIONS_DIRECTORY})
# }}} Include sc-machine


# {{{ Find dependencies
find_program(CCACHE_PROGRAM ccache)
# }}} Find dependencies


# {{{ Configuring compilers
if(CCACHE_PROGRAM AND ${AUTO_CCACHE})
	message(STATUS "Using ${CCACHE_PROGRAM} as compiler launcher")
	set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
	set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()
# }}} Configuring compilers


# for multi-config builds (e.g. msvc)
foreach(OUTPUT_CONFIG ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER ${OUTPUT_CONFIG} OUTPUT_CONFIG)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${SC_EXTENSIONS_DIRECTORY})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${SC_EXTENSIONS_DIRECTORY})
endforeach(OUTPUT_CONFIG CMAKE_CONFIGURATION_TYPES)


# {{{ Include subsystems (problem-solver components)
set(SC_BUILD_TESTS ${SC_BUILD_SUBSYSTEMS_TESTS})

set(SC_BUILD_TESTS ${INITIAL_SC_BUILD_TESTS})
# }}} Include subsystems (problem-solver components)


# {{{ Include problem-colver
add_subdirectory(problem-solver)
# }}} Include problem-solver


# {{{ Unsetting cached variables values
unset(SC_AUTO_TEST CACHE)
unset(SC_BUILD_SUBSYSTEMS_TESTS CACHE)
unset(SC_BUILD_TESTS CACHE)
unset(CMAKE_BUILD_TYPE CACHE)
unset(INITIAL_SC_BUILD_TESTS CACHE)
# }}} Unsetting cached variables values
