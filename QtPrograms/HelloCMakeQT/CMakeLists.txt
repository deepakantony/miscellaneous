project(hello_world_cmake)
find_package(qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
add_executable(hello_world_cmake hello_world.cpp)
target_link_libraries(hello_world_cmake ${QT_LIBRARIES})
