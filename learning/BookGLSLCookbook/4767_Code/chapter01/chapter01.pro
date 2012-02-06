
GLM_INCLUDE_PATH = "C:/OpenGL/include"
GLEW_INCLUDE_PATH = "C:/OpenGL/include"
GLEW_LIB_PATH = "C:/OpenGL/lib"

QT       += opengl
CONFIG   += console

TARGET = chapter01

win32 {
    CONFIG   -= app_bundle
    LIBS += -L$$GLEW_LIB_PATH -lglew32
}

TEMPLATE = app

INCLUDEPATH += $$GLM_INCLUDE_PATH $$GLEW_INCLUDE_PATH

SOURCES += main.cpp \
    mainview.cpp \
    glutils.cpp \
    scenebasic.cpp \
    scenebasic_layout.cpp \
    scenebasic_uniform.cpp \
    scenebasic_uniformblock.cpp \
    glslprogram.cpp

HEADERS += \
    mainview.h \
    glutils.h \
    scene.h \
    scenebasic.h \
    scenebasic_layout.h \
    scenebasic_uniform.h \
    scenebasic_uniformblock.h \
    glslprogram.h
