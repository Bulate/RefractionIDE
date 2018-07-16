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

INCLUDEPATH += \
	source \
	source/compiler \

SOURCES += \
    source/main.cpp \
    source/MainWindow.cpp \
    source/RefractionIDE.cpp \
    source/CodeEditor.cpp \
        source/Compiler/Compiler.cpp \
        source/Compiler/CompilerCall.cpp \
        source/Compiler/CompilerDiagnostic.cpp \
        source/Compiler/Diagnostic.cpp \
        source/Compiler/LinkerCall.cpp \
        source/Compiler/LinkerDiagnostic.cpp \

HEADERS += \
    source/MainWindow.h \
    source/RefractionIDE.h \
    source/CodeEditor.h \
    source/Compiler/Compiler.h \
	source/Compiler/CompilerCall.h \
	source/Compiler/CompilerDiagnostic.h \
	source/Compiler/Diagnostic.h \
	source/Compiler/LinkerCall.h \
	source/Compiler/LinkerDiagnostic.h \
