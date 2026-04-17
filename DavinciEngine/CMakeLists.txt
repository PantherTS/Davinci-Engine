cmake_minimum_required(VERSION 3.20)

project(DavinciEngine)

set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

# -------------------------
# Dependencies FIRST
# -------------------------

include(FetchContent)

# -------------------------
# SDL3
# -------------------------
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL_TESTS OFF CACHE BOOL "" FORCE)

if (NOT TARGET SDL3::SDL3)
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.4
    )
    FetchContent_MakeAvailable(SDL3)
endif()

# -------------------------
# tinyxml2
# -------------------------
set(tinyxml2_BUILD_TESTING OFF CACHE BOOL "" FORCE)

if (NOT TARGET tinyxml2)
    FetchContent_Declare(
        tinyxml2
        GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
        GIT_TAG 11.0.0
    )
    FetchContent_MakeAvailable(tinyxml2)
endif()

# -------------------------
# stb
# -------------------------
if (NOT TARGET stb)
    FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(stb)
endif()

# -------------------------
# LUA
# -------------------------
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(LUA_BUILD_BINARY OFF CACHE BOOL "" FORCE)

if (NOT TARGET lua)
    FetchContent_Declare(
        lua
        GIT_REPOSITORY https://github.com/walterschell/Lua.git
        GIT_TAG v5.4.7
    )
    FetchContent_MakeAvailable(lua)
endif()

# -------------------------
# sol2 (Lua binding)
# -------------------------
if (NOT TARGET sol2)
    FetchContent_Declare(
        sol2
        GIT_REPOSITORY https://github.com/ThePhD/sol2.git
        GIT_TAG v3.5.0
    )

    FetchContent_MakeAvailable(sol2)
endif()

# -------------------------
# GLM
# -------------------------
if (NOT TARGET glm)
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3
    )
    FetchContent_MakeAvailable(glm)
endif()

# -------------------------
# Engine Source
# -------------------------

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS
    include/*.h
)

add_library(DavinciEngine SHARED
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

target_compile_definitions(DavinciEngine PRIVATE DAVINCIENGINE_EXPORTS)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

file(GLOB_RECURSE THIRDPARTY_SOURCES
    thirdparty/*.cpp
    thirdparty/*.c
)

add_library(glad STATIC ${THIRDPARTY_SOURCES})

# -------------------------
# Includes
# -------------------------

target_include_directories(DavinciEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${stb_SOURCE_DIR}
    ${sol2_SOURCE_DIR}/include
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include
)

# -------------------------
# Linking
# -------------------------

target_link_libraries(DavinciEngine PUBLIC
    SDL3::SDL3
    tinyxml2
    glm
    glad
    lua_static
    sol2
)