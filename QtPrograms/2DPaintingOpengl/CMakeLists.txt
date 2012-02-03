cmake_minimum_required (VERSION 2.8)

project (2DPaintingOpenGL)

find_package (Qt4 REQUIRED)
find_package (OPENGL REQUIRED)

set (QT_USE_QTOPENGL TRUE)
set (QT_WRAP_CPP TRUE)

include ( ${QT_USE_FILE} )

set (MOCHEADER ${2DPaintingOpenGL_HEADERS})
QT4_WRAP_CPP (MOCFILES ${MOCHEADER})

add_executable(2DPaintingOpenGL
		${MOCFILES}
)

target_link_libraries(2DPaintingOpenGL
		${QT_LIBRARIES}
		${OPENGL_LIBRARIES}
)
