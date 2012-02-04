cmake_minimum_required(VERSION 2.8)

project(HelloQuad)

find_package(Qt4 REQUIRED)
find_package(OPENGL REQUIRED)

set(QT_USE_QTOPENGL TRUE)
set(QT_WRAP_CPP TRUE)

include ( ${QT_USE_FILE} )

set(MOCHEADER 
QT4_WRAP_CPP(MOCFILES ${MOCHEADER})

add_definitions( HelloQuad
HelloQuad.cpp
${MOCFILES}
)

target_link_libraries( HelloQuad
${QT_LIBRARIES}
${OPENGL_LIBRARIES}
)					   
