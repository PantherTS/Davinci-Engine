cmake_minimum_required(VERSION 3.20)

project(TheGame)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(RUNTIME_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/out/runtime)

add_subdirectory(DavinciEngine)
add_subdirectory(MainGame)

file(MAKE_DIRECTORY
    ${RUNTIME_OUTPUT_DIR}/assets
    ${RUNTIME_OUTPUT_DIR}/assets/shaders
    ${RUNTIME_OUTPUT_DIR}/scripts
)

set(RUNTIME_DIR ${CMAKE_SOURCE_DIR}/out/runtime)

set_target_properties(MainGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_DIR}
)

set_target_properties(DavinciEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_DIR}
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MainGame)