cmake_minimum_required(VERSION 3.25)
project(env_parser VERSION 1.0 LANGUAGES C)
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EXECUTABLE main)
add_executable(${EXECUTABLE})

target_include_directories(${EXECUTABLE} PUBLIC ${INCLUDE_DIR})
target_sources(${EXECUTABLE} PUBLIC ${SOURCE_DIRECTORY}/${EXECUTABLE}.c)
add_library(env_parser SHARED
  ${SOURCE_DIRECTORY}/io.c
  ${SOURCE_DIRECTORY}/env.c
  ${SOURCE_DIRECTORY}/token.c
  ${SOURCE_DIRECTORY}/lexer.c
  ${SOURCE_DIRECTORY}/parser.c
  ${SOURCE_DIRECTORY}/api.c
)

target_include_directories(env_parser PRIVATE ${INCLUDE_DIR})
set_target_properties(env_parser PROPERTIES VERSION ${PROJECT_VERSION} LIBRARY_OUTPUT_DIRECTORY lib)
set_target_properties(env_parser PROPERTIES PUBLIC_HEADER include/api.h)
target_link_libraries(${EXECUTABLE} env_parser)
