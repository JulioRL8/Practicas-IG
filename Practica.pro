#-------------------------------------------------
#
# Project created by QtCreator 2018-10-05T19:44:11
#
#-------------------------------------------------

QT       -= gui

@CONFIG += debug

QMAKE_LFLAGS += -g@

TARGET = practica2
TEMPLATE = lib

DEFINES += PRACTICA_LIBRARY

SOURCES += \
    axis.cpp \
    cube.cpp \
    PLY.cc \
    object3d.cc \
    practica1.cc \
    revolucion.cc \
    tetrahedron.cc \
    file_ply_stl.cc \
    basic_object3d.cpp \
    cilindro.cpp \
    cono.cpp \
    esfera.cpp \
    extrusion.cpp \
    mesh.cpp \
    transformation.cpp \
    grua.cpp \
    light.cpp \
    tablero.cpp \
    textura.cc

HEADERS +=\
    axis.h \
    cube.h \
    PLY.h \
    object3d.h \
    revolucion.h \
    tetrahedron.h \
    vertex.h \
    file_ply_stl.h \
    basic_object3d.h \
    colors.h \
    cilindro.h \
    cono.h \
    esfera.h \
    extrusion.h \
    mesh.h \
    modelview.h \
    transtype.h \
    transformation.h \
    grua.h \
    light.h \
    tablero.h \
    textura.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    Makefile
