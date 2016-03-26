cmake_minimum_required (VERSION 2.8)
if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif()

if(POLICY CMP0017)
  cmake_policy(SET CMP0017 NEW)
endif()

project (gredis)

# Flags and Options
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules")
set(CMAKE_PROJECT_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_PROJECT_MODULE_PATH}")

## include thirdparty in pkgconfig
if (CMAKE_VERSION LESS 3.1.0)
set( ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${PROJECT_SOURCE_DIR}/thirdparty/lib/pkgconfig" )
else()
set( ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${PROJECT_SOURCE_DIR}/thirdparty/lib/pkgconfig" )
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/src)

# check thirdparty packages
find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)
find_package(Hiredis REQUIRED)

# include thirdparty includes
include_directories(${HIREDIS_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})

## include thirdparty libs
set(GREDIS_LIB_DEPS
    ${GRPC_LIBRARIES}
    ${HIREDIS_LIBRARIES}
    ${Protobuf_LIBRARIES}
)


set(CMAKE_OSX_ARCHITECTURES x86_64)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory(src)
