project(opengl_qt)

find_package (Qt4 REQUIRED)
find_package (OPENGL REQUIRED)

set(QT_USE_QTOPENGL TRUE)
set(QT_WRAP_CPP TRUE)

include ( ${QT_USE_FILE} )

set(MOCHEADER RotatingCubeWidget.h)
QT4_WRAP_CPP(MOCFILES ${MOCHEADER})

#add_definitions(${QT_DEFINITIONS})

add_executable(rotating_cube 
rotating_cube.cpp 
RotatingCubeWidget.cpp 
cube.h
${MOCFILES}
)
target_link_libraries(rotating_cube 
${QT_LIBRARIES} 
${OPENGL_LIBRARIES}
)
