cmake_minimum_required(VERSION 3.20)

add_compile_options(-g -Wall)

project(physica)


file(GLOB PUBLIC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB physica_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)


# add_executable(physica_e ${physica_sources})

list(FILTER physica_ources EXCLUDE REGEX "main.c")

add_library(physica SHARED ${physica_sources})
add_library(physica_static STATIC ${physica_sources})

target_compile_options(physica PUBLIC -fPIC)
target_compile_options(physica_static PUBLIC -fPIC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(
  physica
    PUBLIC
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      ${CMAKE_CURRENT_BINARY_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_include_directories(
  physica_static
    PUBLIC
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      ${CMAKE_CURRENT_BINARY_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/include)


#target_include_directories(
#  physica_e
#    PUBLIC
#      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
#      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#      ${CMAKE_CURRENT_BINARY_DIR}/include
#      ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(FetchContent)

FetchContent_Declare(
        vec_static
        URL /home/ianertson/workspace/vec
        )

if (NOT TARGET vec_static)
  FetchContent_MakeAvailable(vec_static)
endif()


target_link_libraries(physica PUBLIC vec_static)
# target_link_libraries(physica_e PUBLIC vec_static)
target_link_libraries(physica_static PUBLIC vec_static)
