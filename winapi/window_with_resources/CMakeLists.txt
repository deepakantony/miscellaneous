cmake_minimum_required(VERSION 2.8)
project( simple_window )

set( SOURCES simple_window_exe.rc resource.h ${SOURCES} )
add_executable( simple_window_exe WIN32 simple_window.cxx ${SOURCES} )

