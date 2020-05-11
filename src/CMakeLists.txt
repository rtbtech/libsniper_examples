include_directories(.)
include_directories(${SNIPER_INCLUDE_DIRS})

set(PROJECT_LIBS
        ${CMAKE_THREAD_LIBS_INIT}
        ${BOOST_LIBRARIES}
        backtrace dl
        stdc++fs.a
        tcmalloc
        )

add_subdirectory(hello_server)


