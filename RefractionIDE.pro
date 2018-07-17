#-------------------------------------------------
#
# Project created by QtCreator 2018-07-15T12:55:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RefractionIDE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# Application icon. Affects only Mac OS X
ICON = assets/logo.jpg

INCLUDEPATH += \
        source \
        source/Common \
        source/CodeSegment \
        source/Results \

SOURCES += \
    source/CodeSegment/CodeEditor.cpp \
    source/CodeSegment/LineNumberArea.cpp \
    source/CodeSegment/SyntaxHighlighter.cpp \
    source/Common/Common.cpp \
    source/Results/ResultsDockWidget.cpp \
    source/Results/StandardInputOutputInspector.cpp \
    source/main.cpp \
    source/MainWindow.cpp \
    source/RefractionIDE.cpp \
    source/CodeSegment/CodeSegment.cpp


HEADERS += \
    source/CodeSegment/CodeEditor.h \
    source/CodeSegment/LineNumberArea.h \
    source/CodeSegment/SyntaxHighlighter.h \
    source/Common/Common.h \
    source/Results/ResultsDockWidget.h \
    source/Results/StandardInputOutputInspector.h \
    source/MainWindow.h \
    source/RefractionIDE.h \
    source/CodeSegment/CodeSegment.h




