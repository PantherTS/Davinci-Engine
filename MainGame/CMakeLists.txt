project(MainGame)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(MainGame ${GAME_SOURCES})

target_include_directories(MainGame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(MainGame PRIVATE DavinciEngine)

add_custom_command(TARGET MainGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:DavinciEngine>
        $<TARGET_FILE_DIR:MainGame>/$<TARGET_FILE_NAME:DavinciEngine>
)

add_custom_command(TARGET MainGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:MainGame>/$<TARGET_FILE_NAME:SDL3::SDL3>
)

add_custom_command(TARGET MainGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/MainGame/assets
        $<TARGET_FILE_DIR:MainGame>/assets
)

add_custom_command(TARGET MainGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/MainGame/scripts
        $<TARGET_FILE_DIR:MainGame>/scripts
)