#-------------------------------------------------
#
# Project created by QtCreator 2018-01-25T01:17:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImgEsgeSelechen
TEMPLATE = app

CONFIG +=c++14-j4

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    imgprc.cpp \
    geometry0.cpp \
    Base/imgbase.cpp \
    Base/imgdata.cpp

HEADERS += \
        mainwindow.h \
    imgprc.h \
    geometry0.h \
    Base/imgbase.h \
    Base/imgdata.h

FORMS += \
        mainwindow.ui



INCLUDEPATH += C:\opencv\build\include

LIBS += C:\opencv_build\bin\libopencv_core331.dll
LIBS += C:\opencv_build\bin\libopencv_highgui331.dll
LIBS += C:\opencv_build\bin\libopencv_imgcodecs331.dll
LIBS += C:\opencv_build\bin\libopencv_imgproc331.dll
LIBS += C:\opencv_build\bin\libopencv_features2d331.dll
LIBS += C:\opencv_build\bin\libopencv_calib3d331.dll
LIBS += C:\opencv_build\bin\libopencv_dnn331.dll
LIBS += C:\opencv_build\bin\libopencv_flann331.dll
LIBS += C:\opencv_build\bin\libopencv_ml331.dll
LIBS += C:\opencv_build\bin\libopencv_objdetect331.dll
LIBS += C:\opencv_build\bin\libopencv_photo331.dll
LIBS += C:\opencv_build\bin\libopencv_shape331.dll
LIBS += C:\opencv_build\bin\libopencv_stitching331.dll
LIBS += C:\opencv_build\bin\libopencv_superres331.dll
LIBS += C:\opencv_build\bin\libopencv_video331.dll
LIBS += C:\opencv_build\bin\libopencv_videoio331.dll
LIBS += C:\opencv_build\bin\libopencv_videostab331.dll
