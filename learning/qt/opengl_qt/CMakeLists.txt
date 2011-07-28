project(opengl_qt)

find_package (Qt4 REQUIRED)
find_package (OPENGL REQUIRED)

#set(QT_USE_QTMAIN TRUE)
#set(QT_USE_QTCORE TRUE)
set(QT_USE_QTOPENGL TRUE)
#set(QT_WRAP_CPP TRUE)
#set(QT_USE_QTGUI TRUE)

include ( ${QT_USE_FILE} )

#set(MOCHEADER RotatingCubeWidget.h)
#QT4_WRAP_CPP(MOCFILES ${MOCHEADER})

#include_directories (
#		    ${QT_INCLUDE}
#		    ${QT_INCLUDE_DIR}
#		    ${QT_QTCORE_INCLUDE_DIR}
#		    ${QT_QTGUI_INCLUDE_DIR}
#		    ${QT_QTOPENGL_INCLUDE_DIR}
#)

#link_directories (
#		 ${QT_LIBRARIES}
#		 ${QT_LIBRARY_DIR}
#		 ${QT_MAIN_LIBRARY}
#		 ${QT_QTCORE_LIBRARY}
#		 ${QT_QTGUI_LIBRARY}
#		 ${QT_QTOPENGL_LIBRARY}
#)

#add_definitions(${QT_DEFINITIONS})

add_executable(rotating_cube rotating_cube.cpp RotatingCubeWidget.cpp ${MOCFILES})
target_link_libraries(rotating_cube ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
