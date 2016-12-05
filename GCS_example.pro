#-------------------------------------------------
#
# Project created by QtCreator 2016-08-25T11:00:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GCS_example
TEMPLATE = app


SOURCES += main.cpp\
        quad_sim.cpp \
    uavitem.cpp \
    aoi.cpp \
    threat.cpp

HEADERS  += quad_sim.h \
    uavitem.h \
    aoi.h \
    threat.h

FORMS    += quad_sim.ui

RESOURCES += \
    gcs_example.qrc
