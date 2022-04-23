cmake_minimum_required(VERSION 3.10)

project(Test)

set (SERVER_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/server_main.c)
set (CLIENT_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/client_main.c)
set (UTILITIES ${CMAKE_CURRENT_SOURCE_DIR}/src/utilites.c)


set ( INCLUDE_DIRS
      ${CMAKE_SOURCE_DIR}/include/
      ${CMAKE_SOURCE_DIR}/dep/networking/
    )

add_subdirectory(dep)
add_compile_options("-g")
add_executable(server_main ${SERVER_SOURCE} ${UTILITIES})
target_include_directories(server_main PUBLIC ${INCLUDE_DIRS})
target_link_libraries(server_main networking_shared)

add_executable(client_main ${CLIENT_SOURCE} ${UTILITIES})
target_include_directories(client_main PUBLIC ${INCLUDE_DIRS})
target_link_libraries(client_main networking_shared)