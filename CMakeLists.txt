project(git2pp)

#**************************************************************************************************
# General cMake settings
#**************************************************************************************************
cmake_minimum_required(VERSION 3.5)

#**************************************************************************************************
# Find Package **************************************************************************************************
find_path(OPENSSL_INCLUDE_DIR ssl.h)
find_library(OPENSSL_LIBRARY ssl)
find_library(CRYPTO_LIBRARY crypto)
find_library(LIGBGIT2_LIBRARY git2)

find_package(ZLIB REQUIRED)
find_package(Libssh2 CONFIG REQUIRED)

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

#**************************************************************************************************
# Include *****************************************************************************************
include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


#**************************************************************************************************
# Set variable ************************************************************************************
SET(EXAMPLES
    status
)

#**************************************************************************************************
# Set compiler ************************************************************************************
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O3 -fPIC")

#**************************************************************************************************
# Linker ******************************************************************************************


#**************************************************************************************************
# Make configuration
# **************************************************************************************************
foreach(example ${EXAMPLES})
  add_executable("${example}-cpp" examples/${example}.cpp)
  target_link_libraries("${example}-cpp" ${LIGBGIT2_LIBRARY} ${OPENSSL_LIBRARY} ${CRYPTO_LIBRARY} ZLIB::ZLIB -lgit2 Libssh2::libssh2 -lstdc++fs -pthread)
endforeach(example)
