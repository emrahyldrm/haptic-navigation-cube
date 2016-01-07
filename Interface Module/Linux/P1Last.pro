#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = P1Last
TEMPLATE = app


# omp_get_thread_num() and omp_get_num_threads() fuctions

QMAKE_LFLAGS += -fopenmp
QMAKE_CXXFLAGS += -openmp
LIBS += -fopenmp
#-------------------


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    bilmuh.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    bilmuh.h \
    server.h \
    workerthread.h \
    dialogthread.h

FORMS    += mainwindow.ui \
    dialog.ui \
    bilmuh.ui

DISTFILES += \
    InterfaceConnectionForm.ui.qml \
    InterfaceConnection.qml
