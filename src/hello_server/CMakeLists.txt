include_directories(.)

add_executable(hello_server main.cpp Server.h Server.cpp)
target_link_libraries(hello_server ${SNIPER_LIBRARIES} ${PROJECT_LIBS})
