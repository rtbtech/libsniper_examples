include_directories(.)
include_directories(${SNIPER_INCLUDE_DIRS})

set(PROJECT_LIBS
        ${CMAKE_THREAD_LIBS_INIT}
        ${LIBEV_LIBRARY}
        ${BOOST_LIBRARIES}
        dl ${LIBRE2_LIBRARY}
        backtrace dl
        fmt::fmt
        stdc++fs.a
        tcmalloc
        )

add_subdirectory(hello_server)


